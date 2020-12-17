#pragma once

#include <memory>

template<typename ResultType, typename ...ArgTypes>
class Functor;

template<typename ResultType, typename ...ArgTypes>
class Functor<ResultType(ArgTypes...)> {
public:
	Functor() = default;

	template<typename Function>
	Functor(Function function) : function_holder_(new FreeFunctionHolder<Function>(function)) {}

	ResultType operator()(ArgTypes... args) {
		return function_holder_->Invoke(args...);
	}

private:
	class FunctionHolder {
	public:
		FunctionHolder() = default;
		virtual ~FunctionHolder() {}
		virtual ResultType Invoke(ArgTypes...) = 0;
	};

	template<typename Function>
	class FreeFunctionHolder : public FunctionHolder {
	public:
		FreeFunctionHolder(Function function) : FunctionHolder(), function_(function) {}
		
		virtual ResultType Invoke(ArgTypes... args) override {
			return function_(args...);
		}
	
	private:
		Function function_;	
	};

	std::shared_ptr<FunctionHolder> function_holder_;
};
