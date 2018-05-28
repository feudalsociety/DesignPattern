#include <iostream>
#include <string>
using namespace std;

struct Address
{
	string street, city;
	int suite;

	Address(const Address& address)
	: street{address.street}, city{address.city}, suite(address.suite)
	{
	}

	Address(const string &street, const string &city, int suite)
		: street(street), city(city), suite(suite) {}

	friend ostream& operator<<(ostream &os, const Address &address)
	{
		os << "street: " << address.street << " city: " << address.city
			<< " suite: " << address.suite;
		return os;
	}
};
struct Contact
{
	string name;
	Address* address;

	Contact(const string &name, Address *address) :
		name(name), address(address) {}

	Contact(const Contact& other)
		: name {other.name},
		address{ new Address{ *other.address } }
	{
	}

	friend ostream &operator<<(ostream &os, const Contact &contact)
	{
		os << "name: " << contact.name << " address: " << *contact.address;
		return os;
	}

};

struct EmployeeFactory
{
	static unique_ptr<Contact> new_main_office_employee
	(const string& name, const int suite)
	{
		static Contact p{ "", new Address{"123 East dr", "London", 0} };
		return new_employee(name, suite, p);
	}
private:
	// utility function
	static unique_ptr<Contact> new_employee(const string& name, const int suite, Contact& prototype)
	{
		auto result = make_unique<Contact>(prototype);
		result->name = name;
		result->address->suite = suite;
		return result;
	}
};
int main()
{
	/*
	// john is acting as a prototype
	Contact john{ "John Doe", new Address{ "123 East Dr", "London", 123 } };
	// Contact jane{ "Jane Smith", Address{ "123 East Dr", "London", 103 } };
	Contact jane{ john }; // deep copy
	jane.name = "Jane Smith";
	jane.address->suite = 103;
	cout << *john << endl;
	*/

	auto john = EmployeeFactory::new_main_office_employee("John", 123);
	cout << *john << endl;

	getchar();
	return 0;
}