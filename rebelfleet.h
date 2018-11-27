#ifndef PROJECT_REBELFLEET_H
#define PROJECT_REBELFLEET_H


#include <cassert>


template <typename U> class RebelStarship {
protected:

    U shield, speed, attackPower;
    virtual void check() = 0;
    explicit RebelStarship() {}
    /*
    TODO:
     Klasy Explorer, StarCruiser i XWing mają publiczną składową valueType
    reprezentującą typ U, którym zostały sparametryzowane.
    */

public:
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
    U getAttackPower() {
        return attackPower;
    }
};

template <typename U> class Explorer : public RebelStarship<U> {
private:
    using RebelStarship<U>::getAttackPower;
protected:
    void check () {
        assert(299796 <= this->speed && this->speed <= 2997960);
    }
public:
    Explorer (U shield, U speed) {
        this->shield=shield;
        this->speed=speed;
        check();
    }
};

template <typename U> class StarCruiser : public RebelStarship<U> {
    void check () {
        assert (99999 <= this->speed && this->speed <= 299795);
    }

public:
    StarCruiser (U shield, U speed, U attackPower) {
        this->shield=shield;
        this->speed=speed;
        this->attackPower=attackPower;
        check();
    }
};

template <typename U> class XWing : public RebelStarship<U> {
    void check () {
        assert(299796 <= this->speed && this->speed <= 2997960);
    }

public:
    XWing (U shield, U speed, U attackPower) {
        this->shield=shield;
        this->speed=speed;
        this->attackPower=attackPower;

    }
};

#endif //PROJECT_REBELFLEET_H
