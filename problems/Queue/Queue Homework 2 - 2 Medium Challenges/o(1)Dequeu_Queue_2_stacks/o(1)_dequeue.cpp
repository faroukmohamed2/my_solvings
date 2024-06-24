#include <iostream>
#include <cassert>
using namespace std;
class Stack {
private:
	int size{ };
	int top{ };
	int* array{ };
public:
	Stack(int size) :
		size(size), top(-1) {
		array = new int[size];
	}
	~Stack() {
		delete[] array;
	}

	void push(int x) {
		assert(!isFull());
		array[++top] = x;
	}

	int pop() {
		assert(!isEmpty());
		return array[top--];
	}

	int peek() {
		assert(!isEmpty());
		return array[top];
	}

	int isFull() {
		return top == size - 1;
	}

	int isEmpty() {
		return top == -1;
	}

	void display() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}
};
class Queue_stack
{
	int size { };
	int added_elements = 0;
	Stack s1;
	Stack s2;
public:
	Queue_stack(int size) :size(size), s1(size), s2(size)
	{}
	void move(Stack& s1, Stack& s2)
	{
		while (!s1.isEmpty())
			s2.push(s1.pop());
	}
	void enqueue(int x)
	{
		if (isFull())
			return;
		move(s1, s2);
		s1.push(x);
		move(s2, s1);
		added_elements++;
	}
	bool isEmpty()
	{
		return !added_elements;
	}
	bool isFull()
	{
		return added_elements == size;
	}
	int dequeue()
	{
		assert(!isEmpty());
			added_elements--;
			return s1.pop();

	}
	void dis()
	{
		s2.display();
	}
};
int main()
{
	Queue_stack Q(6);
	for (int i = 0; i <= 3; i++)
		Q.enqueue(i);
	cout << Q.dequeue() << " " << endl;
	for (int i = 4; i <= 5; i++)
		Q.enqueue(i);
	while (!Q.isEmpty())
		cout << Q.dequeue() << " ";


	return 0;
}