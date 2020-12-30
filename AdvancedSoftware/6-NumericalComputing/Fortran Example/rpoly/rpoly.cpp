//#include <stdio.h>
//#include <math.h>
//#define DEGREE 4
//#define NCOEF 5
//extern "C"
//{
//	int rpoly_(double*, int*, double*, double*, long int*);
//}
//void main(void) {
//	double poly[NCOEF] = { 1.0, -11.0, 42.35, -66.55, 35.1384 };
//	int degree = DEGREE;
//	double zeror[DEGREE], zeroi[DEGREE];
//	long int fail;
//	int i;
//	rpoly_(poly, &degree, zeror, zeroi, &fail);
//	if (fail) {
//		printf("wrong\n");
//		return;
//	}
//	for (i = 0; i < degree; i++)
//		printf("%10f ", zeror[i]);
//	printf("\n");
//	for (i = 0; i < degree; i++)
//		printf("%10f ", zeroi[i]);
//	printf("\n");
//}