#ifndef __GRAPH_H__
# define __GRAPH_H__

//#include <pair>
//#include <string>
#include <unistd.h>
#include <iostream>

/* Trying my own implementation with SFINAE without Boost */
template <typename, typename = std::true_type>
struct has_greater : public std::false_type {
};

template <typename T>
struct has_greater
<
	T,
	typename std::is_convertible
	<
		decltype(T() > T()),
		bool
	>::type
> : public std::true_type {
};

//template <typename Tweight>

template <typename Tid>
class Vertex {
public:
	Vertex(Tid id) {
		_id = id;
	}

	Tid getId() {
		return this->_id;
	}
private:
	Tid _id;
};

template <
	typename Tid,
	typename Tweight
	>
class Edge {
public:

private:
	Vertex<Tid> _orig;
	Vertex<Tid> _dest;
};

template <typename _Tdata> class Pgraph {
};

#endif /* __GRAPH_H__ */
