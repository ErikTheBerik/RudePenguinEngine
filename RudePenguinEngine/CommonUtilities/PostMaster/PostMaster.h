#pragma once
#include <vector>
#include "Subscriber.h"
#include "../Containers/GrowingArray.h"

namespace CommonUtilities
{
#define DEFAULT_POSTMASTER_NAME "Master"

	enum class CompletedTask : bool
	{
		Failed = false,
		Success = true
	};

	class PostMaster
	{
	public:
		template <typename ... T>
		static PostMaster* GetInstance(const T* ... aNames)
		{
			if (MasterInstance == nullptr)
			{
				return CreateMaster(aNames...);
			}
			return MasterInstance->GetInstances(aNames...);
		}

		static PostMaster* GetInstance()
		{
			if (MasterInstance == nullptr)
			{
				MasterInstance = new PostMaster(DEFAULT_POSTMASTER_NAME);
			}
			return MasterInstance;
		}


		template<typename T>
		void Subscribe(_Subscriber<T> *aSubscriber)
		{
			if (_Subscriber<T>::MessageID == -1)
			{
				mySubscribers.push_back(std::vector<ISubscriber*>());
				_Subscriber<T>::MessageID = static_cast<int>(mySubscribers.size()) - 1;
			}
			const int messageID = _Subscriber<T>::MessageID;

			for (size_t i = 0; i < mySubscribers[messageID].size(); i++)
			{
				if (aSubscriber == mySubscribers[messageID][i])
				{
					return;
				}
			}

			size_t index = FindIndex(messageID, aSubscriber->myPriority);

			if (index == mySubscribers[messageID].size())
			{
				mySubscribers[messageID].push_back(aSubscriber);
			}
			else
			{
				mySubscribers[messageID].insert(mySubscribers[messageID].begin() + index, aSubscriber);
			}
		}

		template<typename T>
		CompletedTask Unsubscribe(_Subscriber<T> *aSubscriber)
		{
			const int messageID = _Subscriber<T>::MessageID;
			if (messageID == -1 || aSubscriber == nullptr)
			{
				return CompletedTask::Failed;
			}


			for (int i = static_cast<int>(mySubscribers[messageID].size()) - 1; i >= 0; i--)
			{
				if (mySubscribers[messageID][i] == aSubscriber)
				{
					mySubscribers[messageID].erase(mySubscribers[messageID].begin() + i);

				}
			}
			return CompletedTask::Success;
		}

		template<typename T = Message>
		void Publish(const T &aMessage)
		{
			const int messageID = _Subscriber<T>::MessageID;
			if (messageID == -1)
			{
				return;
			}

			for (int i = static_cast<int>(mySubscribers[messageID].size()) - 1; i >= 0; i--)
			{
				if (mySubscribers[messageID][i] == nullptr)
					continue;
				if (mySubscribers[messageID][i]->Notify(aMessage) == NotifyResponse::Stop)
					break;
			}

			for (size_t i = 0; i < myChildren.Size(); i++)
			{
				myChildren[i]->Publish(aMessage);
			}
		}

	private:
		void Clear(bool aRemoveChildren = false, bool aClearChildren = false)
		{
			if (aRemoveChildren == true)
			{
				for (size_t i = 0; i < myChildren.Size(); i++)
				{
					delete myChildren[i];
					myChildren[i] = nullptr;
				}
				myChildren.RemoveAll();
			}
			if (aClearChildren == true)
			{
				for (size_t i = 0; i < myChildren.Size(); i++)
				{
					myChildren[i]->Clear(aClearChildren);
				}
			}
			for (size_t i = 0; i < mySubscribers.size(); i++)
			{
				mySubscribers[i].clear();
			}
		}

		const size_t FindIndex(const int aMessageID, const int aPriority) const
		{
			if (mySubscribers[aMessageID].size() == 0 || aPriority <= mySubscribers[aMessageID][0]->myPriority)
			{
				return 0;
			}

			for (size_t i = 0; i < mySubscribers[aMessageID].size(); i++)
			{
				if (mySubscribers[aMessageID][i]->myPriority >= aPriority)
				{
					return i;
				}
			}

			return mySubscribers[aMessageID].size();
		}

		template <typename ... T >
		PostMaster* GetInstances(const char * aFirstName, const T* ... aNames)
		{
			PostMaster* current = this;
			if (aFirstName == current->myName)
				return current->GetInstances(aNames...);
			current = current->GetChild(aFirstName);
			return current->GetInstances(aNames...);
		}

		template <typename ... T >
		static PostMaster* CreateMaster(const char * aFirstName, const T* ... aNames)
		{
			MasterInstance = new PostMaster(aFirstName);
			return MasterInstance->GetInstances(aNames...);
		}

		PostMaster* GetInstances()
		{
			return this;
		}

		PostMaster* CreatePostMaster(const std::string& aName)
		{
			myChildren.Add(new PostMaster(aName));

			for (size_t i = 0; i < mySubscribers.size(); i++)
			{
				myChildren[myChildren.Size() - 1]->AddList();
			}
			return myChildren[myChildren.Size() - 1];
		}

		void AddList()
		{
			for (size_t i = 0; i < myChildren.Size(); i++)
			{
				myChildren[i]->AddList();
			}

			mySubscribers.push_back(std::vector<ISubscriber*>());
		}

		PostMaster* GetChild(const std::string &aName)
		{
			for (size_t i = 0; i < myChildren.Size(); i++)
			{
				if (myChildren[i]->myName == aName)
					return myChildren[i];
			}

			return CreatePostMaster(aName);
		}

		PostMaster(const std::string& aName)
		{
			myName = aName;
			//mySubscribers.Init(100);
			myChildren.Init(1);
		}

		~PostMaster()
		{
			for (size_t i = 0; i < myChildren.Size(); i++)
			{
				delete myChildren[i];
				myChildren.RemoveCyclicAtIndex(i);
			}
		}
		std::vector<std::vector<ISubscriber*>> mySubscribers;
		GrowingArray<PostMaster*, size_t> myChildren;
		static PostMaster* MasterInstance;
		std::string myName = "Main";
	};
}

namespace CU = CommonUtilities;