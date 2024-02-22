#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
	int data { };
	Node *next { };
	Node(int data) :
			data(data) {
	}
	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList {
private:
	Node *head { };
	Node *tail { };
	int length = 0;	// let's maintain how many nodes

	vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node *node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node *node) {
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
	LinkedList& operator=(const LinkedList &another) = delete;

	void debug_print_address() {
		for (Node *cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}

	void debug_print_node(Node *node, bool is_seperate = false) {
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
		for (int i = 0; i < (int) debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}

	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node *cur = head; cur; cur = cur->next) {
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
		Node *prev = nullptr;
		for (Node *cur = head; cur; prev = cur, cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?

		assert(length == len);
		assert(length == (int)debug_data.size());
		assert(prev == tail);	// last node is tail
	}

	////////////////////////////////////////////////////////////

	void print() {
		for (Node *cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node *node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node *node) {
		debug_add_node(node);
		++length;
	}

	void insert_end(int value) {
		Node *item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else
			tail->next = item, tail = item;

		debug_verify_data_integrity();
	}
    Node* get_nth(int n) const
	{
		assert(n > 0);
		int idx = 1;
		for (Node* cur = head; cur; cur = cur->next, idx++)
		{
			if (idx == n)
				return cur;
		}
		return nullptr;
	}
    /////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////
    //                  Destructor                         //   
    /////////////////////////////////////////////////////////
    ~LinkedList(){
        Node *cur;
        while(head)
        {
            cur = head;
            head = head->next;
            delete cur;
        }
    }
	////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    //                  insert front                         //
    //////////////////////////////////////////////////////////
    void insert_front(int value)
    {
        Node* front = new  Node(value);
        front->next = head;
        head = front;
        add_node(front);
        debug_verify_data_integrity();
    }
    ////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////////
    //                  delete first                         //
    //////////////////////////////////////////////////////////
    void delete_first()
	{
		if (head)
		{
			Node  *cur = head;
			head = head->next;
			delete_node(cur);
		}
		if (!head)
			tail = nullptr;
		debug_verify_data_integrity();
    }
	////////////////////////////////////////////////////

	/////////////////////////////////////////////////////
	//                 get_nth_back                    //
	////////////////////////////////////////////////////
    Node* get_nth_back(int n)
	{
		int idx = 1;
		int n_rev = length - n + 1;
		for (Node* cur = head; cur; cur = cur->next, idx++)
		{
			if (idx == n_rev)
				return cur;
		}
		return nullptr;
	}
    /////////////////////////////////////////////////////

	/////////////////////////////////////////////////////
    //                  is_same_with_len              //
    ////////////////////////////////////////////////////
	bool is_same_with_len(const LinkedList &l)
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
    ///////////////////////////////////////////////////

    //////////////////////////////////////////////////
    //                  is_Same                     //
    //////////////////////////////////////////////////
    bool is_same(const LinkedList& l)
	{
		Node* cur1 = head;
		Node* cur2;
		for (cur2 = l.head; cur1 && cur2; cur1 = cur1->next, cur2 = cur2->next)
		{
			if (cur1->data != cur2->data)
				return false;
		}
		if ((cur1 && !cur2) || (!cur1 && cur2))
			return false;
		return true;
	}
};

void test1() {
	cout << "\n\ntest1\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
    list.insert_front(0);
    list.insert_front(-1);
	list.insert_front(-2);
	list.insert_front(-3);
	// some actions
	list.print();

	string expected = "-3 -2 -1 0 1 2 3";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
				<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

void test2() {
	cout << "\n\ntest2\n";
	LinkedList list;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
    list.insert_front(-1);
	list.insert_front(-2);
	list.insert_front(-3);
	// some actions
	list.print();

	string expected = "-3 -2 -1 1 2 3 4";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
				<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
}
void test3() {
	cout << "\n\ntest2\n";
	LinkedList list;
	LinkedList list2;
	LinkedList list3;
	cout << "is same:  " << list.is_same_with_len(list2) << endl;
	cout << "is same:  " <<  list.is_same(list2) << endl;
	
	list3.insert_end(0);
	list3.insert_end(2);
	list3.insert_end(3);
	list3.insert_end(4);
	
	list2.insert_end(1);
	list2.insert_end(2);
	list2.insert_end(3);
	list2.insert_end(4);

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(3);
	list.insert_end(4);
	cout << "1,2 is same:  " << list.is_same_with_len(list2) << endl;
	cout << "1,3 is same:  " << list.is_same_with_len(list3) << endl;
	cout << "2,3 is same:  " << list2.is_same_with_len(list3) << endl;
	list3.delete_first();
	list2.delete_first();
	cout << "1,2 is same m2:  " << list.is_same(list2) << endl;
	cout << "1,3 is same m2:  " << list.is_same(list3) << endl;
	cout << "2,3 is same m2:  " << list2.is_same(list3) << endl;

	Node* ond1 = list.get_nth_back(1);
	Node* ond2 = list.get_nth_back(2);
	Node* ond3 = list.get_nth_back(3);
	Node* ond4 = list.get_nth_back(4);
		// some actions
	list.print();

	string expected = "1 2 3 4";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
			<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
	cout << ond1->data << endl;
	cout << ond2->data << endl;
	cout << ond3->data << endl;
	cout << ond4->data << endl;

}

int main() {
	test1();
	test2();
	test3();

	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}

