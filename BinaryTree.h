#pragma once

#include <iostream>
#include <queue>

using namespace std;


template <typename T>
class BinaryTree
{
	private:

		struct BTNode
		{
			T data;
			int key;
			BTNode* p, * left, * right;

			BTNode(int key, T data, BTNode* p = nullptr, BTNode* left = nullptr, BTNode* right = nullptr)
			{
				this->key = key;
				this->data = data;
				this->p = p;
				this->left = left;
				this->right = right;
			}
		};

		BTNode* minimum(BTNode* x) {
			while (x->left != nullptr) {
				x = x->left;
			}

			return x;
		}

		BTNode* maximum(BTNode* x) {
			while (x->right != nullptr) {
				x = x->right;
			}

			return x;
		}

		BTNode* next(BTNode* x) {
			if (x->right != nullptr) {
				return minimum(x->right);
			}

			BTNode* y = x->p;
			while ((y != nullptr) && (x == y->right)) {
				x = y;
				y = y->p;
			}

			return y;
		}

		BTNode* prev(BTNode* x) {
			if (x->left != nullptr) {
				return maximum(x->left);
			}

			BTNode* y = x->p;
			while ((y != nullptr) && (x == y->left)) {
				x = y;
				y = y->p;
			}

			return y;
		}

		BTNode* searchHelper(BTNode* x, int key) {
			while ((x != nullptr) && (x->key != key)) {
				x = (x->key < key) ? x->right : x->left;
			}

			return x;
		}

		void insertHelper(BTNode* x, int key, T data) {
			BTNode* temp = nullptr;
			while (x != nullptr) {
				temp = x;
				if (x->key < key) {
					x = x->right;
				}
				else if (x->key > key) {
					x = x->left;
				}
				else {
					return;
				}
			}

			BTNode* y = new BTNode(key, data);
			y->p = temp;

			if (temp == nullptr) {
				this->root = y;
			}
			else if (temp->key < key) {
				temp->right = y;
			}
			else {
				temp->left = y;
			}
		}

		BTNode* removeHelper(BTNode*& z) {
			BTNode* y;

			if ((z->left == nullptr) || (z->right == nullptr)) {
				y = z;
			}
			else {
				y = next(z);
			}

			BTNode* x;
			if (y->left != nullptr) {
				x = y->left;
			}
			else {
				x = y->right;
			}

			if (x != nullptr) {
				x->p = y->p;
			}

			if (y->p == nullptr) {
				this->root = x;
			}
			else if (y == y->p->left) {
				y->p->left = x;
			}
			else {
				y->p->right = x;
			}

			if (y != z) {
				z->key = y->key;
			}

			return y;
		}

		// Нахоидт количество отрицательных элементов 
		// в дереве
		int findNegativesHelper(BTNode* x) {
			if (x == nullptr) {
				return 0;
			}

			return ((x->key < 0) ? 1 : 0) + findNegativesHelper(x->left) + findNegativesHelper(x->right);
		}

		void inorderWalkHelper(BTNode* x) {
			if (x != nullptr) {
				inorderWalkHelper(x->left);
				cout << x->key << " ";
				inorderWalkHelper(x->right);
			}
		}

		void deleteHelper(BTNode* x) {
			if (x != nullptr) {
				deleteHelper(x->left);
				deleteHelper(x->right);

				x->p = nullptr;
				delete x;
				x = nullptr;
			}
		}

		void subTreeWalk(BTNode* T1, BTNode* T2, BinaryTree* merged) {
			if ((T1 != nullptr) && (T2 != nullptr)) {
				if (T1->key == T2->key) {
					merged->Insert(T1->key, T1->data);
					subTreeWalk(T1->left, T2->left, merged);
					subTreeWalk(T1->right, T2->right, merged);
				}
			}
		}

		// Возвращает объедененное дерево T1, T2
		// Задача на 5
		BinaryTree* subTreeHelper(BTNode* T1, BTNode* T2) {
			if ((T1 == nullptr) || (T2 == nullptr)) {
				return nullptr;
			}

			BTNode* start = searchHelper(T1, T2->key);

			if (start != nullptr) {
				BinaryTree* merged = new BinaryTree();
				subTreeWalk(start, T2, merged);
				return merged;
			}

			return nullptr;
		}

		/*
		* Дано двоичное дерево поиска
		* Задача — найти сумму всех элементов, 
		* меньших и равных K-му наименьшему элементу.
		*/
		int solve_1Helper(BTNode* p, int k) {
			BTNode* it = minimum(p);

			int sum = 0;
			for (int i = 0; i < k; i++) {
				if (it != nullptr) {
					sum += it->key;
					it = next(it);
				}
			}

			return sum;
		}

		/*
		* Дано бинарное дерево поиска и два ключа в нем. 
		* Найдите расстояние между двумя узлами по заданным
		* двум ключам. Можно предположить, что оба ключа 
		* существуют в BST.
		*/
		int distFromTo(BTNode* p, int key) {
			if (p == nullptr) {
				return 0;
			}

			if (p->key == key) {
				return 0;
			}
			else if (p->key > key) {
				return 1 + distFromTo(p->left, key);
			}
			else {
				return 1 + distFromTo(p->right, key);
			}
		}

		int findDistTwoNodesHelper(BTNode* p, int k1, int k2) {
			if (p == nullptr) {
				return 0;
			}

			if (p->key > k1 && p->key > k2) {
				return findDistTwoNodesHelper(p->left, k1, k2);
			}

			if (p->key < k1 && p->key < k2) {
				return findDistTwoNodesHelper(p->right, k1, k2);
			}

			if (p->key >= k1 && p->key <= k2) {
				return distFromTo(p, k1) + distFromTo(p, k2);
			}
		}

		/*
		* Дано бинарное дерево, в котором каждый узловой
		* элемент содержит число. Задача состоит в том, чтобы
		* найти минимально возможную сумму от одного конечного
		* узла к другому.
		*/
		int findMinPathSum(BTNode* p, int& result) {
			if (p == nullptr) {
				return 0;
			}

			if ((p->left == nullptr) && (p->right == nullptr)) {
				return p->key;
			}

			int ls = findMinPathSum(p->left, result);
			int rs = findMinPathSum(p->right, result);

			if ((p->left != nullptr) && (p->right != nullptr)) {
				result = min(result, ls + rs + p->key);

				return min(ls + p->key, rs + p->key);
			}
			else if (p->left == nullptr) {
				return rs + p->key;
			}
			else {
				return ls + p->key;
			}
		}

		/*
		* Дано бинарное дерево, в котором каждый узловой
		* элемент содержит число. Задача состоит в том, чтобы
		* найти максимально возможную сумму от одного конечного
		* узла к другому.
		*/
		int findMaxPathSum(BTNode* p, int& result) {
			if (p == nullptr) {
				return 0;
			}

			if ((p->left == nullptr) && (p->right == nullptr)) {
				return p->key;
			}

			int ls = findMaxPathSum(p->left, result);
			int rs = findMaxPathSum(p->right, result);

			if ((p->left != nullptr) && (p->right != nullptr)) {
				result = max(result, ls + rs + p->key);

				return max(ls + p->key, rs + p->key);
			}
			else if (p->left == nullptr) {
				return rs + p->key;
			}
			else {
				return ls + p->key;
			}
		}

		BTNode* root;

	public:

		BinaryTree()
		{
			this->root = nullptr;
		}

		~BinaryTree()
		{
			deleteHelper(root);
		}

		void Insert(int key, T data)
		{
			insertHelper(root, key, data);
		}

		bool Remove(int key)
		{
			BTNode* x = searchHelper(root, key);

			if (x == nullptr) {
				return false;
			}

			removeHelper(x);

			return true;
		}

		bool Contains(int key)
		{
			return searchHelper(root, key) != nullptr;
		}

		int FindNegatives()
		{
			return findNegativesHelper(root);
		}

		void InorderWalk()
		{
			inorderWalkHelper(root);
			cout << endl;
		}

		int Solve_1(int k)
		{
			return solve_1Helper(root, k);
		}

		BinaryTree* SubTreeWith(BinaryTree* other)
		{
			return subTreeHelper(root, other->root);
		}

		int FindDistTwoNodeds(int k1, int k2)
		{
			if (k1 > k2) {
				swap(k1, k2);
			}

			return findDistTwoNodesHelper(root, k1, k2);
		}

		int FindMaxPathSum()
		{
			int result = -INT_MAX;
			findMaxPathSum(root, result);
			return result;
		}

		int FindMinPathSum()
		{
			int result = INT_MAX;
			findMinPathSum(root, result);
			return result;
		}
};
