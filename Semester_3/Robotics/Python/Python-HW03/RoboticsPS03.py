import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

import matplotlib as plt

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)

###################################################
# select the demo
select = int(input('Which demo do you want to run? (1-4)\n'))


###################################################
# maximum motor power
#
if select == 1:
    # convert N0 from rpm to rad/sec
    N0_rpm = 6000
    print('N0 (rpm) : ', N0_rpm, '\n')
    
    N0 = 1/60.0 * 2* np.pi * N0_rpm
    print('N0 (rad/sec), i.e., in SI units: ', N0, '\n')
    
    # convert Ts from gr*cm to Nm
    Ts_gr_cm = 0.5
    print('Ts (gr*cm) : ', Ts_gr_cm, '\n')
    
    Ts = Ts_gr_cm / 1000 * 9.8 * 0.01
    print('Ts (N m) : ', Ts, '\n')
    
    # maximum motor power as 1/4 Ts * N0
    Pmax = 0.25 * Ts * N0 
    print('Pmax (W) : ', Pmax, '\n')


###################################################
# spur gear train with 2 axes
#
if select == 2:
    # gear ratios
    z1a = 10
    z2a = 20
    
    z2b = 50
    z3a = 100
    
    gr1 = -z1a/z2a
    gr2 = -z2b/z3a
        
    # changes in speed and torque
    N1 = 100
    N3 = gr2 * gr1 * N1
    print('N1 (input): ', N1, '\n')
    print('N3 (output): ', N3, '\n')
    
    T1 = 10
    T3 = 1/gr2 * 1/gr1 * T1
    print('T1 (input): ', T1, '\n')
    print('T3 (output): ', T3, '\n')

    
###################################################
# worm gear
#
if select == 3:
    print('\nworm gear')
    
    # gear ratio
    zw = 100
    print('teeth worm wheel: ', zw)
    
    grw = 1/zw
    print('gear ratio: ', grw)
    
    # changes in speed and torque
    N1 = 100
    N3 = grw * N1
    print('N1 (input): ', N1)
    print('N3 (output): ', N3)
    
    T1 = 10
    T3 = 1/grw * T1
    print('T1 (input): ', T1)
    print('T3 (output): ', T3)


###################################################
# planetary gear
if select == 4:
    print('\nplanetary gear')
    
    # gear ratio
    zs = 10
    zi = 200
    print('teeth sun: ', zs)
    print('teeth internal gear: ', zi)
    
    grp = zs/(zi+zs)
    print('gear ratio: ', grp)
    
    # changes in speed and torque
    N1 = 100
    N3 = grp * N1
    print('N1 (input): ', N1)
    print('N3 (output): ', N3)
    
    T1 = 10
    T3 = 1/grp * T1
    print('T1 (input): ', T1)
    print('T3 (output): ', T3)
    
