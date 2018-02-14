/*
 * @file     : main.cpp
 * @author   : antoinex
 *
 * question  :
 *	Given an array 'arr' of integers (not necessarily distinct), we split the array into some number of "chunks" (partitions),
 *	and individually sort each chunk. After concatenating them, the result equals the sorted array.
 *	What is the most number of chunks we could have made?
 *
 * example   :
 *	Input       : arr = [ 5, 4, 3, 2, 1 ]
 *	Output      : 1
 *	Explanation :
 *		Splitting into two or more chunks will not return the required result.
 *		For example, splitting into [ 5, 4 ], [ 3, 2, 1 ] will result in [ 4, 5, 1, 2, 3 ] after concatenating the sorted chunks.
 *		However, this result isn't sorted. The only way to sort this is to consider the entire array as a chunk and sort it, resulting
 *		in just 1 chunk as the answer here.
 *
 * example   :
 *	Input       : arr = [ 2, 1, 3, 4, 5 ]
 *	Output      : 4
 * 	Explanation :
 *		We can split into two chunks, such as [ 2, 1 ], [ 3, 4, 4 ].
 *		However, splitting into [ 2, 1 ], [ 3 ], [ 4 ], [ 4 ] is the highest number of chunks possible.
 *
 * solutions :
 *
 *	Solution 1  :
 *	-------------
 * 	One solution is to parition 'arr' into 2 chunks : a left chunk, and a right chunk.
 *	Each chunk is then sorted.
 *	Afterwards, if the max value in the left chunk <= min value in the right chunk, we increment our count of chunks by 1.
 *	However, if the max value in the left chunk > min value in the right chunk, we expand the left chunk by 1 element, and
 *	shrink the right chunk by 1 element, and check again.
 *	After finding a chunk, we move onto the next elements in the array.
 *
 *	Example      :
 *	Let arr = [ 2, 1, 3, 4, 4 ]
 *
 *			      |
 *	First partition : [ 2 | 1, 3, 4, 4 ]
 *			      |
 *		After sorting each chunk, we have [ 2 ] and [ 1, 3, 4, 4 ]
 *		Since 2 <= 1 is false, we expand the left chunk.
 *			         |
 *	Second parition : [ 2, 1 | 3, 4, 4 ]
 *				 |
 *		After sorting each chunk, we have [ 1, 2 ] and [ 3, 4, 4 ]
 *		Since 2 <= 3, we increase our count of chunks to 1.
 *
 *		Since we have found one chunk, we omit it and partition the rest of the array.
 *
 *			      |
 *	Third partition : [ 3 | 4, 4 ]
 *			      |
 *		Aftre sorting each chunk, we have [ 3 ] and [ 4, 4 ]
 *		Since 3 <= 4, we increase our count of chunks to 2.
 *
 *		Since we have found another chunk, we omit it and partition the rest of the array.
 *
 *			      |
 *	Fourth parition : [ 4 | 4 ]
 *			      |
 *		After sorting each chunk, we have [ 4 ] and [ 4 ]
 *		Since 4 <= 4, we increase our count of chunks to 3.
 *
 *		Since we have found another chunk, we omit it and partition the rest of the array.
 *
 *	Fifth parition  : [ 5 ]
 *		We are at the last index, so we cannot really partition any further, so the last element is it's own chunk here
 *		Thus we increase our count of chunks to 4.
 *
 *	We return 4 as our answer.
 *
 *
 *	Solution 2      :
 *	-----------------
 *	Think of the end result of sorting the entire array (ascending order). This end result is achieved by sorting each chunk and concatenating.
 *	Thus, the array will be represented as such :
 *
 *		[ min0...max0 | min1...max1 | min2...max2 | min3...max3 | min4...max4 ]
 *
 *	Note that we have a pattern here:
 *
 *		min0 <= max0 <= min1 <= max1 <= min2 <= max2 <= min3 <= max3 <= min4 <= max4
 *
 *	So looking at this pattern, we can go in reverse order and find all the 'min' for each chunk.
 *	Since we don't know the actual chunks, we will simply find the 'min' at each index going in reverse order.
 *
 *	Alternatively, we can go in the forward order, and find the 'max' at each index.
 *
 *	Let's take option 1 (finding the 'min' values in reverse order):
 *
 *	Let arr = [ 2, 1, 3, 4, 4 ].
 *
 *	In reverse order, the min values are [ 1, 1, 3, 4 , 4 ].
 *
 *	Let's place the two arrays next to each other:
 *
 *		indices  0  1  2  3  4
 *		arr  = [ 2, 1, 3, 4, 4 ]
 *		mins = [ 1, 1, 3, 4, 4 ]
 *
 *	Looking back at the pattern above, we can iterate over 'arr' in the forward direction, and calculate the max value seen so far.
 *	So at index i in arr, if the max seen so far is <= mins[i + 1], then we increment our count of chunks by 1.
 *
 *	NOTE : The minimum number of chunks is 1, so we can start with that value.
 *	       And then iterate over arr from 0 to < arr.size() - 1, so that the mins[i + 1] doesn't go over the bounds of the mins array.
 */

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

int max_chunks_to_sorted_2(std::vector<int> const& arr);
int max_chunks_to_sorted_2_alt(std::vector<int> const& arr);

int main()
{
	std::vector<int> arr = { 5, 4, 3, 2, 1 };

	std::cout << max_chunks_to_sorted_2(arr) << std::endl;
	std::cout << max_chunks_to_sorted_2_alt(arr) << std::endl;

	arr = { 2, 1, 3, 4, 4 };

	std::cout << max_chunks_to_sorted_2(arr) << std::endl;
	std::cout << max_chunks_to_sorted_2_alt(arr) << std::endl;

	arr = { 4, 2, 2, 1, 1, 1, 1 };

	std::cout << max_chunks_to_sorted_2(arr) << std::endl;
	std::cout << max_chunks_to_sorted_2_alt(arr) << std::endl;

	return 0;
}

/*
 * @description :
 * 	This solution paritions 'arr' into 2 chunks : a left chunk, and a right chunk.
 *	Each chunk is then sorted. Afterwards, if the max value in the left chunk <= min value in the right chunk,
 *	we increment our count of chunks by 1.
 */
int max_chunks_to_sorted_2(std::vector<int> const& arr)
{
	if (arr.empty())
	{
		return -1;
	}

	if (arr.size() == 1)
	{
		return 1;
	}

	// Vector to hold the minimum values
	// so far while iterating in reverse order.
	std::vector<int> mins(arr.size());

	mins[arr.size() - 1] = arr.back();

	for (int i = arr.size() - 2; i >= 0; i--)
	{
		mins[i] = std::min(mins[i + 1], arr[i]);
	}

	// Now we could iterate over arr in the forward order
	// and keep track of all the maximum values so far, in another vector.
	// However, we don't need this extra vector. We can just use the max
	// value seen so far to determine the chunks without storing them.
	// This is because after we use a max value, we don't use it again,
	// thus no need to store it.

	// Minimum number of chunks = 1.
	int count = 1;

	int max = arr.front();

	for (std::size_t i = 0; i < arr.size() - 1; i++)
	{
		if (max <= mins[i + 1])
		{
			count++;
		}

		max = std::max(max, arr[i + 1]);
	}

	return count;
}

/*
 * This is an alternate solution, that solves the problem in the "reverse" format, compared to max_chunks_to_sorted_2 above.
 * We established above that the sorted array will be of the format:
 *
 *	[ min0...max0 | min1...max1 | min2...max2 | min3...max3 | min4...max4 ]
 *
 * Note that we have a pattern here:
 *
 *	min0 <= max0 <= min1 <= max1 <= min2 <= max2 <= min3 <= max3 <= min4 <= max4
 *
 * Looking at this pattern, we can iterate in the forward direction, over 'arr' to find the max so far at each index.
 * And then iterate over 'arr' in the reverse order, and compare the min so far, with the max so far in the opposite direction.
 *
 */
int max_chunks_to_sorted_2_alt(std::vector<int> const& arr)
{
	if (arr.empty())
	{
		return -1;
	}

	if (arr.size() == 1)
	{
		return arr.front();
	}

	std::vector<int> max_so_far(arr.size());

	max_so_far[0] = arr.front();

	for (int i = 1; i < arr.size(); i++)
	{
		max_so_far[i] = std::max(max_so_far[i - 1], arr[i]);
	}

	int curr_min = arr.back();

	int count = 1;

	for (int i = arr.size() - 1; i >= 1; i--)
	{
		if (curr_min >= max_so_far[i - 1])
		{
			count++;
		}

		curr_min = std::min(curr_min, arr[i - 1]);
	}

	return count;
}

