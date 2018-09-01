/*
 * @file     : main.cpp
 * @author   : antoinex
 *
 * @question :
 * 	Given a video with a number of ad slots, and a collection of ads, write an algorithm to determine the maximum ad profit for the video.
 *
 * @note     :
 *	Each ad can be used once. For each ad inserted into ad slot, the duration of the ad should be less than or equal to the duration of the slot.
 *
 * @example  :
 *	Durations of the ad slots of a video (each value in seconds) = [3, 2]
 *	Collection of ads for this video (format of each ad is { duration in seconds, profit in $ }) = [ {2, 9}, {2, 1}, {3, 4}, {4, 20}]
 *
 *	To obtain the max profit, we insert the {3, 4} ad into the video's 3-second ad slot, and then the {2, 9} ad into the video's 2-second ad slot.
 *	This gives us a total profit of $4 + $9 = $13, which is the max profit we can make in this scenario.
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

struct ad
{
	unsigned int duration;
	unsigned int profit;

	ad (
		unsigned int duration_in,
		unsigned int profit_in)
	   : duration(duration_in)
	   , profit(profit_in)
	{
	}
};

std::vector<ad> ad_sequence;

unsigned int get_max_ad_profit(
	std::vector<unsigned int> const& ad_slots,
	std::vector<ad> const& ad_collection);

std::vector<unsigned int> get_durations_from_ad_collection(std::vector<ad> const& ad_collection);

ad get_ad_with_max_profit_for_given_duration(
	unsigned int duration,
	std::vector<ad> & ad_collection);

unsigned int calculate_max_profit(std::vector<ad> const& ads);

void print_matrix(std::vector< std::vector< std::vector<ad> > > const& matrix);

int main()
{
	std::vector<ad> ad_collection =
	{
		{ 2, 9 },
		{ 2, 1 },
		{ 3, 4 },
		{ 4, 20 }
	};

	std::vector<unsigned int> ad_slots = { 3, 2 };

	unsigned int max_ad_profit = get_max_ad_profit(ad_slots, ad_collection);
	std::cout << "max profit = " << max_ad_profit << std::endl;

	ad_collection =
	{
		{ 2, 9 },
		{ 2, 1 },
		{ 2, 4 },
		{ 3, 4 },
		{ 3, 5 }
	};

	ad_slots = { 2, 3, 2 };

	max_ad_profit = get_max_ad_profit(ad_slots, ad_collection);
	std::cout << "max profit = " << max_ad_profit << std::endl;

	return 0;
}

/*
 * Using the example from above:
 *	ad_slots = [3, 2]
 *	ad_collection = [ {2, 9}, {2, 1}, {3, 4}, {4, 20}]
 *
 * So we can create a maxtrix to determine the max ad profits for each scenario depending on the restrictions given.
 * For example, if we were given only 1 ad slot, with a duration of 2-seconds, and the same ad collection above,
 * then the max ad profit will be from {2, 9}, which is $9. The matrix below lists out all possibilities. We are
 * going to use it for memoization so that we can solve this problem using Dynamic Programming.
 *
 * 					   	   ad slots
 *
 *					   |    0s    |    2s    |    3s    |
 *					---|----------|----------|----------|-
 *					   | {0s, $0} | {0s, $0} | {0s, $0} |
 *					0s |	      |		 |	    |
 *					---|----------|----------|----------|-
 *					   | {0s, $0} | {2s, $9} | {2s, $9} |
 *					2s |          |          | {2s, $1} |
 *			ad durations	---|----------|----------|----------|-
 *					   | {0s, $0} | {2s, $9} | {2s, $9} |
 *					3s |          |	         | {3s, $4} |
 *					---|----------|----------|----------|-
 *					   | {0s, $0} | {2s, $9} | {2s, $9} |
 *					4s |          |          | {3s, $4} |
 *					---|----------|----------|----------|-
 *
 * How to read this matrix?
 *	Ignore the 0s ad slots column. That column is only added for simplification of logic.
 *	Ignore the 0s ad durations row. That row is only added for simplification of logic.
 *
 * 	2nd row, 2nd column :
 *		Given a 2-second ad slot,
 *		and all the 2-second ads from the collection above,
 *		the max profit that can be made will be from {2s, $9} => $9.
 *
 *	2nd row, 3rd column : 
 *		Given a 2-second and a 3-second ad slot,
 *		and all the 2-second ads from the collection above,
 *		the max profit that can be made will be from {2s, $9} + {2s, $1} => $9 + $1 = $10.
 *
 *	3rd row, 2nd column :
 *		Given a 2-second ad slot,
 *		and all the 2-second and 3-second ad slots from the collection above,
 *		the max profit that can be made will be from {2s, $9} => $9.
 *
 *	3rd row, 3rd column :
 *		Given a 2-second and a 3-second ad slot,
 *		and all the 2-second and 3-second ad slots from the collection above,
 *		the max profit that can be made will be from {2s, $9} + {3s, $4} => $9 + $4 = $13.
 *
 *	4th row, 2nd column :
 *		Given a 2-second ad slot,
 *		and all the 2-second and 3-secnd and 4-second ad slots from the collection above,
 *		the max profit that can be made will be from {2s, $9} => $9.
 *
 *	4th row, 3rd column :
 *		Given a 2-second and a 3-second slot,
 *		and all the 2-second and 3-second and 4-second ad slots from the collection above,
 *		the max profit that can be made will be from {2s, $9} + {3s, $4} => $9 + $4 = $13.
 */
unsigned int get_max_ad_profit(
	std::vector<unsigned int> const& ad_slots,
	std::vector<ad> const& ad_collection)
{
	// Make a copy of ad_slots so that we can sort it.
	std::vector<unsigned int> ad_slots_copy = ad_slots;

	// Make a copy of ad_collection.
	std::vector<ad> ad_collection_copy = ad_collection;

	// Add a dummy 0s ad slot. This is assuming that ad_slots doesn't contain a zero slot.
	ad_slots_copy.push_back(0);

	// Sort ad_slots_copy in increasing order for memoization matrix.
	std::sort(ad_slots_copy.begin(), ad_slots_copy.end(), std::less<unsigned int>());

	// Get a list of unique, sorted ad durations from ad_collection.
	std::vector<unsigned int> durations = get_durations_from_ad_collection(ad_collection);

	// Create matrix for memoization.
	std::vector< std::vector< std::vector<ad> > > matrix(
		durations.size(),
		std::vector< std::vector<ad> >(ad_slots_copy.size()));

	// Populate zeroth column of matrix with {0s, $0} dummy ads.
	for (std::size_t i = 0; i < matrix.size(); i++)
	{
		matrix[i][0].push_back({0, 0});
	}

	// Populate zeroth row of matrix with {0s, $0} dummy ads.
	// We start at 1 because the [0][0] was populated above.
	for (std::size_t i = 1; i < matrix[0].size(); i++)
	{
		matrix[0][i].push_back({0, 0});
	}

	// Populate the remaining rows and columns of matrix with real data.
	for (std::size_t i = 1; i < matrix.size(); i++)
	{
		unsigned int duration = durations[i];

		for (std::size_t j = 1; j < matrix[0].size(); j++)
		{
			unsigned int ad_slot = ad_slots_copy[j];
			// std::cout << duration << "->" << ad_slot << std::endl;

			if (duration > ad_slot)
			{
				// If the current duration is greater than the ad slot, then we just copy down in the matrix.
				matrix[i][j] = matrix[i - 1][j];
			}
			else
			{
				// If the current duration is less than/equal to the ad slot, then we copy right in the matrix.
				matrix[i][j] = matrix[i][j - 1];

				// Get the ad with the max profit for the given duration, and remove it from ad_collection_copy.
				ad a = get_ad_with_max_profit_for_given_duration(duration,  ad_collection_copy);

				if (a.duration > 0 && a.profit > 0)
				{
					matrix[i][j].push_back(a);
				}
			}
		}
	}

	print_matrix(matrix);

	return calculate_max_profit(matrix[matrix.size() - 1][matrix[0].size() - 1]);
}

std::vector<unsigned int> get_durations_from_ad_collection(std::vector<ad> const& ad_collection)
{
	std::unordered_set<unsigned int> durations_set;

	// Assuming that we don't have an actual ad with a zero-second duration.
	durations_set.insert(0);

	for (ad const& a : ad_collection)
	{
		durations_set.insert(a.duration);
	}

	std::vector<unsigned int> result(
		durations_set.begin(),
		durations_set.end());

	std::sort(
		result.begin(),
		result.end(),
		std::less<unsigned int>());

	return result;
}

ad get_ad_with_max_profit_for_given_duration(
	unsigned int duration,
	std::vector<ad> & ad_collection)
{
	ad a (0, 0);

	unsigned int profit = 0;
	int index = -1;

	for (std::size_t i = 0; i < ad_collection.size(); i++)
	{
		ad const& temp_ad = ad_collection[i];

		if (temp_ad.duration == duration && temp_ad.profit > profit)
		{
			index = static_cast<int>(i);
			profit = temp_ad.profit;
		}
	}

	if (index > -1)
	{
		a = ad_collection[index];
		ad_collection.erase(ad_collection.begin() + index);
	}

	return a;
}

unsigned int calculate_max_profit(std::vector<ad> const& ads)
{
	unsigned int profit = 0;

	for (ad const& a : ads)
	{
		profit += a.profit;
	}

	return profit;
}

void print_matrix(std::vector< std::vector< std::vector<ad> > > const& matrix)
{
	for (std::vector< std::vector<ad> > const& vec : matrix)
	{
		for (std::vector<ad> const& v : vec)
		{
			std::cout << "[";
			
			for (ad const& temp_ad : v)
			{
				std::cout << "{" << temp_ad.duration << "," << temp_ad.profit << "},";
			}

			std::cout << "], ";
		}

		std::cout << std::endl;
	}
}
