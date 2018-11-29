#ifndef PROJECT_IMPERIALFLEET_H
#define PROJECT_IMPERIALFLEET_H

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

    //~ImperialStarship() = default;
};

template <typename U>
using DeathStar = ImperialStarship<U>;

template <typename U>
using ImperialDestroyer = ImperialStarship<U>;

template <typename U>
using TIEFighter = ImperialStarship<U>;


template <typename A, typename B>
void attack(ImperialStarship<A> &imperialShip, Explorer<B> &rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template <typename A, typename R>
void attack(ImperialStarship<A> &imperialShip, R &rebelShip) {
    //std::cout << typeid(R).name() << std::endl;
    rebelShip.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(rebelShip.getAttackPower());
}

#endif //PROJECT_IMPERIALFLEET_H
