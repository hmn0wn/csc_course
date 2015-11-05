#include "matrices.hpp"

int main(int argc, char *argv[])
{

    Matrix mat1(3,3,1), mat2(3,3,2), mat3(3,3,3);
    Matrix mat4(mat2);
    //mat1 = mat2 = mat3;
    (mat1 + mat3).print();
     mat3 = mat2 * mat3;

    //mat1.print();
    mat2.print();
    mat3.print();
    //mat4.print();
    
    return 0;
}
