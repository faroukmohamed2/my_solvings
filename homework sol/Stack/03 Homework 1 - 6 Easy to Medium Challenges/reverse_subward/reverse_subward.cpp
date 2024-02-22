#include <iostream>
#include <cassert>
#include <string>
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

/////////////////////////////////
//		string sub ward		   //
/////////////////////////////////
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
	string str = "farouk mohamed farouk";
	cout << reverse_subward(str);
	return 0;
}
