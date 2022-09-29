import numpy as np
from scipy import linalg as la

import matplotlib
import matplotlib.pyplot as plt

from mpl_toolkits import mplot3d


##################################################################################
# Robotics Library
# v00.7
# 
# (quick & dirty) library for the robotics course
# written by Andreas Birk
#
# do not distribute!!!
#
##################################################################################


##################################################################################
#
# 3D Homogeneous Matrix Class
#
class Hmat:
    def __init__(self, H = np.array([[1.0,0.0,0.0,0.0],[0.0,1.0,0.0,0.0],[0.0,0.0,1.0,0.0],[0.0,0.0,0.0,1.0]])):
        self.H = np.copy(H)
        self.type = 'Hmat'

    def __str__(self):
        return '{}'.format(self.H)        

    ##############################################################################
    # mathematical operators for homogeneous matrices
    #
    def __matmul__(self, B): # matrix, repsectively matrix/vector multiplication with '@'
        if B.type == 'Hmat':
            HA = self.H
            HB = B.H
            HC = HA @ HB
            C =  Hmat(HC)
        if B.type == 'Hvec':
            HA = self.H
            Hb = B.v
            Hc = HA @ Hb
            C =  Hvec(Hc)
        return C

    def __add__(self, B):
        HA = self.H
        HB = B.H
        HC = HA + HB
        HC[3][3] = 1
        C =  Hmat(HC)
        return C

    def __sub__(self, B):
        HA = self.H
        HB = B.H
        HC = HA - HB
        HC[3][3] = 1
        C =  Hmat(HC)
        return C

    def __neg__(self):
        HA = self.H
        HB = -HA
        HB[3][3] = 1
        B =  Hmat(HB)
        return B

    def __mul__(self, c): # scalar multiplication for convenience only!!! Rot of H will not be orthoNORMAL anymore
        HA = self.H
        HB = c*HA
        HB[3][3] = 1
        B =  Hmat(HB)
        return B

    def __rmul__(self, c): # scalar multiplication for convenience only!!! Rot of H will not be orthoNORMAL anymore
        HA = self.H
        HB = c*HA
        HB[3][3] = 1
        B =  Hmat(HB)
        return B

    def __eq__(self, B):  # equal?
        HA = self.H
        HB = B.H
        b = np.array_equal(HA, HB)
        return b

    def __ne__(self, B):  # nonequal?
        HA = self.H
        HB = B.H
        b = not np.array_equal(HA, HB)
        return b
    
    ##############################################################################
    # compute inverse of a homogeneous matrix via rotation transpose
    #
    def inv(self):
        R = self.get_rot()
        HRinv = (R.H).T
        Hinv = Hmat(HRinv)
        
        t = self.get_transl()
        t = -Hinv @ t
        Hinv.set_transl_v(t)
    
        return Hinv 

    ##############################################################################
    # compute transpose of a homogeneous matrix 
    # (NOTE: this is only meaningful for pure homogeneous rotation matrices, i.e., translation is Zero) 
    def T(self):
        HT = Hmat()
        HT.H = self.H.T    
        return HT

    ##############################################################################
    # (re-)set a homogeneous matrix to the Identy matrix
    #
    def set_I(self):
        self.H = np.array([[1.0,0.0,0.0,0.0],[0.0,1.0,0.0,0.0],[0.0,0.0,1.0,0.0],[0.0,0.0,0.0,1.0]])
                 
    ##############################################################################
    # set translation component of a homogeneous matrix
    # (via homogeneous vector v, respectively x,y,z coordinates)
    #
    def set_transl_v(self, v):
        self.H[0,3] = v.v[0,0]
        self.H[1,3] = v.v[1,0]
        self.H[2,3] = v.v[2,0]

    def set_transl_xyz(self, x,y,z):
        self.H[0,3] = x
        self.H[1,3] = y
        self.H[2,3] = z

    ##############################################################################
    # set rotation component of a homogeneous matrix
    # via homogeneous rotation matrices for Roll, Pitch, Yaw
    #    
    def set_rot_X(self, alpha):
        self.set_I()
        self.H[1][1] = np.cos(alpha)
        self.H[1][2] = -np.sin(alpha)
        self.H[2][1] = np.sin(alpha)
        self.H[2][2] = np.cos(alpha)
    
    def set_rot_Y(self, beta):
        self.set_I()
        self.H[0][0] = np.cos(beta)
        self.H[0][2] = np.sin(beta)
        self.H[2][0] = -np.sin(beta)
        self.H[2][2] = np.cos(beta)
    
    def set_rot_Z(self, gamma):
        self.set_I()
        self.H[0][0] = np.cos(gamma)
        self.H[0][1] = -np.sin(gamma)
        self.H[1][0] = np.sin(gamma)
        self.H[1][1] = np.cos(gamma)

    ###################################################
    # generate homogeneous matrices for X-,Y-Z-reflection
    #
    def set_reflect_X(self):
        self.set_I()
        self.H[0][0] = -1

    def set_reflect_Y(self):
        self.set_I()
        self.H[1][1] = -1

    def set_reflect_Z(self):
        self.set_I()
        self.H[2][2] = -1

    ##############################################################################
    # get rotation part of a homogeneous matrices 
    # (return as homogeneous matrix)
    #
    def get_rot(self):
        R = Hmat()
        for i in range(3):
            for j in range(3):
                R.H[i,j] = self.H[i,j]
        return R

    ##############################################################################
    # get rotation part of a homogeneous matrices 
    # (return as 3D 3x3 matrix as plain numpy array)
    #
    def get_rot3D(self):
        R = np.array([[1.0,0.0,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]])
        for i in range(3):
            for j in range(3):
                R[i,j] = self.H[i,j]
        return R

    ##############################################################################
    # get x-/y-/z-axis of the rotation part of a homogeneous matrices 
    # (return as homogeneous vector)
    #
    def get_rotX(self):
        rX = Hvec()
        rX.v[0,0] = self.H[0,0]
        rX.v[1,0] = self.H[1,0]
        rX.v[2,0] = self.H[2,0]
        return rX

    def get_rotY(self):
        rY = Hvec()
        rY.v[0,0] = self.H[0,1]
        rY.v[1,0] = self.H[1,1]
        rY.v[2,0] = self.H[2,1]
        return rY

    def get_rotZ(self):
        rZ = Hvec()
        rZ.v[0,0] = self.H[0,2]
        rZ.v[1,0] = self.H[1,2]
        rZ.v[2,0] = self.H[2,2]
        return rZ

    ##############################################################################
    # get translation part of a homogeneous matrices 
    # (return as homogeneous vector)
    #
    def get_transl(self):
        t = Hvec()
        t.v[0,0] = self.H[0,3]
        t.v[1,0] = self.H[1,3]
        t.v[2,0] = self.H[2,3]
        return t

##################################################################################
# child classes of Hmat:
# - HId : homogeneous identity matrix (just for completeness)
# - HRotX/Y/Z : homogeneous Roll, Pitch, Yaw rotation matrices 
# - HReflectX/Y/Z : homogeneous X-, Y-, Z-axis reflection matrices 
# - HTransl : homogeneous translation matrix, initialized with x,y,z
#        
class HId(Hmat):
    def __init__(self):
        super().__init__(None)
        self.set_I()

class HRotX(Hmat):
    def __init__(self, a):
        super().__init__(None) 
        self.set_rot_X(a)

class HRotY(Hmat):
    def __init__(self, a):
        super().__init__(None) 
        self.set_rot_Y(a)

class HRotZ(Hmat):
    def __init__(self, a):
        super().__init__(None) 
        self.set_rot_Z(a)

class HReflectX(Hmat):
    def __init__(self):
        super().__init__(None) 
        self.set_reflect_X()

class HReflectY(Hmat):
    def __init__(self):
        super().__init__(None) 
        self.set_reflect_X()

class HReflectZ(Hmat):
    def __init__(self):
        super().__init__(None) 
        self.set_reflect_X()

class HTransl(Hmat):
    def __init__(self, x, y, z):
        self.type = 'Hmat'
        self.set_I()
        self.set_transl_xyz(x,y,z)

##################################################################################
# END : 3D Homogeneous Matrix Class & Sub-Classes
##################################################################################

        
##################################################################################
#
# 3D Homogeneous Vector Class
#
class Hvec:
    def __init__(self, hv=np.array([[0.0,0.0,0.0,1.0]]).T):
        self.v = np.copy(hv)
        self.v = np.copy(hv)
        self.type = 'Hvec'

    def __str__(self):
        return '{}'.format(self.v)        

    ##############################################################################
    # mathematical operators for homogeneous vectors
    #
    def __add__(self, b):
        va = self.v
        vb = b.v
        vc = va + vb
        vc[3][0] = 1
        c =  Hvec(vc)
        return c

    def __sub__(self, b):
        va = self.v
        vb = b.v
        vc = va - vb
        vc[3][0] = 1
        c =  Hvec(vc)
        return c

    def __neg__(self):
        va = self.v
        vb = -va
        vb[3][0] = 1
        b =  Hvec(vb)
        return b

    def __mul__(self, c): # (right) scalar multiplication with constant c
        va = self.v
        vb = c*va
        vb[3][0] = 1
        b =  Hvec(vb)
        return b

    def __rmul__(self, c): # (left) scalar multiplication with constant c
        va = self.v
        vb = c*va
        vb[3][0] = 1
        b =  Hvec(vb)
        return b

    def __eq__(self, b):  # equal?
        va = self.v
        vb = b.v
        b = np.array_equal(va, vb)
        return b

    def __ne__(self, b):  # nonequal?
        va = self.v
        vb = b.v
        b = not np.array_equal(va, vb)
        return b

    ##############################################################################
    # cross product of two homogeneous vectors 
    #
    def cross(self, v1):
        hv0 = self.v
        hv1 = v1.v

        cx = hv0[1,0]*hv1[2,0] - hv0[2,0]*hv1[1,0]
        cy = hv0[2,0]*hv1[0,0] - hv0[0,0]*hv1[2,0]
        cz = hv0[0,0]*hv1[1,0] - hv0[1,0]*hv1[0,0]

        v2 = Hvec()
        v2.set_xyz(cx,cy,cz)
        return v2 

    ##############################################################################
    # dot product of two homogeneous vectors (excluding the 4th component '1') 
    #
    def dot(self, v1):
        v0 = self.v
        v1 = v1.v
        s = v0[0,0]*v1[0,0]+v0[1,0]*v1[1,0]+v0[2,0]*v1[2,0]
        return s 

    ##############################################################################
    # set coordinates of a homogeneous vector 
    #
    def set_xyz(self,x,y,z):
        self.v[0][0] = x
        self.v[1][0] = y
        self.v[2][0] = z

    ################################################### 
    # generate quaternion from homogeneous point 
    def hv2q(self):
        q = Quat()
        q.q[0] = 0
        for i in range(3): q.q[i+1] = self.v[i,0]
        return q

    ##############################################################################
    # length and normalization of a homogeneous vector
    #
    def length(self):
        l = np.sqrt(self.v[0,0]*self.v[0,0] + self.v[1,0]*self.v[1,0] + self.v[2,0]*self.v[2,0])
        return l
    
    def normalize(self):
        vn = Hvec()
        l = self.length()
        if l == 0: return 'ERROR: Zero vector can not be normalized'
        for i in range(3): vn.v[i,0] = self.v[i,0]/l
        return vn

    ################################################### 
    # rotation with Rodrigues' formula
    #   k : rotation axis    
    #   a : angle (in radians)
    #
    def rogrigues(self, k, a):
        pr = Hvec()
        kn = k.normalize()
        pr = np.cos(a)*self + np.sin(a)* kn.cross(self) + (1-np.cos(a))*kn.dot(self)*kn
        return pr

# END : 3D Homogeneous Vector Class
##################################################################################


##################################################################################
#
# (Rotation) Quaternion Class
#
class Quat:
    def __init__(self, q_in=np.array([0.0,0.0,0.0,0.0])):
        self.q = np.copy(q_in)
        self.type = 'Quat'

    def __str__(self):
        return '{}'.format(self.q)        

    ##############################################################################
    # mathematical operators for quaternions
    #
    def __add__(self, b):
        qa = self.q
        qb = b.q
        qc = qa + qb
        c =  Quat(qc)
        return c

    def __sub__(self, b):
        qa = self.q
        qb = b.q
        qc = qa - qb
        c =  Quat(qc)
        return c

    def __matmul__(self, q2): # quaternion product with '@'
        qm = Quat()
    
        s1 = self.q[0]
        s2 = q2.q[0]
        v1 = self.get_v()
        v2 = q2.get_v()
 
        qm.q[0] = s1*s2 - np.dot(v1.T,v2)[0,0]
        vm = s1*v2 + s2*v1 + v3D_cross(v1,v2)
        for i in range(3): qm.q[i+1] = vm[i][0]
        return qm

    def __eq__(self, b): # equal?
        qa = self.q
        qb = b.q
        b = np.array_equal(qa, qb)
        return b

    def __ne__(self, b): # nonequal?
        qa = self.q
        qb = b.q
        b = not np.array_equal(qa, qb)
        return b

    ################################################### 
    # conjugate of quaternion q
    def conj(self):
        qc = Quat()
        qc.q[0] = self.q[0]
        for i in range(3): qc.q[i+1] = -self.q[i+1]
        return qc

    ################################################### 
    # norm of quaternion q
    def norm(self):
        l = np.sqrt(self.q[0]*self.q[0] + self.q[1]*self.q[1] + self.q[2]*self.q[2] + self.q[3]*self.q[3])
        return l
    
    ################################################### 
    # normalize quaternion q
    def normalize(self):
        l = self.norm()
        qn = Quat()
        for i in range(4): qn.q[i] = self.q[i]/l
        return qn

    ################################################### 
    # set the 4 values of a quaternion
    def set_q(self, a,b,c,d):
        self.q[0] = a
        self.q[1] = b
        self.q[2] = c
        self.q[3] = d

    ################################################### 
    # generate quaternion values from (homogeneous) point 
    def set_point(self, v):
        self.q[0] = 0
        for i in range(3): self.q[i+1] = v.v[i,0]

    ################################################### 
    # generate rotation quaterion from angle and axis
    #   v : axis as (homogeneous) vector    
    #   a : angle (in radians)
    def set_rot_axis_angle(self, v, a):
        vn = v.normalize()
        self.q = np.array([np.cos(a/2), np.sin(a/2)*vn.v[0,0], np.sin(a/2)*vn.v[1,0], np.sin(a/2)*vn.v[2,0]])

    ################################################### 
    # set the scalar part to s and the vector part from a (homogeneous) vector 
    def set_s_v(self, s, v):
        self.q[0] = s
        self.q[1] = v.v[0,0]
        self.q[2] = v.v[1,0]
        self.q[3] = v.v[2,0]
        
    ################################################### 
    # get scalar part of a quaternion 
    def get_s(self, q):
        s = self.q[3]
        return s

    ################################################### 
    # get vector part of a quaternion as 3D (column) vector
    def get_v(q):
        v = np.array([[0.0,0.0,0.0]]).T
        for i in range(3): v[i,0] = q.q[i+1]
        return v

    ################################################### 
    # convert quaternion q to homogeneous vector hv
    def q2hv(self):
        hv = Hvec()
        for i in range(3): hv.v[i,0] = self.q[i+1]
        return hv


##################################################################################
#
# 3D Vector Functions 
# - mainly as tools like 3D cross-product (e.g., in quaternion multiplication)
# - based on plain column vectors as plain np.arary
# - the homogeneous vector / matric classes are the preferred options when using this library 
#

def v3D_set(x,y,z):
    v = np.array([[x,y,z]]).T
    return v 

def v3D_cross(v0, v1):

    cx = v0[1,0]*v1[2,0] - v0[2,0]*v1[1,0]
    cy = v0[2,0]*v1[0,0] - v0[0,0]*v1[2,0]
    cz = v0[0,0]*v1[1,0] - v0[1,0]*v1[0,0]

    v2 = v3D_set(cx,cy,cz)
    return v2 

##################################################################################

 
##################################################################################
#
# 3D DISPLAY CLASS 
#
##################################################################################

##################################################################################
#
# 3D Plotting for Homogeneous Matrices and Vectors
#
class Fig:
    def __init__(self, min = -10, max = 10):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(projection='3d')
        self.amin = min
        self.amax = max

        self.ax.autoscale(enable=False)
        self.ax.set_xlim3d(self.amin, self.amax)
        self.ax.set_ylim3d(self.amin, self.amax)
        self.ax.set_zlim3d(self.amin, self.amax)
        self.ax.scatter3D(0, 0, 0, color='red') # mark origin
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')
        self.ax.set_zlabel('Z')
        plt.draw()

    ##############################################################################
    # clear figure and set up axes again
    #    
    def clear(self):
        self.ax.cla() 
        self.ax.set_xlim3d(self.amin, self.amax)
        self.ax.set_ylim3d(self.amin, self.amax)
        self.ax.set_zlim3d(self.amin, self.amax)
        self.ax.scatter3D(0, 0, 0, color='red') # mark origin
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')
        self.ax.set_zlabel('Z')
        plt.draw()

    ##############################################################################
    # pause for "wait" seconds to get a nice animation
    #    
    def pause(self, t=0.1):
        time = t
        plt.pause(time)

    ##############################################################################
    # plot a 3D point hp (in homogeneous coordinates)
    #    
    def plot_point(self, hp, *args, **kwargs):
        c = kwargs.get('color', 'black')
        label = kwargs.get('label', None)

        p = hp.v
        self.ax.scatter3D(p[0][0],p[1][0],p[2][0], color=c)

        s = (self.amax-self.amin)
        self.ax.text(p[0][0],p[1][0],p[2][0]-s/100, label, horizontalalignment='center', verticalalignment='top')

        plt.draw()
     
    ##############################################################################
    # plot a 3D vector hv (in homogeneous coordinates)
    #
    def plot_vector(self, hv, *args, **kwargs):
        c = kwargs.get('color', 'black')
        label = kwargs.get('label', None)

        v = hv.v
        self.ax.quiver(0,0,0,v[0][0],v[1][0],v[2][0], color=c)

        s = (self.amax-self.amin)
        self.ax.text(v[0][0],v[1][0],v[2][0]-s/100, label, horizontalalignment='center', verticalalignment='top')

        plt.draw()

    ##############################################################################
    # plot a 3D arrow from hv0 to hv1 (in homogeneous coordinates)
    #
    def plot_arrow(self, hv0, hv1, *args, **kwargs):
        l = 1.0
        l = kwargs.get('length', 1)
        c = kwargs.get('color', 'black')
        label = kwargs.get('label', None)

        v0 = hv0.v
        v1 = hv1.v
        v2 = v1-v0
        self.ax.quiver(v0[0][0],v0[1][0],v0[2][0], v2[0][0],v2[1][0],v2[2][0], length=l, color=c)

        s = (self.amax-self.amin)
        self.ax.text(v0[0][0],v0[1][0],v0[2][0]-s/100, label, horizontalalignment='center', verticalalignment='top')

        plt.draw()

    ##############################################################################
    # plot a 3D line from hv0 to hv1 (in homogeneous coordinates)
    #
    def plot_line(self, hv0, hv1, *args, **kwargs):
        c = kwargs.get('color', 'black')
        w = kwargs.get('linewidth', 1)

        v0 = hv0.v
        v1 = hv1.v        
        self.ax.plot([v0[0][0],v1[0][0]], [v0[1][0],v1[1][0]], [v0[2][0],v1[2][0]], linewidth=w, color=c)
        plt.draw()

    ##############################################################################
    # plot fct for a frame in form of a homogeneous matrix
    #  H : homogeneous matrix
    # (optional) label : name of the frame as string
    # (optional) size : scale of the frame
    # 
    def plot_frame(self, H, *args, **kwargs):
        s = 1.0
        s = kwargs.get('size', s)
        l = (self.amax-self.amin)/10  
        
        origin = H.get_transl()
        self.plot_point(origin, color='black')

        label = kwargs.get('label', None)
        self.ax.text(H.H[0][3], H.H[1][3], H.H[2][3]-l/10, label, horizontalalignment='center', verticalalignment='top')
        
        vx = H.get_rotX()
        self.plot_arrow(origin, origin+vx, length=s, color='red')
        vy = H.get_rotY()
        self.plot_arrow(origin, origin+vy, length=s, color='green')
        vz = H.get_rotZ()
        self.plot_arrow(origin, origin+vz, length=s, color='blue')
    
        plt.draw()

    ##############################################################################
    # close the figure
    # 
    def close(self):
        plt.close()

# END : 3D Plotting for Homogeneous Matrices and Vectors
##################################################################################



################################################################################################################################
################################################################################################################################
# 2D 
################################################################################################################################
################################################################################################################################


##################################################################################
#
# 2D Homogeneous Matrix Class
#
class Hmat2D:
    def __init__(self, H = np.array([[1.0,0.0,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]])):
        self.H = np.copy(H)
        self.type = 'Hmat'

    def __str__(self):
        return '{}'.format(self.H)        

    ##############################################################################
    # mathematical operators for homogeneous matrices
    #
    def __matmul__(self, B): # matrix, repsectively matrix/vector multiplication with '@'
        if B.type == 'Hmat':
            HA = self.H
            HB = B.H
            HC = HA @ HB
            C =  Hmat2D(HC)
        if B.type == 'Hvec':
            HA = self.H
            Hb = B.v
            Hc = HA @ Hb
            C =  Hvec2D(Hc)
        return C

    def __add__(self, B):
        HA = self.H
        HB = B.H
        HC = HA + HB
        HC[2][2] = 1
        C =  Hmat2D(HC)
        return C

    def __sub__(self, B):
        HA = self.H
        HB = B.H
        HC = HA - HB
        HC[2][2] = 1
        C =  Hmat(HC)
        return C

    def __neg__(self):
        HA = self.H
        HB = -HA
        HB[2][2] = 1
        B =  Hmat2D(HB)
        return B

    def __mul__(self, c): # scalar multiplication for convenience only!!! Rot of H will not be orthoNORMAL anymore
        HA = self.H
        HB = c*HA
        HB[2][2] = 1
        B =  Hmat2D(HB)
        return B

    def __rmul__(self, c): # scalar multiplication for convenience only!!! Rot of H will not be orthoNORMAL anymore
        HA = self.H
        HB = c*HA
        HB[2][2] = 1
        B =  Hmat2D(HB)
        return B

    def __eq__(self, B):  # equal?
        HA = self.H
        HB = B.H
        b = np.array_equal(HA, HB)
        return b

    def __ne__(self, B):  # nonequal?
        HA = self.H
        HB = B.H
        b = not np.array_equal(HA, HB)
        return b
    
    ##############################################################################
    # compute inverse of a homogeneous matrix via rotation transpose
    #
    def inv(self):
        R = self.get_rot()
        HRinv = (R.H).T
        Hinv = Hmat2D(HRinv)
        
        t = self.get_transl()
        t = -Hinv @ t
        Hinv.set_transl_v(t)
    
        return Hinv 

    ##############################################################################
    # compute transpose of a homogeneous matrix 
    # (NOTE: this is only meaningful for pure homogeneous rotation matrices, i.e., translation is Zero) 
    def T(self):
        HT = Hmat2D()
        HT.H = self.H.T    
        return HT

    ##############################################################################
    # (re-)set a 2D homogeneous matrix to the 3x3 Identy matrix
    #
    def set_I(self):
        self.H = np.array([[1.0,0.0,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]])
                 
    ##############################################################################
    # set translation component of a 2D homogeneous matrix
    # (via 2D homogeneous vector v, respectively x,y coordinates)
    #
    def set_transl_v(self, v):
        self.H[0,2] = v.v[0,0]
        self.H[1,2] = v.v[1,0]

    def set_transl_xy(self, x,y):
        self.H[0,2] = x
        self.H[1,2] = y

    ##############################################################################
    # set rotation component of a 2D homogeneous matrix
    # via homogeneous 2D rotation matrix
    #    
    def set_rot(self, alpha):
        self.set_I()
        self.H[0][0] = np.cos(alpha)
        self.H[0][1] = -np.sin(alpha)
        self.H[1][0] = np.sin(alpha)
        self.H[1][1] = np.cos(alpha)

    ###################################################
    # generate 2D homogeneous matrices for X-,Y-reflection
    #
    def set_reflect_X(self):
        self.set_I()
        self.H[0][0] = -1

    def set_reflect_Y(self):
        self.set_I()
        self.H[1][1] = -1

    ##############################################################################
    # get rotation part of a 2D homogeneous matrices 
    # (return as 2D homogeneous matrix)
    #
    def get_rot(self):
        R = Hmat2D()
        for i in range(3):
            for j in range(3):
                R.H[i,j] = self.H[i,j]
        return R

    ##############################################################################
    # get rotation part of a 2D homogeneous matrices 
    # (return as 2D 2x2 matrix as plain numpy array)
    #
    def get_rot2D(self):
        R = np.array([[1.0,0.0],[0.0,1.0]])
        for i in range(2):
            for j in range(2):
                R[i,j] = self.H[i,j]
        return R

    ##############################################################################
    # get x-/y-axis of the rotation part of a 2D homogeneous matrices 
    # (return as homogeneous vector)
    #
    def get_rotX(self):
        rX = Hvec2D()
        rX.v[0,0] = self.H[0,0]
        rX.v[1,0] = self.H[1,0]
        return rX

    def get_rotY(self):
        rY = Hvec2D()
        rY.v[0,0] = self.H[0,1]
        rY.v[1,0] = self.H[1,1]
        return rY

    ##############################################################################
    # get translation part of a 2D homogeneous matrices 
    # (return as homogeneous vector)
    #
    def get_transl(self):
        t = Hvec2D()
        t.v[0,0] = self.H[0,2]
        t.v[1,0] = self.H[1,2]
        return t

##################################################################################
# child classes of Hmat2D:
# - HId2D : 2D homogeneous identity matrix (just for completeness)
# - HRot2D : 2D homogeneous rotation matrix 
# - HReflectX/Y2D : 2D homogeneous X-, Y- reflection matrices 
# - HTransl2D : 2D homogeneous translation matrix, initialized with x,y
#        
class HId2D(Hmat2D):
    def __init__(self):
        super().__init__(None)
        self.set_I()

class HRot2D(Hmat2D):
    def __init__(self, a):
        super().__init__(None) 
        self.set_rot(a)

class HReflectX2D(Hmat2D):
    def __init__(self):
        super().__init__(None) 
        self.set_reflect_X()

class HReflectY2D(Hmat2D):
    def __init__(self):
        super().__init__(None) 
        self.set_reflect_X()

class HTransl2D(Hmat2D):
    def __init__(self, x, y):
        self.type = 'Hmat'
        self.set_I()
        self.set_transl_xy(x,y)

##################################################################################
# END : 2D Homogeneous Matrix Class & Sub-Classes
##################################################################################

        
##################################################################################
#
# 2D Homogeneous Vector Class
#
class Hvec2D:
    def __init__(self, hv=np.array([[0.0,0.0,1.0]]).T):
        self.v = np.copy(hv)
        self.v = np.copy(hv)
        self.type = 'Hvec'

    def __str__(self):
        return '{}'.format(self.v)        

    ##############################################################################
    # mathematical operators for homogeneous vectors
    #
    def __add__(self, b):
        va = self.v
        vb = b.v
        vc = va + vb
        vc[2][0] = 1
        c =  Hvec2D(vc)
        return c

    def __sub__(self, b):
        va = self.v
        vb = b.v
        vc = va - vb
        vc[2][0] = 1
        c =  Hvec2D(vc)
        return c

    def __neg__(self):
        va = self.v
        vb = -va
        vb[2][0] = 1
        b =  Hvec2D(vb)
        return b

    def __mul__(self, c): # (right) scalar multiplication with constant c
        va = self.v
        vb = c*va
        vb[2][0] = 1
        b =  Hvec2D(vb)
        return b

    def __rmul__(self, c): # (left) scalar multiplication with constant c
        va = self.v
        vb = c*va
        vb[2][0] = 1
        b =  Hvec2D(vb)
        return b

    def __eq__(self, b):  # equal?
        va = self.v
        vb = b.v
        b = np.array_equal(va, vb)
        return b

    def __ne__(self, b):  # nonequal?
        va = self.v
        vb = b.v
        b = not np.array_equal(va, vb)
        return b

    ##############################################################################
    # dot product of two homogeneous 2D vectors (excluding the 3th component '1') 
    #
    def dot(self, v1):
        v0 = self.v
        v1 = v1.v
        s = v0[0,0]*v1[0,0]+v0[1,0]*v1[1,0]
        return s 

    ##############################################################################
    # compute transpose of a homogeneous 2D vector 
    # (NOTE: this is mainy useful for printing a vector 
    def T(self):
        vT = Hvec2D()
        vT.v = self.v.T    
        return vT


    ##############################################################################
    # set coordinates of a homogeneous 2D vector 
    #
    def set_xy(self,x,y):
        self.v[0][0] = x
        self.v[1][0] = y

    ##############################################################################
    # get plain 2D vector as numpy array 
    #
    def get_v2D(self):
        v = np.array([[0.0],[0.0]])
        v[0,0] = self.v[0,0]
        v[1,0] = self.v[1,0]
        return v

    ##############################################################################
    # length and normalization of a homogeneous 2D vector
    #
    def length(self):
        l = np.sqrt(self.v[0,0]*self.v[0,0] + self.v[1,0]*self.v[1,0])
        return l
    
    def normalize(self):
        vn = Hvec()
        l = self.length()
        if l == 0: return 'ERROR: Zero vector can not be normalized'
        for i in range(2): vn.v[i,0] = self.v[i,0]/l
        return vn

# END : 2D Homogeneous Vector Class
# ##################################################################################

 
##################################################################################
#
# 2D DISPLAY CLASS 
#
##################################################################################

##################################################################################
#
# 2D Plotting for Homogeneous Matrices and Vectors
#
class Fig2D:
    def __init__(self, min = -10, max = 10):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot()
        self.amin = min
        self.amax = max

        self.ax.autoscale(enable=False)
        self.ax.set_xlim(self.amin, self.amax)
        self.ax.set_ylim(self.amin, self.amax)
        self.ax.scatter(0, 0, color='red') # mark origin
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')

        plt.grid(b=True, which='major', axis='both')

        plt.draw()

    ##############################################################################
    # clear figure and set up axes again
    #    
    def clear(self):
        self.ax.cla() 
        self.ax.set_xlim(self.amin, self.amax)
        self.ax.set_ylim(self.amin, self.amax)
        self.ax.scatter(0, 0, color='red') # mark origin
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')

        plt.grid(b=True, which='major', axis='both')

        plt.draw()

    ##############################################################################
    # pause for "wait" seconds to get a nice animation
    #    
    def pause(self, t=0.1):
        time = t
        plt.pause(time)

    ##############################################################################
    # plot a 2D point hp (in homogeneous coordinates)
    #    
    def plot_point(self, hp, *args, **kwargs):
        c = kwargs.get('color', 'black')
        label = kwargs.get('label', None)

        p = hp.v
        self.ax.scatter(p[0][0],p[1][0], color=c)

        s = (self.amax-self.amin)
        self.ax.text(p[0][0],p[1][0]-s/100, label, color=c, horizontalalignment='center', verticalalignment='top')

        plt.draw()
     
    ##############################################################################
    # plot a 2D vector hv (in homogeneous coordinates)
    #
    def plot_vector(self, hv, *args, **kwargs):
        c = kwargs.get('color', 'black')
        label = kwargs.get('label', None)

        v = hv.v
        self.ax.quiver(0,0,v[0,0],v[1,0], color=c, width=0.005, angles='xy', scale_units='xy', scale=1)

        s = (self.amax-self.amin)
        self.ax.text(v[0][0],v[1][0]-s/100, label, horizontalalignment='center', verticalalignment='top')

        plt.draw()

    ##############################################################################
    # plot a 2D arrow from hv0 to hv1 (in homogeneous coordinates)
    #
    def plot_arrow(self, hv0, hv1, *args, **kwargs):
        l = 1.0
        l = kwargs.get('length', l)

        c = kwargs.get('color', 'black')
        label = kwargs.get('label', None)

        v0 = hv0.v
        v1 = hv1.v
        v2 = v1-v0
        self.ax.quiver(v0[0,0],v0[1,0], v2[0,0]*l,v2[1,0]*l, color=c, width=0.005, angles='xy', scale_units='xy', scale=1)

        s = (self.amax-self.amin)
        self.ax.text(v0[0,0],v0[1,0]-s/100, label, horizontalalignment='center', verticalalignment='top')

        plt.draw()

    ##############################################################################
    # plot a 2D line from hv0 to hv1 (in homogeneous coordinates)
    #
    def plot_line(self, hv0, hv1, *args, **kwargs):
        c = kwargs.get('color', 'black')
        w = kwargs.get('linewidth', 1)

        v0 = hv0.v
        v1 = hv1.v        
        self.ax.plot([v0[0][0],v1[0][0]], [v0[1][0],v1[1][0]], linewidth=w, color=c)
        plt.draw()

    ##############################################################################
    # plot a 2D circle with center hv (in homogeneous coordinates) and radius r (as scalar)
    #
    def plot_circle(self, hv, r, *args, **kwargs):
        c = kwargs.get('color', 'black')
        w = kwargs.get('linewidth', 1)
        f = kwargs.get('fill', False)

        circ = plt.Circle((hv.v[0,0], hv.v[1,0]),r,fill=f,color=c,linewidth=w)        
        self.ax.add_artist(circ)
        plt.draw()

    ##############################################################################
    # plot fct for a 2D frame in form of a 2D homogeneous matrix
    #  H : homogeneous matrix
    # (optional) label : name of the frame as string
    # (optional) size : scale of the frame
    # 
    def plot_frame(self, H, *args, **kwargs):
        s = 1.0
        s = kwargs.get('size', s)
        l = (self.amax-self.amin)/10  
        
        origin = H.get_transl()
        self.plot_point(origin, color='black')

        label = kwargs.get('label', None)
        self.ax.text(H.H[0,2], H.H[1,2]-l/10, label, horizontalalignment='center', verticalalignment='top')
        
        vx = H.get_rotX()
        self.plot_arrow(origin, origin+vx, length=s, color='red')
        vy = H.get_rotY()
        self.plot_arrow(origin, origin+vy, length=s, color='green')
 
        C = matplotlib.patches.Circle([1,3], radius=2)

        plt.draw()

    ##############################################################################
    # plot a 2D mobile robot mr as circle plus frame
    #
    def plot_mrob(self, mr, *args, **kwargs):
        c = kwargs.get('color', 'blue')
        s = kwargs.get('size', 1)
        f = kwargs.get('fill', False)
        r = s/2.0
        
        x = mr.pose[0,0]
        y = mr.pose[1,0]
        theta = mr.pose[2,0]
        
        circ = plt.Circle((x, y), r, fill=True, color=c, zorder=0)        
        self.ax.add_artist(circ)
        plt.draw()

        F = HRot2D(theta)
        F.set_transl_xy(x,y)
        self.plot_frame(F, size = r)

    ##############################################################################
    # plot a list of 2D beacons (multilateration)
    #
    def plot_beacons(self, ml, *args, **kwargs):
        c = kwargs.get('color', 'black')
        f = kwargs.get('fill', True)

        s = (self.amax-self.amin)
        
        nb = ml.n   # number of beacons
        for i in range(nb):
            x = ml.BL[i][0,0]
            y = ml.BL[i][1,0]
            self.ax.scatter(x,y, color=c)

            self.ax.text(x,y+s/100, ml.NL[i], color=c, horizontalalignment='center', verticalalignment='bottom')
           
        plt.draw()

    ##############################################################################
    # plot a list of 2D ranges (multilateration)
    #
    def plot_ranges(self, ml, *args, **kwargs):
        c = kwargs.get('color', 'black')
        f = kwargs.get('fill', False)

        nb = ml.n   # number of beacons
        for i in range(nb):
            x = ml.BL[i][0,0]
            y = ml.BL[i][1,0]
            r = ml.RL[i]
            circ = plt.Circle((x, y), r, fill=f, color=c)        
            self.ax.add_artist(circ)
            
        plt.draw()


    ##############################################################################
    # close the figure
    # 
    def close(self):
        plt.close()

# END : 2D Plotting for Homogeneous Matrices and Vectors
#################################################################################


##################################################################################
#
# 2D MOBILE ROBOTS 
#
##################################################################################

##################################################################################
#
# wheel class (including aspects of the attached motor-unit) 
#
class WheelGearMotor:
    def __init__(self, radius = 1.0, gear_ratio = 1.0, qdec_ppr = 1.0):
        self.r = radius             # wheel radius
        self.gr = gear_ratio        # gear ratio of the motor unit
        self.qdec_ppr = qdec_ppr    # pulses per rotation (ppr) of the motor quadrature encoder

    def set_radius(self, r):
        self.r = r

    def set_gearratio(self, gr):
        self.gr = gr

    def set_qdec_ppr(self, ppr):
        self.qdec_ppr = ppr 

    ##############################################################################
    # convert motor speed (RPM) to wheel velocity (m/sec)
    def rpm2mpsec(self, motor_rpm):
        velocity = self.r * self.gr * (1/60.0 * motor_rpm * 2*np.pi) 
        return velocity

    ##############################################################################
    # convert convert qdec counts (pure number) in a time-interval (sec) to wheel velocity (m/sec)
    def qdec2mpsec(self, qdec_counts, delta_t):
        velocity = self.r * self.gr * (qdec_counts/self.qdec_ppr * 1/delta_t) 
        return velocity

 
##################################################################################
#
# generic mobile robot class
#
class MobileRob:
    def __init__(self, pose = np.array([[0.0, 0.0, 0.0]]).T):
        self.pose = np.copy(pose)
        
    def set_pose(self, x, y, theta):
        self.pose[0,0] = x
        self.pose[1,0] = y
        self.pose[2,0] = theta

    def get_pose(self):
        return self.pose
        
##################################################################################
#
# differential drive class
#
class MobileDifferential(MobileRob):
    def __init__(self, wheeldistance = 1.0, pose = np.array([[0.0, 0.0, 0.0]]).T):
        super().__init__(None)
        self.pose = np.copy(pose)
        self.D = wheeldistance # distance between the two wheels

    def set_wheeldistance(self, d):
        self.D = d
        
    ##############################################################################
    # move differential drive robot 
    # - v : list with left/right wheel speed (m/sec)
    # - dt : time interval (sec)
    def move(self, v, dt):
        D = self.D
        x = self.pose[0,0]
        y = self.pose[1,0]
        theta = self.pose[2,0]

        vl = v[0]
        vr = v[1]
        
        if vl == vr:        # the "arc" has an infinite radius, i.e., it is a line
            d = vl * dt
            self.pose[0,0] = np.cos(theta) * d
            self.pose[1,0] = np.sin(theta) * d           
        else:               # vl and vr differ, i.e., there is a proper arc
            R = D/2.0 * (vr + vl)/(vr - vl)
            omega = (vr - vl)/D
            
            x_icc = x - R*np.sin(theta) 
            y_icc = y + R*np.cos(theta) 
            
            a = omega * dt
            self.pose[0,0] = np.cos(a)*(x-x_icc) - np.sin(a)*(y-y_icc) + x_icc
            self.pose[1,0] = np.sin(a)*(x-x_icc) + np.cos(a)*(y-y_icc) + y_icc
            self.pose[2,0] = theta + a

##################################################################################
#
# Omnidirectional-Drive (4 evenly spaced Wheels)  
#
class MobileOmni4W(MobileRob):
    def __init__(self, wheeltocenter = 1.0, pose = np.array([[0.0, 0.0, 0.0]]).T):
        super().__init__(None)
        self.pose = np.copy(pose)
        self.R = wheeltocenter  # distance to the Center of Motion
        self.wheelangle = np.deg2rad(90.0)
        
        a = self.wheelangle
        R = self.R
        M_IK = np.array([[-np.sin(0.0), np.cos(0.0), R],
                         [-np.sin(a), np.cos(a), R],
                         [-np.sin(2*a), np.cos(2*a), R],
                         [-np.sin(3*a), np.cos(3*a), R]])
        M_FK = la.inv(M_IK.T @ M_IK) @ M_IK.T   # Note: Pseudo-Inverse here needed
        self.IK = M_IK
        self.FK = M_FK
            
    ##############################################################################
    # move omni drive robot 
    # - velocity vector with 4x wheel speed (m/sec)
    # - time interval dt (sec)
    def move(self, velocities, dt):
        
        # generate a 4x1 velocity column vector
        v = np.array([[0.0,0.0,0.0,0.0]]).T
        for i in range(4): v[i,0] = velocities[i]
            
        # compute pose change
        delta_p = self.FK @ (dt*v)                      # pose change in the local robot frame
        a = self.pose[2,0] + delta_p[2,0]/2.0           # angle in between old and new orientation
        delta_p = HRot2D(a).H @ delta_p                 # pose change in the global frame

        self.pose[0,0] += delta_p[0,0] 
        self.pose[1,0] += delta_p[1,0] 
        self.pose[2,0] += delta_p[2,0]


##################################################################################
#
# Omnidirectional-Drive (3 Wheels evenly spaced wheels  
#
class MobileOmni3W(MobileRob):
    def __init__(self, wheeltocenter = 1.0, pose = np.array([[0.0, 0.0, 0.0]]).T):
        super().__init__(None)
        self.pose = np.copy(pose)
        self.R = wheeltocenter  # distance to the Center of Motion
        self.wheelangle = np.deg2rad(120.0)
        
        a = self.wheelangle
        R = self.R
        M_IK = np.array([[-np.sin(0.0), np.cos(0.0), R],
                         [-np.sin(a), np.cos(a), R],
                         [-np.sin(2*a), np.cos(2*a), R]])
        M_FK = la.inv(M_IK)     # Note: normail Inverse is here sufficient
        self.IK = M_IK
        self.FK = M_FK
            
    ##############################################################################
    # move omni drive robot 
    # - velocity vector with 4x wheel speed (m/sec)
    # - time interval dt (sec)
    def move(self, velocities, dt):
        
        # generate a 4x1 velocity column vector
        v = np.array([[0.0,0.0,0.0]]).T
        for i in range(3): v[i,0] = velocities[i]
            
        # compute pose change
        delta_p = self.FK @ (dt*v)                      # pose change in the local robot frame
        a = self.pose[2,0] + delta_p[2,0]/2.0           # angle in between old and new orientation
        delta_p = HRot2D(a).H @ delta_p                 # pose change in the global frame

        self.pose[0,0] += delta_p[0,0] 
        self.pose[1,0] += delta_p[1,0] 
        self.pose[2,0] += delta_p[2,0]


##################################################################################
#
# 2D LOCALIZATION 
#
##################################################################################

##################################################################################
#
# multilateration class 
#
class Multilateration2D:
    def __init__(self):
        self.NL = []    # list of the numbers (identifiers) of each beacon
        self.BL = []    # list of beacon locations        
        self.RL = []    # list of ranges
        self.n = 0      # number of beacons

    def add_beacon(self, number, x, y):
        self.NL.append(number)
        b = np.array([[x,y,1.0]]).T
        self.BL.append(b)
        self.RL.append(0.0)
        self.n += 1

    def add_range(self, number, dist):
        i = self.NL.index(number)
        self.RL[i] = dist
    
    def LLS_fit(self, verbose=False):        
        rows = self.n-1

        x_end = self.BL[rows][0,0]
        y_end = self.BL[rows][1,0]
        d_end = self.RL[rows]

        A = np.array([[0.0, 0.0]]*rows)
        for i in range(rows):
            x_i = self.BL[i][0,0]
            y_i = self.BL[i][1,0]
            
            A[i,0] = 2*(x_i - x_end)
            A[i,1] = 2*(y_i - y_end)
        if verbose: print('A \n', A)

        b = np.array([[0.0]]*rows)
        for i in range(rows):
            x_i = self.BL[i][0,0]
            y_i = self.BL[i][1,0]
            d_i = self.RL[i]
   
            b[i,0] = x_i**2 - x_end**2 + y_i**2 - y_end**2 - d_i**2 + d_end**2 
        if verbose: print('b \n', b)

        Apinv = la.inv(A.T @ A) @ A.T
        if verbose: print('The Pseudo-Inverse of A\n', Apinv)

        pos = Apinv @ b     # find the least squares fit
        
        hpos = Hvec2D()
        hpos.set_xy(pos[0,0], pos[1,0])
        if verbose: print('the solution\n', hpos)
        
        return hpos
    
##################################################################################
#
# multidimensional scaling (MDS) class 
#
class MultiDimensionalScaling2D:
    def __init__(self, n_nodes, verbose=False):
        self.n = n_nodes                                # number of nodes

        self.D = np.array([[0.0]*n_nodes]*n_nodes)  	# 2D matrix with the distances Dij between the nodes ij
        if verbose: print('initial distance matrix D\n', self.D)

        self.A = np.array([[0.0]*n_nodes]*n_nodes)  	# 2D matrix with the distances squared
        if verbose: print('initial matrix A = -1/2 D^(2) \n', self.A)
 
    def add_distance(self, node0, node1, dist, verbose=False):
        self.D[node0,node1] = dist
        self.D[node1,node0] = dist  # D must be a symmetric matrix 
        if verbose: print('updated distance matrix D\n', self.D)

        self.A[node0,node1] = -0.5 * dist**2
        self.A[node1,node0] = -0.5 * dist**2  # A must be a symmetric matrix 
        if verbose: print('updated matrix A = -1/2 D^(2)\n', self.A)
    
    def centering(self, verbose=False):
        n = self.n
        I = np.identity(n)
        M1 = np.array([[1.0]*n]*n)

        C = I - 1/n * M1
        if verbose: print('centering matrix C\n', C)        
        return C
    
    def MDS_fit(self, verbose=False): 
        if verbose: print('distance matrix D\n', self.D)

        C = self.centering()
        if verbose: print('\nintermediate matrix A\n', self.A)

        B = C @ self.A @ C
        if verbose: print('\nintermediate matrix B\n', B)

        V, L, VT = la.svd(B)
        # Note: S is a vector of the Singular values
        if verbose: print('\nV of the (symmetric) SVD \n', V)
        if verbose: print('\nL of the (symmetric) SVD \n', L)
        if verbose: print('\nVT of the (symmetric) SVD \n', VT)

        Lsqrt = np.identity(2)
        Lsqrt[0,0] = np.sqrt(L[0]) 
        Lsqrt[1,1] = np.sqrt(L[1]) 
        if verbose: print('\nL^(1/2) \n', Lsqrt)

        V2D = np.array([[0.0]*2]*self.n)
        for i in range(self.n):
            V2D[i,0] = V[i,0]
            V2D[i,1] = V[i,1]            
        if verbose: print('\nthe 2D version of V (i.e., as #nodes x 2 matrix)\n', V2D)
        
        X = V2D @ Lsqrt
        
        if verbose: print('\nthe solution\n', X)
        return X
    