#include "my_solver.h"
#include "math.h"

extern "C"
{
	int rpoly_(double*, int*, double*, double*, long int*);
}

struct complex
{
	double real;
	double imagin;
};

void add(struct complex x, struct complex* partial)
{
	partial->real += x.real;
	partial->imagin += x.imagin;

}

void mult(struct complex x, struct complex y, struct complex* partial)
{
	partial->real = x.real * y.real - x.imagin * y.imagin;
	(*partial).imagin = x.real * y.imagin + x.imagin * y.real;
}

void sub(struct complex x, struct complex* partial)
{
	partial->real -= x.real;
	partial->imagin -= x.imagin;
}

void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;

	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

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

		fscanf(fp_r, "%d", &DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);


		/********************************/

		double inputnum;
		for (int i = 0; i < NCOEF; i++) {
			fscanf(fp_r, "%lf", &inputnum);
			poly[i] = inputnum;
		}

		long int fail;
		int i;
		rpoly_(poly, &DEGREE, zeror, zeroi, &fail);

		if (fail) {
			printf("wrong\n");
			continue;
		}

		for (i = 0; i < DEGREE; i++) {
			printf("%10f + %10f\n", zeror[i], zeroi[i]);
			fprintf(fp_w, "%10f + %10f", zeror[i], zeroi[i]);
		}


		for (i = 0; i < DEGREE; i++) {
			double sum = 0;
			for (int j = 0; j < DEGREE; j++) {
				sum += poly[j];
				sum *= zeror[i];
			}
			sum += poly[DEGREE];
			printf("%lf\n", sum);
		}
		

		printf("\n");
		//	for (i = 0; i < DEGREE; i++) {
		//		printf("%10f ", zeroi[i]);
		//		fprintf(fp_w, "%10f ", zeroi[i]);
		//	}
		//	printf("\n");
			/*ax^3 + bx^2 + cx + d = 0 은
	d + x (c + x ( b + ax)) = 0 으로 표현
	i*/
		switch (t) {
		case 1:
			for (int i = 0; i < DEGREE; i++) {
				complex c; complex partial, partial2, partial3, partial4, partial5;
				c.real = zeror[i]; c.imagin = zeroi[i];

				mult(c, c, &partial2);
				mult(partial2, c, &partial3);
				mult(partial3, c, &partial4);
				mult(partial4, c, &partial5);

			}
			break;
		case 2:
			for (int i = 0; i < DEGREE; i++) {
				printf("t - answoer %lf\n", 
					poly[0] + (zeror[i]) *
					(poly[1] + (zeror[i]) * (poly[2] + (zeror[i]) * (poly[3]* (zeror[i])))));
			}
			break;
		case 3:
			for (int i = 0; i < DEGREE; i++) {
				printf("t - answoer %lf\n", 
					poly[0] + (zeror[i]) *
					(poly[1] + (zeror[i]) * (poly[2] + (zeror[i]) * (poly[3]
						+ poly[4] * (zeror[i] )))));
			}
			break;
		case 4:
			for (int i = 0; i < DEGREE; i++) {
				printf("t - answoer %lf\n", 
					poly[0] + (zeror[i]) *
					(poly[1] + (zeror[i] ) * (poly[2] + (zeror[i]) 
						* (poly[3] + (zeror[i]) *
						(poly[4] + poly[5]*(zeror[i]))))));
			}
			break;
		case 5:
			for (int i = 0; i < DEGREE; i++) {
				printf("t - answoer %lf\n", 
					-240 + (zeror[i] + zeroi[i]) *
					(76 + (zeror[i] + zeroi[i]) * (159 + (zeror[i] + zeroi[i]) * (88 + 16*(zeror[i] + zeroi[i])))));
			}
			break;
		case 6:
			for (int i = 0; i < DEGREE; i++) {
				printf("t - answoer %lf\n", 
					poly[0] + (zeror[i]) *
					(poly[1] + (zeror[i]) * (poly[2] + (zeror[i] ) 
						* (poly[3] + (zeror[i]) *
						(poly[4] + (zeror[i]) * (poly[5] + 
							poly[6]*(zeror[i] )))))));
			}
			break;
		}
		/********************************/


		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}