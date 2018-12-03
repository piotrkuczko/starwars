#ifndef PROJECT_BATTLE_H
#define PROJECT_BATTLE_H

#include <iostream>
#include <limits>
#include <tuple>
#include <cassert>
#include <cmath>
#include <array>
#include <algorithm>
#include "rebelfleet.h"
#include "imperialfleet.h"

template <typename T, T t0, T t1, typename ... S> class SpaceBattle {
    static constexpr size_t countTimes(){
        size_t i = 1;
        while(i*i <= t1)
            i++;
        return i;
    }

    static constexpr std::array<T, countTimes()> set_attack_times(){
        std::array<T, countTimes()> attackTimes;
        size_t index = 0;
        for(size_t i = 0; i*i<=t1; i++){
            attackTimes[index] = i*i;
            index++;
        }
        return attackTimes;
    }

    std::array<T, countTimes()> attackTimes {set_attack_times()};

    std::tuple<S...> starShips;
    size_t rebelsFleet;
    size_t imperialsFleet;
    T currentTime;

    template <typename Q>
    void countRebels(Q ship){
        if(ship.getShield() > 0) {
            if (ship.isRebel())
                rebelsFleet++;
        }
    }

    template <typename Q, typename ... R>
    void countRebels(Q ship, R... ships){
        if(ship.getShield() > 0) {
            if (ship.isRebel())
                rebelsFleet++;
        }
        countRebels(ships...);
    }



    void imperialsAttack(){
        /* dla każdego statku Imperium
  dla każdego statku Rebelii
    jeśli oba statki nie nie zostały jeszcze zniszczone,
      statek Imperium atakuje statek Rebelii. */



    }

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
        imperialsFleet = 0;
        imperialsFleet = std::tuple_size<decltype(starShips)>::value - rebelsFleet;

    }

    size_t countImperialFleet(){
        return imperialsFleet;
    }

    size_t countRebelFleet(){
        return rebelsFleet;
    }

    void tick(T timestep){
        if(std::find(attackTimes.begin(), attackTimes.end(), currentTime) != attackTimes.end()) {
            if (countRebelFleet() > 0 && countImperialFleet() > 0) {
                imperialsAttack();
            } else {
                battle_result();
            }
        }
        currentTime += timestep;
        if(currentTime > t1) currentTime = currentTime-t1;
    }
};

#endif //PROJECT_BATTLE_H