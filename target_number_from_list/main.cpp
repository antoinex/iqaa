/*
 * @file    : main.cpp
 * @author  : antoinex
 *
 * question :
 *	Given a list of numbers and a target unmber, write a program to determine
 * 	whether the target number can be caculated by applying all of the following operations:
 *		addition ( + )
 *		subtraction ( - )
 *		multiplication ( x )
 *		division ( ÷ )
 *
 *	You can assume that parentheses are automatically added when necessary.
 *	Each number can be used once.
 *	Assume no number is repeated.
 *
 * example   :
 *	List of numbers = [ 1, 2, 3, 4 ]
 *	Target = 21
 *	Output = true, because ( 1 + 2 ) x ( 3 + 4 ) = 21.
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

/*
	Assumptions:
		All numbers in nums_list are unique.
*/

// Allowed operations : +, -, *, /
bool is_possible(std::vector<int> const& nums_list, int target);

int main()
{
	std::vector<int> nums_list = { 1, 9, 5, 7 };
	int target = 7;

	std::cout << is_possible(nums_list, target) << std::endl << std::endl;

	nums_list = { 1, 2, 3, 4 };
	target = 21;

	std::cout << is_possible(nums_list, target) << std::endl;

	return 0;
}

bool is_possible_helper(
	std::vector<int> const& nums_list,
	int target,
	std::unordered_set<int> & seen,
	int curr_total,
	std::vector<std::string> & equation)
{
	if (seen.size() == nums_list.size())
	{
		return curr_total == target;
	}

	for (int const& num : nums_list)
	{
		if (seen.find(num) == seen.end())
		{
			seen.insert(num);

			int new_total = curr_total + num;
			equation.push_back("+");
			equation.push_back(std::to_string(num));
			if (is_possible_helper(nums_list, target, seen, new_total, equation))
			{
				return true;
			}

			new_total = curr_total - num;
			equation[equation.size() - 2] = "-";
			if (is_possible_helper(nums_list, target, seen, new_total, equation))
			{
				return true;
			}

			new_total = curr_total * num;
			equation[equation.size() - 2] = "*";
			if (is_possible_helper(nums_list, target, seen, new_total, equation))
			{
				return true;
			}

			// Note that we cannot divide by zero, so we should check that the divisor is NOT zero.
			if (num != 0)
			{
				new_total = curr_total / num;
				equation[equation.size() - 2] = "/";
				if (is_possible_helper(nums_list, target, seen, new_total, equation))
				{
					return true;
				}
			}

			seen.erase(num);

			equation.pop_back();
			equation.pop_back();
		}
	}

	return false;
}

void print_equation(std::vector<std::string> const& equation, int target)
{
	for (std::string const& str : equation)
	{
		std::cout << str.c_str() << " ";
	}

	std::cout << " = " << target << std::endl;
}

bool is_possible(std::vector<int> const& nums_list, int target)
{
	for (int const& num : nums_list)
	{
		// Since we are assuming that all numbers in the list of numbers are unique,
		// we can use a set to track the numbers we have already seen/used.
		// If, however, the numbers in the list were not unique, then we could instead
		// use the set to track their indices in the list of numbers.
		std::unordered_set<int> seen;
		seen.insert(num);

		std::vector<std::string> equation;
		equation.push_back(std::to_string(num));

		if (is_possible_helper(nums_list, target, seen, num, equation))
		{
			print_equation(equation, target);
			return true;
		}
	}

	return false;
}
