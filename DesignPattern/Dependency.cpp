#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
using namespace std;

enum class Relationship
{
	parent,
	child,
	sibling
};

struct Person
{
	string name;
};

struct RelationshipBrowser // interface
{
	virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser // lpw-level module
{
	vector<tuple<Person, Relationship, Person>> relations;

	void add_parent_and_child(const Person& parent, const Person& child)
	{
		relations.push_back({ parent, Relationship::parent, child });
		relations.push_back({ child, Relationship::child, parent });	
	}

	vector<Person> find_all_children_of(const string& name) override
	{
		vector<Person> result;
		for (int i = 0; i < relations.size(); i++)
		{
			auto &&first = get<0>(relations[i]);
			auto &&rel = get<1>(relations[i]);
			auto &&second = get<2>(relations[i]);

			if (first.name == name && rel == Relationship::parent)
			{
				result.push_back(second);
			}
		}
		return result;
	}
};

struct Research // high-level, depend just on Relationship browser
{
	Research(RelationshipBrowser& browser)
	{
		for (auto& child : browser.find_all_children_of("John"))
		{
			cout << "John has a child called " << child.name << endl;
		}
	}
	// depends on low-level module & depend on details
	/*
	Research(Relationships& relationships)
	{
		auto& relations = relationships.relations;
		for (int i = 0; i < relations.size(); i++)
		{
			auto &&first = get<0>(relations[i]);
			auto &&rel = get<1>(relations[i]);
			auto &&second = get<2>(relations[i]);

			if (first.name == "John" && rel == Relationship::parent)
			{
				cout << "John has a child called " << second.name << endl;
			}
		}
	}
	*/
}; // move it to low-level module and introduce abstraction

int main()
{
	Person parent{ "John" };
	Person child1{ "Chris" }, child2{ "Matt" };
	Relationships relationships;
	relationships.add_parent_and_child(parent, child1);
	relationships.add_parent_and_child(parent, child2);

	Research _(relationships);

	return 0;
}