/*
 * Strategy Pattern
 *
 * Helps avoid duplicate code in classes
 * Helps avoid instances where implementation of one class affects another
 * Lets the algorithm vary independently from clients that use it 
 */

#include <iostream>

using namespace std;

/* abstract class decouples the capability to fly */
class Fly
{
public:
	virtual string fly() = 0;	
};

/* Restricting flying behavior code in the specialized classes
 * Flies and CantFly help avoid duplication of code -
 * flying behavior
 */
class Flies : public Fly
{
public:
	virtual string fly() {
		return "Flying high";
	}
};

class CantFly : public Fly
{
public:
	virtual string fly() {
		return "Cannot fly";
	}
};

class Animal
{
	string name;
public:
	// composition helps change capability at runtime
	Fly *flyingtype;
	string try_to_fly() {
		return flyingtype->fly();
	}
	void set_flying_ability(Fly *newftype)
	{
		flyingtype = newftype;
	}
	void set_name(string newname) {
		name = newname;
	}
	string get_name() {
		return name;
	}
};

class Eagle: public Animal
{
public:
	Eagle()
	{
		flyingtype = new Flies();
	}
	~Eagle()
	{
		delete flyingtype;
	}
};

class Sparrow: public Animal
{
public:
	Sparrow()
	{
		flyingtype = new Flies();
	}
	~Sparrow()
	{
		delete flyingtype;
	}
};


class Dog: public Animal
{
public:
	Dog()
	{
		flyingtype = new CantFly();
	}
	~Dog()
	{
		delete flyingtype;
	}
};

class Cat: public Animal
{
public:
	Cat()
	{
		flyingtype = new CantFly();
	}
	~Cat()
	{
		delete flyingtype;
	}
};

int main()
{
	Animal *jimmy = new Dog();
	Animal *missy = new Cat();
	Animal *snowy = new Eagle();
	Animal *dovey = new Sparrow();

	cout << "Dog     : " << jimmy->try_to_fly() << endl;
	cout << "Cat     : " << missy->try_to_fly() << endl;
	cout << "Eagle   : " << snowy->try_to_fly() << endl;
	cout << "Sparrow : " << dovey->try_to_fly() << endl;

	delete jimmy;
	delete missy;
	delete snowy;
	delete dovey;

	return 0;
}

