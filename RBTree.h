#pragma once

#include <iostream>

using namespace std;

template <typename T>
class RBTree
{
	private:

		const bool RED = true;
		const bool BLACK = false;

		struct RBNode
		{
			T data;
			int key;
			bool red;
			RBNode* p;
			RBNode* left;
			RBNode* right;

			RBNode(int key, T data, bool red = BLACK, RBNode* p = nullptr, RBNode* left = nullptr, RBNode* right = nullptr)
			{
				this->key = key;
				this->data = data;
				this->red = red;
				this->p = p;
				this->left = left;
				this->right = right;
			}
		};

		RBNode* minimum(RBNode* p) {
			while (p->left != nil) {
				p = p->left;
			}

			return p;
		}

		RBNode* maximum(RBNode* p) {
			while (p->right != nil) {
				p = p->right;
			}

			return p;
		}

		RBNode* next(RBNode* p) {
			if (p->right != nil) {
				return minimum(p->right);
			}

			RBNode* it = p->p;
			while ((it != nil) && (p == it->right)) {
				p = it;
				it = it->p;
			}

			return it;
		}

		RBNode* prev(RBNode* p) {
			if (p->left != nil) {
				return maximum(p->left);
			}

			RBNode* it = p->p;
			while ((it != nil) && (p == it->left)) {
				p = it;
				it = it->p;
			}

			return it;
		}

		void rotateRight(RBNode* x) {
			if (x == nil) {
				return;
			}

			RBNode* y = x->left;
			x->left = y->right;

			if (y->right != nil) {
				y->right->p = x;
			}

			y->p = x->p;

			if (x->p == nil) {
				this->root = y;
			}
			else if (x->p->left == x) {
				x->p->left = y;
			}
			else {
				x->p->right = y;
			}

			y->right = x;
			x->p = y;
		}

		void rotateLeft(RBNode* x) {
			if (x == nil) {
				return;
			}

			RBNode* y = x->right;
			x->right = y->left;

			if (y->left != nil) {
				y->left->p = x;
			}

			y->p = x->p;

			if (x->p == nil) {
				this->root = y;
			}
			else if (x->p->right == x) {
				x->p->right = y;
			}
			else {
				x->p->left = y;
			}

			y->left = x;
			x->p = y;
		}

		void insertHelper(RBNode* p, int key, T data) {
			RBNode* temp = nil;
			while (p != nil) {
				temp = p;
				if (p->key < key) {
					p = p->right;
				}
				else if (p->key > key) {
					p = p->left;
				}
				else {
					temp = nullptr;
					return;
				}
			}

			RBNode* x = new RBNode(key, data, RED);
			x->p = temp;
			x->left = nil;
			x->right = nil;

			if (temp == nil) {
				x->red = BLACK;
				this->root = x;
			}
			else if (temp->key < key) {
				temp->right = x;
			}
			else {
				temp->left = x;
			}

			insertFixup(x);
		}

		void insertFixup(RBNode* x) {
			RBNode* uncle;
			while (x->p->red) {
				if (x->p == x->p->p->left) {
					uncle = x->p->p->right;

					if (uncle->red) {
						uncle->red = BLACK;
						x->p->p->red = RED;
						x->p->red = BLACK;
						x = x->p->p;
					}
					else {
						if (x == x->p->right) {
							x = x->p;
							rotateLeft(x);
						}

						x->p->red = BLACK;
						x->p->p->red = RED;
						rotateRight(x->p->p);
					}
				}
				else {
					uncle = x->p->p->left;

					if (uncle->red) {
						uncle->red = BLACK;
						x->p->p->red = RED;
						x->p->red = BLACK;
						x = x->p->p;
					}
					else {
						if (x == x->p->left) {
							x = x->p;
							rotateRight(x);
						}

						x->p->red = BLACK;
						x->p->p->red = RED;
						rotateLeft(x->p->p);
					}
				}
			}

			this->root->red = BLACK;
		}

		RBNode* removeHelper(RBNode* z) {
			RBNode* y;
			
			if ((z->left == nil) || (z->right == nil)) {
				y = z;
			}
			else {
				y = next(z);
			}

			RBNode* x;
			if (y->left != nil) {
				x = y->left;
			}
			else {
				x = y->right;
			}

			x->p = y->p;

			if (y->p == nil) {
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

			if (y->red == BLACK) {
				removeFixup(x);
			}

			return y;
		}

		void removeFixup(RBNode* x) {
			RBNode* w;
			while ((x != root) && (x->red == BLACK)) {
				if (x == x->p->left) {
					w = x->p->right;

					if (w->red == RED) {
						w->red = BLACK;
						x->p->red = RED;
						rotateLeft(x->p);
						w = x->p->right;
					}

					if ((w->left->red == BLACK) && (w->right->red == BLACK)) {
						w->red = RED;
						x = x->p;
					}
					else {
						if (w->right->red == BLACK) {
							w->red = RED;
							w->left->red = BLACK;
							rotateRight(w);
							w = x->p->right;
						}

						w->red = w->p->red;
						x->p->red = BLACK;
						w->right->red = BLACK;
						rotateLeft(x->p);
						x = root;
					}
				}
				else {
					w = x->p->left;

					if (w->red == RED) {
						w->red = BLACK;
						x->p->red = RED;
						rotateRight(x->p);
						w = x->p->left;
					}

					if ((w->right->red == BLACK) && (w->left->red == BLACK)) {
						w->red = RED;
						x = x->p;
					}
					else {
						if (w->left->red == BLACK) {
							w->red = RED;
							w->right->red = BLACK;
							rotateLeft(w);
							w = x->p->left;
						}

						w->red = x->p->red;
						x->p->red = BLACK;
						w->left->red = BLACK;
						rotateRight(x->p);
						x = root;
					}
				}
			}

			x->red = BLACK;
		}

		RBNode* searchHelper(RBNode* p, int key) {
			while ((p != nil) && (p->key != key)) {
				p = (p->key < key) ? p->right : p->left;
			}

			return p;
		}

		void inorderWalkHelper(RBNode* p) {
			if (p != nil) {
				inorderWalkHelper(p->left);
				cout << p->key << "(" << ((p->red) ? "R" : "B") << ") ";
				inorderWalkHelper(p->right);
			}
		}

		void deleteHelper(RBNode* p) {
			if (p != nil) {
				deleteHelper(p->left);
				deleteHelper(p->right);

				p->p = nullptr;
				delete p;
				p = nullptr;
			}
		}

		RBNode* nil;
		RBNode* root;

	public:

		RBTree()
		{
			this->nil = new RBNode(-1, T(), BLACK, nil, nil, nil);
			this->root = nil;
		}

		~RBTree()
		{
			deleteHelper();
			delete nil;
			nil = nullptr;
		}

		void Insert(int key, T data)
		{
			insertHelper(root, key, data);
		}

		bool Remove(int key) {
			RBNode* z = searchHelper(root, key);

			if (z == nil) {
				return false;
			}

			removeHelper(z);

			return true;
		}

		bool Search(int key) {
			return searchHelper(root, key) != nil;
		}

		void InorderWalk()
		{
			inorderWalkHelper(root);
			cout << endl;
		}
};
