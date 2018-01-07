#pragma once

//hata livet
// template <typename ... T>
// class Subscriber : CU::Subscriber<T>...
// {
// public:
// 	inline void Subscribe();
// 	inline void Unsubscribe();
// 	inline void ChangePriority(const int aPriority);
// 
// private:
// 	template <class TFirst, class TSecond, class ... TArgs>
// 	inline void Subscribe();
// 
// 	template <typename TFirst>
// 	inline void Subscribe();
// 
// 	template <class TFirst, class TSecond, class ... TArgs>
// 	inline void Unsubscribe();
// 
// 	template <typename TFirst>
// 	inline void Unsubscribe();
// 
// 	template <class TFirst, class TSecond, class ... TArgs>
// 	inline void ChangePriority(const int aPriority);
// 
// 	template <typename TFirst>
// 	inline void ChangePriority(const int aPriority);
// };
// 
// template <typename ... T>
// template <typename TFirst>
// void Subscriber<T...>::Subscribe()
// {
// 	CU::Subscriber<TFirst>::Subscribe();
// }
// 
// template <typename ... T>
// inline void Subscriber<T...>::Subscribe()
// {
// 	Subscribe<T...>();
// }
// 
// template <typename ... T>
// template <class TFirst, class TSecond, class ... TArgs>
// inline void Subscriber<T...>::Subscribe()
// {
// 	CU::Subscriber<TFirst>::Subscribe();
// 	Subscribe<TSecond, TArgs...>();
// }
// 
// template <typename ... T>
// template <typename TFirst>
// void Subscriber<T...>::Unsubscribe()
// {
// 	CU::Subscriber<TFirst>::Unsubscribe();
// }
// 
// template <typename ... T>
// inline void Subscriber<T...>::Unsubscribe()
// {
// 	Unsubscribe<T...>();
// }
// 
// template <typename ... T>
// template <class TFirst, class TSecond, class ... TArgs>
// inline void Subscriber<T...>::Unsubscribe()
// {
// 	CU::Subscriber<TFirst>::Unsubscribe();
// 	Unsubscribe<TSecond, TArgs...>();
// }
// 
// template <typename ... T>
// template <typename TFirst>
// void Subscriber<T...>::ChangePriority(const int aPriority)
// {
// 	CU::Subscriber<TFirst>::ChangePriority(const int aPriority);
// }
// 
// template <typename ... T>
// inline void Subscriber<T...>::ChangePriority(const int aPriority)
// {
// 	ChangePriority<T...>(const int aPriority);
// }
// 
// template <typename ... T>
// template <class TFirst, class TSecond, class ... TArgs>
// inline void Subscriber<T...>::ChangePriority(const int aPriority)
// {
// 	CU::Subscriber<TFirst>::ChangePriority(const int aPriority);
// 	ChangePriority<TSecond, TArgs...>(const int aPriority);
// }
// 
