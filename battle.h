#ifndef PROJECT_BATTLE_H
#define PROJECT_BATTLE_H

#include <iostream>
#include <limits>
#include <tuple>
#include <cassert>

#include <cmath>
#include <array>
#include <vector>
#include <algorithm>
#include "rebelfleet.h"
#include "imperialfleet.h"

#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>

using namespace std;



template <typename T, T t0, T t1, typename ... S> class SpaceBattle {
    //liczenie kwadratow czasu dziala na 99%
    static constexpr size_t countTimes(){
        size_t i = 1;
        while(i*i <= t1)
            i++;
        return i;
    }

    //auto zmienna;

    std::array<T, countTimes()> set_attack_times(){
        std::array<T, countTimes()> attackTimes;
        size_t index = 0;
        for(size_t i = 0; i*i<=t1; i++){
            attackTimes[index] = i*i;
            index++;
        }
        return attackTimes;
    }

    std::array<T, countTimes()> attackTimes = set_attack_times();

    std::tuple<S...> starShips;
    size_t allShips = 0;
    size_t rebelsFleet; // liczba zyjacych statkow rebelii
    size_t imperialsFleet; // liczba zyjacych statkow imperium
    T currentTime;

    // zliczanie statkow rebelii na poczatku bitwy dziala na 99%
    template <typename Q>
    void countEachFraction(Q ship){
        //std::cout << "to pierwsze " << std::endl;
        allShips++;
        if (ship.isRebel()) {
            if (ship.getShield() > 0)
                rebelsFleet++;
        } else {
            if (ship.getShield() > 0)
                imperialsFleet++;
        }
    }

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
    /*template <typename I, typename Q, typename ... R>
    void iterateAndAttack (I imper, Q ship, R... ships){
        if (ship.isRebel())
            attack(imper, ship);
        iterateAndAttack(imper, ships);
    };
    template <typename I, typename Q>
    void iterateAndAttack (I imper, Q ship){
        if (ship.isRebel())
            attack(imper, ship);
    };*/
    /*template <typename Q>
    void iterateByImper(Q shiclang -wall -Wextra -std=c++17 -O2 -ls
p){
        if (!ship.isRebel())
            //iterateAndAttack(ship, starShips);
            std::cout << "atakuj single" << std::endl;
    };

    template <typename Q, typename ... R>
    void iterateByImper(Q ship, R... ships){
        if (!ship.isRebel())
            std::cout << "atakuj" << std::endl;
            //iterateAndAttack(ship, starShips);
        iterateByImper(ships...);
    };*/



    /*template <typename Q, typename Lam, typename beginType>
    std::tuple<beginType> fold(Q ship, Lam&& lambda, beginType begin){
        return lambda (ship, begin);
    }

    template <typename Q, typename ... R, typename Lam, typename beginType>
    std::tuple<beginType> fold(Q ship, R... ships, Lam&& lambda, beginType begin){
        return lambda (ship, fold(ships..., lambda), begin);
    }*/

    /*template <typename Q, typename I>
    void funkcja2 (I imperial, Q ship) {
        if (ship.isRebel()) {
            attack(imperial, ship);
        }
    }

    template <typename Q>
    void funkcja1 (Q ship, void()) {
        if (!ship.isRebel()) {
            fold(starShips, funkcja2(), ship);
        }
    }*/

    /*void atatc<0> () {
        if (get<0>(starShips).isRebel()) {
            cout << "is Rebel" << endl;
        }
    }

    template <typename a>
    void atatc<a>()  {
        if (get<0>(starShips).isRebel()) {
            cout << "is Rebel" << endl;
        }
        atatc<a-1>();
    }*/

    template <typename U, size_t numElem = 0>
    void rebeliantAttack(ImperialStarship<U> &imperialShip) {

    std::tuple_element_t<numElem, decltype(starShips)> &rebelShip = std::get<numElem>(starShips);

    if constexpr (std::tuple_element_t<numElem, decltype(starShips)>::isRebel()) {
        if (imperialShip.getShield() > 0 && rebelShip.getShield() > 0) {
            attack(imperialShip, rebelShip);

            if (imperialShip.getShield() == 0)
            imperialsFleet--;

            if (rebelShip.getShield() == 0)
            rebelsFleet--;
        }
    }

    const size_t newIndex = numElem+1;

    if constexpr (newIndex < std::tuple_size<decltype(starShips)>::value)
        rebeliantAttack<U, newIndex>(imperialShip);
}


    //walka dziala na 0%
    template <size_t numElem = 0>
    void imperialsAttack(){
        std::tuple_element_t<numElem, decltype(starShips)> &imperialShip = std::get<numElem>(starShips);
        if constexpr (!std::tuple_element_t<numElem, decltype(starShips)>::isRebel()) {
            if (imperialShip.getShield() > 0) {
                rebeliantAttack(imperialShip);
            }
        }

    const size_t newIndex = numElem+1;

    if constexpr (newIndex < std::tuple_size<decltype(starShips)>::value) {
        imperialsAttack<newIndex>();
    }

        /* dla każdego statku Imperium
  dla każdego statku Rebelii
    jeśli oba statki nie nie zostały jeszcze zniszczone,
      statek Imperium atakuje statek Rebelii. */

    }

    // wypisywanie wynikow dziala na 60%
    void battle_result(){
        if(countImperialFleet() == 0){
            if(countRebelFleet() == 0)
                std::cout << "DRAW\n";
            else
                std::cout << "REBELLION WON\n";
        } else {
            std::cout << "IMPERIUM WON\n";
        }
    }

public:
    explicit SpaceBattle(S... ships) : starShips(std::tuple<S...>(ships...)) {
        static_assert(t0 <= std::numeric_limits<T>::max() &&
                      t0 >= 0, "Starting time is not in range of given type");
        static_assert(t1 <= std::numeric_limits<T>::max() &&
                      t1 >= 0, "Ending time is not in range of given type");
        static_assert(t0 <= t1, "Ending must take place after the start of battle");

        currentTime = t0;
        rebelsFleet = 0;
        imperialsFleet = 0;
        countEachFraction(ships...);
        //zmienna = ships;

        //imperialsFleet = std::tuple_size<decltype(starShips)>::value - rebelsFleet;

    }

    size_t countImperialFleet(){
        return imperialsFleet;
    }

    size_t countRebelFleet(){
        return rebelsFleet;
    }

    //brakuje imperialsAttack wiec nie dziala
    void tick(T timestep){
        if(countRebelFleet() > 0 && countImperialFleet() > 0){
            if(std::find(attackTimes.begin(), attackTimes.end(), currentTime) != attackTimes.end()) {
                imperialsAttack();
            }
        } else {
            battle_result();
        }
        //tu nie jestem pewna co sie stanie jak timestep wykroczy poza limit T
        currentTime += timestep;
        if(currentTime >= t1) currentTime = currentTime%t1;
    }

};

#endif //PROJECT_BATTLE_H
//clang -Wall -Wextra -std=c++17 -O2 -lstdc++ starwars_example.cc -o starwars
