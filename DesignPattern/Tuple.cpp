#include <iostream>
#include <string>
#include <tuple>
#include <map>

using namespace std;

tuple<string, int> getNameAge() 
{
	//...
	return make_tuple("Bob", 34);
}

int main()
{
	struct Person { string name; int age; } p;
	tuple<string, int> t;

	cout << p.name << " " << p.age << endl;
	cout << get<0>(t) << " " << get<1>(t) << endl;

	// As a one-time only structure to transfer a group of data
	string name;
	int age;
	tie(name, age) = getNameAge();

	// Comparison of tuples
	tuple<int, int, int> time1, time2; // hours, mintues, seconds
	if (time1 > time2)
		cout << "time1 is a later time";

	// Multi index map
	map<tuple<int, char, float>, string> m;
	m[make_tuple(2, 'a', 2.3)] = "Faith will move mountains";

	// shift data position
	int a, b, c;
	tie(b, c, a) = make_tuple(a, b, c);
}