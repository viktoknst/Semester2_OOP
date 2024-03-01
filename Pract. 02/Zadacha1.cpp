#include <iostream>
#include <fstream>

constexpr char FILE_NAME[] = "result.txt";

void returnResult() {
    std::ifstream usedFile(FILE_NAME);
    
    if (!usedFile.is_open()) {
        std::cout << -1;
        return;
    }
    
    int sum, mult;
    char buff[BUFF_SIZE];
    
    usedFile >> sum >> mult;

    std::cout << sum - mult;

    usedFile.close();
}

int main() {
    std::ofstream file(FILE_NAME);

    if (!file.is_open()) {
        return -1;
    }

    int a = 4, b = 2, c = 5, sum = 0, mult = 1;
    sum = a + b + c;
    mult = a * b * c;

    file << sum << " " << mult;

    file.close();

    returnResult();
}
