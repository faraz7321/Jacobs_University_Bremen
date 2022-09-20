import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)

###################################################
# select the demo(
select = int(input('Which demo do you want to run? (1-2)\n'))

###################################################
# short-cuts for trigonometric functions
def s(a): return np.sin(a)
def c(a): return np.cos(a)

def d2r(a): return np.deg2rad(a)
def r2d(a): return np.rad2deg(a)

###################################################
# calculation of PS07-01

if select == 1:

    rfig = rob.Fig2D(min=-5, max=80)
    
    ml = rob.Multilateration2D()
    
    ml.add_beacon(0, 35, 40)
    ml.add_beacon(1, 12, 23)
    ml.add_beacon(2, 7, 18)
    ml.add_beacon(3, 9, 9)
    rfig.plot_beacons(ml)
    
    ml.add_range(0, 37)
    ml.add_range(1, 9)
    ml.add_range(2, 2)
    ml.add_range(3, 10)
    rfig.plot_ranges(ml)
    
    hpos = ml.LLS_fit(verbose=True)
    rfig.plot_point(hpos, color='green', label='solution')
    
###################################################
# 2nd example (just more beacons and ranges)

if select == 2:

    rfig = rob.Fig2D(min=-40, max=100)
    
    ml = rob.Multilateration2D()
    
    ml.add_beacon(0, 55, 40)
    ml.add_beacon(1, 12, 63)
    ml.add_beacon(2, 39, 18)
    ml.add_beacon(3, 9, 9)
    ml.add_beacon(4, 62, 37)
    ml.add_beacon(5, 25, 38)
    rfig.plot_beacons(ml)
    
    ml.add_range(0, 27)
    ml.add_range(1, 32)
    ml.add_range(2, 19)
    ml.add_range(3, 41)
    ml.add_range(4, 38)
    ml.add_range(5, 14)
    rfig.plot_ranges(ml)
    
    hpos = ml.LLS_fit()
    rfig.plot_point(hpos, color='green', label='solution')