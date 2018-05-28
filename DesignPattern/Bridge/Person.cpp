#include "Person.h"

// in cpp file, not get details of implementation in header file
class Person::PersonImpl
{
public:
	void greet(Person* p)
	{
		std::cout << "hello my name is" <<
			p->name << std::endl;
	}
};

Person::Person()
	: impl(new PersonImpl)
{
 }

void Person::greet()
{
	// relay the implementation
	impl->greet(this);
}

Person::~Person()
{
	delete impl;
}

// advantage 