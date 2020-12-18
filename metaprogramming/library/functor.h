#pragma once

#include <cassert>
#include <memory>

template<typename ResultType, typename ...ArgTypes>
class Functor;

template<typename ResultType, typename ...ArgTypes>
class Functor<ResultType(ArgTypes...)> {
public:
	Functor() = default;

	template<typename Function>
	Functor(Function function) : invoker_(new FreeFunctionHolder<Function>(function)) {}

	template<typename Function, class Class>
	Functor(Function Class::* function) : invoker_(new MemberFunctionHolder<Function, ArgTypes...>(function)) {}

	Functor(const Functor& other) : invoker_(other.invoker_->Clone()) {}

	Functor& operator=(const Functor& other) {
		this->invoker_ = other.invoker_->Clone();
	}

	ResultType operator()(ArgTypes... args) {
		assert(invoker_ != nullptr);
		return invoker_->Invoke(args...);
	}

private:
	class FunctionHolder;
	using Invoker = std::shared_ptr<FunctionHolder>;

	Invoker invoker_;

	class FunctionHolder {
	public:
		FunctionHolder() = default;

		virtual ~FunctionHolder() {}
		virtual ResultType Invoke(ArgTypes...) = 0;
		virtual Invoker Clone() = 0;

	private:
		FunctionHolder(const FunctionHolder&);
		FunctionHolder operator=(const FunctionHolder&);
	};

	template<typename Function>
	class FreeFunctionHolder : public FunctionHolder {
	public:
		FreeFunctionHolder(Function function) : FunctionHolder(), function_(function) {}
		
		virtual ResultType Invoke(ArgTypes... args) override {
			return function_(args...);
		}

		virtual Invoker Clone() override {
			return Invoker(new FreeFunctionHolder<Function>(function_));
		}
	
	private:
		Function function_;	
	};

	template<typename Function, class Class, typename ...OtherArgs>
	class MemberFunctionHolder : public FunctionHolder {
	public:
		using MemberFunction = Function Class::*;

		MemberFunctionHolder(MemberFunction member_function) : member_function_(member_function) {}

		virtual ResultType Invoke(Class object, OtherArgs... args) override {
			return (object.*member_function_)(args...);
		}

		virtual ResultType Invoke(Class* object, OtherArgs... args) {
			return (object->*member_function_)(args...);
		}

		virtual Invoker Clone() override {
			return Invoker(new MemberFunctionHolder<Function, Class>(member_function_));
		}

	private:
		MemberFunction member_function_;
	};
};
