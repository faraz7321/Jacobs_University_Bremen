#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>

using namespace std;
using namespace Eigen;
int main()
{

    // vectors/matrices given
    Vector3d a(1, 1, 0);
    Vector3d b(-1, 2, 5);
    Matrix3d M;
    M << 2, -1, 0, -1, 2, -1, 0, -1, 2; // 3x3 matrix

    // a)
    double in_prod = a.dot(b);
    cout << "\na) Inner product between a and b (a . b): " << in_prod << endl;

    // b)
    Vector3d matrix_vector = M * b;
    cout << "\nb) Matrix-vector product: [" << matrix_vector.transpose() << "]t" << endl;

    // c)
    double b_norm = b.norm();
    cout << "\nc) L2 norm of b: " << b_norm << endl;

    // d) linear system of equation 'Mx = b' LU factorization
    Vector3d x;
    x = M.fullPivLu().solve(b);
    cout << "\nd) x: [" << x.transpose() << "]t" << endl;

    // e) Cholesky factorization.
    LLT<Matrix3d> temp(M);
    x = temp.solve(b);
    cout << "\ne) x: [" << x.transpose() << "]t" << endl;

    return 0;
}