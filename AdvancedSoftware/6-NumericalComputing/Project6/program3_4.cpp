#include "my_solver.h"
#define index_2d(row, col, dim) row*dim+col

extern "C"
{
    int gespp_(int*, float*, int*, int*, float*);
    int solve_(int*, float*, int*, int*, float*, float*);
};


void program3_4(void) {

	FILE* fp_r = fopen("linear_system_3-4", "r");
	if (fp_r == NULL) {
		printf("%s file open error...\n", "linear_system_3-4");
		return;
	}

	/*FILE* fp_r = fopen("Hilbert_32.txt", "r");
	if (fp_r == NULL) {
		printf("%s file open error...\n", "General_4");
		return;
	}*/

	FILE* fp_w = fopen("solution_3-4.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "solution_3-4.txt");
		return;
	}

	int SOLNUMS;
	fscanf(fp_r, "%d", &SOLNUMS);
	fprintf(fp_w, "%d", SOLNUMS);
	int ia, n;
	int* l = new int[SOLNUMS];
	float* a = new float[SOLNUMS * SOLNUMS];
	float* temp = new float[SOLNUMS * SOLNUMS];
	float* b = new float[SOLNUMS];
	float* x = new float[SOLNUMS];
	float* s = new float[SOLNUMS];

	double tmp;
	printf("%d\n", SOLNUMS);
	for (int j = 0; j < SOLNUMS; j++) {
		for (int i = 0; i < SOLNUMS; i++) {
			fscanf(fp_r, "%lf", &tmp);
			a[index_2d(i, j, SOLNUMS)] = tmp;
			temp[index_2d(i, j, SOLNUMS)] = tmp;
		}
	}
	for (int i = 0; i < SOLNUMS; i++) {
		fscanf(fp_r, "%lf", &tmp);
		b[i] = tmp;
	}
	n = ia = SOLNUMS;
	printf("***** Equation *****\n");
//	fprintf(fp_w, "***** Equation *****\n");
	for (int i = 0; i < SOLNUMS; i++) {
		for (int j = 0; j < SOLNUMS; j++) {
			printf("a[%d][%d] = %f, ", i, j, a[index_2d(j, i, SOLNUMS)]);
	//		fprintf(fp_w, "a[%d][%d] = %f, ", i, j, a[index_2d(j, i, SOLNUMS)]);
		}
		printf("\n");
	}
	for (int j = 0; j < SOLNUMS; j++) {
		printf("b[%d] = %f, ", j, b[j]);
	//	fprintf(fp_w, "b[%d] = %f, ", j, b[j]);
	}
	printf("\n");
//	fprintf(fp_w, "\n");

	gespp_(&n, a, &ia, l, s);
	printf("***** After LU-decomposition *****\n");
//	fprintf(fp_w, "***** After LU-decomposition *****\n");
	for (int j = 0; j < SOLNUMS; j++) {
		printf("s[%d] = %f, ", j, s[j]);
	//	fprintf(fp_w, "s[%d] = %f, ", j, s[j]);
	}
	printf("\n");
//	fprintf(fp_w, "\n");

	for (int j = 0; j < SOLNUMS; j++) {
		printf("l[%d] = %f, ", j, l[j]);
	//	fprintf(fp_w, "l[%d] = %f, ", j, l[j]);
	}
	printf("\n");
	fprintf(fp_w, "\n");

	for (int i = 0; i < SOLNUMS; i++) {
		for (int j = 0; j < SOLNUMS; j++) {
			printf("a[%d][%d] = %f, ", i, j, a[index_2d(j, i, SOLNUMS)]);
	//		fprintf(fp_w, "a[%d][%d] = %f, ", i, j, a[index_2d(j, i, SOLNUMS)]);
		}
	//	fprintf(fp_w, "\n");
		printf("\n");
	}

	solve_(&n, a, &ia, l, b, x);
	printf("***** Solution *****\n");
	fprintf(fp_w, "***** Solution *****\n");
	for (int j = 0; j < SOLNUMS; j++) {
		printf("x[%d] = %f, ", j, x[j]);
		fprintf(fp_w, "%f\n", x[j]);
	}
	double sumb=0;
	double suma=0;

	for (int j = 0; j < SOLNUMS; j++) {
		for (int i = 0; i < SOLNUMS; i++) {
			suma = a[index_2d(j, i, SOLNUMS)] * x[j] - b[i];
			suma = pow(suma, 2);
		}
	}
	suma = sqrt(suma);

	for (int i = 0; i < SOLNUMS; i++) {
		sumb += b[i] * b[i];
	}
	sumb = sqrt(sumb);

	printf("\n");
	fprintf(fp_w, "\n");
	printf("sol %lf\n", suma / sumb);
	fprintf(fp_w, "%lf\n", suma / sumb);
	/********************************/
}
