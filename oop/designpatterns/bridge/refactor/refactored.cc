#include <iostream>
#include <string>
#include "gtest/gtest.h"

/*
 * Code refactored with bridge design pattern
 */

using namespace std;

struct Renderer {
    virtual string what_to_render_as() const = 0;
};

struct Shape {
    string name;
    const Renderer& renderer;
    Shape(const Renderer& renderer): renderer{renderer} {
    }
    string str() const {
        ostringstream oss;
        oss << "Drawing " << name << " as "
            << renderer.what_to_render_as();
        return oss.str();
    }
};

struct Triangle : Shape {
    explicit Triangle(const Renderer& renderer) : Shape{renderer} {
        name = "Triangle";
    }
};

struct Square : Shape {
    explicit Square(const Renderer& renderer) : Shape{renderer} {
        name = "Square";
    }
};

struct RasterRenderer : Renderer {
    string what_to_render_as() const override {
        return "pixels";
    }
};

struct VectorRenderer : Renderer {
    string what_to_render_as() const override {
        return "lines";
    }
};

namespace {
    class Evaluate : public testing::Test {
    };
    TEST_F(Evaluate, SimpleTest) {
        ASSERT_EQ("Drawing Square as lines", Square{VectorRenderer{}}.str());
    }
} // namespace

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
