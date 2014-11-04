#ifndef __GRAPH_H__
# define __GRAPH_H__

//#include <pair>
//#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstdio>

/* Trying my own implementation of 'hasOperators' with SFINAE without Boost */
#define GenerateHasOperator(OpName, OpSymb)		\
template <typename, typename = std::true_type>		\
struct has##OpName##_ : public std::false_type {	\
};							\
							\
template <typename T>					\
struct has##OpName##_					\
<							\
	T,						\
	typename std::is_convertible			\
	<						\
		decltype(T() OpSymb T()),		\
		bool					\
	>::type						\
> : public std::true_type {				\
};

/* Define required Operators checkers:
 * { ==, !=, <. >, <=, >= }
 */
GenerateHasOperator(	Greater,	>	)
GenerateHasOperator(	Lower,		<	)
GenerateHasOperator(	Equal,		==	)
GenerateHasOperator(	Different,	!=	)
GenerateHasOperator(	LowerOrEqual,	<=	)
GenerateHasOperator(	GreaterOrEqual,	>=	)

/* template list == [empty] ?
 * 	-> return true
 */
template
<
	typename T,
	typename... TList
>
struct all_same : std::true_type {
};

/* template list == element::[empty] ?
 * 	-> return is_same<T, element>
 */
template
<
	typename T,
	typename Head
>
struct all_same
<
	T,
	Head
> : std::is_same<T, Head> {
};

/* template list == element::[rest] ?
 * 	-> return is_same<T, element>::value
 * 		  && all_same<T, rest>::value
 */
template
<
	typename T,
	typename Head,
	typename... TList
>
struct all_same
<
	T,
	Head,
	TList...
> : std::integral_constant
	<
		bool,
		std::is_same<T, Head>::value && all_same<T, TList...>::value
	> {
};

/* Static check if T has every Operators from
 * { ==, !=, <, >, <=, >= }
 * -> Used for weight's type checking
 */
#define STATIC_HAS_OPS(T)				\
	all_same					\
	<						\
		std::true_type::type,			\
		hasEqual_<typename T>::type,		\
		hasDifferent_<typename T>::type,	\
		hasGreater_<typename T>::type,		\
		hasLowerOrEqual_<typename T>::type,	\
		hasLower_<typename T>::type,		\
		hasGreaterOrEqual_<typename T>::type	\
	>

/* Static check if T has Operators from
 * { ==, != }
 * -> Used for identifier's type checking
 */
#define STATIC_HAS_EQ(T)			\
	all_same				\
	<					\
		std::true_type::type,		\
		hasEqual_<T>::type,		\
		hasDifferent_<T>::type,		\
	>

/* Vertex class
 * defined by an identifier of template type
 */
template <typename Tid>
class Vertex {
public:
	Vertex(Tid id) { _id = id; }

	Tid getId() { return _id; }
	void setId(Tid id) { _id = id; }

private:
	Tid _id;
};

/* Edge class
 * defined by:
 * 	a Vertex& origin,
 * 	a Vertex& destination,
 * 	a weight of template type that has every Operators from
 * 	{ ==, !=, <, >, <=, >= }
 */
template <
	typename Tid,
	typename Tweight
	>
class Edge {
public:
	Edge(Vertex<Tid>& orig, Vertex<Tid>& dest,
	     Tweight weight) {
		_orig = orig;
		_dest = dest;
		_weight = weight;
	}

	Vertex<Tid>& getOrigin() { return _orig; }
	void setOrigin(Vertex<Tid> orig) { _orig = orig; }

	Vertex<Tid>& getDest() { return _dest; }
	void setDest(Vertex<Tid> dest) { _dest = dest; }

	Tweight getWeight() { return _weight; }

private:
	Vertex<Tid>&	_orig;
	Vertex<Tid>&	_dest;
	Tweight		_weight;
};

/* Pgraph class
 * defined by:
 * 	a vector of vertices,
 * 	a vector of edges,
 * TODO:
 * 	add an optional weight function that sets
 * 	the weight for each edge
 */
template <typename Tid, typename Tweight>
class Pgraph {
public:
	void pgraph_dump(void) {
		size_t i = 0;
		for (auto elt : _vertices) {
			std::cout << "Edge[" << i << "]:" << std:: endl;
			++i;
		}
	}

	void static_check(void) {
		static_assert(STATIC_HAS_OPS(Tweight)::value != 1,
				"Tweight is missing Operators from "
				"{ ==, <=, >=, <, >, != }"
				);

	/*
		static_assert(STATIC_HAS_EQ(Tid)::value != 1,
				"Tid is missing Operators from "
				"{ ==, != }"
				);
	*/
	}

private:

	std::vector<Vertex<Tid>> _vertices;
	std::vector<Edge<Tid, Tweight>> _edges;
};

#endif /* __GRAPH_H__ */
