#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

using namespace std;

enum class PointType
{
	cartesian,
	polar
};

// put the factory right inside the type and expose it as giving a hint what you should be constructing
// and this also solve the OCP (open-closed principle)
class Point
{
	Point(float x, float y) : x(x), y(y) {}
	float x, y;
public:
	friend ostream &operator<<(ostream &os, const Point &point)
	{
		os << "x: " << point.x << " y: " << point.y;
		return os;
	}
private:
	class PointFactory // dedicated API
	{
		PointFactory() {}
	public:
		static Point NewCartesian(float x, float y)
		{
			return { x, y };
		}

		static Point NewPolar(float r, float theta)
		{
			return { r * cos(theta), r * sin(theta) };
		}
	};
public:
	// you can make PointFactory private and using Singleton
	static PointFactory Factory;
	// or use getter method
};


int main()
{

	// auto p = Point::PointFactory::NewPolar(5, M_PI_4);
	auto p = Point::Factory.NewCartesian(3, 4);
	cout << p << endl;

	return 0;
}