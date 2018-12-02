#ifndef PROJECT_REBELFLEET_H
#define PROJECT_REBELFLEET_H


#include <cassert>
#include <iostream>

using type_to_speed = int;


template <typename U, bool notexplorer, type_to_speed min_value, type_to_speed max_value>
class RebelStarship {
private:

    U shield, speed, attackPower;

public:

    explicit RebelStarship(U shield, U speed) {
        this->shield = shield;
        this->speed = speed;
        assert(min_value <= speed && speed <= max_value);
    }


    explicit RebelStarship(U shield, U speed, U attackPower) {
        this->shield = shield;
        this->speed = speed;
        this->attackPower = attackPower;
        assert(min_value <= speed && speed <= max_value);
    }

    using valueType = U;

    U getShield() {
        return shield;
    }
    U getSpeed() {
        return speed;
    }
    void takeDamage(U damage) {
        if (shield >= damage)
            shield -= damage;
        else
            shield = 0;
    }

//    U getAttackPower() {
//        if (!notexplorer) throw "explorer";
//        return attackPower;
//    }

    /*template <bool checker = notexplorer, typename = typename std::enable_if<checker, U>::type>*/// U getAttackPower();


    template<bool condition = notexplorer>
    typename std::enable_if<condition, U>::type getAttackPower() {
        return attackPower;
    }

    bool isRebel(){
        return true;
    }

};


template <typename U>
using Explorer = RebelStarship<U, false, 299796, 2997960>;

template <typename U>
using StarCruiser = RebelStarship<U, true, 99999, 299795>;

template <typename U>
using XWing = RebelStarship<U, true, 299796, 2997960>;


#endif //PROJECT_REBELFLEET_H
