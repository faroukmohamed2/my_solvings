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
		if (n < 0)
        cout << "Error " << endl;
		int idx = 1;
		for (Node* cur = head; cur; cur = cur->next, idx++)
		{
			if (idx == n)
				return cur;
		}
		return nullptr;
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
    ///////////////////////////////////////////////////

    //////////////////////////////////////////////////
    //          without length and tail             //
    /////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////

    ///////////////////////////////////////////////////
    //              delete with key                 //
    //////////////////////////////////////////////////
    void delete_node_with_key(int value)
	{
		int idx = search(value);
		delete_nth_node(++idx);
	}
    //////////////////////////////////////////////////

    //////////////////////////////////////////////////
    //                swap_pairs                    //
    //////////////////////////////////////////////////
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
    ////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////
    //                  reverse                       //
    ////////////////////////////////////////////////////
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
    /////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////
    //             delete_even_positions               //
    /////////////////////////////////////////////////////
	void delete_even_position()
	{
		Node* cur = head;
		Node* cur2 = head;
		while(cur && cur->next)
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
    ////////////////////////////////////////////////
    
    ////////////////////////////////////////////////
    //             insert_to_be_sorted            //
    ////////////////////////////////////////////////
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
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    //              swap head and tail                //
    ////////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////

    ///////////////////////////////////////////////////
    //              delete dublicate                //
    //////////////////////////////////////////////////
	}
	void delete_dublicates()
	{
		if (!head || !head->next)
			return;
		for (Node* cur = head; cur; cur = cur->next)
		{
			int temp = cur->data;
			Node* prev = cur;
			for (Node *cur1 = cur->next; cur1; cur1 = cur1->next)
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
    ////////////////////////////////////////////////

    ///////////////////////////////////////////////
    //          remove last occurrence          //
    //////////////////////////////////////////////
    Node* delete_link(Node* prev, Node* cur)
	{
		if (prev && cur)
		{
			prev->next = cur->next;
			delete_node(cur);
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
		Node* del = head;
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
    ////////////////////////////////////////////
    
    ////////////////////////////////////////////
    //              move to back              //
    ////////////////////////////////////////////
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
void test4()
{
	cout << "\ntest4\n";
	LinkedList list;
	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(1);


	list.print();
	list.remove_last_occurrence(1);
	list.print();
	string expected = "1 2 1 2";
	string result = list.debug_to_string();
	if (expected != result) {
		cout << "no match:\nExpected: " << expected << "\nResult  : " << result
			<< "\n";
		assert(false);
	}
	list.debug_print_list("********");
}
void test5()
{
	cout << "\ntest5\n";
	LinkedList list;
	list.insert(10);
	list.insert(115);
	list.insert(14);
	list.insert(3);
	list.insert(11);
	list.insert(-2);
	list.insert(12);
	list.insert(42);
	list.print();
	string expected = "-2 3 10 11 12 14 42 115";
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
	test2();
	test3();
    test4();
    test5();
	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}

