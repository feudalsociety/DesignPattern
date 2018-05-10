#pragma once

#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
	Person& person;
public:
	PersonBuilderBase(Person &person);

	operator Person() const
	{
		return std::move(person);
	}

	PersonAddressBuilder lives() const;
	PersonJobBuilder works() const;
};

// create base class for avoiding creating multiple actual Person memory
// and inherit from it
class PersonBuilder : public PersonBuilderBase
{
public:
	PersonBuilder();
private:	
	Person p;
};

