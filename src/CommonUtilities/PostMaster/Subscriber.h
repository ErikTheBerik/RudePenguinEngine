#pragma once
#include "Message.h"

namespace CommonUtilities
{
	class PostMaster;

	enum class NotifyResponse : bool
	{
		Stop = false,
		Continue = true
	};

	class ISubscriber
	{
	public:
		virtual ~ISubscriber()
		{
		}

		virtual NotifyResponse Notify(const Message &aMessage) = 0;
		int myPriority = 0;
	};

	template <typename T>
	class _Subscriber : public ISubscriber
	{
	public:
		virtual NotifyResponse Notify(const T &aMessage) = 0;

		NotifyResponse Notify(const Message &aMessage) override
		{
			return Notify(static_cast<const T&>(aMessage));
		}

		void ChangePriority(const int aNewPriority)
		{
			myPriority = aNewPriority;
			if (myPostMaster->Unsubscribe(this) == CompletedTask::Success)
			{
				myPostMaster->Subscribe(this);
			}
		}

		void Subscribe(PostMaster* aPostMaster = nullptr)
		{
			if (aPostMaster == nullptr)
			{
				myPostMaster = PostMaster::GetInstance();
			}
			else
			{
				myPostMaster = aPostMaster;
			}

			myPostMaster->Subscribe(this);
		}

		void Unsubscribe(PostMaster* aPostMaster = nullptr)
		{
			if (aPostMaster == nullptr)
			{
				aPostMaster = myPostMaster;
			}

			aPostMaster->Unsubscribe(this);
		}

	protected:
		_Subscriber(int aPriority = 0, bool aSubscribe = false, PostMaster* aPostMaster = nullptr)
		{
			myPriority = aPriority;
			if (aPostMaster == nullptr)
			{
				myPostMaster = PostMaster::GetInstance();
			}
			else
			{
				myPostMaster = aPostMaster;
			}
			if (aSubscribe == false)
				return;
			myPostMaster->Subscribe(this);
		}

		_Subscriber(bool aSubscribe, int aPriority = 0, PostMaster* aPostMaster = nullptr)
			:_Subscriber(aPriority, aSubscribe, aPostMaster)
		{
		}

		virtual ~_Subscriber()
		{
			myPostMaster->Unsubscribe(this);
		}

		PostMaster *myPostMaster;
	private:

		friend class PostMaster;
		static int MessageID;
	};
	template <typename T>
	int _Subscriber<T>::MessageID = -1;
}

namespace CommonUtilities
{
	//hata livet
	template <typename ... T>
	class Subscriber : public _Subscriber<T>...
	{
	public:
		inline void Subscribe();
		inline void Unsubscribe();
		inline void ChangePriority(const int aPriority);

	private:
		template <class TFirst, class TSecond, class ... TArgs>
		inline void Subscribe();

		template <typename TFirst>
		inline void Subscribe();

		template <class TFirst, class TSecond, class ... TArgs>
		inline void Unsubscribe();

		template <typename TFirst>
		inline void Unsubscribe();

		template <class TFirst, class TSecond, class ... TArgs>
		inline void ChangePriority(const int aPriority);

		template <typename TFirst>
		inline void ChangePriority(const int aPriority);
	};

	template <typename ... T>
	template <typename TFirst>
	void Subscriber<T...>::Subscribe()
	{
		_Subscriber<TFirst>::Subscribe();
	}

	template <typename ... T>
	inline void Subscriber<T...>::Subscribe()
	{
		Subscribe<T...>();
	}

	template <typename ... T>
	template <class TFirst, class TSecond, class ... TArgs>
	inline void Subscriber<T...>::Subscribe()
	{
		_Subscriber<TFirst>::Subscribe();
		Subscribe<TSecond, TArgs...>();
	}

	template <typename ... T>
	template <typename TFirst>
	void Subscriber<T...>::Unsubscribe()
	{
		_Subscriber<TFirst>::Unsubscribe();
	}

	template <typename ... T>
	inline void Subscriber<T...>::Unsubscribe()
	{
		Unsubscribe<T...>();
	}

	template <typename ... T>
	template <class TFirst, class TSecond, class ... TArgs>
	inline void Subscriber<T...>::Unsubscribe()
	{
		_Subscriber<TFirst>::Unsubscribe();
		Unsubscribe<TSecond, TArgs...>();
	}

	template <typename ... T>
	template <typename TFirst>
	void Subscriber<T...>::ChangePriority(const int aPriority)
	{
		_Subscriber<TFirst>::ChangePriority( aPriority);
	}

	template <typename ... T>
	inline void Subscriber<T...>::ChangePriority(const int aPriority)
	{
		ChangePriority<T...>(aPriority);
	}

	template <typename ... T>
	template <class TFirst, class TSecond, class ... TArgs>
	inline void Subscriber<T...>::ChangePriority(const int aPriority)
	{
		_Subscriber<TFirst>::ChangePriority(aPriority);
		ChangePriority<TSecond, TArgs...>(aPriority);
	}
}

namespace CU = CommonUtilities;