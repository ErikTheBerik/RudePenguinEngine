#pragma once
#include <assert.h>

namespace CU = CommonUtilities;

namespace CommonUtilities
{
    template<typename T>
    class DoubleLinkedList
    {
    public:

		#pragma region Node
		class Node
		{
		public:
			Node(const T& aValue)
			{
				myData = aValue;
				myNextNode = nullptr;
				myPreviousNode = nullptr;
			}
			~Node()
			{
			}
			Node* GetNext() const
			{
				return myNextNode;
			}
			Node* GetPrevious() const
			{
				return myPreviousNode;
			}
			T GetData() const
			{
				return myData;
			}
		private:
			friend class DoubleLinkedList;
			T myData;
			Node* myNextNode;
			Node* myPreviousNode;
		};
		#pragma endregion Node class used by the list

		DoubleLinkedList();

		Node* GetFirstNode(void) const;
        Node* GetLastNode(void) const;

		unsigned short Size() const;
		bool Empty() const;

        void InsertNodeBeforeNode(Node* aNode, Node* aNodeToInsert);
        void InsertNodeSorted(Node* aNodeToInsert);
        void InsertNodeSorted(const T& aValueToInsert);
		void Add(Node* aNodeToAdd);

		void DeleteAll();
        void DeleteNode(Node* aNodeToDelete);
        void DeleteNode(const T& aValueToDelete);

        Node* Find(const T& aValue) const;

		inline Node* operator[](const unsigned short& aIndex);

	private:
		Node* myFirstNode;
		Node* myLastNode;
		unsigned short myCount;
    };
	

//////DEFINITIONS:///////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	//Initializes first and last node to nullptr
	DoubleLinkedList<T>::DoubleLinkedList()
	{
		myFirstNode = nullptr;
		myLastNode = nullptr;
		myCount = 0;
	}

	template<typename T>
	//Returns the head of the list.
	//@return Returns the first node of the list or nullptr if the list is empty.
	typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::GetFirstNode(void) const
	{
		return myFirstNode;
	}

	template<typename T>
	//Returns the tail of the list.
	//@return Returns the last node of the list or nullptr if the list is empty.
	typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::GetLastNode(void) const
	{
		return myLastNode;
	}

	template<typename T>
	//Returns the size of the list.
	unsigned short DoubleLinkedList<T>::Size() const
	{
		/*unsigned short count = 0;
		
		Node* currentNode = GetFirstNode();
		while (currentNode != nullptr)
		{
			++count;
			currentNode = currentNode->myNextNode;
		}

		return count;*/
		return myCount;
	}

	template<typename T>
	//Returns true if the list is empty.
	bool DoubleLinkedList<T>::Empty() const
	{
		if (myFirstNode == nullptr)
		{
			return true;
		}

		return false;
	}

	template<typename T>
	//Inserts a node after another node.
	//@param  aNode gives the node which to place the new node BEFORE (aNode is pushed back in the list)
	//@param  aNodeToInsert gives the node to insert into the list
	void DoubleLinkedList<T>::InsertNodeBeforeNode(Node* aNode, Node* aNodeToInsert)
	{
		assert(aNodeToInsert != nullptr && "Attempted to insert a nullptr Node into DoubleLinkedList");

		if (Empty() == true)
		{
			myFirstNode = aNodeToInsert;
			myLastNode = aNodeToInsert;
		}
		else if (aNode == nullptr) //We want aNodeToInsert to be the last element
		{
			Add(aNodeToInsert);
		}
		else if (aNode == myFirstNode) //Insert as new first element
		{
			myFirstNode->myPreviousNode = aNodeToInsert;
			aNodeToInsert->myNextNode = aNode;
			myFirstNode = aNodeToInsert;
		}
		else
		{
			aNodeToInsert->myPreviousNode = aNode->myPreviousNode;
			aNodeToInsert->myNextNode = aNode;
			aNode->myPreviousNode->myNextNode = aNodeToInsert;
			aNode->myPreviousNode = aNodeToInsert;
		}
		myCount++;
	}

	template<typename T>
	//Insert a node sorted in decending order. The value of the node to insert must be comparable using the < operator.
	//@param  aNodeToInsert gives the node to insert.
	void DoubleLinkedList<T>::InsertNodeSorted(Node* aNodeToInsert)
	{
		Node* currentNode = GetFirstNode();
		while (currentNode != nullptr)
		{
			if (currentNode->myData < aNodeToInsert->myData)
			{
				break;
			}

			currentNode = currentNode->myNextNode;
		}

		if (currentNode == nullptr)
		{
			Add(aNodeToInsert);
		}
		else
		{
			InsertNodeBeforeNode(currentNode, aNodeToInsert);
		}
		myCount++;
	}

	template<typename T>
	//Insert a node sorted in decending order. The value to insert must be comparable using the < operator.
	//@param  aValueToInsert gives the value to insert.
	void DoubleLinkedList<T>::InsertNodeSorted(const T& aValueToInsert)
	{
		Node* currentNode = GetFirstNode();
		while (currentNode != nullptr)
		{
			if (currentNode->myData < aValueToInsert)
			{
				break;
			}

			currentNode = currentNode->myNextNode;
		}

		if (currentNode == nullptr)
		{
			Add(new Node(aValueToInsert));
		}
		else
		{
			InsertNodeBeforeNode(currentNode, new Node(aValueToInsert));
		}
		myCount++;
	}

	template<typename T>
	//Add aNodeToAdd to the back of the list (as the tail)
	void DoubleLinkedList<T>::Add(Node* aNodeToAdd)
	{
		assert(aNodeToAdd != nullptr && "Attempted to Add nullptr Node to DoubleLinkedList");

		if (Empty() == true)
		{
			myFirstNode = aNodeToAdd;
			myLastNode = aNodeToAdd;
		}
		else
		{
			aNodeToAdd->myPreviousNode = myLastNode;
			myLastNode->myNextNode = aNodeToAdd;
			myLastNode = aNodeToAdd;
			aNodeToAdd->myNextNode = myFirstNode; //just in case
			myFirstNode->myPreviousNode = myLastNode;
		}
		myCount++;
	}

	template<typename T>
	void DoubleLinkedList<T>::DeleteAll()
	{
		std::cout << myCount << std::endl;
		Node* node = myLastNode;
		if (node != nullptr)
		{
			while (node != myFirstNode)
			{
				Node* temp = node->GetPrevious();
				delete node;
				node = temp;
				temp->myNextNode = nullptr;
			}

			delete node;
		}
		myLastNode = nullptr;
		myFirstNode = nullptr;
		myCount = 0;
	}

	template<typename T>
	//Deletes the given node from the list.
	//!!Asserts if the node isn't found.
	//@param  aNodeToDelete gives the node to delete from the list.
	void DoubleLinkedList<T>::DeleteNode(Node* aNodeToDelete)
	{
		assert(aNodeToDelete != nullptr && "DeleteNode in DoubleLinkedList attempted to delete an invalid Node");
		assert(Empty() != true && "Attempted to DeleteNode from an empty DoubleLinkedList");

		Node* currentNode = GetFirstNode();
		while (currentNode != nullptr)
		{
			if (currentNode == aNodeToDelete)
			{
				if (currentNode == myFirstNode && currentNode == myLastNode)
				{
					delete currentNode;
					myFirstNode = nullptr;
					myLastNode = nullptr;
					myCount--;
					return;
				}
				else if (currentNode == myFirstNode)
				{
					myFirstNode = currentNode->myNextNode;
					currentNode->myNextNode->myPreviousNode = nullptr;
					delete currentNode;
					myCount--;
					return;
				}
				else if (currentNode == myLastNode)
				{
					myLastNode = currentNode->myPreviousNode;
					currentNode->myPreviousNode->myNextNode = nullptr;
					delete currentNode;
					myCount--;
					return;
				}
				else
				{
					currentNode->myNextNode->myPreviousNode = currentNode->myPreviousNode;
					currentNode->myPreviousNode->myNextNode = currentNode->myNextNode;
					delete currentNode;
					myCount--;
					return;
				}
			}

			currentNode = currentNode->myNextNode;
		}
		assert(false && "DeleteNode in DoubleLinkedList was unable to find the specified Node");
	}

	template<typename T>
	//Deletes the first node with the given value from the list.
	//!!Asserts if the value isn't found.
	//@param  aValueToDelete gives the value to delete from the list.
	void DoubleLinkedList<T>::DeleteNode(const T& aValueToDelete)
	{
		DeleteNode(Find(aValueToDelete));
	}

	template<typename T>
	// Searches the list for the given value and if found returns the first node with the value.
	//@param  aValue gives the value to search for
	//@return Returns the first node with the given value or nullptr if the value isn't found.
	typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::Find(const T& aValue) const
	{
		Node* currentNode = GetFirstNode();
		while (currentNode != nullptr)
		{
			if (currentNode->myData == aValue)
			{
				return currentNode;
			}

			currentNode = currentNode->myNextNode;
		}

		return nullptr;
	}

	template<typename T>
	inline typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::operator[](const unsigned short & aIndex)
	{
		assert((aIndex >= myCount) == false && "DoubleLinkedList out of bounds");
		Node* node = myFirstNode;
		unsigned short counter = 0;
		while(counter < aIndex)
		{
			node = node->myNextNode;
			counter++;
		}

		return node;
	}

} namespace CU = CommonUtilities;
