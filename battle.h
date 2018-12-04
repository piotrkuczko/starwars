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
    void countRebels(Q ship){
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
    void countRebels(Q ship, R... ships){
        //std::cout << "to duze " << std::endl;
        allShips++;
        if (ship.isRebel()) {
            if (ship.getShield() > 0)
                rebelsFleet++;
        } else {
            if (ship.getShield() > 0)
                imperialsFleet++;
        }
        countRebels(ships...);
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
    template <typename Q>
    void iterateByImper(Q ship){
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
    };



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




    //walka dziala na 0%
    void imperialsAttack(){
        if constexpr (1==2) {
            cout << "2";
        }
        /*template <typename Tt, Tt t0t, Tt t1t, typename ... St> class Wykonaj {
        public:
            Wykonaj(St... ships) {
                iterateByImper(ships...);
            }
        };

        Wykonaj a = Wykonaj(starShips);*/

        /*for (int i=0; i<allShips; i++) {
            if (get<starShips+i>(starShips).isRebel())
                cout << "is Rebel" << endl;
            else cout << "notRebel" << endl;
        }*/

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
        countRebels(ships...);
        //zmienna = ships;
        imperialsFleet = 0;
        imperialsFleet = std::tuple_size<decltype(starShips)>::value - rebelsFleet;

    }

    size_t countImperialFleet(){
        return imperialsFleet;
    }

    size_t countRebelFleet(){
        return rebelsFleet;
    }

    //brakuje imperialsAttack wiec nie dziala
    void tick(T timestep){
        if(std::find(attackTimes.begin(), attackTimes.end(), currentTime) != attackTimes.end()) {
            if (countRebelFleet() > 0 && countImperialFleet() > 0) {
                imperialsAttack();
            } else {
                battle_result();
            }
        }
        //tu nie jestem pewna co sie stanie jak timestep wykroczy poza limit T
        currentTime += timestep;
        if(currentTime > t1) currentTime = currentTime-t1;
    }
};

#endif //PROJECT_BATTLE_H