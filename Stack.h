#pragma once

template <typename T>
class Stack
{
	private:
		T* stack; 
		int top;
		int cap;

		const int defaultCap = 4;

		void resize() 
		{
			cap *= 2;
			auto newStack = new T[cap];

			for (int i = 0; i < top; i++) {
				newStack[i] = stack[i];
			}

			delete[] stack;
			stack = newStack;
		}

	public:

		Stack(int cap)
		{
			if (cap <= 0) {
				cap = defaultCap;
			}

			this->cap = cap;
			this->stack = new T[cap];
			this->top = 0;
		}

		bool IsEmpty() 
		{
			return this->top == 0;
		}

		void Push(T elem)
		{
			if (top == cap) {
				resize();
			}

			stack[top] = elem;
			top++;
		}

		T Pop()
		{
			if (!IsEmpty()) {
				top--;
				return stack[top];
			}
		}
};

