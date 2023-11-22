# JTMS-14
# a12_p4.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from graphics import *

def main():
    win = GraphWin("Drawing a Rectangle", 400, 400)
    p1 = win.getMouse()
    p2 = win.getMouse()

    rect = Rectangle(p1, p2)
    rect.draw(win)

    # get coordinates
    p1, p2 = rect.getP1(), rect.getP2()
    length = abs(p1.getX() - p2.getX())
    width = abs(p1.getY() - p2.getY())

    #calculate area and perimeter
    perimeter = 2 * (length + width)
    area = length * width

    print("Perimeter:", perimeter)
    print("Area:", area)

    win.getMouse()
    win.close()

main()
