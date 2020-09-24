// Point.cpp

#include <iostream>
#include <math.h>
#include "Point.h"

using namespace std;

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Point.
// --------------------------------------------------------------------------------------

int Point::s_pointInstanceCount = 0;

// Constructor
Point::Point()
{
	s_pointInstanceCount++;
}

// ------------------ Access methods ------------------------
float Point::getX()
{
	return _x;
}

float Point::getY()
{
	return _y;
}

// ------------------ Modify methods ------------------------
void Point::initDetails()
{
	// Getting the data from the user
	cout << "Enter the x coordinate please" << endl;
	cin >> _x;
	cout << "Enter the y coordinate please" << endl;
	cin >> _y;
}

// ------------------ Other methods ------------------------
void Point::print()
{
	cout << "( " << _x << " , " << _y << " )" << endl;
}

bool Point::isEqual(const Point& other)
{
	bool isEqual = false;

	// Checking both members
	if (_x == other._x && _y == other._y)
	{
		isEqual = true;
	}

	return isEqual;
}

/**
 * The Euclidian distance between points \f$(x_1,y_1)\f$ and \f$(x_2,y_2)\f$ 
 * is defined as \f$d=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$.
 */
float Point::calcDistance(const Point& other)
{
	return sqrt( pow((_x - other._x), 2) + pow((_y - other._y), 2) );
}