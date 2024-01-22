#pragma once

#include <iostream>

using namespace std;

template <typename T>
class Node {

	public:
		T Data;
		Node* Next;
		Node* Prev;

		Node() {
			this->Data = T();
			this->Next = nullptr;
			this->Prev = nullptr;
		}

		Node(T data) : Node() {
			this->Data = data;
		}

		~Node() {
			delete this->Next;
			delete this->Prev;
			this->Next = nullptr;
			this->Prev = nullptr;
		}
};

template <typename T>
class LinkedList
{
	private:
		Node<T>* head;
		Node<T>* tail;


		void recurPrintHelper(Node<T>* head) {
			if (head != nullptr) {
				cout << head->Data << " ";
				recurPrintHelper(head->Next);
			}
		}

	public:
		LinkedList() {
			this->head = nullptr;
			this->tail = nullptr;
		}

		~LinkedList() {
			Clear();
		}

		Node<T>* UnsafeHeadPtr() {
			return this->head;
		}

		bool IsEmpty() {
			return this->head == nullptr;
		}

		Node<T>* PushBack(T data) {
			Node<T>* newNode = new Node<T>(data);

			if (IsEmpty()) {
				this->head = this->tail = newNode;
			}
			else {
				this->tail->Next = newNode;
				newNode->Prev = this->tail;
				this->tail = newNode;
			}

			return newNode;
		}

		Node<T>* PushFront(T data) {
			Node<T>* newNode = new Node<T>(data);

			if (IsEmpty()) {
				this->head = this->tail = newNode;
			}
			else {
				this->head->Prev = newNode;
				newNode->Next = this->head;
				this->head = newNode;
			}

			return newNode;
		}

		void PopBack() {
			if (IsEmpty()) {
				return;
			}

			Node<T>* prev = this->tail->Prev;

			if (prev != nullptr) {
				prev->Next = nullptr;
			}
			else {
				this->head = nullptr;
			}

			this->tail->Prev = nullptr;
			delete this->tail;
			this->tail = prev;
		}

		void PopFront() {
			if (IsEmpty()) {
				return;
			}

			Node<T>* next = this->head->Next;

			if (next != nullptr) {
				next->Prev = nullptr;
			}
			else {
				this->tail = nullptr;
			}

			this->head->Next = nullptr;
			delete this->head;
			this->head = next;
		}

		void ItterPrint() {
			Node<T>* it = this->head;

			while (it != nullptr) {
				cout << it->Data << " ";
				it = it->Next;
			}

			cout << endl;
		}

		Node<T>* Search(T data) {
			Node<T>* it = this->head;

			while (it != nullptr) {
				if (it->Data == data) {
					break;
				}

				it = it->Next;
			}

			return it;
		}

		void Remove(T data) {
			Node<T>* node = Search(data);

			if (node == nullptr) {
				return;
			}

			if (node->Prev == nullptr) {
				PopFront();
				return;
			}

			if (node->Next == nullptr) {
				PopBack();
				return;
			}

			Node<T>* left = node->Prev;
			Node<T>* right = node->Next;
			left->Next = right;
			right->Prev = left;

			node->Prev = nullptr;
			node->Next = nullptr;
			delete node;
		}

		void RecurPrint() {
			recurPrintHelper(this->head);
			cout << endl;
		}

		void Clear() {
			while (!IsEmpty()) {
				PopFront();
			}
		}
};
