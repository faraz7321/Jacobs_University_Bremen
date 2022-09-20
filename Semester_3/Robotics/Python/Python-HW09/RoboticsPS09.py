import numpy as np
from scipy import linalg as la

import RoboticsLib as rob

import matplotlib
import matplotlib.pyplot as plt


###################################################
# set printing options for numpy
np.set_printoptions(precision=2, suppress=True)

###################################################
# map example

# locations of the robot over time
rob = [0,0,3,3,3]

# sensor readings over time (NOTE that at time t=0, there is no reading)
s = [-1,6,4,3,3]


# the odds of occupancy of cells between the robot and one cell in front of the sensor reading
odds_occ_rob2d = np.log2(0.2/0.8)
# the odds of occupancy at the two cells next to the sensor reading
odds_occ_around_d = np.log2(0.3/0.7)
# the odds of occupancy for the cell of the sensor reading
odds_occ_at_d = np.log2(0.9/0.1)


# initialization of the map with only Zeros
occ_map = np.array([0.0]*10)
# occ_map = [0]*10



t = 0
print('time =',t,', map:', occ_map, '\n')

for t in range(1, 5):
    x = rob[t] + s[t]

    # update cells up to the cell before sensor reading
    for i in range(rob[t], x-1): occ_map[i] += odds_occ_rob2d
    # update cells around the sensor reading
    if x > 0: occ_map[x-1] += odds_occ_around_d
    if x < 9: occ_map[x+1] += odds_occ_around_d
    # update cell of the sensor reading
    occ_map[x] += odds_occ_at_d
    print('time =',t,', map:', occ_map, '\n')

    

    