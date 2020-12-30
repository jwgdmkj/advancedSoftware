#define _USE_MATH_DEFINES
#include <math.h>
#define PH 3.141592

//실습 4에서 쓸 것들
float _sp_f1(float x) {
	//x2 −4x + 4−lnx 
	return pow(x, 2) - 4 * x + 4 - log(x);
}

float _sp_fp1(float x) {
	return 2 * x - 4 - (1 / x);
}

//실습1 - 파이
float _sp_f2(float x) {
	//f2(x) = x+1−2sinπx = 0
	return x + 1 - 2 * sin(PH * x);
}

float _sp_fp2(float x) {
	return 1 - 2 * PH * cos(PH * x);
}

//실습 1-4-sp: float형으로
float _sp_f3(float x) {
	return log(x) - 1;
}
float _sp_fp3(float x) {
	return 1 / x;
}
//f1(x) = lnx − 1 = 0