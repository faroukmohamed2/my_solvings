#include <iostream>
using namespace std;
class stack
{
	int added_items{};
	int* arr{};
	int size{};
	int top{};
public:
	stack(int size) :size(size)
	{
		arr = new int[size];
		top = -1;
	}
	bool isfull()
	{
		return added_items == size;
	}
	bool isEmpty()
	{
		return added_items == 0;
	}
	bool push(int value)
	{
		if (isfull())
			return false;
		for (int i = added_items - 1; i >= 0; i--)
			arr[i + 1] = arr[i];
		arr[0] = value;
		top = arr[0];
		added_items++;
		return true;
	}
	bool pop(int &result)
	{
		if (isEmpty())
			return false;
		result = arr[0];
		for (int i = 0; i < added_items; i++)
			arr[i] = arr[i + 1];
		--added_items;
		top = arr[0];
		return true;
	}
	bool peak(int &result)
	{
		if (isEmpty())
			return false;
		result = top;
		return true;
	}
};
int main()
{
	stack s1(10);
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);
	int x;
	s1.peak(x);
	cout << x << endl;
	s1.pop(x);
	cout << x << endl;
	s1.peak(x);
	cout << x << endl;
	return 0;
}