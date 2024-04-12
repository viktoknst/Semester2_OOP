#include <iostream>
#include "Vector.h"

void Vector::free() {
	delete[] numbers;
	numbers = nullptr;
	capacity = 1;
	size = 0;
}

void Vector::copyFrom(const Vector& other) {
	this->size = other.size;
	this->capacity = other.capacity;

	numbers = new int[capacity];

	for (int i = 0; i < size; i++) {
		this->numbers[i] = other.numbers[i];
	}
}
