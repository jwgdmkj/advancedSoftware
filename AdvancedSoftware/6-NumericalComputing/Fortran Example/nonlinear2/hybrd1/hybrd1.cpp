//#include <stdio.h>
//#include <math.h>
//
////solve
////x1 + x2 + x3 - 3 = 0
////x1^2 + x2^2 + x3^3 - 5 = 0
////e^x1 + x1*x2 + x1*x3 - 1 = 0
//
//#define SOLNUMS 3
//#define MATCOLS SOLNUMS
//#define MATROWS SOLNUMS
//#define TOLERANCE 0.0000001
//
//extern "C"
//{
//	int hybrd1_(void fcn(int*, double*, double*, int*), int*, double*, double*, double*, int*, double*, int*);
//}
//
//void fcn(int* n, double* x, double* fvec, int* iflag)
//{
//	fvec[0] = x[0] + x[1] + x[2] - 3.0;
//	fvec[1] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5.0;
//	fvec[2] = exp(x[0]) + x[0] * x[1] + x[0] * x[2] - 1.0;
//}
//
//void main(void)
//{
//	int n = SOLNUMS;
//	double x[SOLNUMS] = { 0.1, 1.2, 2.5 };	//need to initilize x0
//	double fvec[SOLNUMS];
//	double tol = TOLERANCE;
//	int info;
//	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
//	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;
//
//	hybrd1_(fcn, &n, x, fvec, &tol, &info, wa, &lwa);
//
//	printf("%d %lf %lf %lf\n", info, x[0], x[1], x[2]);
//}