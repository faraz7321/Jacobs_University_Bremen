import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)

###################################################
# select the demo(
# select = int(input('Which demo do you want to run? (1-2)\n'))

###################################################
# short-cuts for trigonometric functions
def s(a): return np.sin(a)
def c(a): return np.cos(a)

def d2r(a): return np.deg2rad(a)
def r2d(a): return np.rad2deg(a)

###################################################
# calculation of PS07-02

# if select == 1:

#     rfig = rob.Fig2D(min=-5, max=80)
    
mds = rob.MultiDimensionalScaling2D(n_nodes=4)
mds.add_distance(0, 1, 50.0)
mds.add_distance(0, 2, 44.72)
mds.add_distance(0, 3, 31.62)
mds.add_distance(1, 2, 60.83)
mds.add_distance(1, 3, 22.36)
mds.add_distance(2, 3, 58.31)

mds.MDS_fit(verbose=True)
