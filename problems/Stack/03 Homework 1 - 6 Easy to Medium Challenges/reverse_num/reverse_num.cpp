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
////////////////////////////////
//      reverse_num          //
///////////////////////////////
int reverse_num(int n)
{
	Stack stk(15);
	int rev = 0;
	while (n)
	{
		stk.push(n % 10);
		n /= 10;
	}
	int i = 1;
	while (!stk.isEmpty())
	{
		rev += stk.pop() * i;
		i *= 10;
	}
	return rev;
}
int main()
{
    int to_rev1= 1234;
    int to_rev2 = 54;
    int to_rev3 = 134;
    int to_rev4 = 31854;
    int to_rev5 = 1;
	cout << reverse_num(to_rev1) << endl;
	cout << reverse_num(to_rev2) << endl;
	cout << reverse_num(to_rev3) << endl;
	cout << reverse_num(to_rev4) << endl;
	cout << reverse_num(to_rev5) << endl;
    return 0;
}