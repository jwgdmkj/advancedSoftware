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
//	int hybrj1_(void fcn(int*, double*, double*, double*, int*, int*), int*, double*, double*, double*, int*, double*, int*, double*, int*);
//}
//
//void fcn(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
//{
//	if (*iflag == 1) {
//		fvec[0] = x[0] + x[1] + x[2] - 3.0;
//		fvec[1] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5.0;
//		fvec[2] = exp(x[0]) + x[0] * x[1] + x[0] * x[2] - 1.0;
//	}
//	else if (*iflag == 2) {
//		fjac[0] = 1.0;						fjac[3] = 1.0;		fjac[6] = 1.0;
//		fjac[1] = 2.0 * x[0];					fjac[4] = 2.0 * x[1];	fjac[7] = 2.0 * x[2];
//		fjac[2] = exp(x[0]) + x[1] + x[2];	fjac[5] = x[0];		fjac[8] = x[2];
//	}
//}
//
//void main(void)
//{
//	int n = SOLNUMS;
//	double x[SOLNUMS] = { 0.1, 1.2, 2.5 };	//need to initilize x0
//	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
//	int ldfjac = SOLNUMS;
//	double tol = TOLERANCE;
//	int info;
//	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
//	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;
//
//	hybrj1_(fcn, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
//
//	printf("%lf %lf %lf\n", x[0], x[1], x[2]);
//
//}