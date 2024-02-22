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
////////////////////////////
//    remove dublicates   //
///////////////////////////
string removeDuplicates(string s) {
	Stack stk(s.size());
	for (int i = 0; i < s.size(); i++)
	{
		if (!stk.isEmpty() && stk.peek() == s[i])
		{
			s.erase(i - 1, 2);
			i -= 2;
			stk.pop();
		}
		else
			stk.push(s[i]);

	}
	return s;
}
int main()
{
    string s = "abbaca";
	cout << removeDuplicates(s) << endl;
    return 0;
}