#include <iostream>
#include "MagicCard.h"

#pragma warning(disable: 4996);

MagicCard::MagicCard(Effects type, const char* name, const char* effect) {
	this->type = type;
	
	if (strlen(name) <= MAX_NAME_LENGTH) {
		strcpy(this->name, name);
	}
	
	if (strlen(effect) <= MAX_EFFECT_LENGTH) {
		strcpy(this->effect, effect);
	}
}

bool MagicCard::isEmpty() const {
	if (type == Effects::Unknown && strcmp(name, "") == 0 && strcmp(effect, "") == 0) {
		return true;
	}

	return false;

}

void MagicCard::print() const {
	std::cout << name << " " << effect << " " << (int)type << std::endl;
}
