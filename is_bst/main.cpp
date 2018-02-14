/*
 * @file    : main.cpp
 * @author  : antoinex
 *
 * question : Write a program to check if a binary tree is a BST or not.
 */

#include <iostream>
#include <limits>

// Ideally, we should use unique_ptr's here instead of naked pointers.
struct node
{
	int val;
	node * left = nullptr;
	node * right = nullptr;

	node (int val_in)
	{
		val = val_in;
	}
};

// Check if a binary tree is a Binary Search Tree.
bool is_bst(node * nd);

void test_success_00();
void test_failure_00();

int main()
{
	test_success_00();

	test_failure_00();

	return 0;
}

bool is_bst_helper(node * nd, int min, int max)
{
	if (nd == nullptr)
	{
		return true;
	}

	if (nd->val <= min)
	{
		return false;
	}

	if (nd->val >= max)
	{
		return false;
	}

	if (is_bst_helper(nd->left, min, nd->val))
	{
		return is_bst_helper(nd->right, nd->val, max);
	}

	return false;
}

bool is_bst(node * nd)
{
	if (nd != nullptr)
	{
		// If the left subtree is a valid BST,
		// then return the outcome of checking if the right subtree is a valid BST.
		if (is_bst_helper(nd->left, std::numeric_limits<int>::min(), nd->val))
		{
			return is_bst_helper(nd->right, nd->val, std::numeric_limits<int>::max());
		}

		return false;
	}

	return true;
}

/*
				 20
			         .
			      .    .
			   .         .
			.              .
		       10		30
		       .
		     .	  .
		  .	     .
		8		12
			        .
			     .    .
			  11       13
*/
void test_success_00()
{
	node * root = new node(20);

	node * left_10 = new node(10);
	root->left = left_10;

	node * right_30 = new node(30);
	root->right = right_30;

	node * left_8 = new node(8);
	left_10->left = left_8;

	node * right_12 = new node(12);
	left_10->right = right_12;

	node * left_11 = new node(11);
	right_12->left = left_11;

	node * right_13 = new node(13);
	right_12->right = right_13;

	std::cout << is_bst(root) << std::endl;

	delete right_13;
	delete left_11;
	delete right_12;
	delete left_8;
	delete left_10;
	delete right_30;
	delete root;
}

/*
				 20
			         .
			      .    .
			   .         .
			.              .
		       10		30
		       .
		     .	  .
		  .	     .
		8		27
			        .
			     .    .
			  11       13
*/
void test_failure_00()
{
	node * root = new node(20);

	node * left_10 = new node(10);
	root->left = left_10;

	node * right_30 = new node(30);
	root->right = right_30;

	node * left_8 = new node(8);
	left_10->left = left_8;

	node * right_27 = new node(27);
	left_10->right = right_27;

	node * left_11 = new node(11);
	right_27->left = left_11;

	node * right_13 = new node(13);
	right_27->right = right_13;

	std::cout << is_bst(root) << std::endl;

	delete right_13;
	delete left_11;
	delete right_27;
	delete left_8;
	delete left_10;
	delete right_30;
	delete root;
}
