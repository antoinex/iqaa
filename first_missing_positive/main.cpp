/*
 * @file     : main.cpp
 * @author   : antoinex
 *
 * @question :
 *	Given an unsorted integer array, find the first missing positive integer.
 *	Your algorithm should run in O(n) time and uses constant space.
 *
 * @example  :
 *	Given [ 1, 2, 0 ], return 3.
 *	Give [ 3, 4, -1, 1 ], return 2.
 *
 * @solution :
 *	The idea here is that we want to "sort" the vector so that all the numbers x, such that 1 <= x <= vector.size(),
 *	are positioned at their "correct" indices. This means that for each value x, it's correct index is x - 1.
 *	For all values y, such that 0 >= y > vector.size(), they can be at any index in the vector, as long as they are
 *	not occupying the "correct" index or the x-values.
 *
 *	Assuming we have this vector : nums = [ 3, 5, -1, 1 ].
 *	Then x = ( 3, 1 ). The correct index for 3 is 2, and the correct index for 1 is 0.
 *	Then y = ( 5, -1 ). They can be at any of the remaining indices in nums.
 *
 *	After "sorting/re-arranging" nums, we will get an output similar to:
 *
 *		indices	  0  1  2   3
 *		nums	[ 1, 5, 3, -1 ]
 *
 *	Now all we have to do is to iterate over nums, and check to see if each index i has a value equal to i + 1.
 *	If not, we return i + 1 as the first missing positive number.
 */

#include <iostream>
#include <vector>
#include <algorithm>

int first_missing_positive(std::vector<int> & nums);

int main()
{
	std::vector<int> nums = { 3, 5, -1, 1 };
	std::cout << first_missing_positive(nums)  << std::endl;

	nums = { 1, 2, 0 };
	std::cout << first_missing_positive(nums)  << std::endl;

	nums = { -7, -6, 4, 5, 3 };
	std::cout << first_missing_positive(nums)  << std::endl;

	return 0;
}

int first_missing_positive(std::vector<int> & nums)
{
	if (nums.empty())
	{
		// If the vector is empty,
		// the first positive number is simply the first positive integer, which is 1.
		// This special case is not needed because we return nums.size() + 1 below, which will take care of this.
		// It is only here for the purposes of micro-optimization.
		return 1;
	}

	// Re-arrange the x's and y's in nums.
	for (std::size_t i = 0; i < nums.size(); i++)
	{
		while ((nums[i] > 0) && (nums[i] <= static_cast<int>(nums.size())) && (nums[nums[i] - 1] != nums[i]))
		{
			std::swap(nums[nums[i] - 1], nums[i]);
		}
	}

	// Check the indices against the values.
	for (std::size_t i = 0; i < nums.size(); i++)
	{
		if (nums[i] != static_cast<int>(i + 1))
		{
			return i + 1;
		}
	}

	return nums.size() + 1;
}
