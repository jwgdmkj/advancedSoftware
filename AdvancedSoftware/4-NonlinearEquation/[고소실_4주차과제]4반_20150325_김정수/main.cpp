#include "my_solver.h"

extern void program1_1(FILE* fp); // Newton-Raphson Method
extern void program1_2(FILE* fp); // Secant Method
extern void program1_3(FILE* fp); // homework 1

extern void sp_program1_1(FILE* fp); // Newton-Raphson Method
extern void sp_program1_2(FILE* fp); // Secant Method

double (*_f)(double);
double (*_fp)(double);

float (*_sp_f)(float);
float (*_sp_fp)(float);

int main() {
	FILE* fp;
	fp = fopen("result.txt", "w");
	
	//3 / 2, 4 / 0.75 / 0.5, 1 / 3
	_f = _f1;
	_fp = _fp1;

	program1_1(fp);
	program1_2(fp);	//여기까지 x2 -...lnx=0을 뉴튼랩슨 세컨트로 풀기 
//	program1_3(fp);

	_f = _f2;
	_fp = _fp2;

	program1_1(fp);
	program1_2(fp);		//여기까지 사인함수 등을 뉴튼랩스 세컨트로 풀기
//	program1_3(fp);

	////실습 1-2: 4차방정식
	_f = _f5;
	_fp = _fp5;
	program1_1(fp);

	//실습 1-4
	_sp_f = _sp_f1;
	_sp_fp = _sp_fp1;
	sp_program1_1(fp);

	_sp_f = _sp_f2;
	_sp_fp = _sp_fp2;
	sp_program1_2(fp);	//1-1짜리를 sp로 돌리기
	
	//실습 1-4 ln
	_f = _f3;
	_fp = _fp3;
	program1_1(fp);
	_sp_f = _sp_f3;
	_sp_fp = _sp_fp3;
	sp_program1_1(fp);

	//숙제 1 : 1 2 4 쓰기
	_f = _f1;
	_fp = _fp1;
	program1_3(fp);

	_f = _f2;
	_fp = _fp2;
	program1_3(fp);

	_f = _f3;
	_fp = _fp3;
	program1_3(fp);

	////숙제 2
	_f = hw2;
	_fp = hw2_1;
	program1_1(fp);

	fclose(fp);
}
