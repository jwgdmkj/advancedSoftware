#ifndef __MY_SOLVER_H__
#define __MY_SOLVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define DELTA 0.000001
#define Nmax 50
#define EPSILON 0.00001

double _f1(double x);
double _fp1(double x); 
double _f2(double x);
double _fp2(double x);

double _f5(double x);
double _fp5(double x);

double _f3(double x);
double _fp3(double x);

float _sp_f1(float x);
float _sp_fp1(float x);
float _sp_f2(float x);
float _sp_fp2(float x);
float _sp_f3(float x);
float _sp_fp3(float x);

double hw2(double x);
double hw2_1(double x);
#endif  // __MY_SOLVER_H__