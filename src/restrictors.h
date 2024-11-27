/**
 * @file restrictors.h
 * @brief Structs an expressions to use in SFINAE
 * @date Nov 2024
*/
#pragma once

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T,
	std::void_t<
	decltype(std::begin(std::declval<T&>())),
	decltype(std::end(std::declval<T&>()))
	>
> : std::true_type {};

template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

// -----------

template <typename T, typename = void>
struct is_string : std::false_type {};

template <typename T>
struct is_string<T,
	typename std::is_same<T, std::string>::type
> : std::true_type {};

template <typename T>
constexpr bool is_string_v = std::is_same_v<T, std::string>;

// -----------

template <typename T, typename = void>
struct is_tuple : std::false_type {};

template <typename ...T> struct is_tuple<std::tuple<T...>> : std::true_type {};

template <typename T>
constexpr bool is_tuple_v = is_tuple<T>::value;


// -----------

template<typename ...Args>
struct check_tuple_types;

template<typename ONE>
struct check_tuple_types<ONE>
{
	static constexpr bool value = true;
};

template<typename F, typename S, typename ...TailArgs>
struct check_tuple_types<F, S, TailArgs...>
{
	static constexpr bool value = std::is_same_v<F, S> ?
		check_tuple_types<S, TailArgs...>::value :
		false;
};

template<typename ...Args>
constexpr bool check_tuple_types_v = check_tuple_types<Args...>::value;