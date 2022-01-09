#include <iostream>
#include <cstdlib>
#include <ctime>
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
int random();
int random(int a);
int random(int a, int b);
const int num_obj = 25;
const char colors[4][7] = {"RED", "BLACK", "VIOLET", "BLUE"};

int main()
{
	int num_circ = 0;
	int num_ring = 0;
	int num_rect = 0;
	int num_sqr = 0;
	int a, randomNumber;
	for (int i = 0; i < num_obj; i++)
	{
		a = random(4);
		if (a == 1)
		{
			num_circ++;
		}
		else if (a == 2)
		{
			num_ring++;
		}
		else if (a == 3)
		{
			num_rect++;
		}
		else if (a == 4)
		{
			num_sqr++;
		}
	}

	Circle *circles = new Circle[num_circ];
	for (int i = 0; i < num_circ; i++)
	{
		circles[i] = Circle(colors[random()], random(5, 100));
	}

	Ring *rings = new Ring[num_ring];
	for (int i = 0; i < num_ring; i++)
	{
		rings[i] = Ring(colors[random()], random(5, 100), random(5, 100));
	}

	Rectangle *rectangles = new Rectangle[num_rect];
	for (int i = 0; i < num_rect; i++)
	{
		rectangles[i] = Rectangle(colors[random()], random(5, 100), random(5, 100));
	}

	Square *squares = new Square[num_sqr];
	for (int i = 0; i < num_sqr; i++)
	{
		squares[i] = Square(colors[random()], random(5, 100));
	}
	for (int i = 0; i < num_circ; i++)
	{
		cout << circles->calcArea() << endl;
		cout << circles->calcPerimeter() << endl;
	}

	return 0;
}
int random(int a)
{
	int randomNumber = rand();
	int b = (randomNumber % a) + 1;
	return b;
}
int random(int a, int b)
{
	int randomNumber = rand();
	int c = (randomNumber % b) + a;
	return c;
}