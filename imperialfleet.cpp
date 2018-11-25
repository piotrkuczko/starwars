#include <string>
#include <iostream>
#include "rebelfleet.h"
#include "imperialfleet.h"
template <typename I, typename R>
void attack(I imperialShip, R rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower);
    //R = StarCruiser<T> lub R = XWing<T>
    std::string type = typeid(rebelShip).name();
    std::cout << type << std::endl;
    //if (rebelShip.)
    //    imperialShip.takeDamage(rebelShip.getAttackPower);
};

