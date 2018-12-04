#ifndef PROJECT_IMPERIALFLEET_H
#define PROJECT_IMPERIALFLEET_H

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

    static constexpr bool isRebel(){
        return false;
    }
};
//
//ostream &operator << (ostream &os, ImperialStarship &a) {
//    ostringstream ss;
//    ss << a.getShield() << " " << a.getAttackPower() << "\n";
//    return ss;
//}

template <typename U>
using DeathStar = ImperialStarship<U>;

template <typename U>
using ImperialDestroyer = ImperialStarship<U>;

template <typename U>
using TIEFighter = ImperialStarship<U>;


/*template <typename I, template <class> class U>
void attack(I &imperialShip, U &rebelShip) {
    std::cout << typeid(rebelShip).name() << std::endl;
    //rebelShip.takeDamage(imperialShip.getAttackPower());
}*/

template <typename I, typename R>
void attack(I &imperialShip, R &rebelShip) {
//    std::cout << typeid(R).name() << std::endl;
    static_assert(!I::isRebel(), "First isn't imperialShip");
    static_assert(R::isRebel(), "Secont isn't rebelShip");
    rebelShip.takeDamage(imperialShip.getAttackPower());
//    std::cout << rebelShip.isExplorer() << std::endl;
    if constexpr (!R::isExplorer())
        imperialShip.takeDamage(rebelShip.getAttackPower());
}

#endif //PROJECT_IMPERIALFLEET_H
