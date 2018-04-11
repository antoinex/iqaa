/*
 * @file     : main.cpp
 * @author   : antoinex
 *
 * @question :
 *	You have a list of points in a plane.
 *	Return the area of the largest triangle that can be formed by any 3 of the points.
 *
 * @example  :
 *	points = [ [0,0], [0,1], [1,0], [0,2], [2,0] ]
 *
 *	Visualizing these points on a Cartesian plane, the triangle with the largest area
 *	is quite obvious.
 *
 *	^
 *	|
 *	3
 *	|
 *	2.
 *	|  .
 *	1    .
 *	|      .
 *	0---1---2---3--->
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <algorithm>

double get_triangle_side_length(
	std::vector<int> const& coord0,
	std::vector<int> const& coord1);

double herons_formula(
	std::vector<int> const& point0,
	std::vector<int> const& point1,
	std::vector<int> const& point2);

double shoelace_formula(
	std::vector<int> const& point0,
	std::vector<int> const& point1,
	std::vector<int> const& point2);

using AreaFunc = std::function<double(std::vector<int> const&, std::vector<int> const&, std::vector<int> const&)>;

double largest_triangle_area(
	std::vector<std::vector<int> > const& points,
	AreaFunc area_func);

double largest_triangle_area_using_herons_formula(std::vector<std::vector<int> > const& points);
double largest_triangle_area_using_shoelace_formula(std::vector<std::vector<int> > const& points);

int main()
{
	std::vector<std::vector<int> > points =
	{
		{ 0, 0 },
		{ 0, 1 },
		{ 1, 0 },
		{ 0, 2 },
		{ 2, 0 }
	};

	// Print the output (which is a double) to 1 decimal place.
	std::cout << std::fixed;
	std::cout << std::setprecision(1) << largest_triangle_area_using_herons_formula(points) << std::endl;
	std::cout << std::setprecision(1) << largest_triangle_area_using_shoelace_formula(points) << std::endl;

	return 0;
}

double largest_triangle_area_using_herons_formula(std::vector<std::vector<int> > const& points)
{
	return largest_triangle_area(
		points,
		herons_formula);
}

double largest_triangle_area_using_shoelace_formula(std::vector<std::vector<int> > const& points)
{
	return largest_triangle_area(
		points,
		shoelace_formula);
}

double largest_triangle_area(
	std::vector<std::vector<int> > const& points,
	AreaFunc area_func)
{
	double largest_area = 0.0;

	for (std::size_t i = 0; i < points.size(); i++)
	{
		std::vector<int> const& point0 = points[i];

		for (std::size_t j = i + 1; j < points.size(); j++)
		{
			std::vector<int> const& point1 = points[j];

			for (std::size_t k = j + 1; k < points.size(); k++)
			{
				std::vector<int> const& point2 = points[k];

				double area = area_func(point0, point1, point2);

				largest_area = std::max(largest_area, area);
			}
		}
	}

	return largest_area;
}

double get_triangle_side_length(
	std::vector<int> const& coord0,
	std::vector<int> const& coord1)
{
	int x_length = std::abs(coord0[0] - coord1[0]);
	int y_length = std::abs(coord0[1] - coord1[1]);

	int pythagorean_sum = (x_length * x_length) + (y_length * y_length);

	return std::sqrt(pythagorean_sum);
}

double herons_formula(
	std::vector<int> const& point0,
	std::vector<int> const& point1,
	std::vector<int> const& point2)
{
	double a = get_triangle_side_length(point0, point1);
	double b = get_triangle_side_length(point1, point2);
	double c = get_triangle_side_length(point2, point0);

	double s = (a + b + c) / 2.0;

	return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double shoelace_formula(
	std::vector<int> const& point0,
	std::vector<int> const& point1,
	std::vector<int> const& point2)
{
	return 
		std::abs
		(
			( (point0[0] * point1[1]) + (point1[0] * point2[1]) + (point2[0] * point0[1]) )
			-
			( (point0[1] * point1[0]) + (point1[1] * point2[0]) + (point2[1] * point0[0]) )
		) / 2.0;
}
