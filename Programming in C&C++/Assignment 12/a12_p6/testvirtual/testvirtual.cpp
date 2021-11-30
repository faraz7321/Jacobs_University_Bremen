#include <iostream>
using namespace std;
#include "Area.h"
#include "Circle.h"
#include "Ring.h"
#include "Rectangle.h"
#include "Square.h"
/* CLASS DIAGRAM

       AREA
  		|
  		V
 Circle | Rectangle
	|        |
	V        V
   Ring    Square

A circle has-a area
A rectangle has-a area
A ring is-a circle
A square is-a rectangle
*/

const int num_obj = 7;
int main()
{
	Area *list[num_obj]; // (1)
	/* (1) an array of Area class is created
	(6 instances)*/
	int index = 0; // (2)
	/* (2) index used in while loop to 
	iterate over array*/
	double sum_area = 0.0; // (3)
	//intializing variable to store sum of area
	double sum_perimeter = 0.0;
	cout << "Creating Ring: ";
	Ring blue_ring("BLUE", 5, 2); // (4)
	/*creating blue ring with outer radius 5
	and inner radius 2*/
	cout << "Creating Circle: ";
	Circle yellow_circle("YELLOW", 7);
	cout << "Creating Rectangle: ";
	Rectangle green_rectangle("GREEN", 5, 6);
	cout << "Creating Circle: ";
	Circle red_circle("RED", 8);
	cout << "Creating Rectangle: ";
	Rectangle black_rectangle("BLACK", 10, 20);
	cout << "Creating Ring: ";
	Ring violet_ring("VIOLET", 100, 5);
	cout << "Creating Square: ";
	Square pink_square("PINK", 7);
	list[0] = &blue_ring; // (5)
	//calcArea() of child class ie circle will be called
	list[1] = &yellow_circle;
	list[2] = &green_rectangle;
	list[3] = &red_circle;
	list[4] = &black_rectangle;
	list[5] = &violet_ring;
	list[6] = &pink_square;
	while (index < num_obj)
	{ // (7)
		(list[index])->getColor();
		double area = list[index]->calcArea(); // (8)
		//calculates area and stores it in temporary var
		sum_area += area;
		//calculating perimeter
		double perimeter = list[index]->calcPerimeter();
		sum_perimeter += perimeter;
		index++;
	}
	//prints area of all shapes
	cout << "\nThe total area is "
		 << sum_area << " units " << endl; // (9)

	cout << "\nThe total perimeter is "
		 << sum_perimeter << " units " << endl;
	return 0;
}
