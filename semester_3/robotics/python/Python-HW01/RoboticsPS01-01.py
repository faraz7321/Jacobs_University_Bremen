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
# handedness of a frame
#

if select == 1:
    rfig = rob.Fig()

    # option 1: create homogeneous matrix with numpy array on initialization of the instance
    A = rob.Hmat(np.array([[0.866, -0.433, -0.250, 2], [0.0, -0.5,
                 0.866, -4.0], [-0.5, -0.75, -0.433, 1.0], [0, 0, 0, 1]]))
    print('matrix A\n', A)
    rfig.plot_frame(A, size=4, label='A')

    # rotation part of matrix A (as plain 3x3 numpy array)
    RA = A.get_rot3D()
    print('rotation part RA of matrix A \n', RA)

    det = la.det(RA)
    print('det(RA) =\n', det, '\n')

    # reflection on Y-axis
    Refl = rob.HReflectY()
    B = Refl @ A
    print('matrix B (A reflected on y-axis)\n', B)
    rfig.plot_frame(B, size=4, label='B')

    # rotation part of matrix A (as plain 3x3 numpy array)
    RB = B.get_rot3D()
    print('rotation part RB of matrix B \n', RB)

    det = la.det(RB)
    print('det(RB) =\n', det, '\n')

###################################################
# handedness of a rotation (right-handed)
#
if select == 2:
    rfig = rob.Fig()
    Fw = rob.HId()

    # homogeneous matrix of point (1,2,3)
    H1 = rob.Hmat()
    H1.set_transl_xyz(1, 2, 3)
    print('matrix H1\n', H1)

    # option 2: create homogeneous matrix from combination of Roll, Pitch, Yaw, and Translation
    # e.g., 1st roll by 3, 2nd pitch by 4.5, 3rd no yaw, no translation
    A = rob.Hmat()
    R0 = rob.HRotX(np.deg2rad(3))
    R1 = rob.HRotY(np.deg2rad(4.5))
    R2 = rob.HRotZ(np.deg2rad(0))
    T = rob.HTransl(0, 0, 0)
    A = T @ R2 @ R1 @ R0
    print('matrix A\n', A)

    RA = A.get_rot3D()
    print('rotation part RA of matrix A \n', RA)
    det = la.det(RA)
    print('det(RA) =\n', det, '\n')

    wait = 0.05
    for i in range(90):
        rfig.clear()
        rfig.plot_frame(Fw, size=2)

        H1 = A @ H1
        rfig.plot_frame(H1, size=2)
        rfig.pause(wait)

###################################################
# handedness of a rotation ("left-handed"): angle = -angle
#
if select == 3:
    rfig = rob.Fig()
    Fw = rob.HId()

    # homogeneous matrix of point (1,2,3)
    H1 = rob.Hmat()
    H1.set_transl_xyz(5, 0, 0)
    print('matrix H1\n', H1)

    # create a "left-handed" Yaw rotation matrix Rz (according to cork-srew rule):
    # - the rotation is in the opposite direction,
    # - i.e., clockwise, which means that the rotation angle is negated
    # - and we can use: cos(-a) = cos(a) and sin(-a) = -sin(a)
    # NOTE: we are still in a right-handed coordinate system, i.e., det(Rz) = 1
    gamma = np.deg2rad(5)
    Rz = rob.HRotZ(gamma)
    Rz.H[0, 1] = np.sin(gamma)  # change from -sin() to sin()
    Rz.H[1, 0] = -np.sin(gamma)  # change from sin() to -sin()

    print('matrix Rz\n', Rz)

    R = Rz.get_rot3D()
    print('rotation part R of matrix Rz \n', R)
    det = la.det(R)
    print('det(RB) =\n', det, '\n')

    wait = 0.05
    for i in range(90):
        rfig.clear()
        rfig.plot_frame(Fw, size=2)

        H1 = Rz @ H1
        rfig.plot_frame(H1, size=2)
        rfig.pause(wait)

###################################################
# handedness of a rotation ("left-handed"): rotation = inverse rotation
#
if select == 4:
    rfig = rob.Fig()
    Fw = rob.HId()

    # homogeneous matrix of point (1,2,3)
    H1 = rob.Hmat()
    H1.set_transl_xyz(5, 0, 0)
    print('matrix H1\n', H1)

    # create a "left-handed" Yaw rotation matrix Rz (according to cork-srew rule):
    # - the rotation is in the opposite direction,
    # - i.e., we can also use the homogenous matrix inverse for the inverse rotation
    # NOTE: we are still in a right-handed coordinate system, i.e., det(Rz) = 1
    gamma = np.deg2rad(5)
    Rz = rob.HRotZ(gamma)
    Rz = Rz.inv()

    print('matrix Rz\n', Rz)

    R = Rz.get_rot3D()
    print('rotation part R of matrix Rz \n', R)
    det = la.det(R)
    print('det(RB) =\n', det, '\n')

    wait = 0.05
    for i in range(90):
        rfig.clear()
        rfig.plot_frame(Fw, size=2)

        H1 = Rz @ H1
        rfig.plot_frame(H1, size=2)
        rfig.pause(wait)

###################################################
# close figure (works also from Console)
#input("hit enter")
# plt.close()

# closes all open figures
# plt.close('all')
