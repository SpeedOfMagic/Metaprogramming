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

/*===============================================*/

template<class TypeList>
struct Size {
	constexpr static size_t size = 1 + Size<typename TypeList::Tail>::size;
};

template<>
struct Size<EmptyTypeList> {
	constexpr static size_t size = 0;
};

/*===============================================*/

template<class type_list, size_t ind>
struct TypeAt {
	using value = typename TypeAt<typename type_list::Tail, ind - 1>::value;
};

template<class type_list>
struct TypeAt<type_list, 0> {
	using value = typename type_list::Head;
};

/*===============================================*/

template<class type_list, class T>
struct IndexOf {
	constexpr static size_t value = 1 + IndexOf<typename type_list::Tail, T>::value;
};

template<class type_list>
struct IndexOf<type_list, typename type_list::Head> {
	constexpr static size_t value = 0;
};

template<class T>
struct IndexOf<EmptyTypeList, T> {
	constexpr static size_t value = UINT64_MAX;
};

/*===============================================*/

template<class type_list, class T, size_t ind>
struct Add {
	using result = TypeList<typename type_list::Head,
							typename Add<typename type_list::Tail, T, ind - 1>::result>;
};

template<class type_list, class T>
struct Add<type_list, T, 0> {
	using result = TypeList<T, type_list>;
};

/*===============================================*/

template<class type_list, typename T>
struct Remove {
	using result = TypeList<typename type_list::Head, 
							typename Remove<typename type_list::Tail, T>::result>;
};

template<class type_list>
struct Remove<type_list, typename type_list::Head> {
	using result = typename type_list::Tail;
};

template<typename T>
struct Remove<EmptyTypeList, T> {
	using result = EmptyTypeList;
};

/*===============================================*/

template<class type_list, class T>
struct RemoveAll {
	using result = TypeList<typename type_list::Head, 
				       typename RemoveAll<
					       typename type_list::Tail, T
					   >::result
				   >;
};

template<class type_list>
struct RemoveAll<type_list, typename type_list::Head> {
	using result = typename RemoveAll<
								typename type_list::Tail, typename type_list::Head
							>::result;
};

template<typename T>
struct RemoveAll<EmptyTypeList, T> {
	using result = EmptyTypeList;
};

/*===============================================*/

template<class type_list>
struct NoDuplicates {
	using result = TypeList<
				       typename type_list::Head,
					   typename NoDuplicates<
					       typename RemoveAll<
						       typename type_list::Tail, typename type_list::Head
						   >::result
					   >::result
				   >;
};

template<>
struct NoDuplicates<EmptyTypeList> {
	using result = EmptyTypeList;
};

/*===============================================*/
#pragma once
