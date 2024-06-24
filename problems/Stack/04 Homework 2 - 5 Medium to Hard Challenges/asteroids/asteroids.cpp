#include <iostream>
#include <cassert>
#include <string>
#include <stack>
#include <vector>
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
vector<int> asteroid(vector<int> asteroids)
{
	Stack stk(50);
	stk.push(-1);
	vector<int> ast;
	int i = 0;
	for (int i = 0;  i < asteroids.size(); i++)
	{
		int aste = asteroids[i];
		bool is_explode = false;
		while (!stk.isEmpty() && stk.peek() > 0 && aste < 0)
		{
			if (stk.peek() < -aste)
			{
				stk.pop();
				ast.pop_back();
				continue;
			}
			else if (stk.peek() == -aste)
			{
				stk.pop();
				ast.pop_back();
			}
			is_explode = true;
			break;
		}
		if (!is_explode)
		{
			stk.push(aste);
			ast.push_back(aste);
		}
	}
	return ast;
}