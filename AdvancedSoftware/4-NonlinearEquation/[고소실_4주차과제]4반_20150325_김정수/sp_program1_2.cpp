#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Secant Method
**********************************************/
void sp_program1_2(FILE* fp) {
	int i=0;	//루프 횟수
	float x0, x1, x_next; //초기값 입력 및 해
	scanf("%f", &x0); scanf("%f", &x1);

	//	float y_next = _fp(3);

		//f1(x) = x2 −4x + 4−lnx = 0
	printf("i	xn1	|f(xn1)|\n");
	printf("0	%20.18e	%20.18e\n", i, x0, _sp_f(x0));
	fprintf(fp, "0	%20.18e	%20.18e\n", i, x0, _sp_f(x0)); 
	while (i < Nmax) {
		
		x_next = x1 - (_sp_f(x1) * (x1 - x0)) / (_sp_f(x1) - _sp_f(x0));	
		//다음 식의 해
		printf("%d	%20.18e	%20.18e\n", i, x_next, _sp_f(x_next));
		fprintf(fp,"%d	%20.18e	%20.18e\n", i, x_next, _sp_f(x_next));
		if (fabs(_sp_f(x_next)) < DELTA)
			break;
		//충분히 해가 입실론보다 작을 때
		if (fabs(x1 - x0) < EPSILON) {
			printf("%d	%20.18e	%20.18e\n", i, x_next, _sp_f(x_next));
			fprintf(fp, "%d	%20.18e	%20.18e\n", i, x_next, _sp_f(x_next));
			break;
		}
		x0 = x1;
		x1 = x_next;
		i++;
	}
}
