#include "Trie.h"
#pragma warning (disable: 4244)
#include <algorithm>
#pragma warning (default: 4244)
#include <cctype>

namespace CommonUtilities
{
	Trie::Trie()
	{
		myRoot = new STrieNode();
	}


	Trie::~Trie()
	{
		delete myRoot;
		myRoot = nullptr;
	}

	void Trie::AddWord(STrieNode * aNode, const std::string &aWord)
	{
		// if end
		if (aWord == "")
		{
			return;
		}

		// set values
		aNode->myWords.emplace(aWord);

		// next node
		char first = aWord.at(0);
		int i = 0;
		int length = STrieNode::NumberOfChilds;

		while (i < length)
		{
			if (aNode->myChilds[i] == nullptr)
			{
				aNode->myChilds[i] = new STrieNode();
				break;
			}
			else if (aNode->myChilds[i]->myChar == first)
			{
				break;
			}
			i++;
		}

		aNode->myChilds[i]->myChar = first;
		aNode->myChilds[i]->myParent = aNode;
		AddWord(aNode->myChilds[i], aWord.substr(1, aWord.size() - 1));
	}

	const std::vector<std::string> Trie::GetExamples(STrieNode *aNode, const std::string &aWord)
	{
		std::vector<std::string> examples;
		std::string lower = aWord;
		std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
		int i = 0;
		int currentWordIndex = 0;
		char first = lower.at(0);
		int length = STrieNode::NumberOfChilds;
		STrieNode* currentNode = aNode;
		char currentChar = currentNode->myChar;
		currentChar = static_cast<char>(std::tolower(currentChar));
		bool hasAny = false;
		while (i < length)
		{
			if (currentNode->myChilds[i] != nullptr)
			{
				currentChar = currentNode->myChilds[i]->myChar;
				currentChar = static_cast<char>(std::tolower(currentChar));
				if (currentChar == first)
				{
					hasAny = true;
					if (currentWordIndex + 1 < (int)aWord.size())
					{
						first = lower.at(currentWordIndex + 1);
						int j = 0;
						while (j < STrieNode::NumberOfChilds)
						{
							if (currentNode->myChilds[i]->myChilds[j] != nullptr)
							{
								char chechChar = currentNode->myChilds[i]->myChilds[j]->myChar;
								chechChar = static_cast<char>(std::tolower(chechChar));
								if (chechChar == first)
								{
									currentWordIndex++;
									currentNode = currentNode->myChilds[i]->myChilds[j];

									currentChar = currentNode->myChar;
									currentChar = static_cast<char>(std::tolower(currentChar));

									if (currentWordIndex + 1 < (int)aWord.size())
									{
										first = lower.at(currentWordIndex + 1);
										currentWordIndex++;
									}
									i = -1;
									break;
								}
								j++;
							}
							else
							{
								hasAny = false;
								break;
							}
						}
					}
					else
					{
						GetStrings(currentNode->myChilds[i], currentNode->myChilds[i]->myWords, examples, aWord.at(0));
						return examples;
					}
				}
			}
			else
			{
				if (hasAny == true)
				{
					GetStrings(currentNode, currentNode->myWords, examples, aWord.at(0));
				}
				return examples;
			}
			i++;
		}

		return examples;
	}

	void Trie::GetStrings(STrieNode* currentNode, std::set<std::string> &aWords, std::vector<std::string> &examples, const char aChar)
	{
		for (auto &string : aWords)
		{
			std::string parentString = "";
			std::string temp = "";
			STrieNode *parent = currentNode;
			while (parent != nullptr)
			{
				if (parent->myChar != ' ')
				{
					temp = std::string(1, parent->myChar);
					parentString = temp + parentString;
				}
				else
				{
					if (parentString == "")
					{
						temp = std::string(1, aChar);
						parentString = temp + parentString;
					}
				}
				parent = parent->myParent;
			}
			examples.push_back(parentString + string);
		}
	}

	STrieNode* Trie::GetRoot() const
	{
		return myRoot;
	}
}