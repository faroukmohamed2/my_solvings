#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

struct TreeNode {
	int val{ };
	TreeNode* left{ };
	TreeNode* right{ };
	TreeNode(int val) : val(val) { }
};


struct BinaryTree {
	TreeNode* root{ };
	BinaryTree(int root_value) :
		root(new TreeNode(root_value)) {
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		TreeNode* current = this->root;
		// iterate on the path, create all necessary TreeNodes
		for (int i = 0; i < (int)values.size(); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new TreeNode(values[i]);
				else
					assert(current->left->val == values[i]);
				current = current->left;
			}
			else {
				if (!current->right)
					current->right = new TreeNode(values[i]);
				else
					assert(current->right->val == values[i]);
				current = current->right;
			}
		}
	}

	void _print_inorder(TreeNode* current) {
		if (!current)
			return;
		_print_inorder(current->left);
		cout << current->val << " ";
		_print_inorder(current->right);
	}


	void print_inorder() {
		_print_inorder(root);
		cout << "\n";
	}
	///////////////////////////////////
	//        tree hight             //
	///////////////////////////////////
	int TreeHight(TreeNode * cur)
	{
		if (!cur)
			return 0;
		int l = TreeHight(cur->left);
		int r = TreeHight(cur->right);
		return max(l, r) + 1;
	}


};
///////////////////////////////////
//			max Tree			//
//////////////////////////////////
int tree_max(TreeNode* root)
{
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return root->val;
	int l = tree_max(root->left);
	int r = tree_max(root->right);
	return max(max(l,r), root->val);
}

int main() {
	BinaryTree tree(1);
	cout << tree_max(tree.root) << endl;
	tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
	cout << tree_max(tree.root) << endl;
	tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
	cout << tree_max(tree.root) << endl;
	tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
	cout << tree_max(tree.root) << endl;
	tree.add({ 3, 61, 10 }, { 'R', 'R', 'L' });
	cout << tree_max(tree.root) << endl;
	tree.print_inorder();
	// 7 4 8 2 5 9 1 3 10 6

	return 0;
}

