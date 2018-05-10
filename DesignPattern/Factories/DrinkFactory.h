#pragma once
#include "HotDrink.h"
#include "HotdrinkFactory.h"
#include <map>
#include <functional>

using namespace std;

// concrete implementation of the abstract factory, facilitator for using different factories that we made
// keep track of kind of factories

class DrinkFactory
{
	map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
	DrinkFactory()
	{
		hot_factories["coffee"] = make_unique<CoffeeFactory>();
		hot_factories["tea"] = make_unique<TeaFactory>();
	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		auto drink = hot_factories[name]->make(); // all the factories share same interface
		drink->prepare(200);
		return drink;
	}
};

// functional approach, without relying directly on factories 

class DrinkWithVolumeFactory
{
	map<string, function<unique_ptr<HotDrink>()>> factories;
public:
	DrinkWithVolumeFactory()
	{
		factories["tea"] = [] {
			auto tea = make_unique<Tea>();
			tea->prepare(200);
			return tea;
		};
	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		return factories[name]();
	}
};
