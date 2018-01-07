#pragma once
#include <string>
#include <set>
#include <vector>

namespace CommonUtilities
{
	struct STrieNode
	{
		static const int NumberOfChilds = 26;
		STrieNode* myChilds[NumberOfChilds];
		STrieNode* myParent = nullptr;
		char myChar = ' ';
		std::set<std::string> myWords;
	};

	class Trie
	{
	public:
		Trie();
		~Trie();

		void AddWord(STrieNode *aNode, const std::string &aWord);

		const std::vector<std::string> GetExamples(STrieNode *aNode, const std::string &aWord);

		STrieNode* GetRoot() const;
	private:
		void GetStrings(STrieNode* currentNode, std::set<std::string> &aWords, std::vector<std::string> &examples, const char aChar);
		STrieNode* myRoot;
	};
}

namespace CU = CommonUtilities;
