# JTMS-14
# a12_p3.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from graphics import *

def draw_archery(circle_data):
    win = GraphWin('Archery Target', 300, 300)
    # The colors are in reverse order because we draw the largest circle first
    colors = ['white', 'black', 'blue', 'red', 'yellow'] 

    # Drawing from the largest to the smallest circle
    for i, data in enumerate(reversed(circle_data)):
        circle = Circle(Point(data[0], data[1]), data[2])
        circle.setFill(colors[i])
        circle.setOutline(colors[i])
        circle.draw(win)

    win.getMouse()  # Pause to view result
    win.close()

# width = 15
draw_archery([(100, 100, 15), (100, 100, 30),\
(100, 100, 45), (100, 100, 60), (100, 100, 75)])