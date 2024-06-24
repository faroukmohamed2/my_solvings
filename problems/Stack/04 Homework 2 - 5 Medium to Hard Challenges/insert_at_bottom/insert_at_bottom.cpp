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
	void insert_at_bottom(int x)
	{
		insert_at_bottom(x, top + 1);
		top++;
	}
	void insert_at_bottom(int x, int n)
	{
		if (n == size)
			return;
		if (n == 0)
			return;
		array[n] = array[n - 1];
		insert_at_bottom(x, n - 1);
		array[0] = x;
	}
};
string reverse_subward(string str)
{
	Stack word(str.size());
	str += ' ';
	string result;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			while (!word.isEmpty())
			{
				result += word.pop();
			}
			result += ' ';
		}
		else
		{
			word.push(str[i]);
		}
	}
	return result;
}

int main() {
	Stack s(20);
	s.push(4);
	s.push(3);
	s.push(2);
	s.push(1);
	s.display();
	s.insert_at_bottom(10);
	s.insert_at_bottom(11);
	s.insert_at_bottom(12);
	s.display();
	return 0;
}
