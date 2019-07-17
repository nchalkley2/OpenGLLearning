#pragma once
#include <functional>
#include <type_traits>
#include <vector>

template<typename... paramsT>
class Delegate
{
public:
	using FunctionT = typename std::function<void(paramsT...)>;
	using FunctionPtrT = typename std::add_pointer<void(paramsT...)>::type;

	void Broadcast(paramsT... params)
	{
		for (const auto Function : Functions)
		{
			Function(std::forward<paramsT>(params)...);
		}
	};

	void AddCallback(const FunctionT& NewCallback)
	{
		Functions.push_back(NewCallback);
	};

	void AddCallback(FunctionPtrT Function)
	{
		Functions.push_back(std::function(Function));
	};

private:
	std::vector<FunctionT> Functions;
};

template<typename... paramsT>
struct AddStaticCallback
{
	using DelegateT = Delegate<paramsT...>;

	AddStaticCallback(DelegateT& Delegate, const typename DelegateT::FunctionT& NewCallback)
	{
		Delegate.AddCallback(NewCallback);
	};

	AddStaticCallback(DelegateT& Delegate, const typename DelegateT::FunctionPtrT& NewCallback)
	{
		Delegate.AddCallback(NewCallback);
	};
};