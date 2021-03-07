#include <cmath>
#include <iostream>

class Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}

    // Inner Factory class
    class PointFactory {
        PointFactory() {}
    public:
        static Point NewCartesian(double x, double y) {
            return { x, y };
        }
        static Point NewPolar(double r, double theta) {
            return{ r * cos(theta), r * sin(theta) };
        }
    };
    static PointFactory m_factory;
public:
    friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
        return os << "x: " << obj.x << " y: " << obj.y;
    }
    static PointFactory getFactory() { return m_factory; }
};

int main() {
    // nope!
    // Point::PointFactory pf;

    // if factory is public, then
    //auto p = Point::PointFactory::NewCartesian(3, 4);

    // at any rate, use this
    auto pp = Point::getFactory().NewCartesian(2, 3);
    std::cout << "point: " << pp << std::endl;

    return 0;
}