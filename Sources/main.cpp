#include "Graph.hh"

struct Foo {
	bool operator>(const Foo&) const { return true; }
};

int main(int argc, char **argv) {
	Vertex<std::string> vert = Vertex<std::string>("1");
	std::cout << has_greater<Foo>::value << std::endl;
	std::cout << vert.getId() << std::endl;
	return 0;
}
