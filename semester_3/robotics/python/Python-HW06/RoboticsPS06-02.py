import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)

###################################################
# select the demo
select = int(input('Which demo do you want to run? (1-2)\n'))

###################################################
# short-cuts for trigonometric functions
def s(a): return np.sin(a)
def c(a): return np.cos(a)

def d2r(a): return np.deg2rad(a)
def r2d(a): return np.rad2deg(a)



###################################################
# animation of the 4 Wheel Omni-Drive FK
# 
if select == 1:
    rfig = rob.Fig2D(min=-6, max=6)

    ###############################################
    # 4W omni drive motion
    mr1 = rob.MobileOmni4W(wheeltocenter=0.15)
    # mr1.set_pose(0.0, 0.0, d2r(0.0))
    mr1.set_pose(1.3, -0.7, d2r(23.0))


    # the omni-drive FK is in the local frame, which changes during motion  
    # hence step-wise approximate update in small time intervals
    # the smaller the time step, the higher the accuracy
    # here: 0.1 sec steps (100 msec)
    v = np.array([[0.0, -2.0, 0.0, 2.0]]).T # move forward (note: omni "left" wheel turns "backwards")  
    for i in range(20): 
        rfig.clear()
        mr1.move(v, 0.1) 
        rfig.plot_mrob(mr1)        
        rfig.pause(0.1)

    v = np.array([[2.0, 0.0, -2.0, 0.0]]).T # move sideways  
    for i in range(20): 
        rfig.clear()
        mr1.move(v, 0.1) 
        rfig.plot_mrob(mr1)        
        rfig.pause(0.1)

    v = np.array([[2.0, 2.0, 2.0, 2.0]]).T # turn on the spot  
    for i in range(10): 
        rfig.clear()
        mr1.move(v, 0.1) 
        rfig.plot_mrob(mr1)        
        rfig.pause(0.1)

    v = np.array([[-2.3, 3.4, 1.1, -2.9]]).T # move arbitrarily  
    for i in range(20): 
        rfig.clear()
        mr1.move(v, 0.1) 
        rfig.plot_mrob(mr1)        
        rfig.pause(0.1)



###################################################
# animation of the 3 Wheel Omni-Drive FK
# 
if select == 2:
    rfig = rob.Fig2D(min=-6, max=6)

    ###############################################
    # 3W omni drive motion
    mr2 = rob.MobileOmni3W(wheeltocenter=0.15)
    mr2.set_pose(1.3, -0.7, d2r(23.0))

    v = np.array([[2.0, 0.0, -2.0]]).T 
    for i in range(10): 
        rfig.clear()
        mr2.move(v, 0.1) 
        rfig.plot_mrob(mr2)        
        rfig.pause(0.1)

    v = np.array([[2.0, 2.0, 2.0]]).T
    for i in range(10): 
        rfig.clear()
        mr2.move(v, 0.1) 
        rfig.plot_mrob(mr2)        
        rfig.pause(0.1)

    v = np.array([[-2.3, 3.4, 1.1]]).T
    for i in range(20): 
        rfig.clear()
        mr2.move(v, 0.1) 
        rfig.plot_mrob(mr2)        
        rfig.pause(0.1)

