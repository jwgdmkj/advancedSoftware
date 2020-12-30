#include "my_solver.h"

extern double (*_f)(double);	//����� ���� �Լ�
extern double (*_fp)(double);

//void bisection(double* x, float a, float b, int* i) {
//	*x = (a + b) / 2;
//	++(*i);
//}

void program1_3(FILE* fp) {
	int i = 0;	//���� Ƚ��
	double x0, x1, x_next; //�ʱⰪ �Է� �� ��
	double x_next2;
	scanf("%lf", &x0); scanf("%lf", &x1);

	printf("i	xn1	|f(xn1)|\n");
	fprintf(fp, "i	xn1	|f(xn1)|\n");
	double epsil[20];	int c = 10;
	double epsil2[20];

	epsil[0] = x0;
	epsil[1] = x1;
	while (i < Nmax) {
		x_next = (x0 + x1) / 2;		//xnext �߰���

		printf("%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
		fprintf(fp, "%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
	//	epsil[i + 2] = x_next;

		if (fabs(_f(x_next)) < DELTA)
			break;

		//����� �ذ� �ԽǷк��� ���� ��
		if (fabs(x1 - x_next) < EPSILON) {
			printf("%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
			fprintf(fp, "%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
			break;
		}

		if (_f(x1) * _f(x_next) < 0) {
			x0 = x_next;
		}
		else {
			x1 = x_next;
		}
		i++;
	}

	//for (int i = 0; i < 20; i++) {
	//	epsil2[i] = fabs(epsil[i] - x_next);
	////	printf("%20.18e | ", epsil2[i]);
	//	if (i >= 1) {
	//		printf("%20.18e\n", epsil2[i] / epsil2[i - 1]);
	//	}
	//}
}
