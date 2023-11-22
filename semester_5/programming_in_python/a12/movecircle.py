# JTMS-14
# a12_p1.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from graphics import *

def main():
	win = GraphWin()
	size = 20
	
	for i in range(10):
		p = win.getMouse()
		shape = Rectangle(Point(p.getX() - size, p.getY() - size), \
					Point(p.getX() + size, p.getY() + size))
		
		shape.setOutline("red")
		shape.setFill("red")
		shape.draw(win)
	
	win.close()

main()
