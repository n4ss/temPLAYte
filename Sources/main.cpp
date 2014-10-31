#include "Graph.hh"

struct Foo {
	bool operator>(const Foo&) const { return true; }
	bool operator==(const Foo&) const { return true; }
	bool operator<(const Foo&) const { return true; }
	bool operator>=(const Foo&) const { return true; }
//	bool operator<=(const Foo&) const { return true; }
};

int main(int argc, char **argv) {
	Vertex<std::string> vert = Vertex<std::string>("1");
	std::cout << hasEqual_<Foo>::value << std::endl;
	std::cout << hasGreater_<Foo>::value << std::endl;
	std::cout << hasLower_<Foo>::value << std::endl;
	std::cout << hasLowerOrEqual_<Foo>::value << std::endl;
	std::cout << hasGreaterOrEqual_<Foo>::value << std::endl;
	std::cout << HAS_OPS(Foo)::value << std::endl;
//	std::cout << vert.getId() << std::endl;
	return 0;
}
