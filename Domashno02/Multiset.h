#pragma once
#include <iostream>
#include <fstream>

namespace MultisetConstants {
	constexpr size_t BYTE_SIZE = 8;
}

class Multiset {
private:

	uint8_t* data;
	unsigned int n;
	unsigned int k;
	unsigned int bucketsCount;

public:

	Multiset(unsigned int n, unsigned int k);
	Multiset(const Multiset& other);
	Multiset& operator=(const Multiset& other);
	~Multiset();

	void add(unsigned int num);
	unsigned int occurrencesCount(unsigned int num) const;
	void printNumbers() const;
	void printMultisetAsInMemory() const;
	void serialize(const char* fileName) const;
	void deserialize(const char* fileName);

	friend Multiset intersectionOfMultisets(const Multiset& lhs, const Multiset& rhs);
	friend Multiset differenceBetweenMultisets(const Multiset& lhs, const Multiset& rhs);
	friend Multiset additionOfMultisets(const Multiset& mySet);

private:

	unsigned int getBucketIndex(unsigned int n) const;
	unsigned int getRemainder(unsigned int num) const;
	uint8_t getMask(unsigned int n) const;
	
	void free();
	void copyFrom(const Multiset& other);
	void copyNumbers(const int* newElements, size_t newElementsCount);

};
