#include "Deck.h"
#include <iostream>

#pragma warning(disable: 4996);

size_t Deck::getNumberOfMagicCards() const {
	for (size_t i = 0; i < MAX_MAGIC_CARD_NUMBER; i++) {
		if (magicCards[i].isEmpty()) {
			return i;
		}

		return MAX_MAGIC_CARD_NUMBER;
	}
}

size_t Deck::getNumberOfMonsterCards() const {
	for (size_t i = 0; i < MAX_MONSTER_CARD_NUMBER; i++) {
		if (monsterCards[i].isEmpty()) {
			return i;
		}

		return MAX_MONSTER_CARD_NUMBER;
	}
}

void Deck::addMagicCard(Effects type, const char* name, const char* effect) {
	if (getNumberOfMagicCards() >= MAX_MAGIC_CARD_NUMBER) {
		std::cout << "Exceeded number of magic cards!" << std::endl;
		return;
	}

	MagicCard newMagicCard(type, name, effect);
	magicCards[getNumberOfMagicCards()] = newMagicCard;
}

void Deck::addMonsterCard(const char* name, unsigned attack, unsigned defense) {
	if (getNumberOfMonsterCards() >= MAX_MONSTER_CARD_NUMBER) {
		std::cout << "Exceeded number of monster cards!" << std::endl;
		return;
	}

	MonsterCard newMonsterCard(name, attack, defense);
	monsterCards[getNumberOfMonsterCards()] = newMonsterCard;
}

void Deck::changeCertainMagicCard(size_t index, const MagicCard& newCard) {
	if (index >= getNumberOfMagicCards()) {
		std::cout << "Invalid index" << std::endl;
		return;
	}

	magicCards[index] = newCard;
}

void Deck::changeCertainMonsterCard(size_t index, const MonsterCard& newCard) {
	if (index >= getNumberOfMonsterCards()) {
		std::cout << "Invalid index" << std::endl;
		return;
	}

	monsterCards[index] = newCard;
}

void Deck::removeCertainMagicCard(size_t index) {
	size_t numberOfMagicCards = getNumberOfMagicCards();

	for (int i = index; i < numberOfMagicCards; i++) {
		magicCards[i] = magicCards[i + 1];
	}

	magicCards[numberOfMagicCards] = { Effects::Unknown, "", "" };
}

void Deck::removeCertainMonsterCard(size_t index) {
	size_t numberOfMonsterCards = getNumberOfMonsterCards();

	for (int i = index; i < numberOfMonsterCards; i++) {
		monsterCards[i] = monsterCards[i + 1];
	}

	monsterCards[numberOfMonsterCards] = { nullptr, 0, 0 };
}

void Deck::printDeck() const {
	size_t monsterCardsCount = getNumberOfMonsterCards();
	std::cout << "MONSTER CARDS:\n";

	for (int i = 0; i < monsterCardsCount; i++) {
		monsterCards[i].print();
	}

	size_t magicCardsCount = getNumberOfMagicCards();
	std::cout << "MAGIC CARDS:\n";

	for (int i = 0; i < magicCardsCount; i++) {
		magicCards[i].print();
	}
}
