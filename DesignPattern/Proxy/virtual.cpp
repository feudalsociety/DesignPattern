#include <iostream>
#include <string>
using namespace std;

struct Image
{
	virtual void draw() = 0;
};

struct Bitmap : Image
{
	Bitmap(const string& filename)
	{
		cout << "Loading bitmap from " << filename << endl;
	}

	void draw() override
	{
		cout << "Drawing bitmap" << endl;
	}
};

// virtual proxy : defer loading original bitmap until draws
struct LazyBitmap : Image
{
	LazyBitmap(const string &filename) : filename(filename)
	{
	}

	void draw() override
	{
		if (!bmp)
			bmp = new Bitmap(filename);
		bmp->draw();
	}

private:
	string filename;
	Bitmap* bmp{nullptr};
};

int main()
{
	LazyBitmap bmp{ "pokemon.png" };
	bmp.draw();

	return 0;
}