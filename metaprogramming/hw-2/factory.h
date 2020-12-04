#pragma once

#include "../library/TL/has_derived_and_constructible.h"
#include "../library/TL/most_derived_and_constructible.h"
#include "../library/TL/find_required_type_list.h"
#include "../library/TL/find_type_list_by_class.h"

template<class type_list, class ...type_lists>
struct Factory {
	template<class T>
	T* Get() {
		using obj_class = typename TL::MostDerivedAndConstructible<type_list, T>::result;
		return GetObject<T, obj_class, TL::HasDerivedAndConstructible<type_list, T>::result>::Get();
	}

	template<typename parent, typename T, bool found_class>
	struct GetObject;

	template<typename parent, typename T>
	struct GetObject<parent, T, true> {
		static parent* Get() { return new T();  }
	};

	template<typename parent, typename T>
	struct GetObject<parent, T, false> {
		using parent_type_list = typename TL::FindRequiredTypeList<TypeList<type_lists...>, type_list>::result;
		using new_factory = Factory<parent_type_list, type_lists...>;

		static parent* Get() {
			return new_factory().Get<parent>();
		}
	};
};


// Get required factory by class name
template<size_t, size_t, class type_list, class ...type_lists>
struct GetAbstractFactory {
	template<typename T>
	struct GetConcreteFactory {
		using needed_typelist = typename TL::FindTypeListByClass<T, type_list, type_lists...>::result;
		using result = Factory<needed_typelist, type_list, type_lists...>;
	};
};
