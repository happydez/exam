#pragma once

#include <iostream>
#include <queue>

using namespace std;

class TrieTree
{
	private:

		static const int N = 26;

		struct TrieNode
		{
			bool isTerminal;
			TrieNode* children[N];

			TrieNode()
			{
				for (int i = 0; i < N; i++) {
					children[i] = nullptr;
				}

				isTerminal = false;
			}
		};

		void insertHelper(TrieNode* p, string& word) {
			for (auto ch : word) {
				int index = tolower(ch) - 'a';

				if (index < 0 || index > 26) {
					throw out_of_range("symbol out of range");
				}

				if (p->children[index] == nullptr) {
					p->children[index] = new TrieNode();
				}

				p = p->children[index];
			}

			p->isTerminal = true;
		}

		void removeHelper(string& word) {
			TrieNode* p = searchHelper(root, word);

			if ((p != nullptr) && (p->isTerminal)) {
				p->isTerminal = false;
			}
		}

		TrieNode* searchHelper(TrieNode* p, string& word) {
			for (auto ch : word) {
				int index = tolower(ch) - 'a';

				if (index < 0 || index > 26) {
					throw out_of_range("symbol out of range");
				}

				if ((p == nullptr) || (p->children[index] == nullptr)) {
					break;
				}

				p = p->children[index];
			}

			return p;
		}

		void takeAllWords(TrieNode* p, string wseq, queue<string>& words) {
			if (p != nullptr) {
				for (int i = 0; i < N; i++) {
					if (p->children[i] != nullptr) {
						if (p->children[i]->isTerminal) {
							words.push(wseq + string(1, 'a' + i));
						}

						takeAllWords(p->children[i], wseq + string(1, 'a' + i), words);
					}
				}
			}
		}

		int countWordsWithHelper(TrieNode* p, char ch) {
			queue<string> words;
			takeAllWords(p, "", words);

			int cnt = 0;
			while (!words.empty()) {
				if (words.front().find(ch) != string::npos) {
					cnt++;
				}

				words.pop();
			}

			return cnt;
		}

		void inorderWalkHelper(TrieNode* p) {
			queue<string> words;
			takeAllWords(p, "", words);

			while (!words.empty()) {
				cout << words.front() << endl;
				words.pop();
			}

			cout << endl << endl;
		}

		void deleteHeper(TrieNode* p) {
			if (p != nullptr) {
				for (int i = 0; i < N; i++) {
					if (p->children[i] != nullptr) {
						deleteHeper(p->children[i]);
						delete p->children[i];
						p->children[i] = nullptr;
					}
				}
			}
		}

		TrieNode* root;

	public:

		TrieTree()
		{
			this->root = new TrieNode();
		}

		~TrieTree()
		{
			deleteHeper(root);
			delete root;
			root = nullptr;
		}

		void Insert(string word)
		{
			insertHelper(root, word);
		}

		void Remove(string word)
		{
			removeHelper(word);
		}

		bool Contains(string word)
		{
			return searchHelper(root, word)->isTerminal;
		}

		void InorderWalk()
		{
			inorderWalkHelper(root);
		}

		int CountWith(char ch)
		{
			return countWordsWithHelper(root, ch);
		}
};

