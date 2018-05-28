#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace boost;

struct Address
{
	string street, city;
	int suite;

	Address() = default;

	Address(const Address& address)
		: street{ address.street }, city{ address.city }, suite(address.suite)
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

private:
	friend class serialization::access;

	template <class archive>
	void serialize(archive& ar, const unsigned version)
	{
		ar & street;
		ar & city;
		ar & suite;
	}
};
struct Contact
{
	string name;
	Address* address;

	Contact() = default;

	Contact(const string &name, Address *address) :
		name(name), address(address) {}

	Contact(const Contact& other)
		: name{ other.name },
		address{ new Address{ *other.address } }
	{
	}

	friend ostream &operator<<(ostream &os, const Contact &contact)
	{
		os << "name: " << contact.name << " address: " << *contact.address;
		return os;
	}

private:
	friend class serialization::access;

	template <class archive>
	void serialize(archive& ar, const unsigned version)
	{
		ar & name;
		ar & address;
	}
};

struct EmployeeFactory
{
	static unique_ptr<Contact> new_main_office_employee
	(const string& name, const int suite)
	{
		static Contact p{ "", new Address{ "123 East dr", "London", 0 } };
		return new_employee(name, suite, p);
	}
private:
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
	auto clone = [](const Contact& c)
	{
		ostringstream oss;
		archive::text_oarchive oa(oss);
		oa << c;
		string s = oss.str();
		cout << s << endl;

		istringstream iss(s);
		archive::text_iarchive ia(iss);
		Contact result;
		ia >> result;
		return result;
	};
	auto john = EmployeeFactory::new_main_office_employee("John", 123);
	auto jane = clone(*john);
	jane.name = "Jane";
	cout << *john << endl << jane << endl;

	getchar();
	return 0;
}