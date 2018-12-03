#include <iostream>
//#include <any>
#include "rebelfleet.h"
#include "imperialfleet.h"
//#include "battle.h"


int main() {
	Explorer<int> e(100, 2997960);
	XWing<int> xwing(100, 300000, 10);
	ImperialDestroyer<int> imp(100, 10);
	//Explorer<int> f(10, 10);
    //ImperialDestroyer<int> g(10, 100000);
	std::cout << e.getShield() << " " << e.getSpeed() << " " << std::endl;
	std::cout << xwing.getShield() << " " << xwing.getSpeed() << " " << xwing.getAttackPower() << std::endl;
	std::cout << imp.getShield() << " " << imp.getAttackPower() << std::endl;
	attack<ImperialDestroyer <int>, XWing<int>>(imp, xwing);
	std::cout << e.getShield() << " " << e.getSpeed() << std::endl;
	std::cout << xwing.getShield() << " " << xwing.getSpeed() << " " << xwing.getAttackPower() << std::endl;
	std::cout << imp.getShield() << " " << imp.getAttackPower() << std::endl;
	//std::cout << e.getAttackPower() << std::endl;
	//std::cout << g.getAttackPower() << std::endl;
	/*attack<ImperialDestroyer<int>, Explorer<int> >(g, e);


	XWing<float> xwing(100.0f, 300000.0f, 50.0f);
	Explorer<int> explorer(150, 400000);
	StarCruiser<unsigned> cruiser(1234, 100000, 11);
	DeathStar<long> deathStar(10000, 75);
	TIEFighter<unsigned> fighter(50, 9);
	ImperialDestroyer<int> destroyer(150, 20);
	auto battle = SpaceBattle<short, 1, 23,
			DeathStar<long>,
			Explorer<int>,
			TIEFighter<unsigned>,
			XWing<float>>(deathStar,
						  explorer,
						  fighter,
						  xwing);

	assert(battle.countRebelFleet() == 2);
	assert(battle.countImperialFleet() == 2);
*/

	return 0;
}
