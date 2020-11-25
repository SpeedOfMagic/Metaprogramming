#pragma once

struct NullType {};

template<typename ...Args>
struct TypeList {
	using Head = NullType;
	using Tail = NullType;
};

using EmptyTypeList = TypeList<>;

template<typename T>
struct TypeList<T> {
	using Head = T;
	using Tail = EmptyTypeList;
};

template<typename H, typename ...T>
struct TypeList<H, T...> {
	using Head = H;
	using Tail = TypeList<T...>;
};

template<typename H, typename ...T>
struct TypeList<H, TypeList<T...>> {
	using Head = H;
	using Tail = TypeList<T...>;
};
