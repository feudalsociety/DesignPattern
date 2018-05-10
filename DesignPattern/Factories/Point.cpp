#include <iostream>
#include <cmath>

using namespace std;

enum class PointType
{
	cartesian,
	polar
};

struct Point
{
	// Point(float x, float y) : x(x), y(y) {}

	// constructor is insufficient for describing the situation
	// a, b is not a desirable name
	Point(float a, float b, PointType type = PointType::cartesian)
	{
		if (type == PointType::cartesian)
		{
			x = a;
			y = b;
		}
		else
		{
			x = a * cos(b);
			y = a * sin(b);
		}
	}
	// Alternatively use mechanism where instead of using constructor, which can have a proper name - Factory Pattern
	// make sure that the interface	to a particular type provides is sensible
	float x, y;
};