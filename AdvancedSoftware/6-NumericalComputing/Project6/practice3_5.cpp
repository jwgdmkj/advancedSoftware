#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_5(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = 10 * x[0] - 2*x[1]*x[1] - 2*x[2] - 5.0;
	fvec[1] = x[1] * x[1] * 8.0 + 4*x[2]*x[2] - 9.0;
	fvec[2] = 8*x[1]*x[2] + 4.0;
	/********************************/
}

void practice3_5(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 1.0, -1.0, 1.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-5.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/
	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("info : %d --> %lf %lf %lf\n", info, x[0], x[1], x[2]);
	if (info == 1) {
		fprintf(fp_w, "info : %d --> %lf %lf %lf\n", info, x[0], x[1], x[2]);
		printf("fvec --> %lf %lf %lf\n", fvec[0], fvec[1], fvec[2]);
		fprintf(fp_w, "fvec --> %lf %lf %lf\n", fvec[0], fvec[1], fvec[2]);
	}
	else if (info == 4) {
		printf("Iteration is not making good progress\n");
		fprintf(fp_w, "Iteration is not making good progress\n");
	}

	x[0] = 1.0; x[1] = 1.0; x[2] = -1.0;
	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("info : %d --> %lf %lf %lf\n", info, x[0], x[1], x[2]);
	if (info == 1) {
		fprintf(fp_w, "info : %d --> %lf %lf %lf\n", info, x[0], x[1], x[2]);
		printf("fvec --> %lf %lf %lf\n", fvec[0], fvec[1], fvec[2]);
		fprintf(fp_w,"fvec --> %lf %lf %lf\n", fvec[0], fvec[1], fvec[2]);
	}
	else if (info == 4) {
		printf("Iteration is not making good progress\n");
		fprintf(fp_w, "Iteration is not making good progress\n");
	}

	printf("\n");
	/********************************/

	fclose(fp_w);
}