#include "Multiset.h"

int main() {
	Multiset m1(3, 3);
	Multiset m2(4, 3);

	try {
		m1.add(0);
		m1.add(0);
		m1.add(0);
		m1.add(1);
		m1.add(2);
		m1.add(2);
		m1.add(2);
		m1.add(2);
		m1.add(2);
		m1.add(3);
		m1.add(3);

		m2.add(1);
		m2.add(1);
		m2.add(3);
		m2.add(3);
		m2.add(3);
		m2.add(4);
	}
	catch (std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}

	m1.printNumbers();
	m2.printNumbers();
	
	m1.printMultisetAsInMemory();
	intersectionOfMultisets(m1, m2).printNumbers();
	differenceBetweenMultisets(m2, m1).printNumbers();
	additionOfMultisets(m1).printNumbers();
	
	return 0;
}
