#include <string>
#include "person.hpp"

/* Note that the bridge class PersonImpl is defined in the
 * source file instead of the header
 */
struct Person::PersonImpl {
    void greet(Person* p);
};

// Implementation
void Person::PersonImpl::greet(Person* p) {
    printf("hello %s", p->name.c_str());
}

Person::Person() : impl(new PersonImpl) {
}

Person::~Person() {
    delete impl;
}

void Person::greet() {
    impl->greet(this);
}

int main() {
    return 0;
}

