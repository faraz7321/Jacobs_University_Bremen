import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)


###################################################
# select the demo
select = int(input('Which demo do you want to run? (1-5)\n'))


###################################################
# the frame of an object
Po = rob.Hmat(np.array([[0,0,1,2],[0,1,0,-4],[-1,0,1,0],[0,0,0,1]]))


###################################################
# rotate Po, respectively rotate Fw
#
if select == 1:
    rfig = rob.Fig()
    Fw = rob.HId()
    rfig.plot_frame(Fw, size=3, label='Fw')

    rfig.plot_frame(Po, size=2, label='Po')
        
    alpha = np.deg2rad(90) # angles in radians
    R = rob.HRotZ(alpha)
    
    Pon1 = R @ Po
    print('Po rotated \n', Pon1)
    rfig.plot_frame(Pon1, size=2, label='Pon1')

    Pon2 = R.T() @ Po
    print('Fw rotated \n', Pon2)
    rfig.plot_frame(Pon2, size=2, label='Pon2')

###################################################
# axes of Po, i.e., rotation part R, is "weired"
# - important that R is a real rotation matrix
# - i.e., axes in R are a orthonormal basis 
if select == 2:

    # Note: determinant is OK
    RPo = Po.get_rot3D()
    det = la.det(RPo)
    print('determinant of the rotation part of the pose of Po\n', det)

    # Note: but a check whether RPo^-1 = RPo^T reveils the truth
    I = RPo @ RPo.T
    print('RPo @ Rpo.T = Identity?\n', I)


###################################################
# animation of the rotation of Po
# 
if select == 3:    
    Po = rob.Hmat(np.array([[0,0,1,2],[0,1,0,-4],[-1,0,0,0],[0,0,0,1]]))

    rfig = rob.Fig()
    Fw = rob.HId()

    wait = 0.1 # pause in seconds before the next step

    adeg = 5
    a = np.deg2rad(adeg) # angles in radians
    R = rob.HRotZ(a)

    for i in range(int(360/adeg*2)): # plot two full rotations
        rfig.clear()
        rfig.plot_frame(Fw, size=3, label='Fw')
        
        Po = R @ Po
        rfig.plot_frame(Po, size=2, label='Po')

        rfig.pause(wait)

###################################################
# animation of the virtual rotation of Po (Po is fix) while Fw rotates
# 
if select == 4:    
    Po = rob.Hmat(np.array([[0,0,1,2],[0,1,0,-4],[-1,0,0,0],[0,0,0,1]]))

    rfig = rob.Fig()
    Fw = rob.HId()

    wait = 0.1 # pause in seconds before the next step

    adeg = 5
    a = np.deg2rad(adeg) # angles in radians
    R = rob.HRotZ(a)

    for i in range(int(360/adeg*2)): # plot two full rotations
        rfig.clear()
        rfig.plot_frame(Fw, size=3, label='Fw')
        
        Po = R.T() @ Po
        rfig.plot_frame(Po, size=2, label='Po')

        rfig.pause(wait)

###################################################
# animation of the rotation of Fw (Po is fix)
# 
if select == 5:    
    Po = rob.Hmat(np.array([[0,0,1,2],[0,1,0,-4],[-1,0,0,0],[0,0,0,1]]))

    rfig = rob.Fig()
    Fw = rob.HId()

    wait = 0.1 # pause in seconds before the next step

    adeg = 5
    a = np.deg2rad(adeg) # angles in radians
    R = rob.HRotZ(a)

    for i in range(int(360/adeg*2)): # plot two full rotations
        rfig.clear()
        rfig.plot_frame(Fw, size=3, label='Fw')
        
        Fw = R @ Fw
        rfig.plot_frame(Po, size=2, label='Po')

        rfig.pause(wait)


###################################################
# close figure (works also from Console)
#input("hit enter")
#plt.close()

# closes all open figures
# plt.close('all') 
