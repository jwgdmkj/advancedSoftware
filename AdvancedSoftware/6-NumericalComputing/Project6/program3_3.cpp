#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001
#define PI 3.141592

void fcn4_4(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = (sin(x[0] + x[1] + PI / 6) + sqrt(x[0] * x[0] * x[1] * x[1] + 1)) / cos(x[0] - x[1]) + 2.8;
	fvec[1] = (x[0] * exp(x[0] * x[1] + PI / 6) - sin(x[0] - x[1])) / sqrt(x[0] * x[0] * x[1] * x[1] + 1) - 1.66;
	/********************************/
}

void program3_3(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 20.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_found_3-3.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_found_3-3.txt");
		return;
	}

	/********************************/
	hybrd1_(fcn4_4, &n, x, fvec, &tol, &info, wa, &lwa);
	printf("info : %d --> %lf %lf\n", info, x[0], x[1]);
	if (info == 1) {
		fprintf(fp_w, "info : %d --> %lf %lf\n", info, x[0], x[1]);
		printf("fvec --> %lf %lf\n", fvec[0], fvec[1]);
		fprintf(fp_w, "fvec --> %lf %lf\n", fvec[0], fvec[1]);
	}
	else if (info == 4) {
		printf("Iteration is not making good progress\n");
		fprintf(fp_w, "Iteration is not making good progress\n");
	}

	printf("\n");
	/********************************/

	fclose(fp_w);
}