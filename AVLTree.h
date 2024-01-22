#pragma once

#include <iostream>

using namespace std;

template <typename T>
class AVLTree
{
	private:
		struct AVLNode
		{
			T data;
			int key;
			int height;
			AVLNode* left;
			AVLNode* right;

			AVLNode(int key, T data, int height = 1, AVLNode* left = nullptr, AVLNode* right = nullptr)
			{
				this->key = key;
				this->data = data;
				this->height = height;
				this->left = left;
				this->right = right;
			}
		};

		int getHeight(AVLNode* p) {
			return (p == nullptr) ? 0 : p->height;
		}

		void fixHeight(AVLNode* p) {
			p->height = 1 + max(getHeight(p->left), getHeight(p->right));
		}

		int balanceFactor(AVLNode* p) {
			return getHeight(p->right) - getHeight(p->left);
		}

		void balance(AVLNode*& p) {
			if (p == nullptr) {
				return;
			}

			fixHeight(p);

			int bf = balanceFactor(p);
			
			if (bf == -2) {
				if (balanceFactor(p->left) > 0) {
					p->left = rotateLeft(p->left);
				}

				p = rotateRight(p);
			}

			if (bf == 2) {
				if (balanceFactor(p->right) < 0) {
					p->right = rotateRight(p->right);
				}

				p = rotateLeft(p);
			}
		}

		AVLNode* rotateRight(AVLNode* p) {
			AVLNode* x = p->left;
			p->left = x->right;

			x->right = p;

			fixHeight(p);
			fixHeight(x);

			return x;
		}

		AVLNode* rotateLeft(AVLNode* p) {
			AVLNode* x = p->right;
			p->right = x->left;

			x->left = p;

			fixHeight(p);
			fixHeight(x);

			return x;
		}

		AVLNode* minimum(AVLNode* p) {
			while (p->left != nullptr) {
				p = p->left;
			}

			return p;
		}

		AVLNode* maximum(AVLNode* p) {
			while (p->right != nullptr) {
				p = p->right;
			}

			return p;
		}

		void insertHelper(AVLNode*& p, int key, T data) {
			if (p == nullptr) {
				p = new AVLNode(key, data);
			}
			else if (p->key != key) {
				if (p->key < key) {
					insertHelper(p->right, key, data);
				}
				else {
					insertHelper(p->left, key, data);
				}

				balance(p);
			}
		}

		AVLNode* removeHelper(AVLNode*& p, int key) {
			if (p == nullptr) {
				return nullptr;
			}

			if (p->key > key) {
				p->left = removeHelper(p->left, key);
			}
			else if (p->key < key) {
				p->right = removeHelper(p->right, key);
			}
			else if ((p->left != nullptr) && (p->right != nullptr)) {
				p->key = minimum(p->right)->key;
				p->right = removeHelper(p->right, p->key);
			}
			else {
				if (p->left != nullptr) {
					p = p->left;
				}
				else if (p->right != nullptr) {
					p = p->right;
				}
				else {
					delete p;
					p = nullptr;
				}
			}

			balance(p);

			return p;
		}

		AVLNode* searchHelper(AVLNode* p, int key) {
			while ((p != nullptr) && (p->key != key)) {
				p = (p->key < key) ? p->right : p->left;
			}

			return p;
		}

		bool isBalancedTree(AVLNode* p) {
			if (p == nullptr) {
				return true;
			}

			int bf = balanceFactor(p);
			if (abs(bf) == 2) {
				return false;
			}

			return isBalancedTree(p->left) && isBalancedTree(p->right);
		}

		void inorderWalkHelper(AVLNode* p) {
			if (p != nullptr) {
				inorderWalkHelper(p->left);
				cout << p->key << " ";
				inorderWalkHelper(p->right);
			}
		}

		void deleteHelper(AVLNode* p) {
			if (p != nullptr) {
				deleteHelper(p->left);
				deleteHelper(p->right);

				delete p;
				p = nullptr;
			}
		}

		AVLNode* root;

	public:
		AVLTree()
		{
			this->root = nullptr;
		}

		~AVLTree()
		{
			deleteHelper(root);
		}

		void Insert(int key, T data)
		{
			insertHelper(root, key, data);
		}

		void Remove(int key)
		{
			removeHelper(root, key);
		}

		bool Search(int key)
		{
			return searchHelper(root, key) != nullptr;
		}

		bool IsBalanced()
		{
			return isBalancedTree(root);
		}

		int Height()
		{
			return getHeight(root);
		}

		void InorderWalk()
		{
			inorderWalkHelper(root);
			cout << endl;
		}
};
