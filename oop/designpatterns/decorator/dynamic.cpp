#include <iostream>

struct Shape {
    virtual std::string str() const = 0;
};

struct Circle : Shape {
    float radius;

};

int main() {
    return 0;
}