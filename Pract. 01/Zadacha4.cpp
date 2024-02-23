#include <iostream>
#include <cmath>

struct Point
{
    int x;
    int y;
};

int pythTheo(int a, int b) {
    int result;
    result = sqrt(a * a + b * b);
    return result;
}

void readPoint(Point& p) {
    std::cin >> p.x >> p.y;
}

void printPoint(const Point& p) {
    std::cout << "(" << p.x << ", " << p.y << ")";
}



int findDistanceFromBeginning(const Point& p) {
    Point beginning = { 0,0 };
    int result;

    
}

int main()
{
    std::cout << pythTheo(3, 4);
}
