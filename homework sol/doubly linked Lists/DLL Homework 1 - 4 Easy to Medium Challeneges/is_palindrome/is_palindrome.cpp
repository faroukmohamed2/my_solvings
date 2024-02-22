#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
	int data{ };
	Node* next{ };
	Node* prev{ };	 // Previous node!

	Node(int data) : data(data) {}

	void set(Node* next, Node* prev) {
		this->next = next;
		this->prev = prev;
	}

	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList {
private:
	Node* head{ };
	Node* tail{ };
	int length = 0;

	// let's maintain how many nodes

	vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

public:

	// Below 2 deletes prevent copy and assign to avoid this mistake
	LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList& operator=(const LinkedList& another) = delete;

	void debug_print_address() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}

	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}

		if (node->prev == nullptr)
			cout << "X\t";
		else
			cout << node->prev->data << "\t";

		cout << " <= [" << node->data << "]\t => \t";

		if (node->next == nullptr)
			cout << "X\t";
		else
			cout << node->next->data << "\t";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int)debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}

	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node* cur = head; cur; cur = cur->next) {
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
		}
		else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!head->prev);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++) {
			if (len == length - 1)	// make sure we end at tail
				assert(cur == tail);
		}

		assert(length == len);
		assert(length == (int)debug_data.size());

		len = 0;
		for (Node* cur = tail; cur; cur = cur->prev, len++) {
			if (len == length - 1)	// make sure we end at head
				assert(cur == head);
		}
		cout << "\n";
	}
	////////////////////////////////////////////////////////////

	void print() {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node* node) {
		debug_add_node(node);
		++length;
	}

	void print_reversed() {
		for (Node* cur = tail; cur; cur = cur->prev)
			cout << cur->data << " ";
		cout << "\n";
	}
	void insert_end(int value)
	{
		Node* item = new Node(value);
		add_node(item);
		if (!head)
			head = tail = item;
		else
		{
			link(tail, item);
			tail = item;
		}
		debug_verify_data_integrity();
	}
	void insert_front(int value)
	{
		Node* item = new Node(value);
		add_node(item);
		if (!head)
			head = tail = item;
		else
		{
			link(item, head);
			head = item;
		}
		debug_verify_data_integrity();
	}
	void insert_sorted(int value)
	{
		if (!head)
			insert_front(value);
		else if (value <= head->data)
			insert_front(value);
		else if (value >= tail->data)
			insert_end(value);
		else
		{
			for (Node* cur = head; cur; cur = cur->next)
			{
				if (value <= cur->data)
				{
					embed_after(cur->prev, value);
					break;
				}
			}
		}
		debug_verify_data_integrity();
	}
	void delete_first()
	{
		if (head)
		{
			Node* cur = head;
			head = head->next;
			delete_node(cur);
			if (head)
				head->prev = nullptr;
		}
		if (!head)
			tail = nullptr;
		debug_verify_data_integrity();
	}
	void delete_last()
	{
		if (head)
		{
			Node* cur = tail;
			tail = tail->prev;
			delete_node(cur);
			if (tail)
				tail->next = nullptr;
		}
		if (!tail)
			head = nullptr;
		debug_verify_data_integrity();

	}
	///////////
	// link //
	//////////
	void link(Node* first, Node* second)
	{
		if (first)
			first->next = second;
		if (second)
			second->prev = first;
	}
	//////////////////
	// embed after //
	////////////////
	void embed_after(Node*before, int value)
	{
		Node* middle = new Node(value);
		add_node(middle);
		if (before)
		{
			Node *after = before->next;
			link(before, middle);
			link(middle, after);
		}

	}
	/////////////////////
	// delete and link //
	/////////////////////
	Node* delete_and_link(Node* del)
	{
		if (del)
		{
			Node* ret = del->prev;
			link(del->prev, del->next);
			delete_node(del);
			return ret;
		}
	}
	//////////////////////////////////

	/////////////////////////////////
	//		delete with key		  //	
	////////////////////////////////
	void delete_all_with_key(int value)
	{
		if (!head)
			return;
		while (head->data == value)
		{
			delete_first();
			if (!head)
				break;
		}
		if (tail)
		while (tail->data == value)
		{
			delete_last();
			if (!tail)
				break;
		}
		for (Node* cur = head; cur; cur = cur->next)
		{
			if (cur->data == value)
			{
				cur = delete_and_link(cur);
				cur = cur->next;
			}
		}
		debug_verify_data_integrity();
	}
	/////////////////////////////
	//  delete even positions  //
	////////////////////////////
	void delete_even_positions()
	{
		if (!head || !head->next)
			return;
		for (Node* cur = head->next; cur; cur = cur->next)
		{
			cur = delete_and_link(cur);
			if (!cur->next)
			{
				tail = cur;
				break;
			}
			cur = cur->next;
		}
		debug_verify_data_integrity();
	}
	/////////////////////////////
	//  delete odd positions  //
	////////////////////////////
	void delete_odd_positions()
	{
		if (!head)
			return;
		delete_first();
		delete_even_positions();
		debug_verify_data_integrity();
	}
	//////////////////////////////
	//		is palindrome       //
	//////////////////////////////
	bool is_palindrome()
	{
		Node* right = tail;
		for (Node* left = head; left; left = left->next, right = right->prev)
		{
			if (left->data != right->data)
				return false;
		}
		return true;
	}

};
void test1()
{
	LinkedList list;
	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(2);
	list.insert_end(1);


	list.print();
	cout <<  "*******\n" << list.is_palindrome() << endl << "*******\n";
		list.print();
	string expected = "1 2 2 1"; 
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
			<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

int main() {
	test1();
	return 0;
}

