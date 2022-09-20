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
# two frames "earth" and "moon"

Pe = rob.Hmat(np.array([[0,0,1,2],[0,1,0,-4],[-1,0,0,0],[0,0,0,1]]))
Pm = rob.Hmat(np.array([[1,0,0,5],[0,-1,0,7],[0,0,-1,-3],[0,0,0,1]]))


###################################################
# rotate Pm around the frame Pe
# 
if select == 1:
    rfig = rob.Fig()
    Fw = rob.HId()
    rfig.plot_frame(Fw, size=3, label='Fw')
 
    a = np.deg2rad(90) # angles in radians
    R = rob.HRotZ(a)

    rfig.plot_frame(Pe, label='Pe', size=2)
    rfig.plot_frame(Pm, label='Pm', size=2)
    
    Pmn = Pe @ R @ Pe.inv() @ Pm
    print('Pm rotated around Pe\n', Pmn)
    rfig.plot_frame(Pmn, label='Pmn', size=2)


###################################################
# animation of the rotation of Pm around the frame Pe
# 
if select == 2:
    rfig = rob.Fig(min=-15, max=15)
    Fw = rob.HId()

    wait = 0.1 # pause in seconds before the next step

    adeg = 5
    a = np.deg2rad(adeg) # angles in radians
    R = rob.HRotZ(a)

    for i in range(int(360/adeg*2)): # plot two full rotations
        rfig.clear()
        rfig.plot_frame(Fw, size=5, label='Fw')
        rfig.plot_frame(Pe, size=3, label='Pe')
        
        Pm = Pe @ R @ Pe.inv() @ Pm
        rfig.plot_frame(Pm, size=3, label='Pm')

        rfig.pause(wait)


###################################################
# close figure (works also from Console)
#input("hit enter")
#plt.close()

# closes all open figures
# plt.close('all') 
