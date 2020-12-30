#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_7(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = 2 * pow(x[0],3) - 12 * x[0] - x[1] - 1.0;
	fvec[1] = 3 * x[1] * x[1]- 6 * x[1] - x[0] - 3.0;
	/********************************/
}

void practice3_7(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-7.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-7.txt");
		return;
	}

	/********************************/
	for (double i = 0; i < 8; i++) {
		for (double j = 10; j > 0; j--) {
			//	printf("now %lf %lf\n", x[0], x[1]);
			hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);

			if (info != 1) {
				printf("cot\n");
				continue;
			}

			printf("%lf  %lf\n", x[0], x[1]);
			fprintf(fp_w, "%lf %lf \n", x[0], x[1]);
			printf(" fvec --> %lf %lf\n", fvec[0], fvec[1]);
			fprintf(fp_w," fvec --> %lf %lf\n", fvec[0], fvec[1]);

			x[0] = -4.0 + i;
			x[1] = 5.0 - j;
		}
	}
	printf("\n");
	/********************************/

	fclose(fp_w);
}