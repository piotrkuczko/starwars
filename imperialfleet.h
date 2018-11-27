#ifndef PROJECT_IMPERIALFLEET_H
#define PROJECT_IMPERIALFLEET_H


template <typename U> class ImperialStarship {
protected:
    U shield, attackPower;
    explicit ImperialStarship() {}
    /*
    TODO:
     Klasy Explorer, StarCruiser i XWing mają publiczną składową valueType
    reprezentującą typ U, którym zostały sparametryzowane.
    */

public:
    U getShield() {
        return shield;
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

    virtual ~ImperialStarship() = default;
};

template <typename U> class DeathStar : public ImperialStarship<U> {
public:
    DeathStar (U shield, U attackPower) {
        this->attackPower=attackPower;
        this->shield=shield;
    }
};


template <typename U> class ImperialDestroyer : public ImperialStarship<U> {
public:
    ImperialDestroyer (U shield, U attackPower) {
        this->attackPower=attackPower;
        this->shield=shield;
    }
};

template <typename U> class TIEFighter : public ImperialStarship<U> {
public:
    TIEFighter (U shield, U attackPower) {
        this->attackPower=attackPower;
        this->shield=shield;
    }
};

template <typename I, typename R>
void attack(I imperialShip, R rebelShip);

#endif //PROJECT_IMPERIALFLEET_H
