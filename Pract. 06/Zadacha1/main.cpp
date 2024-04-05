#include <iostream>
#include "Duelist.h"

int main() {
	//40 cards = 20 MonsterCards/20 MagicCards
	Deck d;
	d.addMonsterCard("Pikachu", 2000, 1500);
	d.addMonsterCard("Pikachu 2", 2400, 1600);
	d.addMonsterCard("az", 300, 100);
	d.addMonsterCard("az 2", 500, 200);
	d.addMonsterCard("az 3", 700, 300);

	d.printDeck();
	std::cout << std::endl;


	MonsterCard newMonster("Blue-eyes white dragon", 3000, 2500);
	d.changeCertainMonsterCard(4, newMonster);

	d.printDeck();
	std::cout << std::endl;


	d.addMagicCard(Effects::Buff, "APTECHKA", "add 50 DP");
	d.addMagicCard(Effects::Buff, "APTECHKA+", "add 100 DP");
	d.addMagicCard(Effects::Buff, "APTECHKA++", "add 150 DP");
	MagicCard newMagic(Effects::Spell, "Monster reborn", "revive");
	d.changeCertainMagicCard(2, newMagic);

	d.printDeck();
	std::cout << std::endl;


	std::cout << d.getNumberOfMagicCards() << std::endl; //3
	std::cout << d.getNumberOfMonsterCards() << std::endl; //5
	std::cout << std::endl;


	Duelist player1("Seto Kaiba", d);
	MonsterCard DarkMagician("Dark Magician", 2500, 2100);
	player1.changeCertainMonsterCard(2, DarkMagician);
	player1.print();
	std::cout << std::endl;


	Duelist player2("Yugi Muto");
	MagicCard Reflection(Effects::Trap, "Reflection", "Reflects the last played spell");
	player2.changeCertainMagicCard(2, Reflection);
}
