#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

using namespace std;

enum class PointType
{
	cartesian,
	polar
};

class Point
{
public: // also can make everything public
	// friend class PointFactory; // violates OCP, should closed for modification
	Point(float x, float y) : x(x), y(y) {}
// public:
	float x, y;

	friend ostream &operator<<(ostream &os, const Point &point)
	{
		ost << "x: " << point.x << " y: " << point.y;
		return os;
	}
};

// if you have dedicated code which is dedicated to the construction
// why not move it into seperate component(class)
// this is not an abstract factory, concrete factory
class PointFactory
{
public:
	static Point NewCartesian(float x, float y) // don't have to be static
	{
		return { x, y };
	}

	static Point NewPolar(float r, float theta)
	{
		return { r * cos(theta), r * sin(theta) };
	}
};

int main()
{

	auto p = PointFactory::NewPolar(5, M_PI_4);
	cout << p << endl;

	return 0;
}