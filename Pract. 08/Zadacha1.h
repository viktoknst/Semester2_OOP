#pragma once

class Vector {
	int* numbers = nullptr;
	unsigned capacity = 1;
	unsigned size = 0;

	void free();
	void copyFrom(const Vector& other);

public:

	Vector() = default;
	Vector(unsigned capacity);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	void pushBack(int num);
	void popBack();
	void insert(int num, unsigned index);
	void erase(unsigned index);
	void resize();
	bool empty() const;
	void clear();
};
