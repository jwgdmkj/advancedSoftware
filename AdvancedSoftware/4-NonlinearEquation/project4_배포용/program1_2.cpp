#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
#define DELTA 0.000001  //|f(xn+1)| < 델타 : 현 xn+1에 대해 함수값이 충분히 작은가
#define Nmax 50
#define EPSILON 0.00001 //|xn+1 - xn| < 엡실론 : 의미있는 진전 안 하는가

void program1_2(FILE* fp) {
	int i=0;	//루프 횟수
	double x0, x1, x_next; //초기값 입력 및 해
	scanf("%lf", &x0); scanf("%lf", &x1);

	//	double y_next = _fp(3);

		//f1(x) = x2 −4x + 4−lnx = 0
	printf("i	xn1	|f(xn1)|\n");
	fprintf(fp, "i	xn1	|f(xn1)|\n");

	while (i < Nmax) {
		
		x_next = x1 - ( _f(x1) * (x1-x0))/(_f(x1)-_f(x0));	//다음 식의 해
		printf("%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
		fprintf(fp,"%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));

		if (fabs(_f(x_next)) < DELTA)
			break;

		//충분히 해가 입실론보다 작을 때
		if (fabs(x1 - x0) < EPSILON) {
			printf("%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
			fprintf(fp, "%d	%20.18e	%20.18e\n", i, x_next, _f(x_next));
			break;
		}
		x0 = x1;
		x1 = x_next;
		i++;
	}
}
