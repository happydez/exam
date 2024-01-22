#pragma once

template <typename T>
class Queue
{
	private:
		T* data;
		int cap;
		int head;
		int tail;
		int count;

	public:

		Queue(int cap = 4) {
			data = new T[cap];
			cap = cap;
			tail = -1;
			head = 0;
			count = 0;
		}

		void Enqueue(int item) {
			if (IsFull()) {
				return;
			}

			tail = (tail + 1) % cap;
			data[tail] = item;
			count++;
		}

		int Dequeue() {
			if (IsFull()) {
				return;
			}

			int x = data[head];
			head = (head + 1) % cap;
			count--;
		}


		int Size() {
			return count;
		}

		bool IsFull() {
			return Size() == cap;
		}
};

