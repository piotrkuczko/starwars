#include <iostream>
#include "rebelfleet.h"
#include "imperialfleet.h"
int main() {
	Explorer<int> e(10, 2997960);
	//Explorer<int> f(10, 10);
    ImperialDestroyer<int> g(10, 100000);
	std::cout << e.getShield() << " " << e.getSpeed() << std::endl;
	std::cout << g.getAttackPower() << std::endl;
	attack<ImperialDestroyer<int>, Explorer<int> >(g, e);
	//std::cout << e.getAttackPower() << std::endl;
	return 0;
}
