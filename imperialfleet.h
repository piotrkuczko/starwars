#ifndef IMPERIALFLEET_H
#define IMPERIALFLEET_H

#include <typeinfo>

template <typename U>
class ImperialStarship {
private:

    U shield, attackPower;

public:

    explicit ImperialStarship(U shield, U attackPower) {
        this->shield = shield;
        this->attackPower = attackPower;
    }

    using valueType = U;

    //getter for member shield
    U getShield() {
        return shield;
    }

    //function which changes shield durability by damage value
    void takeDamage(U damage) {
        if (shield >= damage)
            shield -= damage;
        else
            //if damage value is greater than remaining shield, shield durability changes to 0
            shield = 0;
    }

    //getter for member attackPower
    U getAttackPower() {
        return attackPower;
    }

    //function that return false, when ship does not belong to rebel's side
    static constexpr bool isRebel(){
        return false;
    }
};


//specializations of class RebelStarship
template <typename U>
using DeathStar = ImperialStarship<U>;

template <typename U>
using ImperialDestroyer = ImperialStarship<U>;

template <typename U>
using TIEFighter = ImperialStarship<U>;


//function that allows to carry out an attack by imperial's ship on rebel's ship
template <typename I, typename R>
void attack(I &imperialShip, R &rebelShip) {
    static_assert(!I::isRebel(), "First isn't imperialShip");
    static_assert(R::isRebel(), "Secont isn't rebelShip");
    rebelShip.takeDamage(imperialShip.getAttackPower());

    //if rebel's ship is not an Explorer it fights back
    if constexpr (!R::isExplorer())
        imperialShip.takeDamage(rebelShip.getAttackPower());
}

#endif //IMPERIALFLEET_H
