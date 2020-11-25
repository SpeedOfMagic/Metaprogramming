#pragma once

#include "../library/TL/find_type_list_by_class.h"
#include "../library/TL/inheritance.h"
#include "../library/TL/type_list.h"

template<class type_list>
struct Factory {
	template<class T>
	T* Get() {
		return new typename TL::MostDerived<type_list, T>::result();
	}
};


template<typename T, class type_list, class ...type_lists>
struct FindAbstractFactory;

template<size_t, size_t, class type_list, class ...type_lists>
struct GetAbstractFactory {
	template<typename T>
	struct GetConcreteFactory {
		using needed_typelist = typename TL::FindTypeListByClass<T, type_list, type_lists...>::result;
		using result = Factory<needed_typelist>;
	};
};
