#ifndef PROJECT_BATTLE_H
#define PROJECT_BATTLE_H

#include <iostream>
#include <limits>
#include <tuple>
#include <cassert>
#include <any>
#include <cmath>
#include <set>
#include <vector>
#include "rebelfleet.h"
#include "imperialfleet.h"

template <typename T, T t0, T t1, typename ... S> class SpaceBattle {
private:
    std::vector<std::any> rebels;
    std::vector<std::any> imperials;
    size_t rebelsFleet;
    size_t imperialsFleet;
    T currentTime;
    std::set<T> attacks;

    constexpr void set_attack_time(){
        size_t time = 0;
        for(size_t i = t0; i <= t1; i++){
            time = sqrt(i);
            if(time*time == i){
                attacks.insert(i);
            }
        }
    }

    template <typename Imp, typename Reb>
    void imperial_attacks(Imp imperial, Reb rebel){
/*
        if(imperial.getShield()>0 && rebel.getShield()>0){
            attack(imperial, rebel);
        }
        if(imperial.getShield() == 0)
            imperialsFleet--;
        if(rebel.getShield() == 0)
            rebelsFleet--;
 */
    }

    template <typename Q>
    void add_ships(Q ship){
        if(ship.isRebel())
            rebels.push_back(ship);
        else
            imperials.push_back(ship);
    }

    template <typename Q, typename ... R>
    void add_ships(Q ship, R ... ships){
        if(ship.isRebel())
            rebels.push_back(ship);
        else
            imperials.push_back(ship);
        add_ships(ships...);
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
    explicit SpaceBattle(S... ships) {
        static_assert(t0 <= std::numeric_limits<T>::max() &&
                      t0 >= 0, "Starting time is not in range of given type");
        static_assert(t1 <= std::numeric_limits<T>::max() &&
                      t1 >= 0, "Ending time is not in range of given type");
        static_assert(t0 <= t1, "Ending must take place after the start of battle");

        set_attack_time();
        currentTime = t0;
        add_ships(ships...);
        rebelsFleet = rebels.size();
        imperialsFleet = imperials.size();

    }

    size_t countImperialFleet(){
        return imperialsFleet;
    }

    size_t countRebelFleet(){
        return rebelsFleet;
    }

    void tick(T timestep){
        if(attacks.find(currentTime) != attacks.end()) {
            if (countRebelFleet()> 0 && countImperialFleet() > 0) {
                for(auto Imperial : imperials){
                    for(auto Rebel : rebels){
                        imperial_attacks(Imperial, Rebel);
                    }
                }
            } else {
                battle_result();
            }
        }
        currentTime+=timestep;
        if(currentTime > t1) currentTime = currentTime-t1;
    }
};

#endif //PROJECT_BATTLE_H