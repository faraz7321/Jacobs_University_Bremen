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
# toy robot arm: compute forward kinematics
#
if select == 1:
    # rfig = rob.Fig()
    Fw = rob.HId()
    # rfig.plot_frame(Fw, size=3, label='Fw')

    F0 = Fw # just for completeness, i.e., not really needed
    
    def F1(theta1):
        R = rob.HRotZ(theta1)
        T = rob.HTransl(0,0,5)
        F = T @ R
        return F

    def F2(theta2):
        R = rob.HRotY(theta2)
        return R

    F3 = rob.HTransl(0,0,3)

    theta1 = np.deg2rad(90)
    theta2 = np.deg2rad(180)
    
    # note the order of the transformations
    Pg = F1(theta1) @ F2(theta2) @ F3 
    print('end effector pose\n', Pg)


###################################################
# animation of the toy robot arm
# 
if select == 2:

    rfig = rob.Fig(min=-8, max=8)
    Fw = rob.HId()

    F0 = Fw
    v0 = F0.get_transl()

    def F1(theta1):
        R = rob.HRotZ(theta1)
        T = rob.HTransl(0,0,5)
        F = T @ R
        return F

    def F2(theta2):
        R = rob.HRotY(theta2)
        return R

    F3 = rob.HTransl(0,0,3)

    wait = 0.1 # pause in seconds before the next step

    theta1 = np.deg2rad(0)
    theta2 = np.deg2rad(0)

    for i in range(72*3):
        rfig.clear()
        rfig.plot_frame(Fw, size=3, label='Fw')

        F1I = F1(theta1)
        v1 = F1I.get_transl()
        rfig.plot_frame(F1I, label='F1', size=1.5)
        rfig.plot_line(v0, v1, linewidth=5)

        F2I = F1I @ F2(theta2)
        rfig.plot_frame(F2I, label='F2', size=1.5)

        F3I = F2I @ F3
        v3 = F3I.get_transl()
        rfig.plot_frame(F3I, label='F3=Pg', size=1.5)
        rfig.plot_line(v1, v3, linewidth=5)
    
        theta1 += np.deg2rad(1)
        theta2 += np.deg2rad(3)

        rfig.pause(wait)

###################################################
# close figure (works also from Console)
#input("hit enter")
#plt.close()

# closes all open figures
# plt.close('all') 
