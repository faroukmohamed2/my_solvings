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
	Node(int data) :
		data(data) {
	}
	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList {
private:
	Node* head{ };
	Node* tail{ };
	int length = 0;	// let's maintain how many nodes

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
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

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
			return;
		}

		assert(head != nullptr);
		assert(tail != nullptr);
		assert(tail->next == nullptr);

		if (length == 1)
			assert(head == tail);
		else {
			assert(head != tail);

			if (length == 2)
				assert(head->next == tail);
			else if (length == 3) {
				assert(head->next);
				assert(head->next->next == tail);
			}
		}
		int len = 0;
		Node* prev = nullptr;
		for (Node* cur = head; cur; prev = cur, cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?

		assert(length == len);
		assert(length == (int)debug_data.size());
		assert(prev == tail);	// last node is tail
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

	void insert_end(int value) {
		Node* item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else
			tail->next = item, tail = item;
		tail->next = nullptr;

		debug_verify_data_integrity();
	}
	Node* get_nth(int n) const
	{
		if (n < 0 || n > length)
		{
			cout << "Error no number";
			return nullptr;
		}
		int idx = 0;
		for (Node* cur = head; cur; cur = cur->next)
		{
			if (++idx == n)
				return cur;
		}
		return nullptr;
	}
	void delete_negative()
	{
		if (!head)
			return;
		Node* prev = head;
		Node* cur = head->next;
		while (cur->next)
		{
			if (cur->data < 0)
			{
				cur = delete_link(prev, cur);
			}
			else
				prev = prev->next;
			cur = cur->next;
		}
		if (head->data < 0)
			delete_first();
	}
	void delete_nth_node(int n) {
		if (n < 1 || n > length)
			cout << "Error. No such nth node\n";
		else if (n == 1)
			delete_first();
		else {
			// Connect the node before nth with node after nth
			Node* before_nth = get_nth(n - 1);
			Node* nth = before_nth->next;
			bool is_tail = nth == tail;
			// connect before node with after
			before_nth->next = nth->next;
			if (is_tail)
				tail = before_nth;

			delete_node(nth);

			debug_verify_data_integrity();
		}
	}
	int search(int value) {
		int idx = 0;
		for (Node* cur = head; cur; cur = cur->next, idx++)
			if (cur->data == value) // Common Mistake to use head
				return idx;
		return -1;
	}
	/////////////////////////////////////////////////////////
	//                  Destructor                         //   
	/////////////////////////////////////////////////////////
	~LinkedList() {
		Node* cur;
		while (head)
		{
			cur = head;
			head = head->next;
			delete cur;
		}
	}
	////////////////////////////////////////////////////////////  
	void insert_front(int value)
	{
		Node* front = new  Node(value);
		add_node(front);
		front->next = head;
		head = front;
		if (length == 1)
			tail = head;
		debug_verify_data_integrity();
	}
	void delete_first()
	{
		if (head)
		{
			Node* cur = head;
			head = head->next;
			delete_node(cur);
		}
		if (!head)
			tail = nullptr;
		debug_verify_data_integrity();
	}
	Node* get_nth_back(int n)
	{
		//assert(n < length);
		int n_rev = length - n + 1;

		return get_nth(n_rev);
	}
	bool is_same_with_len(const LinkedList& l)
	{

		if (this->length == l.length)
		{
			if (length == 0)
				return true;
			for (int i = 1; i <= length; i++)
			{
				if (get_nth(i)->data != l.get_nth(i)->data)
					return false;
			}
			return true;
		}
		return false;
	}
	bool is_same(const LinkedList& l)
	{
		Node* cur1 = head;
		Node* cur2 = l.head;
		for (; cur1 && cur2; cur1 = cur1->next, cur2 = cur2->next)
		{
			if (cur1->data != cur2->data)
				return false;
		}
		if ((cur1 && !cur2) || (!cur1 && cur2))
			return false;
		return true;
	}
	void add_element(int value)
	{
		Node* item = new Node(value);
		item->next = head;
		head = item;
		add_node(item);
	}
	Node* get_tail() const
	{
		if (head)
			for (Node* cur = head; cur; cur = cur->next)
				if (!cur->next)
					return cur;
		return nullptr;
	}
	void delete_node_with_key(int value)
	{
		int idx = search(value);
		delete_nth_node(++idx);
	}
	void swap_pairs()
	{
		if (head && head->next)
		{
			for (Node* cur = head; cur && cur->next; cur = cur->next->next)
			{
				int temp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = temp;
			}
		}
	}
//////////////////////////////////////////////
//  		delete all repeated				//
//////////////////////////////////////////////
void remove_all_repeated()
{
	if (!head || !head->next)
		return;
	Node* prev = nullptr;
	Node* first = head;
	Node* last = head->next;
	while (last)
	{
		if (first->data != last->data)
		{
			prev = first;
			last = last->next;
			first = first->next;
		}
		else
		{
			while (last && last->data == first->data)
			{
				Node* temp = last;
				last = last->next;
				first->next = last;
				delete_node(temp);
			}
			if (!prev)
			{
					delete_node(first);
					first = last;
					head = first;
					if (last)
						last = last->next;
					else
						tail = prev;
			}
			else
			{
				delete_node(first);
				first = last;
				prev->next = first;
				if (last)
					last = last->next;
				else
					tail = prev;
			}
		}
	}
	debug_verify_data_integrity();
}
};
void test6()
{
	cout << "\ntest6\n";
	LinkedList list;
	LinkedList list1;
	list.insert_end(10);
	list.insert_end(10);
	list.insert_end(10);
	list.insert_end(10);
	list.insert_end(11);
	list.insert_end(12);
	list.insert_end(12);
	list.insert_end(12);
	list.insert_end(13);
	list.insert_end(14);
	list.insert_end(14);
	list.insert_end(14);

	//list.insert_end(13);

	//list.add_huge(list1);
	list.remove_all_repeated();
	list.print();
	string expected = "11 13";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
			<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
}
int main()
{
	test6();
	cout << "\n\nNO RTE\n";
	return 0;
}