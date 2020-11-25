namespace TL {
	/* Add class to specific position in TypeList */

	template<class type_list, class T, size_t ind>
	struct Add {
		using result = TypeList<typename type_list::Head,
			typename Add<typename type_list::Tail, T, ind - 1>::result>;
	};

	template<class type_list, class T>
	struct Add<type_list, T, 0> {
		using result = TypeList<T, type_list>;
	};
}