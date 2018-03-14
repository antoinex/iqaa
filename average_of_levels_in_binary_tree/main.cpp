/*
 * @file     : main.cpp
 * @author   : antoinex
 *
 * @question :
 *	Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
 *
 * @note     :
 *	The range of each node's value is in the range of 32-bit signed integer.
 *
 * @example  :
 *	Given the binary tree below,
 *
 *		3
 *		.
 *	     .    .
 *	     9    20
 *		  .
 *		.    .
 *		15   7
 *
 *	the output will be [ 3.0, 14.5, 11.0 ].
 *	This is because:
 *		at level 0, the tree has only 3,
 *		at level 1, the tree has 2 nodes, so the average is (9 + 20) / 2 = 14.5,
 *		at level 2, the tree has 2 nodes, so the average is (15 + 7) / 2 = 11.0.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

struct TreeNode
{
	int val = 0;
	TreeNode * left = nullptr;
	TreeNode * right = nullptr;

	TreeNode (int x)
		: val(x)
	{
	}
};

void print(std::vector<double> averages);

std::vector<double> average_of_levels_1(TreeNode * root);

void get_map_of_levels_info(
	TreeNode * node,
	int level,
	std::unordered_map<int, std::pair<long, int> > & map_of_levels_info);

std::vector<double> average_of_levels_2(TreeNode * root);

int main()
{
	TreeNode * root = new TreeNode(3);

	root->left = new TreeNode(9);
	TreeNode * node20 = new TreeNode(20);
	root->right = node20;

	node20->left = new TreeNode(15);
	node20->right = new TreeNode(7);

	std::vector<double> avg = average_of_levels_1(root);
	print(avg);

	avg = average_of_levels_2(root);
	print(avg);

	return 0;
}

void print(std::vector<double> averages)
{
	std::cout << "{ ";

	std::cout << std::fixed;

	for (double const& i : averages)
	{
		// Print out each double to 1 decimal place.
		std::cout << std::setprecision(1) << i << ", ";
	}

	std::cout << "}" << std::endl;
}

/*
 * This solution uses breadth-first traversal to determine the nodes
 * at each level and then calculates their average on the fly.
 */
std::vector<double> average_of_levels_1(TreeNode * root)
{
	std::vector<double> averages;

	if (root != nullptr)
	{
		std::queue<TreeNode*> q;

		q.push(root);

		while (!q.empty())
		{
			std::size_t num_elements = q.size();

			long sum = 0;

			for (std::size_t i = 0; i < num_elements; i++)
			{
				TreeNode * node = q.front();

				sum += node->val;

				if (node->left != nullptr)
				{
					q.push(node->left);
				}

				if (node->right != nullptr)
				{
					q.push(node->right);
				}

				q.pop();
			}

			averages.push_back(sum / (static_cast<double>(num_elements)));
		}
	}

	return averages;
}

/*
 * This helper method traverses a tree breadth-first, generating a mapping
 * of levels to the sum of their values and their count. So for the example
 * above, this function will generate the following map:

 * key (level)		value (pair of sum of each nodes 'val', and node count)
 * -------------------------------------------------------------------------------
 * 0			[ 3, 1 ]
 * 1			[ 9 + 20, 2 ]
 * 2			[ 15 + 7, 2 ]
 */
void get_map_of_levels_info(
	TreeNode * node,
	int level,
	std::unordered_map<int, std::pair<long, int> > & map_of_levels_info)
{
	if (node != nullptr)
	{
		// p.first = sum
		// p.second = count of nodes at current level
		std::pair<long, int> & p = map_of_levels_info[level];
		p.first += node->val;
		p.second++;

		get_map_of_levels_info(node->left, level + 1, map_of_levels_info);
		get_map_of_levels_info(node->right, level + 1, map_of_levels_info);
	}
}

/*
 * This solution uses the depth-first traversal method above,
 * 'get_map_of_levels_info' to get a mapping of level to the
 * sum of the 'val's of each node at that level, and the count
 * of the nodes at that level.
 */
std::vector<double> average_of_levels_2(TreeNode * root)
{
	std::vector<double> averages;

	if (root != nullptr)
	{
		std::unordered_map<int, std::pair<long, int> > map_of_levels_info;

		get_map_of_levels_info(root, 0, map_of_levels_info);

		for (std::size_t i = 0; i < map_of_levels_info.size(); i++)
		{
			std::pair<long, int> const& p = map_of_levels_info[static_cast<int>(i)];

			averages.push_back(p.first / (static_cast<double>(p.second)));
		}
	}

	return averages;
}
