#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ContainsIntegers
{
	virtual ~ContainsIntegers() = default;
	virtual int* begin() = 0;
	virtual int* end() = 0;
};

struct SingleValue : ContainsIntegers
{
	int value{ 0 };
	       
	SingleValue() = default;

	explicit SingleValue(const int value)
		: value{ value }
	{
	}


	int* begin() override { return &value; }
	int* end() override { return &value + 1; }
};

struct ManyValues : vector<int>, ContainsIntegers
{
	int* begin() override { return &(*this)[0]; }

	int* end() override { return &(*this)[size()]; }

	void add(const int value)
	{
		push_back(value);
	}
};

int sum(const vector<ContainsIntegers*> items)
{
	int result{ 0 };

	for (auto item : items)
	{
		for (auto value : *item)
		{
			result += value;
		}
	}

	return result;
}
