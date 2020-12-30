#define _USE_MATH_DEFINES
#include <math.h>
#define PH 3.1415926535

//실습 1에서 쓸 것들
double _f1(double x) {
	//x2 −4x + 4−lnx 
	return pow(x, 2) - 4*x + 4 - log(x);
}

double _fp1(double x) {
	return 2*x - 4 - (1/x);
}

//실습1 - 파이
double _f2(double x) {
	//f2(x) = x+1−2sinπx = 0
	return x + 1 - 2 * sin(PH * x);
}

double _fp2(double x) {
	return 1 - 2 * PH * cos(PH*x);
}


//실습 2에서 쓸 것들
double _f5(double x) {
	//x4 −11.0x3 + 42.35x2 −66.55x + 35.1384 = 0
	return pow(x, 4) - 11.0 * pow(x, 3) + 42.35 * pow(x, 2) - 66.55 * x +
		35.1384;
}

double _fp5(double x) {
	return 4 * pow(x, 3) - 33.0 * pow(x, 2) + 2 *42.35*x - 66.55;
}


//실습 1-4의 log
double _f3(double x) {
	return log(x) - 1;
}
double _fp3(double x) {
	return 1 / x;
}

//숙제 2
double hw2(double x) {
	return 89 * sin(11.5) * sin(x) * cos(x) + 89 * cos(11.5) * sin(x) * sin(x)
		- ((49 + 0.5 * 55) * sin(11.5) - 0.5 * 55 * tan(11.5)) * cos(11.5)
		- ((49 + 0.5 * 55) * cos(11.5) - 0.5 * 55)* sin(11.5);
}

double hw2_1(double x) {
	return 89 * sin(11.5) * (cos(x * x) - sin(x * x))
		+ 178 * cos(11.5) * sin(x) * cos(x)
		+ sin(x)*((49+0.5*55)*sin(11.5)-0.5*55*tan(11.5))
		- cos(x)*((49 + 0.5 * 55) * cos(11.5) - 0.5*55);
}