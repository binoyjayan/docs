#include <memory>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "di.hpp"

/*
 * Instead of defining singleton objects by explicitly hiding
 * the constructors, and having the 'get' method, rely on
 * an "Inversion of Control Container" used in a DI framework.
 *
 * The basic idea here is allow configuration of different component
 * with a specification of a lifetime. Since, singleton is an specification
 * of a lifetime, the CI methodology can be used here.
 */

using std::make_unique;
using std::make_shared;

struct IFoo {
    virtual std::string name() = 0;
};

struct Foo : IFoo {
    static int id;
    Foo() {
        id++;
    }
    std::string name() override {
        return "foo " + boost::lexical_cast<std::string>(id);
    }
};
int Foo::id = 0;

/* A component that needs a singleton instance of Foo */
struct Bar {
    // Bar has a dependency on 'IFoo' shared pointer
    std::shared_ptr<IFoo> foo;
};

int main() {
    auto injector = boost::di::make_injector(
        /* when asked for IFoo, provide Foo singleton object */
        boost::di::bind<IFoo>().to<Foo>().in(boost::di::singleton)
    );
    // This create only one object of type 'Foo'
    auto bar1 = injector.create<std::shared_ptr<Bar>>();
    auto bar2 = injector.create<std::shared_ptr<Bar>>();

    std::cout << "bar1: " << bar1->foo->name() << std::endl;
    std::cout << "bar2: " << bar2->foo->name() << std::endl;

    std::cout << std::boolalpha << (bar1->foo.get() == bar2->foo.get()) << std::endl;
    return 0;
}
