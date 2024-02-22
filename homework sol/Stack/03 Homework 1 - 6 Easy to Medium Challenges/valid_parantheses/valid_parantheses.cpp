#include <iostream>
#include <cassert>
#include <string>
#include <stack>
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
///////////////////////////////////
//       isvalid paranthese     //
//////////////////////////////////
bool isValid(string s) {

	if (s[0] != '(' && s[0] != '{' && s[0] != '[')
		return false;
	Stack stk(s.size());
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			stk.push(s[i]);
		else if (s[i] == ')')
		{
			if (!stk.isEmpty() && stk.peek() == '(')
				stk.pop();
			else
				stk.push(s[i]);
		}
		else if (s[i] == '}') {
			if (!stk.isEmpty() && stk.peek() == '{')
				stk.pop();
			else
				stk.push(s[i]);
		}
		else if (s[i] == ']')
		{
			if (!stk.isEmpty() && stk.peek() == '[')
				stk.pop();
			else
				stk.push(s[i]);
		}
	}
	return stk.isEmpty();
}
int main()
{
	string str2 = "(){}}{";
	if (isValid(str2))
		cout << "\nvalid" << endl;
	else
		cout << "\nNot valid\n";
		return 0;
}