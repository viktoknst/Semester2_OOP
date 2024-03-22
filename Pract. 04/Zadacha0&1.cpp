#include <iostream>
#pragma warning (disable: 4996) 

constexpr int MAX_SIZE = 30;

enum class Subjects {
	BIOLOGY,
	CHEMISTRY,
	MATH,
	ART,
	UNKNOWN
};

class Student {
private:
	char name[MAX_SIZE + 1] = "";
	int age = 0;
	unsigned fn = 0;

public:
	Student() = default;

	Student(const char* name, int age, unsigned fn) {
		strcpy(this->name, name);
		this->age = age;
		this->fn = fn;
	}
};

class Teacher {
private:
	char name[MAX_SIZE + 1] = "";
	int age = 0;
	Subjects subject = Subjects::UNKNOWN;
	int salary = 0;

public:
	Teacher() = default;

	Teacher(const char* name, int age, Subjects subject, int salary) {
		setName();
		setAge();
		setSubject();
		setSalary();
	}

	void setName() {
		strcpy(this->name, name);
	}

	void setAge() {
		if (age > 17 && age < 71) {
			this->age = age;
		}
	}

	void setSubject() {
		this->subject = subject;
	}

	void setSalary() {
		if (salary > 500) {
			this->salary = salary;
		}
	}

	const char* getName() const {
		return name;
	}

	int getAge() const {
		return age;
	}

	Subjects getSubject() const {
		return subject;
	}

	int getSalary() const {
		return salary;
	}
};

int main()
{
	Student st;
}
