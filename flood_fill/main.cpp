/*
 * @file     : main.cpp
 * @author   : antoinex
 *
 * @question :
 *	An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65,535).
 *	FYI : 65,535 is the maximum value of an 'unsigned short int', and the minimum value is 0.
 *
 *	Given a coordina te (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value 'newColor',
 *	"flood fill" the image.
 *
 *	To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the
 *	same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the
 *	starting pixel), and so on. Replace the color of all of the aforementioned pixels with the 'newColor'.
 *
 *	At the end, return the modified image.
 *
 * @example   :
 *
 *	Inputs
 *		image
 *			  | 0 | 1 | 2 |
 *			--|---|---|---|-
 *			0 | 1 | 1 | 1 |
 *			--|---|---|---|-
 *			1 | 1 | 1 | 0 |
 *			--|---|---|---|-
 *			2 | 1 | 0 | 1 |
 *			--|---|---|---|-
 *
 *
 *		sr = 1, sc = 1
 *		Thus image[sr][sc] = image[1][1] = 1.
 *
 *		newColor = 2
 *
 *	Output
 *		image
 *			  | 0 | 1 | 2 |
 *			--|---|---|---|-
 *			0 | 2 | 2 | 2 |
 *			--|---|---|---|-
 *			1 | 2 | 2 | 0 |
 *			--|---|---|---|-
 *			2 | 2 | 0 | 1 |
 *			--|---|---|---|-
 */

#include <iostream>
#include <vector>

std::vector<std::vector<int> > flood_fill(
	std::vector<std::vector<int> > & image,
	int sr,
	int sc,
	int new_color);


void flood_fill_helper(
	std::vector<std::vector<int> > & image,
	std::vector<std::vector<bool> > & visited,
	int row_index,
	int col_index,
	int new_color);

void print(std::vector<std::vector<int> > const& image);

int main()
{
	std::cout << "before:" << std::endl;
	std::vector<std::vector<int> > image =
	{
		{ 1, 1, 1 },
		{ 1, 1, 0 },
		{ 1, 0, 1 }
	};

	print(image);

	image = flood_fill(image, 1, 1, 2);
	std::cout << "after:" << std::endl;
	print(image);


	std::cout << "before:" << std::endl;
	image =
	{
		{ 0, 0, 0 },
		{ 0, 1, 1 },
	};

	print(image);

	image = flood_fill(image, 1, 1, 1);
	std::cout << "after:" << std::endl;
	print(image);

	return 0;
}

std::vector<std::vector<int> > flood_fill(
	std::vector<std::vector<int> > & image,
	int sr,
	int sc,
	int new_color)
{
	if (!image.empty())
	{
		std::vector<std::vector<bool> > visited(
			image.size(),
			std::vector<bool>(image[0].size(), false));

		flood_fill_helper(image, visited, sr, sc, new_color);
	}

	return image;
}

void flood_fill_helper(
	std::vector<std::vector<int> > & image,
	std::vector<std::vector<bool> > & visited,
	int row_index,
	int col_index,
	int new_color)
{
	int old_color = image[row_index][col_index];
        
        image[row_index][col_index] = new_color;
	visited[row_index][col_index] = true;

        // Go north, if possible.
        if (row_index - 1 >= 0 && !visited[row_index - 1][col_index] && image[row_index - 1][col_index] == old_color)
        {
            flood_fill_helper(image, visited, row_index - 1, col_index, new_color);
        }
        
        // Go east, if possible.
        if (col_index + 1 < image[row_index].size() && !visited[row_index][col_index + 1] && image[row_index][col_index + 1] == old_color)
        {
            flood_fill_helper(image, visited, row_index, col_index + 1, new_color);
        }
        
        // Go south, if possible.
        if (row_index + 1 < image.size() && !visited[row_index + 1][col_index] && image[row_index + 1][col_index] == old_color)
        {
            flood_fill_helper(image, visited, row_index + 1, col_index, new_color);
        }
        
        // Go west, if possible.
        if (col_index - 1 >= 0 && !visited[row_index][col_index - 1] && image[row_index][col_index - 1] == old_color)
        {
            flood_fill_helper(image, visited, row_index, col_index - 1, new_color);
        }
}

void print(std::vector<std::vector<int> > const& image)
{
	std::cout << "{" << std::endl;

	for (std::vector<int> const& vec : image)
	{
		std::cout << "\t{ ";

		for (int const& i : vec)
		{
			std::cout << i << ", ";
		}

		std::cout << "}," << std::endl;
	}

	std::cout << "}" << std::endl << std::endl;
}
