//#include <stdio.h>
//
//#define index_2d(row, col, dim) row*dim+col
//
//extern "C"
//{
//    int gespp_(int*, float*, int*, int*, float*);
//    int solve_(int*, float*, int*, int*, float*, float*);
//};
//
//void main() {
//    int i, ia, j, n, l[3];
//    float a[9], b[3], x[3], s[3];
//    a[index_2d(0, 0, 3)] = 2; a[index_2d(0, 1, 3)] = 4; a[index_2d(0, 2, 3)] = 0;
//    a[index_2d(1, 0, 3)] = 0; a[index_2d(1, 1, 3)] = 1; a[index_2d(1, 2, 3)] = 5;
//    a[index_2d(2, 0, 3)] = 0; a[index_2d(2, 1, 3)] = 1; a[index_2d(2, 2, 3)] = 1;
//    b[0] = 2; b[1] = 6; b[2] = 6;
//
//    n = ia = 3;
//    printf("***** Equation *****\n");
//    for (i = 0; i < 3; i++) {
//        for (j = 0; j < 3; j++) printf("a[%d][%d] = %f, ", i, j, a[index_2d(j, i, 3)]);
//        printf("\n");
//    }
//    printf("b[0] = %f, b[1] = %f, b[2] = %f\n", b[0], b[1], b[2]);
//    gespp_(&n, a, &ia, l, s);
//    printf("***** After LU-decomposition *****\n");
//    printf("s[0] = %f, s[1] = %f, s[2] = %f\n", s[0], s[1], s[2]);
//    printf("l[0] = %d, l[1] = %d, l[2] = %d\n", l[0], l[1], l[2]);
//    for (i = 0; i < 3; i++) {
//        for (j = 0; j < 3; j++) printf("a[%d][%d] = %f, ", i, j, a[index_2d(j, i, 3)]);
//        printf("\n");
//    }
//    solve_(&n, a, &ia, l, b, x);
//    printf("***** Solution *****\n");
//    printf("x[0] = %f, x[1] = %f, x[2] = %f\n", x[0], x[1], x[2]);
//}
