#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

extern "C"
{
	int hybrj1_(void fcn4_1(int*, double*, double*, double*, int*, int*),
		int*, double*, double*, double*, int*, double*, int*, double*, int*);
}


double parr[20];
double cc;
double bb;

void fcn4_2(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = pow(x[0] - parr[0], 2) + pow(x[1] - parr[1], 2) + pow(x[2] - parr[2], 2)
		- pow(cc * (parr[4] + x[3] - parr[3]), 2);
	fvec[1] = pow(x[0] - parr[5], 2) + pow(x[1] - parr[6], 2) + pow(x[2] - parr[7], 2)
		- pow(cc * (parr[9] + x[3] - parr[8]), 2);
	fvec[2] = pow(x[0] - parr[10], 2) + pow(x[1] - parr[11], 2) + pow(x[2] - parr[12], 2)
		- pow(cc * (parr[14] + x[3] - parr[13]), 2);
	fvec[3] = pow(x[0] - parr[15], 2) + pow(x[1] - parr[16], 2) + pow(x[2] - parr[17], 2)
		- pow(cc * (parr[19] + x[3] - parr[18]), 2);
	/********************************/
}

void fcn4_1(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = pow(x[0] - parr[0], 2) + pow(x[1] - parr[1], 2) + pow(x[2] - parr[2], 2)
			- pow(cc*(parr[4]+x[3]-parr[3]),2);
		fvec[1] = pow(x[0] - parr[5], 2) + pow(x[1] - parr[6], 2) + pow(x[2] - parr[7], 2)
			- pow(cc * (parr[9] + x[3] - parr[8]), 2);
		fvec[2] = pow(x[0] - parr[10], 2) + pow(x[1] - parr[11], 2) + pow(x[2] - parr[12], 2)
			- pow(cc * (parr[14] + x[3] - parr[13]), 2);
		fvec[3] = pow(x[0] - parr[15], 2) + pow(x[1] - parr[16], 2) + pow(x[2] - parr[17], 2)
			- pow(cc * (parr[19] + x[3] - parr[18]), 2);
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 2 * x[0] - 2 * parr[0];     fjac[4] = 2 * x[1] - 2 * parr[1];  fjac[8] = 2 * x[2] - 2 * parr[2];
		fjac[12] = cc * cc * (2*x[3] - 2*parr[3] + 2*parr[4]);

		fjac[1] = 2 * x[0] - 2 * parr[5];     fjac[5]= 2 * x[1] - 2 * parr[6];  fjac[9] = 2 * x[2] - 2 * parr[7];
		fjac[13] = cc * cc * (2 * x[3] - 2 * parr[8] + 2 * parr[9]);

		fjac[2] = 2 * x[0] - 2 * parr[10];    fjac[6] = 2 * x[1] - 2 * parr[11]; fjac[10] = 2 * x[2] - 2 * parr[12];
		fjac[14] = cc * cc * (2 * x[3] - 2 * parr[13] + 2 * parr[14]);

		fjac[3] = 2 * x[0] - 2 * parr[15];    fjac[7] = 2 * x[1] - 2 * parr[16]; fjac[11] = 2 * x[2] - 2 * parr[17];
		fjac[15] = cc * cc * (2 * x[3] - 2 * parr[18] + 2 * parr[19]);
		/********************************/
	}
}

void program3_1(void) {
	char readfile[256];
	char writefile[256];
	char writefile2[255];

	for (int t = 0; t <= 2; t++) {
		sprintf(readfile, "GPS_signal_%d.txt", t);
		sprintf(writefile, "GPS_position_3-1_%d.txt", t);
		sprintf(writefile2, "GPS_position_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		FILE* fp_w2 = fopen(writefile2, "w");
		if (fp_w2 == NULL) {
			printf("%s file open error...\n", writefile2);
			return;
		}

		int n = SOLNUMS;
		double x[SOLNUMS];
		double y[SOLNUMS];
		double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
		int ldfjac = SOLNUMS;
		double tol = TOLERANCE;
		int info;
		double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
		double wa2[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
		int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;
		int lwa2 = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

		double arr[20];
		double inputnum;
		double C;
		double d;

		fscanf(fp_r, "%lf", &C);
		fscanf(fp_r, "%lf", &d);
		for (int i = 0; i < 20; i++) {
			fscanf(fp_r, "%lf", &inputnum);
			arr[i] = inputnum;
			parr[i] = arr[i];
		}

		cc = C;
		bb = d;
		///********************************/

		////�ʱⰪ
		for (int i = 0; i < 3; i++) {
			scanf("%lf", &inputnum);
			x[i] = inputnum;
			y[i] = inputnum;
		}
		y[3] = bb;
		x[3] = bb;

		printf("hybrj: ");
		hybrj1_(fcn4_1, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

		if (info == 0) {
			printf("%lf  %lf  %lf  %lf\n", x[0], x[1], x[2], x[3]);
			fprintf(fp_w, "info : %d --> %lf %lf %lf %lf\n", info, x[0], x[1], x[2], x[3]);
			printf("fvec --> %lf %lf %lf %lf\n", fvec[0], fvec[1], fvec[2], fvec[3]);
			fprintf(fp_w, "fvec --> %lf %lf %lf %lf\n", fvec[0], fvec[1], fvec[2], fvec[3]);
		}
		else if (info == 1) {
			printf("Algorithm estimates that the relative error between x and the solution is at most tol\n");
			fprintf(fp_w, "Algorithm estimates that the relative error between x and the solution is at most tol\n");
		}

		if (info == 4) {
			printf("Iteration is not making good progress\n");
			fprintf(fp_w, "Iteration is not making good progress\n");
		}

		/********************************/
		hybrd1_(fcn4_2, &n, y, fvec, &tol, &info, wa2, &lwa2);
		printf("info : %d --> %lf %lf %lf %lf\n", info, y[0], y[1], y[2], y[3]);
		if (info == 1) {
			fprintf(fp_w, " --> %lf %lf %lf %lf\n", y[0], y[1], y[2], y[3]);
			printf("fvec --> %lf %lf %lf %lf\n", fvec[0], fvec[1], fvec[2], fvec[3]);
			fprintf(fp_w, "fvec --> %lf %lf %lf %lf\n", fvec[0], fvec[1], fvec[2], fvec[3]);
		}
		else if (info == 4) {
			printf("Iteration is not making good progress\n");
			fprintf(fp_w, "Iteration is not making good progress\n");
		}
		printf("\n");
	}
	/********************************/
}
