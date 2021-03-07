#include <cmath>
#include <iostream>

enum class PointType {
    cartesian,
    polar
};

class Point {
    double x, y;
public:
    friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
        return os << "x: " << obj.x << " y: " << obj.y;
    }
    // Either make constructor public
    Point(double x, double y) : x(x), y(y){}
    /* Alternatively make concrete class 'PointFactory' a friend class
     * so that it can call the private constructor of 'Point'
     * but the following violates the Open-Closed principle
     */
    // friend class PointFactory; // Violates OCP
};

/*
 * This is a concrete Factory class not an abstract one.
 * In the original GOF design patterns, there is only
 * a Factory Method and an Abstract Factory but here we
 * also see an example of a concrete factory class
 */
struct PointFactory {
    static Point NewCartesian(double x, double y) {
        return Point{ x,y };
    }

    static Point NewPolar(double r, double theta) {
        return Point{ r * cos(theta), r * sin(theta) };
    }
};

int main() {
    Point p1 { 1,2 }; // Works if constructor is public
    auto p2 = PointFactory::NewPolar(5, M_PI_4);
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    return 0;
}
