#include "my_solver.h"

extern double (*_f)(double);	//사용자 정의 함수
extern double (*_fp)(double);

#define DELTA 0.000001  //|f(xn+1)| < 델타 : 현 xn+1에 대해 함수값이 충분히 작은가
#define Nmax 50
#define EPSILON 0.00001 //|xn+1 - xn| < 엡실론 : 의미있는 진전 안 하는가

/*********************************************
  Newton-Rapson Method
**********************************************/

void program1_1(FILE* fp) {
	int i=0;	//루프 횟수
	double x0, x_next; //초기값 입력 및 해
	int flag = 1;
	if (*_f == _f5)
		flag = 4;

	double epsil[10];	int c = 10;
	double epsil2[10];

	for (int f = 0; f < flag; f++) {
		scanf("%lf", &x0);

			//f1(x) = x2 −4x + 4−lnx = 0
		printf("i	xn1	|f(xn1)|\n");
		printf("%d	%20.18e	%20.18e\n", i, x0, _f(x0));
		fprintf(fp, "%d	%20.18e	%20.18e\n", i, x0, _f(x0));
		epsil[0] = x0;

		while (i < Nmax) {
			x_next = x0 - _f(x0) / _fp(x0);	//다음 식의 해
			printf("%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
			fprintf(fp, "%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
		//	epsil[i+1] = x_next;

			if (fabs(_f(x_next)) < DELTA)
				break;
			//충분히 해가 입실론보다 작을 때
			if (fabs(x0 - x_next) < EPSILON) {
				break;
			}
			i++;
			x0 = x_next;
		}
	}
	/*for (int i = 0; i < 6; i++) {
		epsil2[i] = fabs(epsil[i] - x_next);
		if (i >= 1) {
			printf("%20.18e\n", epsil2[i]/(epsil2[i-1] * epsil2[i-1]));
		}
	}*/
}
