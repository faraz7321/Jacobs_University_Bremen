import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)


###################################################
# select the demo
select = int(input('Which demo do you want to run? (1-4)\n'))

###################################################
# quaternion rotation 30 degrees around y-axis
#
if select == 1:    
    # init the figure and plot the Identy matrix as Cartesian frame in the origin 
    rfig = rob.Fig()
    Fw = rob.HId()
    rfig.plot_frame(Fw, size=2, label='Fw')

    p = rob.Hvec()
    p.set_xyz(2,3,4)
    print('point p which is rotated \n', p)
    rfig.plot_point(p, label='p')
    
    qp = p.hv2q() # convert homog. point to quaterion
    print(qp, '\n')

    print('rotate 30 degrees around y-axis\n')         
    a0 = np.deg2rad(30)
    v0 = rob.Hvec()
    v0.set_xyz(0,1,0)
    
    qr = rob.Quat()
    qr.set_rot_axis_angle(v0, a0)
    print('rotation quaternion qr\n', qr) 
    
    qpr = qr @ qp @ qr.conj()
    print('rotated point p as quaternion qpr\n', qpr) 
    pr = qpr.q2hv()
    rfig.plot_point(pr, label='pr')
    print('rotated point p as homogeneous vector pr\n', pr) 
 

###################################################
# quaternion rotation 30 degrees around (1,-1,3)
#
if select == 2:    
    # init the figure and plot the Identy matrix as Cartesian frame in the origin 
    rfig = rob.Fig()
    Fw = rob.HId()
    rfig.plot_frame(Fw, size=2, label='Fw')

    p = rob.Hvec()
    p.set_xyz(2,3,4)
    print('point p which is rotated \n', p)
    rfig.plot_point(p, label='p')
    
    qp = p.hv2q()
    print(qp, '\n')

    print('rotate 30 degrees around (1,-1,3)\n')         
    a0 = np.deg2rad(30)
    v0 = rob.Hvec()
    v0.set_xyz(1,-1,3)
    
    qr = rob.Quat()
    qr.set_rot_axis_angle(v0, a0)
    print('rotation quaternion qr\n', qr) 
    
    qpr = qr @ qp @ qr.conj()
    print('rotated point p as quaternion qpr\n', qpr) 
    pr = qpr.q2hv()
    rfig.plot_point(pr, label='pr')
    print('rotated point p as homogeneous vector pr\n', pr) 

###################################################
# quaternion rotation 
# first by 30 degrees around y-axis 
# then by 30 degrees around (1,-1,3)
#
if select == 3:    
    # init the figure and plot the Identy matrix as Cartesian frame in the origin 
    rfig = rob.Fig()
    Fw = rob.HId()
    rfig.plot_frame(Fw, size=2, label='Fw')

    p = rob.Hvec()
    p.set_xyz(2,3,4)
    print('point p which is rotated \n', p)
    rfig.plot_point(p, label='p')
    
    qp = p.hv2q()
    print(qp, '\n')

    print('rotate 30 degrees around y-axis\n')         
    a1 = np.deg2rad(30)
    v1 = rob.Hvec()
    v1.set_xyz(0,1,0)
    qr1 = rob.Quat()
    qr1.set_rot_axis_angle(v1, a1)
    print('rotation quaternion qr1\n', qr1) 

    print('rotate 30 degrees around (1,-1,3)\n')         
    a2 = np.deg2rad(30)
    v2 = rob.Hvec()
    v2.set_xyz(1,-1,3)
    qr2 = rob.Quat()
    qr2.set_rot_axis_angle(v2, a2)
    print('rotation quaternion qr2\n', qr2) 
    
    qr3 = qr2 @ qr1 
    print('chained rotation qr3 by multiplying qr2 with qr1\n', qr3) 
    
    qpr = qr3 @ qp @ qr3.conj()
    print('rotated point p as quaternion qpr\n', qpr) 
    pr = qpr.q2hv()
    rfig.plot_point(pr, label='pr')
    print('rotated point p as homogeneous vector pr\n', pr) 

###################################################
# animated combined quaternion rotation
#  of point  (4, 5, 6)^T   
#  by 5 degrees around y-axis 
#  and 10 degrees around (1,-1,3)
#  in each step
#    

if select == 4:    
    # init the figure and plot the Identy matrix as Cartesian frame in the origin 
    rfig = rob.Fig()
    Fw = rob.HId()
    rfig.plot_frame(Fw, size=2, label='Fw')

    p = rob.Hvec()
    p.set_xyz(4,5,6)
    print(p, '\n')
    rfig.plot_point(p, label='p')
    
    qp = p.hv2q()
    print(qp, '\n')

    print('rotate 5 degrees around y-axis\n')         
    a1 = np.deg2rad(5)
    v1 = rob.Hvec()
    v1.set_xyz(0,1,0)
    qr1 = rob.Quat()
    qr1.set_rot_axis_angle(v1, a1)
    print('rotation quaternion qr1\n', qr1) 

    print('rotate 10 degrees around (1,-1,3)\n')         
    a2 = np.deg2rad(10)
    v2 = rob.Hvec()
    v2.set_xyz(1,-1,3)
    qr2 = rob.Quat()
    qr2.set_rot_axis_angle(v2, a2)
    print('rotation quaternion qr2\n', qr2) 
    
    qr3 = qr2 @ qr1 
    print('chained rotation qr3 by multiplying qr2 with qr1\n', qr3) 

    for i in range(40):
        # rfig.clear()        
        qp = qr3 @ qp @ qr3.conj()
        print('rotated point p as quaternion qpr\n', qp) 
        pr = qp.q2hv()
        rfig.plot_point(pr)
        print('rotated point p as homogeneous vector pr\n', pr) 
        rfig.pause(0.1)


###################################################
# # close figure (works also from Console)
# rfig.close()
