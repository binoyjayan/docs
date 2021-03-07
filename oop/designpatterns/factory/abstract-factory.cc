#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <functional>

using namespace std;

struct HotDrink {
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink {
    void prepare(int volume) override {
        cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << endl;
    }
};

struct Coffee : HotDrink {
    void prepare(int volume) override {
        cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << endl;
    }
};

// Abstract Factory class
struct HotDrinkFactory {
    virtual unique_ptr<HotDrink> make() const = 0;
};

// Concrete Factory class - TeaFactory
struct TeaFactory : HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<Tea>();
    }
};

// Concrete Factory class - CoffeeFactory
struct CoffeeFactory : HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<Coffee>();
    }
};

// Additional concrete class
class DrinkFactory {
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory() {
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tea"] = make_unique<TeaFactory>();
    }
    unique_ptr<HotDrink> make_drink(const string& name) {
        auto drink = hot_factories[name]->make();
        drink->prepare(200); // oops!
        return drink;
    }
};


/* Another way of implementing factories is by avoiding
 * concrete classes for all factory implementation and having
 * functional implementations using a lamda expression.
 */
class DrinkWithVolumeFactory {
    map<string, function<unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory() {
        factories["tea"] = [] {
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
        factories["coffee"] = [] {
            auto coffee = make_unique<Coffee>();
            coffee->prepare(200);
            return coffee;
        };
    }
    unique_ptr<HotDrink> make_drink(const string& name);
};

inline unique_ptr<HotDrink> DrinkWithVolumeFactory::make_drink(const string& name) {
    return factories[name]();
}

unique_ptr<HotDrink> make_drink(string type) {
    unique_ptr<HotDrink> drink;
    if (type == "tea") {
        drink = make_unique<Tea>();
        drink->prepare(200);
    } else {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}

int main() {
    // Without using a concrete DrinkFactory class
    auto d = make_drink("tea");

    DrinkFactory df;
    df.make_drink("coffee");

    // Functional implementation
    DrinkWithVolumeFactory vf;
    vf.make_drink("coffee");
    return 0;
}