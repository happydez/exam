#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "Stack.h"
#include "LinkedList.h"
#include "BinaryTree.h"
#include "AVLTree.h"
#include "RBTree.h"
#include "TrieTree.h"

using namespace std;

// Сделать стек из строки
Stack<char> InitStack(string str) {
    Stack<char> seq = Stack<char>(4);

    for (auto ch : str) {
        seq.Push(ch);
    }

    return seq;
}

// Задача на валидную послед. скобочек
bool Solve_Stack(Stack<char> seq) {
    auto opposite = [](char ch) -> int {
        return ch == '(' ? ')' : (ch == '[' ? ']' : (ch == '{' ? '}' : ch));
    };

    map<char, int> states;

    while (!seq.IsEmpty()) {
        char next = seq.Pop();

        if (next == '(' || next == '{' || next == '[') {
            int ops = opposite(next);

            if (!states[ops]) {
                return false;
            }

            states[ops]--;
        }
        else {
            states[next]++;
        }
    }

    return true;
}

// Вставить новый элемент перед каждым вхождением
// заданного элемента непустого списка
void Solve_1(int x, int elm, LinkedList<int>* list) {
    auto ptr = list->UnsafeHeadPtr();

    while (ptr != nullptr) {
        if (ptr->Data == elm) {
            if (ptr->Prev == nullptr) {
                list->PushFront(x);
            }
            else {
                Node<int>* newNode = new Node<int>(x);
                ptr->Prev->Next = newNode;
                newNode->Prev = ptr->Prev;
                newNode->Next = ptr;
                ptr->Prev = newNode;
            }
        }

        ptr = ptr->Next;
    }
}

// удалить из списка M за каждым вхождением элемента E
// один элемент, если такой есть и он отличен от E.
void Solve_2(int E, LinkedList<int>* list) {
    Node<int>* ptr = list->UnsafeHeadPtr();

    while (ptr != nullptr) {
        if (ptr->Data == E) {
            if ((ptr->Next != nullptr) && (ptr->Next->Data != E)) {
                Node<int>* next = ptr->Next;
                if (next->Next == nullptr) {
                    list->PopBack();
                }
                else {
                    ptr->Next = next->Next;
                    next->Next->Prev = ptr;
                    next->Prev = nullptr;
                    next->Next = nullptr;
                    delete next;
                }
            }
        }

        ptr = ptr->Next;
    }
}


// Сформировать список М из элементов, входящих
// хотя бы в один из списков М1 и М2, без повторов.
LinkedList<int>* Union(LinkedList<int>* m1, LinkedList<int>* m2) {
    LinkedList<int>* list = new LinkedList<int>();

    Node<int>* ptr = m1->UnsafeHeadPtr();

    while (ptr != nullptr) {
        list->PushBack(ptr->Data);
        ptr = ptr->Next;
    }

    ptr = m2->UnsafeHeadPtr();

    while (ptr != nullptr) {
        if (list->Search(ptr->Data) == nullptr) {
            list->PushBack(ptr->Data);
        }

        ptr = ptr->Next;
    }

    return list;
}


// Сформировать список М из элементов, входящих
// в М1 и не входящих в М2, без повторов.
LinkedList<int>* Solve_3(LinkedList<int>* m1, LinkedList<int>* m2) {
    LinkedList<int>* list = new LinkedList<int>();

    Node<int>* ptr = m1->UnsafeHeadPtr();

    while (ptr != nullptr) {
        if (m2->Search(ptr->Data) == nullptr) {
            list->PushBack(ptr->Data);
        }

        ptr = ptr->Next;
    }

    return list;
}

// Задача на вычисление суммы через стек
// 2 5 + 4 * ... и тд
int Solve_4(string str) {

    string token;
    istringstream iss(str);
    Stack<int>* expr = new Stack<int>(4);

    while (iss >> token) {
        if (isdigit(token[0])) {
            expr->Push(stod(token));
        }
        else {
            if (expr->IsEmpty()) {
                throw out_of_range("stack is empty");
            }

            int secondOperand = expr->Pop();
            
            if (expr->IsEmpty()) {
                throw out_of_range("stack is empty");
            }

            int firstOperand = expr->Pop();

            switch (token[0])
            {
            case '+':
                expr->Push(secondOperand + firstOperand);
                break;
            case '-':
                expr->Push(firstOperand - secondOperand);
                break;
            case '*':
                expr->Push(firstOperand * secondOperand);
                break;
            case '/':
                if (secondOperand == 0) {
                    throw out_of_range("stack is empty");
                }

                expr->Push(firstOperand / secondOperand);
                break;
            default:
                break;
            }
        }
    }

    int result = expr->Pop();
    delete expr;
    return result;
}

int main() {

    return 0;
}