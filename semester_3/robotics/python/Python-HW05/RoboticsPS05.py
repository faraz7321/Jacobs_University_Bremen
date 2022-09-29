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
# short-cuts for trigonometric functions
def s(a): return np.sin(a)
def c(a): return np.cos(a)

def d2r(a): return np.deg2rad(a)
def r2d(a): return np.rad2deg(a)

###################################################
# init figure
rfig = rob.Fig2D(min=-20, max=20)


###################################################
# frames and Jacobian of the 2D Rot-Rot-Transl robot arm

Fw = rob.Hmat2D() # world frame (I)
v0 = rob.Hvec2D() # origin


def F1(a1): # rotation with alpha1
    F = rob.HRot2D(a1)
    return F

F2 = rob.HTransl2D(10,0) # rigid link of length l1=10

def F3(a2): # rotation with alpha2
    F = rob.HRot2D(a2)
    return F

def F4(l2): # prismatic joint with length l2
    if l2<5 : l2=5
    if l2>10 : l2=10    
    F = rob.HTransl2D(l2,0)
    return F

def J(q):
    a1 = q[0,0]
    a2 = q[1,0]
    l2 = q[2,0]
    JM = np.array([[-s(a1)*c(a2)*l2 - c(a1)*s(a2)*l2 - s(a1)*10, -c(a1)*s(a2)*l2 - s(a1)*c(a2)*l2, c(a1)*c(a2)-s(a1)*s(a2)], 
                   [c(a1)*c(a2)*l2 - s(a1)*s(a2)*l2 + c(a1)*10, -s(a1)*s(a2)*l2 + c(a1)*c(a2)*l2, s(a1)*c(a2)+c(a1)*s(a2)]])
    # JM = np.array([[-s(a1)*c(a2)*l2 - c(a1)*s(a2)*l2 - s(a1)*10, -c(a1)*s(a2)*l2 - s(a1)*c(a2)*l2, c(a1)*c(a2)-s(a1)*s(a2)], 
                   # [c(a1)*c(a2)*l2 + s(a1)*s(a2)*l2 + c(a1)*10, -s(a1)*s(a2)*l2 + c(a1)*c(a2)*l2, s(a1)*c(a2)+c(a1)*s(a2)]])
    return JM

###################################################
# Forward Kinematics
pg = rob.Hvec2D() # init position of the end-effector (gripper)

a1 = d2r(0.0)  # initial value for 1st DoF
a2 = d2r(0.0)  # initial value for 2nd DoF
l2 = 5.0       # initial value for 3rd DoF
q = np.array([[a1,a2,l2]]).T # the (column) vector q of the DoF (in a 2D array, i.e., as a single column in a 3x1 matrix)

# compute the Forward Kinematics (and show the frames and the arm)         
def K(q):
    
    F1I = F1(q[0,0])       
    rfig.plot_frame(F1I, size=2, label='F1I')

    F2I = F1I @ F2
    rfig.plot_frame(F2I, size=2, label='F2I')

    F3I = F2I @ F3(q[1,0]) 
    rfig.plot_frame(F3I, size=2, label='F3I')

    F4I = F3I @ F4(q[2,0]) 
    rfig.plot_frame(F4I, size=2, label='F4I')

    pg = F4I @ v0

    # draw the arm (as two lines)         
    v2 = F2I.get_transl()
    rfig.plot_line(v0, v2, linewidth=3)    
    rfig.plot_line(v2, pg, linewidth=3)    

    return pg

###################################################
# animation of the planar Rot-Rot-Transl robot arm
# 
if select == 1:

    for i in range(240):
        rfig.clear()

        q[0,0] = d2r(i/3)       # some arbitrary values for a1
        q[1,0] = d2r(i/2)       # some arbitrary values for a2
        q[2,0] = 5.0+i/50.0     # some arbitrary values for l2

        pg = K(q) # compute FK and show frames plus arm
        print('position of the end-effector \n', pg, '\n')
        
        rfig.pause(0.02)

                
###################################################
# computation of the Jacobian pseudo-inverse at q = (90 deg, 0 deg, 8)
# and one step of Newton, respectively Gradient Descent
# 
if select == 2:
    rfig.close()
    
    q[0,0] = d2r(90.0)  # initial guess for 1st DoF a1
    q[1,0] = d2r(0.0)   # initial guess for 2nd DoF a2
    q[2,0] = 8.0        # initial guess for 3rd DoF l2

    print('DoF vector q\n', q, '\n')
    
    print('Jacobian for q\n', J(q), '\n')
    # Note: J is "wide" (more arm DoF (3) then hand DoF (2))

    input("hit enter\n")

    # use closed form for Pseudo-Inverse of the "wide" Jacobian
    print('\nPseudo-Inverse (closed form) \n')
    Jpinv1 = J(q).T @ la.inv(J(q) @ J(q).T)      
    print('Pseudo-Inverse of the Jacobian for q (closed form) \n', Jpinv1, '\n')

    input("hit enter\n")

    # use SVD for Pseudo-Inverse of the Jacobian    
    print('\nPseudo-Inverse (via SVD) \n')
    U, S, VT = la.svd(J(q))
    # Note: S is a vector of the Singular values
    print('U of the SVD of the Jacobian\n', U, '\n')
    print('S of the SVD of the Jacobian\n', S, '\n')
    print('VT of the SVD of the Jacobian\n', VT, '\n')
    
    Spinv = np.array([[1/S[0], 0.0, 0.0],
                     [0.0, 1/S[1], 0.0]]).T
    print('Pseudo Inverse of S\n', Spinv, '\n')

    Jpinv2 = VT.T @ Spinv @ U.T
    print('Pseudo-Inverse of the Jacobian for q (via SVD) \n', Jpinv2, '\n')

    input("hit enter\n")

    # One step of Newton-Raphson, respectively Gradient Descent
    pt = rob.Hvec2D()   # target position for the endeffector
    pt.set_xy(5, 10)
    pg = K(q)           # position of the endeffector for the initial q    
    diff = pt - pg      # position "error"

    print('target, K(q), diff (as Transposes - for printing only)\n', pt.T(), pg.T(), diff.T(),'\n')

    print('\nOne step of Newton-Raphson \n')
    delta_q = Jpinv1 @ diff.get_v2D()
    print('change in DoF delta_q \n', delta_q, '\n')
    
    alpha = 0.1
    q1 = q + alpha * delta_q
    print('new DoF vector q1 \n', q1, '\n')
    q1[0,0] = r2d(q1[0,0])
    q1[1,0] = r2d(q1[1,0])
    print('new DoF vector q1 (with degrees for a1 and a2) \n', q1, '\n')

    input("hit enter\n")

    print('\nOne step of Gradient Descent \n')
    delta_q = J(q).T @ diff.get_v2D()
    print('change in DoF delta_q \n', delta_q, '\n')
    
    alpha = 0.01
    q1 = q + alpha * delta_q
    print('new DoF vector q1 \n', q1, '\n')
    q1[0,0] = r2d(q1[0,0])
    q1[1,0] = r2d(q1[1,0])
    print('new DoF vector q1 (with degrees for a1 and a2) \n', q1, '\n')


###################################################
# animation of the use of the Jacobian for IK with Gradient Descent
# 
if select == 3:

    pt = rob.Hvec2D()   # target position for the endeffector
    pt.set_xy(-3,17)

    q[0,0] = d2r(0.0)  # initial guess for 1st DoF a1
    q[1,0] = d2r(0.0)  # initial guess for 2nd DoF a2
    q[2,0] = 5.0       # initial guess for 3rd DoF l2

    # Note: very slow conververgence
    # adaptive damping can be helpful 
    damping = 0.001 # step factor (called alpha in the lecture slides)

    pg = K(q)    
    diff = pt - pg
    while diff.length() > 0.1: # threshold of how close we want to get to the target
        rfig.clear()

        print('Jacobian for q\n', J(q), '\n')
        
        q = q + damping * (J(q).T @ diff.get_v2D()) # one step of Gradient Descent IK
        print('new DoF estimates q:\n', q, '\n')
        
        pg = K(q)
        diff = pt - pg
        print('difference between target and actual position \n', diff, '\n')
    
        rfig.pause(0.01)


        
###################################################
# animation of the use of the Jacobian for IK with Newton
# 
if select == 4:

    pt = rob.Hvec2D()   # target position for the endeffector
    pt.set_xy(-3,17)

    q[0,0] = d2r(0.0)  # initial guess for 1st DoF a1
    q[1,0] = d2r(0.0)  # initial guess for 2nd DoF a2
    q[2,0] = 5.0       # initial guess for 3rd DoF l2

    damping = 0.05 # step factor (called alpha in the lecture slides)

    pg = K(q)    
    diff = pt - pg
    while diff.length() > 0.1: # threshold of how close we want to get to the target
        rfig.clear()


        print('Jacobian for q\n', J(q), '\n')

        # NEED PSEUDO-INVERSE FOR NEWTOWN
        Jpinv = J(q).T @ la.inv(J(q) @ J(q).T)      # use closed form for "wide" Jacobian
        print('Pseudo-Inverse of the Jacobian for q\n', Jpinv, '\n')

        q = q + damping * (Jpinv @ diff.get_v2D())  # one step of Newton IK
        print('new DoF estimates q:\n', q, '\n')
        
        pg = K(q)
        diff = pt - pg
        print('difference between target and actual position \n', diff, '\n')
    
        rfig.pause(0.01)
        
        