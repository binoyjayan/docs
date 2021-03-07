#pragma once
#include <string>

struct Person {
    std::string name;

    /*
     * Idea is that the implementation detail is deferred/bridged/relayed
     * into a separate class having the implementation.
     * Here, the inner class 'PersonImpl'
     * It may not necessarily be an inner class.
     *
     * One of the use cases is to hide the bridge's implementation
     * even the contents of the class 'PersonImpl'.
     * It also helps to maintain ABI compatibility for client code
     * which does not know about the implememtation of the bridge.
     *
     * Essentially, the bdige may be thought of as a stronger form
     * of encapsulation
     */
    class PersonImpl;
    PersonImpl *impl;

    Person();
    ~Person();

    void greet();
};