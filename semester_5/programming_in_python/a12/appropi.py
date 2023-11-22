# JTMS-14
# a12_p5.py
# Faraz Ahmad
# fahmad@jacobs-university.de


from graphics import *
import random

def main():
    d = 400
    win = GraphWin("Approximate Pi", d, d)
    inside_circle = 0
    total_points = 10000

    for i in range(1, total_points + 1):
        x = random.randint(0, d)
        y = random.randint(0, d)

        # Check if the point is inside the circle
        if (x - d/2)**2 + (y - d/2)**2 <= (d/2)**2:
            color = color_rgb(255, 0, 0)  # Red
            inside_circle += 1
        else:
            color = color_rgb(0, 0, 255)  # Blue

        win.plotPixelFast(x, y, color)

        # For every 100th point
        if i % 100 == 0:
            pi_approx = 4 * inside_circle / i
            print(f"approximation of π: {pi_approx}")
            win.plotPixel(x, y, color)

    win.getMouse()
    win.close()

main()
