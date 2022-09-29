import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)

###################################################
# select the demo(
select = int(input('Which demo do you want to run? (1-4)\n'))

###################################################
# short-cuts for trigonometric functions
def s(a): return np.sin(a)
def c(a): return np.cos(a)

def d2r(a): return np.deg2rad(a)

###################################################
# init figure
rfig = rob.Fig2D(min=-15, max=15)


###################################################
# frames and Jacobian of the 2D Rot-Transl robot arm

Fw = rob.Hmat2D() # world frame (I)
v0 = rob.Hvec2D() # origin


def F1(a): # rotation with alpha
    F = rob.HRot2D(a)
    return F


def F2(l): # prismatic joint with length l (scaled in 5-10)
    if l<5 : l=5
    if l>10 : l=10    
    F = rob.HTransl2D(l,0)
    return F

def J(q): # Jacobian J(q), where q is the column vector of the DoF (as 2x1 matrix)
    a = q[0,0]
    l = q[1,0]
    JM = np.array([[-s(a)*l, c(a)],
                   [c(a)*l, s(a)]])
    return JM


###################################################
# Forward Kinematics
pg = rob.Hvec2D() # init position of the end-effector (gripper)


a = d2r(0.0)  # initial value for 1st DoF
l = 0.0       # initial value for 3rd DoF
q = np.array([[a],[l]]) # the (column) vector q of the DoF (in a 2D array, i.e., as a single column in a 2x1 matrix)

# compute the Forward Kinematics (and show the frames and the arm)         
def K(q):    
    F1I = F1(q[0,0])       
    rfig.plot_frame(F1I, size=2, label='F1I')

    F2I = F1I @ F2(q[1,0])
    rfig.plot_frame(F2I, size=2, label='F2I')

    pg = F2I @ v0

    # draw the arm (as two lines)         
    rfig.plot_line(v0, pg, linewidth=3)    

    return pg

###################################################
# animation of the planar Rot-Transl robot arm
# 
if select == 1:
    l = 5.0             # some arbitrary start for l
    for a in range(160):
        rfig.clear()

        l =l + 0.1     # some arbitrary change of l
        q[0,0] = d2r(a) # set 1st DoF 
        q[1,0] = l      # set 2nd DoF

        pg = K(q) # compute FK and show frames plus arm
        print('position of the end-effector \n', pg, '\n')
        
        rfig.pause(0.01)

###################################################
# animation of the use of the Jacobian for IK with Newton
# 
if select == 2:

    pt = rob.Hvec2D()   
    pt.set_xy(-2,7)     # target position for the endeffector

    # Note: with the following q(0,0), the Jacobian J(q) becomes singular and can not be inverted!!!
    # a = d2r(0)    # bad initial guess for 1st DoF 
    # l = 0         # bad initial guess for 2nd DoF

    # Note: the following inital guesses work
    q[0,0] = d2r(0)    # initial guess for 1st DoF
    q[1,0] = 5.0       # initial guess for 2nd DoF

    damping = 0.1 # step factor (called alpha in the lecture slides)

    pg = K(q)    
    diff = pt - pg
    while diff.length() > 0.1: # threshold of how close we want to get to the target
        rfig.clear()

        # Note: the Jacobian is square here, i.e., inverse works
        q = q + damping * (la.inv(J(q)) @ diff.get_v2D()) # one step of Newton IK
                
        pg = K(q)
        diff = pt - pg
        print('difference between target and actual position \n', diff, '\n')
        
        rfig.pause(0.01)

###################################################
# animation of the use of the Jacobian for IK with Newton
# 
if select == 3:

    pt = rob.Hvec2D()   
    pt.set_xy(-2,7)     # target position for the endeffector

    q[0,0] = d2r(0)    # initial guess for 1st DoF
    q[1,0] = 5.0       # initial guess for 2nd DoF

    # Note: if the damping is not small enough, we can get oscillations, etc.
    # damping = 0.05 # no convergence for target (-2,7)^T
    damping = 0.02 # step factor (called alpha in the lecture slides)

    pg = K(q)    
    diff = pt - pg
    while diff.length() > 0.1: # threshold of how close we want to get to the target
        rfig.clear()

        q = q + damping * (J(q).T @ diff.get_v2D()) # one step of Gradient Descent IK
                
        pg = K(q)
        diff = pt - pg
        print('difference between target and actual position \n', diff, '\n')
        
        rfig.pause(0.01)
        
###################################################
# approximation of J at q=(1,2) with delta = 0.1
# 
if select == 4:
    rfig.close()
    
    a = 1
    l = 2
    
    q[0][0] = a
    q[1][0] = l
    J = J(q)
    print('The proper Jacobian at (1,2) \n', J, '\n')
    
    def K1(a,l): return c(a)*l 
    def K2(a,l): return s(a)*l 
    
    d = 0.1 # delta
    Japprox = np.array([[0.0,0.0],[0.0,0.0]])
    Japprox[0,0] = (K1(a+d, l) - K1(a, l))/d
    Japprox[1,0] = (K2(a+d, l) - K2(a, l))/d
    Japprox[0,1] = (K1(a, l+d) - K1(a, l))/d
    Japprox[1,1] = (K2(a, l+d) - K2(a, l))/d 
    print('The approximated Jacobian at (1,2) \n', Japprox, '\n')
    