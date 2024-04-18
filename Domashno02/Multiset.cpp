#include "Multiset.h"

void decimalToBinary(uint8_t num) {
	for (int i = MultisetConstants::BYTE_SIZE - 1; i >= 0; i--) {
		int mask = num >> i;

		if (mask & 1) { std::cout << "1"; }
			
		else { std::cout << "0"; }
	}
}

unsigned int Multiset::getBucketIndex(unsigned int num) const {
	return ((num + 1) * k) / MultisetConstants::BYTE_SIZE;
}

unsigned int Multiset::getRemainder(unsigned int num) const {
	return ((num + 1) * k) % MultisetConstants::BYTE_SIZE;
}

uint8_t Multiset::getMask(unsigned int num) const {
	unsigned int currentBucket = getBucketIndex(num);
	unsigned int remainder = getRemainder(num);
	unsigned int mask = 1;
	
	mask <<= MultisetConstants::BYTE_SIZE - remainder;
	return mask;
}

void Multiset::free() {
	delete[] data;
	data = nullptr;
	n = 0;
	k = 0;
	bucketsCount = 0;
}

void Multiset::copyFrom(const Multiset& other) {
	n = other.n;
	k = other.k;
	bucketsCount = other.bucketsCount;

	data = new uint8_t[bucketsCount];

	for (size_t i = 0; i < bucketsCount; i++) {
		data[i] = other.data[i];
	}
}

Multiset::Multiset(unsigned int n, unsigned int k) {
	this->n = n;
	this->k = k;
	this->bucketsCount = n / MultisetConstants::BYTE_SIZE + 1;
	data = new uint8_t[bucketsCount + 1] {};
}

Multiset::Multiset(const Multiset& other) {
	copyFrom(other);
}

Multiset& Multiset::operator=(const Multiset& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Multiset::~Multiset() {
	free();
}

void Multiset::add(unsigned int num) {
	if (num > n) {
		throw std::out_of_range("Number is out of range");
		return;
	}

	// add exception for too many occurrances

	unsigned int bucket = getBucketIndex(num);
	unsigned int remainder = getRemainder(num);
	uint8_t mask = getMask(num);
	
	while (data[bucket] & mask) {
		data[bucket] ^= mask;
		remainder--;

		if (remainder == 0) {
			mask = 1;
			bucket--;
			remainder = k;
			continue;
		}

		mask <<= 1;
	}

	data[bucket] ^= mask;
}

unsigned int Multiset::occurrencesCount(unsigned int num) const {
	unsigned int occurrances = 0;
	unsigned int counter = k;
	unsigned int power = 0;
	unsigned int bucket = getBucketIndex(num);
	unsigned int remainder = getRemainder(num);
	uint8_t mask = getMask(num);

	while (counter) {
		if (data[bucket] & mask) {
			occurrances += pow(2, power);
		}

		remainder--;
		power++;
		counter--;

		if (remainder == 0) {
			mask = 1;
			bucket--;
			remainder = k;
			continue;
		}
			
		mask <<= 1;
	}
	

	return occurrances;
}

void Multiset::printNumbers() const {
	unsigned int occurrances;

	for (size_t i = 0; i <= n; i++) {
		occurrances = occurrencesCount(i);

		while (occurrances) {
			std::cout << i << " ";
			occurrances--;
		}
	}

	std::cout << std::endl;
}

void Multiset::printMultisetAsInMemory() const {
	for (size_t i = 0; i <= bucketsCount; i++) {
		decimalToBinary(data[i]);
		std::cout << " ";
	}

	std::cout << std::endl;
}

void Multiset::serialize(const char* fileName) const {
	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs) {
		std::cout << "Couldn't open file for writing" << std::endl;
		return;
	}

	ofs.write((const char*)&(data), sizeof(uint8_t) * (n + 1));
	ofs.write((const char*)&n, sizeof(unsigned int));
	ofs.write((const char*)&k, sizeof(unsigned int));
	ofs.write((const char*)&bucketsCount, sizeof(unsigned int));
	
	ofs.close();
}

void Multiset::deserialize(const char* fileName) {
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs) {
		std::cout << "Couldn't open file for reading" << std::endl;
		return;
	}

	free();

	data = new uint8_t[n + 1];
	ifs.read((char*)&(data), sizeof(uint8_t) * (n + 1));
	ifs.read((char*)&n, sizeof(unsigned int));
	ifs.read((char*)&k, sizeof(unsigned int));
	ifs.read((char*)&bucketsCount, sizeof(unsigned int));

	ifs.close();
}

Multiset intersectionOfMultisets(const Multiset& lhs, const Multiset& rhs) {
	unsigned int resultCombinedN = std::min(lhs.n, rhs.n);
	Multiset result(resultCombinedN, std::min(lhs.k, rhs.k));
	unsigned int* occurranceOfNumbers = new unsigned int[resultCombinedN + 1] {};

	for (size_t i = 0; i <= resultCombinedN; i++) {
		occurranceOfNumbers[i] = std::min(lhs.occurrencesCount(i), rhs.occurrencesCount(i));
	}

	for (size_t i = 0; i <= resultCombinedN; i++) {
		while (occurranceOfNumbers[i]) {
			result.add(i);
			occurranceOfNumbers[i]--;
		}
	}

	delete[] occurranceOfNumbers;
	return result;
}

Multiset differenceBetweenMultisets(const Multiset& lhs, const Multiset& rhs) {
	Multiset result(lhs.n, lhs.k);
	unsigned int* occurranceOfNumbers = new unsigned int[lhs.n + 1] {};

	for (size_t i = 0; i <= lhs.n; i++) {
		if (lhs.occurrencesCount(i) != 0 && rhs.occurrencesCount(i) == 0) {
			occurranceOfNumbers[i] = lhs.occurrencesCount(i);
		}
	}

	for (size_t i = 0; i <= lhs.n; i++) {
		while (occurranceOfNumbers[i]) {
			result.add(i);
			occurranceOfNumbers[i]--;
		}
	}

	delete[] occurranceOfNumbers;
	return result;
}

Multiset additionOfMultisets(const Multiset& mySet) {
	Multiset result(mySet.n, mySet.k);
	unsigned int* occurranceOfNumbers = new unsigned int[mySet.n + 1] {};

	for (size_t i = 0; i <= mySet.n; i++) {
		occurranceOfNumbers[i] = pow(2, mySet.k) - mySet.occurrencesCount(i) - 1;
	}

	for (size_t i = 0; i <= mySet.n; i++) {
		while (occurranceOfNumbers[i]) {
			result.add(i);
			occurranceOfNumbers[i]--;
		}
	}

	delete[] occurranceOfNumbers;
	return result;
}
