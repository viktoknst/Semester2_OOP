#pragma once

constexpr unsigned MAX_NAME_LENGTH = 25;
constexpr unsigned MAX_EFFECT_LENGTH = 100;

enum class Effects {
	Trap,
	Buff,
	Spell,
	Unknown
};

class MagicCard {
	Effects type = Effects::Unknown;
	char name[MAX_NAME_LENGTH] = {};
	char effect[MAX_EFFECT_LENGTH] = {};

public:

	MagicCard() = default;

	MagicCard(Effects type, const char* name, const char* effect);

	bool isEmpty() const;
	void print() const;
};
