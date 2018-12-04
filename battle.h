#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <limits>
#include <tuple>

#include <array>
#include <algorithm>
#include "rebelfleet.h"
#include "imperialfleet.h"

#include <functional>
#include <type_traits>


template <typename T, T t0, T t1, typename ... S>
class SpaceBattle {
private:

    static_assert(t0 <= std::numeric_limits<T>::max() &&
                  t0 >= 0, "Starting time is not in range of given type");
    static_assert(t1 <= std::numeric_limits<T>::max() &&
                  t1 >= 0, "Ending time is not in range of given type");
    static_assert(t0 <= t1, "Ending must take place after the start of battle");

    //function used for making collection of times when attacks can occur
    static constexpr size_t countTimes(){
        size_t i = 1;
        while(i*i <= t1)
            i++;
        return i;
    }

    //function used for making collection of times when attacks can occur
    std::array<T, countTimes()> set_attack_times(){
        std::array<T, countTimes()> attackTimes;
        size_t index = 0;
        for(size_t i = 0; i*i<=t1; i++){
            attackTimes[index] = i*i;
            index++;
        }
        return attackTimes;
    }

    //collection of times when attacks can occur
    std::array<T, countTimes()> attackTimes = set_attack_times();

    //tuple with all ships, that take part in battle
    std::tuple<S...> starShips;

    //number of all ships, that take part in battle
    size_t allShips = 0;

    //numbers of ships of each fraction, that take part in battle
    size_t rebelsFleet;
    size_t imperialsFleet;

    //current time in counted in interstellar time
    T currentTime;


    //function that counts ships of each fraction
    template <typename Q>
    void countEachFraction(Q ship){
        allShips++;
        if (ship.isRebel()) {
            if (ship.getShield() > 0)
                rebelsFleet++;
        } else {
            if (ship.getShield() > 0)
                imperialsFleet++;
        }
    }

    //function that counts ships of each fraction
    template <typename Q, typename ... R>
    void countEachFraction(Q ship, R... ships){
        //std::cout << "to duze " << std::endl;
        allShips++;
        if (ship.isRebel()) {
            if (ship.getShield() > 0)
                rebelsFleet++;
        } else {
            if (ship.getShield() > 0)
                imperialsFleet++;
        }
        countEachFraction(ships...);
    }

    //function that allows imperialShip to carry out an attack on rebel's ships
    template <typename U, size_t numElem = 0>
    void imperialAttacks(ImperialStarship<U> &imperialShip) {

        std::tuple_element_t<numElem, decltype(starShips)> &rebelShip = std::get<numElem>(starShips);

        if constexpr (std::tuple_element_t<numElem, decltype(starShips)>::isRebel()) {
            if (imperialShip.getShield() > 0 && rebelShip.getShield() > 0) {
                attack(imperialShip, rebelShip);

                if (imperialShip.getShield() == 0)
                    //if after attack imperialShis's shield go down to 0,
                    //then number of undestroyed imperial's ships is decreased by 1
                    imperialsFleet--;

                if (rebelShip.getShield() == 0)
                    //if after attack rebelShis's shield go down to 0,
                    //then number of undestroyed rebel's ships is decreased by 1
                    rebelsFleet--;
            }
        }

        const size_t newIndex = numElem+1;

        if constexpr (newIndex < std::tuple_size<decltype(starShips)>::value)
            imperialAttacks<U, newIndex>(imperialShip);
    }


    //function that for every imperial's ship, that is not destroyed, invokes function imperialAttacks
    template <size_t numElem = 0>
    void battle(){
        std::tuple_element_t<numElem, decltype(starShips)> &imperialShip = std::get<numElem>(starShips);
        if constexpr (!std::tuple_element_t<numElem, decltype(starShips)>::isRebel()) {
            if (imperialShip.getShield() > 0) {
                imperialAttacks(imperialShip);
            }
        }

        const size_t newIndex = numElem+1;

        if constexpr (newIndex < std::tuple_size<decltype(starShips)>::value) {
            battle<newIndex>();
        }
    }

    //function that prints battle result depending on the number of undestroyed ships of each fraction
    void battle_result(){
        if(countImperialFleet() == 0){
            if(countRebelFleet() == 0)
                //if each fraction is destroyed function prints "DRAW\n"
                std::cout << "DRAW\n";
            else
                //if only imperials are destroyed function prints "REBELLION WON\n"
                std::cout << "REBELLION WON\n";
        } else {
            //if only rebels are destroyed function prints "IMPERIUM WON\n"
            std::cout << "IMPERIUM WON\n";
        }
    }

public:

    explicit SpaceBattle(S... ships) : starShips(std::tuple<S...>(ships...)) {
        //setting current time to t0
        currentTime = t0;

        //setting rebels and imperials number of ships to appropriate values
        rebelsFleet = 0;
        imperialsFleet = 0;
        countEachFraction(ships...);
    }

    //getter for number of undestroyed imperial's ship
    size_t countImperialFleet(){
        return imperialsFleet;
    }

    //getter for number of undestroyed rebel's ship
    size_t countRebelFleet(){
        return rebelsFleet;
    }

    //function that simulate moment in fight
    void tick(T timestep){
        if(countRebelFleet() > 0 && countImperialFleet() > 0){
            //if there are 1 or more ship of each fraction undestroyed...
            if(std::find(attackTimes.begin(), attackTimes.end(), currentTime) != attackTimes.end()) {
                //... and it is time when attack can occur, then function battle is invoked
                battle();
            }
        } else {
            //if there is 0 ships of any of fractions, then battle is ended, and function battle_result is invoked
            battle_result();
        }

        //after the battle time is changed by timestep, and if it goes beyond t1,
        //then it loops and start counting from 0
        currentTime += timestep;
        if(currentTime > t1) currentTime = currentTime%(t1 + 1);
    }

};

#endif //BATTLE_H