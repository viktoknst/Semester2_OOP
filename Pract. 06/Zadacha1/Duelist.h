#pragma once

#include "Deck.h"

class Duelist {
	char* name = nullptr;
	Deck deck = {};
	
	void copyName(const char* newName);
	void copyFrom(const Duelist& other);
	void free();
	
public:

	Duelist() = default;
	Duelist(const char* name);
	Duelist(const char* name, const Deck& deck);
	Duelist(const Duelist& other);
	Duelist& operator=(const Duelist& other);
	~Duelist();

	void setName(const char* newName);

	void addMagicCard(Effects type, const char* name, const char* effect);
	void addMonsterCard(const char* name, unsigned attack, unsigned defense);

	void changeCertainMagicCard(size_t index, const MagicCard& newCard);
	void changeCertainMonsterCard(size_t index, const MonsterCard& newCard);

	void removeCertainMagicCard(size_t index);
	void removeCertainMonsterCard(size_t index);

	void print() const;
};
