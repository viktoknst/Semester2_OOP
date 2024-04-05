#include <iostream>
#include "Duelist.h"

#pragma warning(disable: 4996);

void Duelist::copyName(const char* newName) {
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

void Duelist::copyFrom(const Duelist& other) {
	deck = other.deck;
	copyName(other.name);
}

void Duelist::free() {
	delete[] name;
	name = nullptr;
	deck = {};
}

Duelist::Duelist(const char* name) : deck() {
	setName(name);
}

Duelist::Duelist(const char* name, const Deck& deck) {
	setName(name);
	this->deck = deck;
}

Duelist::Duelist(const Duelist& other) {
	copyFrom(other);
}

Duelist& Duelist::operator=(const Duelist& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Duelist::~Duelist() {
	free();
}

void Duelist::setName(const char* newName) {
	if (!newName || name == newName) {
		return;
	}

	delete[] name;
	copyName(newName);
}

void Duelist::addMagicCard(Effects type, const char* name, const char* effect) {
	deck.addMagicCard(type, name, effect);
}

void Duelist::addMonsterCard(const char* name, unsigned attack, unsigned defense) {
	deck.addMonsterCard(name, attack, defense);
}

void Duelist::changeCertainMagicCard(size_t index, const MagicCard& newCard) {
	deck.changeCertainMagicCard(index, newCard);
}

void Duelist::changeCertainMonsterCard(size_t index, const MonsterCard& newCard) {
	deck.changeCertainMonsterCard(index, newCard);
}

void Duelist::removeCertainMagicCard(size_t index) {
	deck.removeCertainMagicCard(index);
}

void Duelist::removeCertainMonsterCard(size_t index) {
	deck.removeCertainMonsterCard(index);
}

void Duelist::print() const {
	std::cout << name << std::endl;
	deck.printDeck();
}
