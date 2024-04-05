#pragma once

#include "MonsterCard.h"
#include "MagicCard.h"

constexpr size_t MAX_MONSTER_CARD_NUMBER = 20;
constexpr size_t MAX_MAGIC_CARD_NUMBER = 20;

class Deck {
	MagicCard magicCards[MAX_MAGIC_CARD_NUMBER] = {};
	MonsterCard monsterCards[MAX_MONSTER_CARD_NUMBER] = {};

public:

	Deck() = default;

	size_t getNumberOfMagicCards() const;
	size_t getNumberOfMonsterCards() const;
	
	void addMagicCard(Effects type, const char* name, const char* effect);
	void addMonsterCard(const char* name, unsigned attack, unsigned defense);

	void changeCertainMagicCard(size_t index, const MagicCard& newCard);
	void changeCertainMonsterCard(size_t index, const MonsterCard& newCard);

	void removeCertainMagicCard(size_t index);
	void removeCertainMonsterCard(size_t index);

	void printDeck() const;
};
