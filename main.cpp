#include <iostream>
#include "rebelfleet.h"
int main() {
	Explorer<int> e(10, 2997960);
	//Explorer<int> f(10, 10);
	StarCruiser<int> g(10, 100000, 10);
	std::cout << e.getShield() << " " << e.getSpeed() << std::endl;
	std::cout << g.getAttackPower() << std::endl;
	//std::cout << e.getAttackPower() << std::endl;
	return 0;
}
