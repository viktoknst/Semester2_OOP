#include <iostream>
#include "MonsterCard.h"

#pragma warning(disable: 4996);

void MonsterCard::free() {
	delete[] name;
	name = nullptr;
	attack = 0;
	defense = 0;
}

void MonsterCard::copyName(const char* newName) {
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

void MonsterCard::copyFrom(const MonsterCard& other) {
	attack = other.attack;
	defense = other.defense;

	if (other.name) {
		copyName(other.name);
	}
}

MonsterCard::MonsterCard(const char* name, unsigned attack, unsigned defense) {
	setName(name);
	setAttack(attack);
	setDefense(defense);
}

MonsterCard::MonsterCard(const MonsterCard& other) {
	copyFrom(other);
}

MonsterCard& MonsterCard::operator=(const MonsterCard& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MonsterCard::~MonsterCard() {
	free();
}

void MonsterCard::setName(const char* name) {
	if (!name || name == this->name) {
		return;
	}
	
	delete[] this->name;
	copyName(name);
}

void MonsterCard::setAttack(unsigned attack) {
	this->attack = attack;
}

void MonsterCard::setDefense(unsigned defense) {
	this->defense = defense;
}

bool MonsterCard::isEmpty() const {
	if (name == nullptr && attack == 0 && defense == 0) {
		return true;
	}

	return false;

}

void MonsterCard::print() const {
	std::cout << name << " " << attack << " " << defense << std::endl;
}
