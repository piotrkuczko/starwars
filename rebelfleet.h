#ifndef REBELFLEET_H
#define REBELFLEET_H

#include <cassert>

using type_to_speed = int;

template <typename U, bool explorer, type_to_speed min_value, type_to_speed max_value>
class RebelStarship {};

template <typename U, int min_value, int max_value>
class RebelStarship <U, false, min_value, max_value> {
private:

    U shield, speed;

public:

    explicit RebelStarship(U shield, U speed) {
        this->shield = shield;
        this->speed = speed;
        //checking if speed is in range between min_value and max_value
        assert(min_value <= speed && speed <= max_value);
    }


    using valueType = U;

    //getter for member shield
    U getShield() {
        return shield;
    }

    //getter for member speed
    U getSpeed() {
        return speed;
    }

    //function which changes shield durability by damage value
    void takeDamage(U damage) {
        if (shield >= damage)
            shield -= damage;
        else
            //if damage value is greater than remaining shield, shield durability changes to 0
            shield = 0;
    }

    //function that return true, when ship belongs to rebel's side
    static constexpr bool isRebel(){
        return true;
    }

    //function that returns true, when ship is of type Explorer
    static constexpr bool isExplorer() {
        return true;
    }

};

template <typename U, int min_value, int max_value>
class RebelStarship <U, true, min_value, max_value>{
private:

    U shield, speed, attackPower;

public:

    explicit RebelStarship(U shield, U speed, U attackPower) {
        this->shield = shield;
        this->speed = speed;
        this->attackPower = attackPower;
        //checking if speed is in range between min_value and max_value
        assert(min_value <= speed && speed <= max_value);
    }

    using valueType = U;

    //getter for member shield
    U getShield() {
        return shield;
    }

    //getter for member speed
    U getSpeed() {
        return speed;
    }

    //function which changes shield durability by damage value
    void takeDamage(U damage) {
        if (shield >= damage)
            shield -= damage;
        else
            shield = 0;
    }

    //getter for member attackPower
    U getAttackPower() {
        return attackPower;
    }

    //function that return true, when ship belongs to rebel's side
    static constexpr bool isRebel(){
        return true;
    }

    //function that returns false, when ship is not of type Explorer
    static constexpr bool isExplorer() {
        return false;
    }

};

//specializations of class RebelStarship
template <typename U>
using Explorer = RebelStarship<U, false, 299796, 2997960>;

template <typename U>
using StarCruiser = RebelStarship<U, true, 99999, 299795>;

template <typename U>
using XWing = RebelStarship<U, true, 299796, 2997960>;


#endif //REBELFLEET_H
