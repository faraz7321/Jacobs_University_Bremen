# JTMS-14
# a12_p2.py
# Faraz Ahmad
# fahmad@jacobs-university.de

from graphics import *

win = GraphWin('Face', 300, 300)

# Draw head
head = Circle(Point(150, 150), 100)
head.setFill("lightyellow")
head.draw(win)

# Draw eyes
left_eye = Circle(Point(120, 130), 15)
left_eye.setFill("white")
left_eye.draw(win)

right_eye = Circle(Point(180, 130), 15)
right_eye.setFill("white")
right_eye.draw(win)

# Draw pupils
left_pupil = Circle(Point(120, 130), 5)
left_pupil.setFill("black")
left_pupil.draw(win)

right_pupil = Circle(Point(180, 130), 5)
right_pupil.setFill("black")
right_pupil.draw(win)

# Draw nose 
nose = Polygon(Point(150, 140), Point(140, 170), Point(160, 170))
nose.setFill("yellow")
nose.draw(win)

# Draw mouth 
mouth = Oval(Point(130, 190), Point(170, 210))
mouth.setFill("red")
mouth.draw(win)

# Draw ears
left_ear = Circle(Point(50, 150), 20)
left_ear.setFill("lightyellow")
left_ear.draw(win)

right_ear = Circle(Point(250, 150), 20)
right_ear.setFill("lightyellow")
right_ear.draw(win)

win.getMouse() 
win.close()

