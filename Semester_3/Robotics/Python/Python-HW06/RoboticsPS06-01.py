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
# calculation of PS06-01

if select == 1:
    
    mr = rob.MobileDifferential()
    mr.set_wheeldistance(0.3)
    mr.set_pose(0.0, 0.0, d2r(0.0))

    rpm_l = 18849
    rpm_r = 15708
    vl = 0.1 * 1/100.0 * rpm_l/60.0 * 2*np.pi 
    vr = 0.1 * 1/100.0 * rpm_r/60.0 * 2*np.pi 

    print('left wheel velocity (m/sec) \n', vl)
    print('right wheel velocity (m/sec) \n', vr)
    
    v = [vl, vr] # left/right wheel velocities
    mr.move(v, 0.04)
    pose = mr.get_pose()
    print('\nnew pose of the differential drive\n', pose)


###################################################
# animation of the Differential Drive FK
# 
if select == 2:
    rfig = rob.Fig2D(min=-5, max=5)

    mr = rob.MobileDifferential()
    mr.set_wheeldistance(0.3)
    mr.set_pose(0.0, 0.0, d2r(0.0))     # start pose from PS06-01
    # mr.set_pose(-2.3, 1.7, d2r(45.0)) # different start pose 
    
    w = rob.WheelGearMotor()    # wheel (plus motor & gear) instance for velocity calculations
    w.set_radius(0.1)           # wheel radius = 0.1m 
    w.set_gearratio(1/100.0)    # GR = 1:100

    vl = w.rpm2mpsec(18849)      # convert motor RPM to wheel velocity in m/sec
    vr = w.rpm2mpsec(15708)
    v = [vl, vr]

    for i in range(100):
        rfig.clear()
        mr.move(v, 0.1)
        rfig.plot_mrob(mr)        
        rfig.pause(0.1)

    pose = mr.get_pose()
    print('\nnew pose of the differential drive\n', pose)

