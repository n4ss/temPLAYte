#ifndef __GRAPH_H__
# define __GRAPH_H__

//#include <pair>
//#include <string>
#include <unistd.h>
#include <iostream>

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

GenerateHasOperator(	Greater,	>	)
GenerateHasOperator(	Lower,		<	)
GenerateHasOperator(	Equal,		==	)
GenerateHasOperator(	LowerOrEqual,	<=	)
GenerateHasOperator(	GreaterOrEqual,	>=	)

/* template list == [empty] -> return false */
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
 * 	-> return is_same<T, element>::value && all_same<T, rest>::value
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

#define HAS_OPS(T)				\
	all_same				\
	<					\
		std::true_type::type,		\
		hasEqual_<T>::type,		\
		hasGreater_<T>::type,		\
		hasLowerOrEqual_<T>::type,	\
		hasLower_<T>::type,		\
		hasGreaterOrEqual_<T>::type	\
	>

/*
template
<
	typename T
>
bool hasOps <T, typename = std::false_type> () {
	std::cout << "LOOOOOOOOOOOOOOOOOOL" << std::endl;
	return true;
}

template
<
	typename T, 
	class = typename std::enable_if
	<
		hasGreater_<T>::value
		& hasLower_<T>::value
		& hasEqual_<T>::value
		& hasLowerOrEqual_<T>::value
		& hasGreaterOrEqual_<T>::value
	>::type
>
bool hasOps () {
	std::cout << "LOOOOOOOOOOOOOOOOOOL" << std::endl;
	return true;
}
*/

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
