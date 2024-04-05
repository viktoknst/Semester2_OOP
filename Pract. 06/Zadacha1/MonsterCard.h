#pragma once

class MonsterCard {
	char* name = nullptr;
	unsigned attack = 0;
	unsigned defense = 0;

	void free();
	void copyName(const char* newName);
	void copyFrom(const MonsterCard& other);
	
public:

	MonsterCard() = default;
	MonsterCard(const char* name, unsigned attack, unsigned defense);
	MonsterCard(const MonsterCard& other);
	MonsterCard& operator=(const MonsterCard& other);
	~MonsterCard();

	void setName(const char* name);
	void setAttack(unsigned attack);
	void setDefense(unsigned defense);

	bool isEmpty() const;
	void print() const;
};
