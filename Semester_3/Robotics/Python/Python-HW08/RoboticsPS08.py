import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)

###################################################
# select the demo
select = int(input('Which demo do you want to run? (1-3)\n'))

###################################################
# short-cuts for trigonometric functions
def s(a): return np.sin(a)
def c(a): return np.cos(a)

def d2r(a): return np.deg2rad(a)
def r2d(a): return np.rad2deg(a)



###################################################
# error propagation

if select == 1:

    def F(x):
        x1 = x[0]
        x2 = x[1]
        
        y1 = s(x1) * x2
        y2 = c(x1) + x2**2
        y = np.array([[y1, y2]]).T
        return y
    
    
    def J(x):
        x1 = x[0]
        x2 = x[1]
        
        JM = np.array([[c(x1)*x2 , s(x1)],
                       [-s(x1) , 2*x2]])
        return JM
    
    C = np.array([[0.021, 0.004],
                  [0.004, 0.038]])
    
    
    # propogate mean, i.e., compute F() at x
    x = np.array([2.1, 3.7])
    print('\n','F(2.1, 3.7) = \n', F(x))
    
    # propogate Covariance, i.e., compute new C with J*C*C^T at x
    C = J(x) @ C @ J(x).T
    print('\n','new Covariance = \n', C)


###################################################
# example with a simple 1D Kalman Filter (KF)

if select == 2:
    u = [2.4, 1.8, -3.1, -2.7]
    z = [1.33, 2.031, -0.37, -0.588]
    
    x = 0
    P = 0
    Q = 0.2
    H = 0.1
    R = 0.3
    
    for i in range(4):
        print('step', i+1)
        x_pred = 1*x + 5*u[i]
        print('prediction of the state x^- : ', x_pred)
        P_pred = 1*P*1 + Q
        print('prediction of the error Covariance P^- : ', P_pred)
        K = P_pred * H * 1/(H * P_pred * H + R)
        print('Kalman gain K : ', K)
        x = x_pred + K*(z[i] - H*x_pred)
        print('new state estimate x : ', x)
        P = (1 - K*H)*P_pred
        print('new error Covariance P : ', P)
        
        print('\n')
        
###################################################
# example with a simple 1D Extended Kalman filter (EKF)

if select == 3:
    u = [np.pi/2]
    z = [1.1]
    
    x = 0
    P = 0
    Q = 0.2
    R = 0.3
    
    for i in range(1):
        print('step', i+1)
        x_pred = x**2 + np.sin(u[i])
        print('prediction of the state x^- : ', x_pred)
        P_pred = 2*x*P*2*x + Q
        print('prediction of the error Covariance P^- : ', P_pred)
        K = P_pred * 3*(x_pred**2) * 1/(3*(x_pred**2) * P_pred * 3*(x_pred**2) + R)
        print('Kalman gain K : ', K)
        x = x_pred + K*(z[i] - x_pred**3)
        print('new state estimate x : ', x)
        P = (1.0 - K*3*(x**2))*P_pred
        print('new error Covariance P : ', P)
        
        print('\n')
        
