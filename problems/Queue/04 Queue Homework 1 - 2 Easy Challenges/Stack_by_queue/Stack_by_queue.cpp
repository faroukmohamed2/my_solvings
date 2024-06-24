#include <iostream>
#include <cassert>
#include "LinkedList.h"
class Queue
{
	LinkedList l;
	int size;
public:
	Queue(int size):size(size)
	{}
	void enqueue(int value)
	{
		l.insert_end(value);
	}
	void enqueue_front(int value)
	{
		l.insert_front(value);
	}
	int dequeue()
	{
		return l.delete_first();
	}
	int get_front()
	{
		return l.get_head();
	}
	/*int dequeu_rear()
	{
		return l.delete_last();

	}*/
	void display()
	{
		l.print();
	}
};
class Stack
{
	Queue q;
	int size{ };
	int added_elements{ };
public:
	Stack(int size):q(size),added_elements(0),size(size)
	{}
	void push(int value)
	{
		assert(!isFull());
		q.enqueue_front(value);
		++added_elements;
	}
	int pop()
	{
		assert(!isEmpty());
		--added_elements;
		return q.dequeue();
	}
	int peek()
	{
		assert(!isEmpty());
		return q.get_front();
	}
	bool isEmpty()
	{
		return added_elements == 0;
	}
	bool isFull()
	{
		return added_elements == size;
	}
};
int main()
{
	Stack stk(3);
	stk.push(10);
	stk.push(20);
	stk.push(30);
	while (!stk.isEmpty())
	{
		cout << stk.peek() << " ";
		stk.pop();
	}
	return 0;
}