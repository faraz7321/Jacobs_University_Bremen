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
# rotation with Rodriguez formula
# by 30 degrees around (1,-1,3)
#
if select == 1:
    # init the figure and plot the Identy matrix as Cartesian frame in the origin
    rfig = rob.Fig()
    Fw = rob.HId()
    rfig.plot_frame(Fw, label='Fw', size=2)

    # point p as homogeneous vector
    p = rob.Hvec()
    p.set_xyz(2, 3, 4)
    print('point p that is rotated\n', p)
    rfig.plot_point(p, label='p')

    # define the axis and the angle
    a = np.deg2rad(10)
    v = rob.Hvec()
    v.set_xyz(1, -1, 3)
    print('rotation axis v, angle a\n', v, '\n',  a)
    rfig.plot_vector(v, label='v')

    # rotate with Rodrigues formula
    # (NOTE: axis v is normalized inside Rodrigues formula method)
    pr = p.rogrigues(v, a)
    print('rotated point pr \n', pr)
    rfig.plot_point(pr, label='pr')


###################################################
# animated rotation with Rodriguez formula
#
if select == 2:
    # init the figure and plot the Identy matrix as Cartesian frame in the origin
    rfig = rob.Fig()
    Fw = rob.HId()
    rfig.plot_frame(Fw, size=2)

    # point p as homogeneous vector
    p = rob.Hvec()
    p.set_xyz(2, 3, 4)
    print('point p that is rotated\n', p)
    rfig.plot_point(p, label='p')

    # define the axis and the angle
    a = np.deg2rad(30)
    v = rob.Hvec()
    v.set_xyz(1, -1, 3)
    print('rotation axis v, angle a\n', v, '\n',  a)
    rfig.plot_vector(v, label='v')

    for i in range(36):
        # rotate with Rodrigues formula
        # (NOTE: axis v is normalized inside Rodrigues formula method)
        p = p.rogrigues(v, a)
        # print('rotated point p \n', p)
        rfig.plot_point(p)
        rfig.pause(0.1)


###################################################
# # close figure (works also from Console)
# rfig.close()
