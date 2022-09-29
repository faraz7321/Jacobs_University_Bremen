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
# move in "circles": 4x 90 deg
#    
if select == 1:
    rfig = rob.Fig()

    Move = rob.Hmat()
    R2 = rob.HRotZ(np.deg2rad(90))
    T = rob.HTransl(5,0,0) 
    Move = T @ R2
    print('matrix Move\n', Move)

    H0 = rob.Hmat()

    wait = 2
    for i in range(5):
        rfig.clear()

        rfig.plot_frame(H0, size=2)
        
        H0 = Move @ H0
        rfig.pause(wait)

###################################################
# move in "circles": n x 360/n deg
#          
if select == 2:
    rfig = rob.Fig()

    n = 180
    
    Move = rob.Hmat()
    R2 = rob.HRotZ(np.deg2rad(360/n))
    T = rob.HTransl(25/n,0,0) 
    Move = T @ R2
    print('matrix Move\n', Move)

    H0 = rob.Hmat()

    wait = 0.05
    for i in range(n+1):
        rfig.clear()

        rfig.plot_frame(H0, size=2)
        
        H0 = Move @ H0
        rfig.pause(wait)

###################################################
# close figure (works also from Console)
#input("hit enter")
#plt.close()

# closes all open figures
# plt.close('all') 
