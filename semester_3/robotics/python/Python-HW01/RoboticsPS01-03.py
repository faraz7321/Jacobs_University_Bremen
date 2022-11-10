import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

###################################################
# set printing options for numpy
np.set_printoptions(precision=4, suppress=True)

###################################################
# rotation quaternion basics
#

# option 1 : initialize quaternion instance on creation
q1 = rob.Quat(np.array([1, 2, 3, 4]))

# option 2 :
# - create quaternion instance,
# - then set its components with the according method
q2 = rob.Quat()
q2.set_q(0.4811480, 0.1984591, 0.7246066, 0.4517253)

# compute quaternion norms and print them
n1 = q1.norm()
n2 = q2.norm()
print('quaternion q1\n', q1, '\n')
print('norm of quaternion q1\n', n1, '\n')
print('quaternion q2\n', q2, '\n')
print('norm of quaternion q2\n', n2, '\n')

# compute quaternion product and print it
q3 = q2 @ q1
print('\n')
print('quaternion product of q1 and q2 \n', q3, '\n')
