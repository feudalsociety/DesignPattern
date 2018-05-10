#include <sstream>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

class HtmlElement // just utility class for modeling Html element
{
	friend class HtmlBuilder;
	string name, text;
	vector<HtmlElement> elements;

	const size_t indent_size = 2;

	// hide constructor
	HtmlElement() {}
	HtmlElement(const string &name, const string &text) : name(name), text(text) {}
public:
	string str(int ident = 0) const
	{
		// print, implementation of str is not important
		return {};
	}

	static HtmlBuilder create(string root_name)
	{
		return { root_name }; 
		// compile error - needs declaration of HtmlBuilder
		// keeping HtmlBuilder class below in a same file for simplicity
	}

	// static std::unique_ptr<HtmlBuilder> build (...
	// returning unique pointer
};

// using builder
class HtmlBuilder
{
	HtmlElement	root;
public:
	HtmlBuilder(string root_name)
	{
		root.name = root_name;
	}

	HtmlBuilder& add_child(string child_name, string child_text)
	{
		HtmlElement e{ child_name, child_text };
		root.elements.emplace_back(e);
		return *this;
	}

	HtmlBuilder* add_child2(string child_name, string child_text)
	{
		HtmlElement e{ child_name, child_text };
		root.elements.emplace_back(e);
		return this;
	}
	
	HtmlElement build() { return root; };

	string str() const { return root.str(); }

	operator HtmlElement() const { return root; }
	// return std::move(root);
};

int main()
{
	auto text = "hello";
	string output;
	output += "<p>";
	output += text;
	output += "</p>";
	cout << output << endl;

	string words[] = { "hello", "world" };
	ostringstream oss;
	oss << "<ul>";
	for (auto w : words)
		oss << "  <li>" << w << "</li>";
	cout << oss.str() << endl;

//

	HtmlBuilder builder{ "ul" };
	builder.add_child("li", "hello").add_child("li", "world"); 
	cout << builder.str() << endl;

// 

	HtmlElement builder2 = HtmlElement::create("ul").add_child("", "");

	// HtmlElement e; // not allowed

	HtmlElement::create("").add_child("", "").build();
	return 0;
}

