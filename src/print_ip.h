/**
 * @file print_ip.h
 * @brief Printing values as ip addresses
 * @date Nov 2024
*/
#pragma once
#include <iostream>
#include <tuple>
#include "restrictors.h"

// TODO remove
#ifdef _MSC_VER
#define PRINT_F __FUNCSIG__
#else
#define PRINT_F __PRETTY_FUNCTION__
#endif

/// \brief Prints a POD value as ip address
/// \param v POD value
/// \param os output stream
/// \param fake unused
template <typename T,
	class E = std::enable_if_t< std::is_pod_v<T> >
>
void print_ip(T v, std::ostream &os = std::cout, [[maybe_unused]] std::integral_constant<int, 0> fake = {})
{
	uint8_t *start = reinterpret_cast<uint8_t*>(&v) + sizeof(T) - 1;
	uint8_t* end = reinterpret_cast<uint8_t*>(&v);
	while (true)
	{
		os << (int)(*start);
		if (start != end)
			os << ".";
		else
			break;
		start--;
	}
}

/// \brief Prints container values as ip address
/// \param container an iterable container
/// \param os output stream
/// \param fake unused
template< typename T,
	class E = std::enable_if_t< is_iterable_v<T> && !is_string_v<T> >
>
void print_ip(const T &container, std::ostream& os = std::cout, [[maybe_unused]] std::integral_constant<int, 1> fake = {})
{
	auto it = container.begin();
	if (it != container.end())
	{
		os << *it;
		++it;
	}
	for (; it != container.end(); ++it)
		os << "." << *it;
}


/// \brief Prints string as is
/// \param s string
/// \param os output stream
/// \param fake unused
template <typename T,
	class E = std::enable_if_t< is_string_v<T> >
>
auto print_ip(const T &s, std::ostream& os = std::cout, [[maybe_unused]] std::integral_constant<int, 2> fake = {})
{
	os << s;
}


/// \brief Prints tuple values separated by '.'
/// \param t tuple
/// \param os output stream
template<size_t IDX, size_t SZ, typename T>
void tuple_print(const T& t, std::ostream& os = std::cout)
{
	os << std::get<IDX>(t);
	if constexpr (IDX < SZ - 1)
	{
		os << ".";
		tuple_print<IDX + 1, SZ>(t ,os);
	}
}

/// \brief Prints tuple values separated by '.'
/// \param t tuple
/// \param os output stream
/// \param fake unused
/// \details tuple types must be the same
template <typename ...Args,
	class E = std::enable_if_t< is_tuple_v<std::tuple<Args...>> && check_tuple_types_v<Args...> >
>
void print_ip(const std::tuple<Args...>& t, std::ostream& os = std::cout, [[maybe_unused]] std::integral_constant<int, 3> fake = {})
{
	constexpr size_t SZ = std::tuple_size<std::tuple<Args...>>();
	tuple_print<0, SZ, std::tuple<Args...>>(t, os);
}