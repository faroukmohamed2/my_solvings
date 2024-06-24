#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

class Vector {
private:
	int* arr = nullptr;
	int size = 0;
	int capacity;

public:
	Vector(int size) :
		size(size) {
		if (size < 0)
			size = 1;
		capacity = size + 10;
		arr = new int[capacity] {};
	}

	~Vector() {
		delete[] arr;
		arr = nullptr;
	}

	int get_size() {
		return size;
	}

	int get(int idx) {
		assert(0 <= idx && idx < size);
		return arr[idx];
	}

	void set(int idx, int val) {
		assert(0 <= idx && idx < size);
		arr[idx] = val;
	}

	void print() {
		for (int i = 0; i < size; ++i)
			cout << arr[i] << " ";
		cout << "\n";
	}

	int find(int value) {
		for (int i = 0; i < size; ++i)
			if (arr[i] == value)
				return i;
		return -1;	// -1 for NOT found
	}
	
	void expand_capacity()
	{
		capacity *= 2;
		int* arr2 = new int[capacity];

		for (int i = 0; i < size; i++)
			arr2[i] = arr[i];
		swap(arr, arr2);
		delete[]arr2;
	}
	
	void push_back(int value)
	{
		if (size == capacity)
			expand_capacity();
		arr[size] = value;
		size++;
	}
	//////////////////////////////////////////////
	//				right rotate				//
	//////////////////////////////////////////////
	void right_rotate()
	{
		if (size <= 1)
			return;
		int last = arr[size - 1];
		for (int i = size - 2; i >= 0; i--)
			arr[i + 1] = arr[i];
		arr[0] = last;
	}
	//////////////////////////////////////////////
	//				left rotate					//
	//////////////////////////////////////////////
	void left_rotate()
	{
		if (size <= 1)
			return;
		int first = arr[0];
		for (int i = 0; i < size; i++)
			arr[i] = arr[i + 1];
		arr[size - 1] = first;
	}
	//////////////////////////////////////////////
	//			right rotate times				//
	//////////////////////////////////////////////
	void right_rotate(int times)
	{
		times %= size;
		while (times-- > 0)
			right_rotate();
	}
	//////////////////////////////////////////////
	//					pop						//
	//////////////////////////////////////////////
	int pop(int idx)
	{
		assert(0 <= idx && size > 1);
		int val = arr[idx];
		for (int i = idx; i < size; i++)
		{
			arr[i] = arr[i + 1];
		}
		arr[size--] = 0;
		return val;
	}
	//////////////////////////////////////////////
	//			Improves search					//
	//////////////////////////////////////////////
	int find_transposition(int value)
	{
		for (int i = 0; i < size; i++)
		{
			if (arr[i] == value)
			{
				if (i == 0)
					return i;
				int temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
				return i - 1;
			}
		}
		return -1;
	}
};

int main() {


	Vector v(1);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.print();
	cout << endl;
	v.right_rotate();
	v.left_rotate();
	v.right_rotate(3);
	cout << v.find_transposition(20) << endl;
	v.print();


	return 0;
}
