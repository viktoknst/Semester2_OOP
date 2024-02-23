#include <iostream>

struct ComplexNum
{
    int realPart;
    int imaginaryPart;
};

ComplexNum addNumbers(const ComplexNum &first, const ComplexNum &second) {
    ComplexNum result;
    result.realPart = first.realPart + second.realPart;
    result.imaginaryPart = first.imaginaryPart + second.imaginaryPart;
    return result;
}

void printResult(const ComplexNum& result) {
    std::cout << result.realPart << " " << result.imaginaryPart;
}

int main()
{
    ComplexNum first = { 3, 1 };
    ComplexNum second = { 2, 3 };
    ComplexNum result = addNumbers(first, second);

    printResult(result);
}
