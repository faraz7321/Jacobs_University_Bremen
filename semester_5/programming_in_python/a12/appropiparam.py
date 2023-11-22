# JTMS-14
# a12_p6.py
# Faraz Ahmad
# fahmad@jacobs-university.de


from graphics import *
import random
import sys

def main(d, total_points):
    if not (0 < d <= 1000) or total_points <= 0:
        print("Invalid parameters.")
        sys.exit()

    win = GraphWin("Approximate Pi", d, d)
    inside_circle = 0

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
            print(f"After {i} points, approximation of π: {pi_approx}")
            win.plotPixel(x, y, color)

    win.getMouse()
    win.close()

# Example usage
main(400, 10000)
