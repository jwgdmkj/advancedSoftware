#include<stdio.h>
#include<math.h>
#include<cuda.h>
#include <time.h>
#include <assert.h>
#include <Windows.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#define CUDA_CALL(x) { const cudaError_t a = (x); if(a != cudaSuccess) { printf("\nCuda Error: %s (err_num=%d) at line:%d\n", cudaGetErrorString(a), a, __LINE__); cudaDeviceReset(); assert(0);}}
typedef float TIMER_T;

#define USE_CPU_TIMER 1
#define USE_GPU_TIMER 1

#if USE_CPU_TIMER == 1
__int64 start, freq, end;
#define CHECK_TIME_START { QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start); }
#define CHECK_TIME_END(a) { QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f)); }
#else
#define CHECK_TIME_START
#define CHECK_TIME_END(a)
#endif

#define N 20
#define BLOCK_SIZE 4

float* A, * B, * C;
float * X0, *X1, *FX0, *FX1;

__global__ void roots_kernel(float *a, float* b, float* c,
	float* phi1, float* phi2, float *xx, float * xx2)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;

	float a2, b2, c2, d2, x02, x12, tmp2;

	a2 = a[i]; b2 = b[i]; c2 = c[i];
	d2 = sqrtf(b2 * b2 - 4.0f * a2 * c2);
	tmp2 = 1.0f / (2.0f * a2);
	phi1[i] = x02 = (-b2 - d2) * tmp2;
	phi2[i] = x12 = (-b2 + d2) * tmp2;
	xx[i] = (a2 * x02 + b2) * x02 + c2;
	xx2[i] = (a2 * x12 + b2) * x12 + c2;
}

void find_roots_CPU(float* A, float* B, float* C,
	float* X0, float* X1, float* FX0, float* FX1, int n) {
	int i;
	float a, b, c, d, x0, x1, tmp;
	for (i = 0; i < n; i++) {
		a = A[i]; b = B[i]; c = C[i];
		d = sqrtf(b * b - 4.0f * a * c);
		tmp = 1.0f / (2.0f * a);
		X0[i] = x0 = (-b - d) * tmp;
		X1[i] = x1 = (-b + d) * tmp;
		FX0[i] = (a * x0 + b) * x0 + c;
		FX1[i] = (a * x1 + b) * x1 + c;
	}
}


void find_roots_GPU(float* A, float* B, float* C,
	float* X0, float* X1, float* FX0, float* FX1, int n)
{
	//아래 함수들을 사용하여 어떻게 하면 가급적 정확한 시간을 측정할 수 있을지 생각해볼 것.
	//CHECK_TIME_INIT_GPU()
	//	CHECK_TIME_START_GPU()
	//	CHECK_TIME_END_GPU(device_time)
	//	CHECK_TIME_DEST_GPU()

		cudaError_t cudaStatus;
	// Choose which GPU to run on, change this on a multi-GPU system.
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		goto Error;
	}/////////////  if(cu.....  ==CUDA_CALL

	size_t size;
	float* a2, * b2, * c2, *x0, *x1, *fx0, *fx1;

	size = n* sizeof(float);
	CUDA_CALL(cudaMalloc(&a2, size))
		CUDA_CALL(cudaMemcpy(a2, A, size, cudaMemcpyHostToDevice))
		CUDA_CALL(cudaMalloc(&b2, size))
		CUDA_CALL(cudaMemcpy(b2, B, size, cudaMemcpyHostToDevice))
		CUDA_CALL(cudaMalloc(&c2, size))
		CUDA_CALL(cudaMemcpy(c2, C, size, cudaMemcpyHostToDevice))

	CUDA_CALL(cudaMalloc(&x0, size))
		CUDA_CALL(cudaMalloc(&x1, size))
		CUDA_CALL(cudaMalloc(&fx0, size))
		CUDA_CALL(cudaMalloc(&fx1, size))

		//    // Assume that width and height are multiples of BLOCK SIZE.
			//쓰레드 결정 하는 데
			//블럭 안에 쓰레드가 블럭사이즈(=32)만큼 존재 (쓰레드가 블럭수만큼 생성됨)
		dim3 dimBlock(BLOCK_SIZE); // dimblock(block_size, 1, 1) 블록 안에 32개의 쓰레드가 존재
	//블럭의 총 갯수. 블록 하나당 쓰레드가 blocksize만큼 존재.
	//엘리먼트 사이즈가 총 쓰레드 개수, 딤블록.x == 블록의 개수
	dim3 dimGrid(N / dimBlock.x); //즉, 블록의 총갯수는 엘리먼트사이즈/딤블록(=32)
	roots_kernel << < dimGrid, dimBlock >> > (a2, b2, c2, x0, x1, fx0, fx1);

	CUDA_CALL(cudaGetLastError())

		//    // cudaDeviceSynchronize waits for the kernel to finish, and returns
		//    // any errors encountered during the launch.
		CUDA_CALL(cudaDeviceSynchronize())
		///*CUDA_CALL(cudaMemcpy(p_VecY_G, p_VecY_G2, size, cudaMemcpyDeviceToHost))
		//CUDA_CALL(cudaMemcpy(p_VecY_G, p_VecY_G2, size, cudaMemcpyDeviceToHost))*/

		Error:
	//cudaFree(p_VecY_G2);
	//cudaFree(p_VecX2);
	//cudaFree(p_MatA2);

}

int main()
{

	A = new float[20]; B = new float[20]; C = new float[20];
	X0 = new float[20]; X1 = new float[20]; FX0 = new float[20]; FX1 = new float[20];
	float a, b, c;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20; i++) {
		a =  ((float)rand() / RAND_MAX) * 10.0f;
		b =  ((float)rand() / RAND_MAX) * 10.0f;
		c =  ((float)rand() / RAND_MAX) * 10.0f;

		if (b * b - 4 * a * c >= 0) {
			A[i] = a; B[i] = b; C[i] = c;
		}
		else
			i--;
	}
	find_roots_CPU(A, B, C, X0, X1, FX0, FX1, N);

	for(int i=0; i<20; i++)
		printf("%f %f %f %f %f %f %f\n", A[i], B[i], C[i], X0[i], X1[i], FX0[i], FX1[i]);

	find_roots_GPU(A, B, C, X0, X1, FX0, FX1, N);

	printf("\n");
	for (int i = 0; i < 20; i++)
		printf("%f %f %f %f %f %f %f\n", A[i], B[i], C[i], X0[i], X1[i], FX0[i], FX1[i]);

	return 0;
}