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

template<typename ONE>
constexpr void check_tuple_types_helper()
{
}

template<typename F, typename S, typename ...TailArgs>
constexpr void check_tuple_types_helper()
{
	if constexpr( ! std::is_same_v<F, S> )
		static_assert(false, "Tuple arguments must be the same type");
	check_tuple_types_helper<S, TailArgs...>();
}

template<typename ...Args>
constexpr void check_tuple_types(const std::tuple<Args...>& t)
{
	check_tuple_types_helper<Args...>();
}

