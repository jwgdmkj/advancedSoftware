#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn4_3(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = x[1] + 10*x[2] - 9.0;
	fvec[1] = sqrt(5) * (x[3]-x[1]) - 2*sqrt(5);
	fvec[2] = pow(x[2] - 2*x[3], 2) -9;
	fvec[3] = sqrt(10) * pow(x[1] - x[0], 2) - 2 * sqrt(10);
	/********************************/
}

void program3_2(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.9, -0.9, 1.25, -1.25 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_found_3-2.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/
	hybrd1_(fcn4_3, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("info : %d --> %lf %lf %lf %lf\n", info, x[0], x[1], x[2], x[3]);
	if (info == 1) {
		fprintf(fp_w, "info : %d --> %lf %lf %lf %lf\n", info, x[0], x[1], x[2], x[3]);
		printf("fvec --> %lf %lf %lf %lf\n", fvec[0], fvec[1], fvec[2], fvec[3]);
		fprintf(fp_w, "fvec --> %lf %lf %lf %lf\n", fvec[0], fvec[1], fvec[2], fvec[3]);
	}
	else if (info == 4) {
		printf("Iteration is not making good progress\n");
		fprintf(fp_w, "Iteration is not making good progress\n");
	}

	printf("\n");
	/********************************/

	fclose(fp_w);
}