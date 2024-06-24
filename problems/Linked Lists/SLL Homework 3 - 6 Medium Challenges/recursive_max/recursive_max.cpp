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
	void reverse()
	{
		if (head)
		{
			Node* prv = head;
			Node* cur = head->next;
			while (cur)
			{
				Node* temp = cur->next;
				cur->next = prv;
				prv = cur;
				cur = temp;
			}
			Node* temp = head;
			head = tail;
			tail = temp;
			tail->next = nullptr;
		}
		debug_verify_data_integrity();
	}
	void delete_even_position()
	{
		Node* cur = head;
		Node* cur2 = head;
		while (cur && cur->next)
		{
			cur = cur->next->next;
			delete_node(cur2->next);
			cur2->next = cur;
			if (!cur)
			{
				tail = cur2;
			}
			cur2 = cur2->next;
		}
		debug_verify_data_integrity();

	}
	void insert(int value)
	{
		if (!head)
		{
			insert_end(value);
		}
		else if (value >= tail->data)
			insert_end(value);
		else if (value <= head->data)
			insert_front(value);
		else
		{
			Node* item = new Node(value);
			for (Node* cur = head; cur; cur = cur->next)
			{
				if (item->data >= cur->data && item->data <= cur->next->data)
				{
					Node* temp = cur->next;
					cur->next = item;
					item->next = temp;

				}
			}
			add_node(item);
		}
		debug_verify_data_integrity();
	}
	void swap_h_t()
	{
		if (head)
		{
			Node* tail_prev = head;
			Node* head_temp = head;
			Node* tail_temp = tail;
			if (tail_prev->next)
			{
				while (tail_prev->next->next)
					tail_prev = tail_prev->next;
				tail_prev->next = head;
				head = tail_temp;
				head->next = head_temp->next;
				tail = head_temp;
				tail->next = nullptr;
			}

		}
		debug_verify_data_integrity();
	}
	void left_rotate()
	{
		if (head && head->next)
		{
			Node* headtemp = head;
			head = head->next;
			tail->next = headtemp;
			tail = headtemp;
			tail->next = nullptr;
		}
		debug_verify_data_integrity();
	}
	void left_rotate(int k)
	{
		k %= length;
		for (int i = 0; i < k; i++)
			left_rotate();
	}
	void delete_dublicates()
	{
		if (!head || !head->next)
			return;
		for (Node* cur = head; cur; cur = cur->next)
		{
			int temp = cur->data;
			Node* prev = cur;
			for (Node* cur1 = cur->next; cur1; cur1 = cur1->next)
			{
				if (cur1->data == temp)
				{
					prev->next = cur1->next;
					delete_node(cur1);
					cur1 = prev;
					if (!cur1->next)
						tail = cur1;
				}
				else
					prev = prev->next;

			}
		}
		debug_verify_data_integrity();
	}
	Node* delete_link(Node* prev, Node* cur)
	{
		if (prev && cur)
		{
			prev->next = cur->next;
			delete_node(cur);
			cur = nullptr;
			if (!prev->next)
				tail = prev;
			return prev;
		}

	}
	void remove_last_occurrence(int key)
	{
		if (!head)
			return;
		Node* cur = head;
		Node* prev = nullptr;
  		Node* del = nullptr;
		for (; cur; cur = cur->next)
		{
			if (cur->next)
			{
				if (cur->next->data == key)
				{
					del = cur->next;
					prev = cur;
				}
			}
		}
		if (del == head)
		{
			delete_first();
			return;
		}

		if (del)
		{
			delete_link(prev, del);
		}
		debug_verify_data_integrity();
	}
	void move_to_back(int key)
	{
		if (!head || !head->next)
			return;
		Node* prev = head;
		Node* tailcpy = tail;
		for (Node* cur = head->next; cur != tailcpy; cur = cur->next)
		{
			if (cur->data == key)
			{
				insert_end(key);
				cur = delete_link(prev, cur);
			
			}
			else
				prev = prev->next;
		}
	}
	Node* embed_after(Node* back, int value)
	{
		Node* middle = new Node(value);
		middle->next = back->next;
		back->next = middle;
		add_node(middle);
		if (!middle->next)
			tail = middle;
		return middle;
	}
	void arrange_odd_even()
	{
		if (!head || !head->next)
			return;
		Node* cur = head->next->next;
		Node* prev = head->next;
		Node* back = head;
		int temp;
		for (; cur; cur = cur->next)
		{
			temp = cur->data;
			
			cur = delete_link(prev, cur);
			cur = cur->next;
			prev = prev->next;
			back = embed_after(back, temp);
			if (!cur)
				break;
		}
		debug_verify_data_integrity();
	}
	void insert_alternate(LinkedList& another)
	{
		Node* ancur = another.head;
		Node* cur = head;
		for (; ancur; ancur = ancur->next)
		{
			if (!cur)
			{
				insert_end(ancur->data);
			}
			else
			{
				cur = embed_after(cur, ancur->data);
				cur = cur->next;
			}

		}
		debug_verify_data_integrity();
	}


};
int GetMax_rec(Node* cur)
{
	if (!cur->next)
		return cur->data;
	int sub = GetMax_rec(cur->next);
	return max(sub, cur->data);
}
void test7()
{
	LinkedList l;
	l.insert_end(-9);
	l.insert_end(10);
	l.insert_end(-3);
	l.insert_end(92);
	l.insert_end(0);
	l.insert_end(9);
	cout << GetMax_rec(l.get_nth(1)) << endl;
	l.print();
	l.delete_negative();
	l.print();

}
int main() {
	test7();
	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}