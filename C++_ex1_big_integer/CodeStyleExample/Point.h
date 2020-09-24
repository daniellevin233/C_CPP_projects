// Point.h

#ifndef POINT_H
#define POINT_H
/**
 *  A point class. 
 *  This class represents a point with (x,y) coordinates.
 */
class Point
{
public:
	/**
     * A constructor.
     * A more elaborate description of the constructor.
     * @see initDetails()
     */
	Point();

	/**
	 * Access method for the x value.
	 * @return The x value
	 */
	float getX();
	/**
	 * Access method for the y value.
	 * @return The y value
	 */
	float getY();

	/**
     * Inits the Point object according to input from the user.
     * More details.
     */
	void initDetails();

	/**
     * Prints the point in the format: ( x , y ).
     */
	void print();
	
	/**
     * Checks if two points are equal.
     * @param other another point.
     * @return True if two points are equal, false otherwise.
     */
	bool isEqual(const Point& other);
	
	/**
     * Calculates the Euclidean distance between two points.
     * @param other another point.
     * @return the Euclidean distance between two points.
     */
	float calcDistance(const Point& other);

private:
	float _x; /**< the x coordinate. Details. */
	float _y; /**< the y coordinate. Details. */

	static int s_pointInstanceCount; /**< Instances count. Details. */
};

#endif