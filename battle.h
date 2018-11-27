#ifndef PROJECT_BATTLE_H
#define PROJECT_BATTLE_H

#include <iostream>
#include <limits>
#include <queue>
#include <cassert>
#include <any>
#include <cmath>
#include "rebelfleet.h"
#include "imperialfleet.h"

template <typename T, T t0, T t1, typename ... S> class SpaceBattle {
private:
    std::vector<std::any> rebelShips;
    std::vector<std::any> imperialShips;
    T currentTime;
    std::vector<T> attacks;

    constexpr void set_attack_time(){
        size_t time = 1;
        for(size_t i = t0; i <= t1; i++){
            time = sqrt(i);
            if(time*time == i){
                attacks.emplace_back(i);
            }
        }
    }

    template <template <class> class U, class Q>
    void add_ships(U<Q> ship) {

        if (dynamic_cast<RebelStarship<Q> *>(&ship))
            rebelShips.push_back(ship);
        else
            imperialShips.push_back(ship);
    }

    template <template <class> class U, class Q, typename ... R>
    void add_ships(U<Q> ship, R ... ships){
        if (dynamic_cast<RebelStarship<Q> *>(&ship))
            rebelShips.push_back(ship);
        else
            imperialShips.push_back(ship);
        add_ships(ships...);
    }

    void rebel_attack(){
        auto imperialIter = imperialShips.begin();
        while (imperialIter != imperialShips.end()){
            auto rebelIter = rebelShips.begin();
            while (rebelIter != rebelShips.end()){
                attack(*imperialIter, *rebelIter);
                rebelIter++;
            }
            imperialIter++;
        }
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
    explicit SpaceBattle(S ... ships){
        static_assert(t0 <= std::numeric_limits<T>::max() &&
                      t0 >= std::numeric_limits<T>::min(), "Starting time is not in range of given type");
        static_assert(t1 <= std::numeric_limits<T>::max() &&
                      t1 >= std::numeric_limits<T>::min(), "Ending time is not in range of given type");
        static_assert(t0 <= t1, "Ending must take place after the start of battle");

        set_attack_time();
        currentTime = t0;

        add_ships(ships...);

    }

    size_t countImperialFleet(){
        return imperialShips.size();
    }

    size_t countRebelFleet(){
        return rebelShips.size();
    }

    void tick(T timestep){
        if(countRebelFleet()>0 && countImperialFleet()>0){

            auto iter = attacks.begin();
            while (iter != attacks.end() && *iter < currentTime) iter++;
            if(iter != attacks.end() && *iter == currentTime)
                rebel_attack();
            currentTime+=timestep;
        } else {
            battle_result();
        }
    }
};

#endif //PROJECT_BATTLE_H