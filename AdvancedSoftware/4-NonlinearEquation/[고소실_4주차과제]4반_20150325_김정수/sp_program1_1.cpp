#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/
void sp_program1_1(FILE* fp) {
	int i=0;	//루프 횟수
	float x0, x_next; //초기값 입력 및 해
	scanf("%f", &x0);

	//	double y_next = _sp_fp(3);

		//f1(x) = x2 −4x + 4−lnx = 0
	printf("i	xn1	|f(xn1)|\n");
	printf("%d	%20.18e	%20.18e\n", i, x0, _sp_f(x0));
	fprintf(fp, "%d	%20.18e	%20.18e\n", i, x0, _sp_f(x0));
	while (i < Nmax) {

		x_next = x0 - _sp_f(x0) / _sp_fp(x0);	//다음 식의 해
		printf("%d	%f	%f\n", i, x_next, _sp_f(x_next));
		fprintf(fp, "%d	%20.18e	%20.18e\n", i, x_next, _sp_f(x_next));

		//충분히 해가 입실론보다 작을 때
		if (fabs(x0 - x_next) < EPSILON) {
			break;
		}
		if (fabs(_sp_f(x_next)) < DELTA)
			break;
		i++;
		x0 = x_next;
	}
}