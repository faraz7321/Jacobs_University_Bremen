# JTMS-14
# a12_p7.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from graphics import *

def main():
    size = 255
    win = GraphWin("Colored Pixels", size, size)

    # creting unique colors and plotting pixels
    for i in range(size):
        for j in range(size):
            # create a unique color for each pixel
            color = color_rgb(i, j, (i+j) % size)
            win.plotPixelFast(i, j, color)
    
    # plotting every 150th pixel
    for i in range(0, size, 150):
        for j in range(0, size, 150):
            color = color_rgb(i, j, (i+j) % size)
            win.plotPixel(i, j, color)

    win.getMouse() 
    win.close()

main()
