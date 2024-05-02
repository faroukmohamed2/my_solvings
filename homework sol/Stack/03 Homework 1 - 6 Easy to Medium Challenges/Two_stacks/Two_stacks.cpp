#include <iostream>
#include <cassert>
#include <string>
#include <stack>
using namespace std;

class Stack {
private:
	int size{ };
	int top1{ };
	int top2{ };
	int* array{ };
public:
	Stack(int size) :
		size(size), top1(-1), top2(size) {
		array = new int[size];
	}
	~Stack() {
		delete[] array;
	}

	void push(int idx, int x) {
		assert(!isFull());
		if (idx == 1)
		{
			array[++top1] = x;
		}
		else if (idx == 2)
			array[--top2] = x;

	}

	int pop(int place) {
		assert(!isEmpty());
		if (place == 1)
			return array[top1--];
		if (place == 2)
			return array[top2++];
	}

	int peek(int idx) {
		assert(!isEmpty());
		if (idx == 1)
			return array[top1];
		if (idx == 2)
			return array[top2];
	}

	int isFull() {
		return top1 == top2 -1;
	}

	int isEmpty() {
		return top1 == -1 && top2 == size;
	}

	void display() {
		for (int i = top1; i >= 0; i--)
			cout << array[i] << " ";
		cout << endl;
		for (int i = top2; i < size; i++)
			cout << array[i] << " ";
		cout << "\n";
	}
};
int main()
{
	Stack stk(10);
	stk.push(2, 5);
	stk.push(2, 6);
	stk.pop(2);
	stk.push(2, 7);
	stk.push(2, 9);
	stk.push(1, 4);
	cout << stk.peek(1) << endl;
	cout << stk.peek(2) << endl;
	stk.push(1, 6);
	stk.push(1, 8);
	stk.push(2, 3);
	stk.display();
	return 0;

}