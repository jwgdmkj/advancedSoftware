#ifndef MLP_H
#define MLP_H
#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<math.h>
//#include<openblas/cblas.h>		//openblas�� �����Դϴ�. cblas_sgemm�� ����Ҽ� ���ٸ� �Ʒ��� my_sgemm�� ����� �� �ִ�.
#ifndef CBLAS_H
#define CblasRowMajor 0
#define CblasNoTrans 111
#define CblasTrans 112	//112�� openblas�� CblasTrans�� ���
#endif
#ifndef MAX
#  define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif
#ifndef MIN
#  define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif
#ifndef __cplusplus
typedef struct FCLayer FCLayer;
typedef struct Network Network;
#endif

//���� ����ü���� ���(Ȥ�� ����)
struct FCLayer {		// Fully connected layer
	int n;				// ������ ����
	float* w;			// ����ġ , [�������̾��� ũ��] x [���緹�̾��� ũ��] �� 2���� ���                         (�����δ� 1����)
	float* neuron;	    // ����
	float* error;		// ����
};
struct Network {
	FCLayer* layers;	//���̾���� �迭
	int depth;			//���̾��� ����
};
inline Network CreateNetwork(int* size_of_layers, int num_of_layers) {
	/*
	*	@TODO
	*	1. num_of_layers ��ŭ ���̾ ����
	*	2. Network::depth�� num_of_layers�� ����
	*	3. �� Layer���� ������ ������ size_of_layers �迭�� �̿��� ����
	*	4. �� Layer�� error�� neuron�� �Ҵ�
	*	5. Layer�� w�� �������̾���ũ��x���緹�̾���ũ�� �� 2���� �迭�� �Ҵ�
	*	6. �Ҵ��� w�� [-1,1]�� �Ǽ� ���� ������ �ʱ�ȭ
	*/
	Network network;
	network.layers = (FCLayer*)calloc(num_of_layers, sizeof(FCLayer));
	network.depth = num_of_layers; //2

	for (int i = 0; i < num_of_layers; i++) {
		network.layers[i].n = size_of_layers[i];
		network.layers[i].error = (float*)calloc(size_of_layers[i], sizeof(float));
		if (i != 0) {	//ù��° ���̾�� ����ġ�� �������� ����.
			network.layers[i].w = (float*)calloc(size_of_layers[i - 1] * size_of_layers[i], sizeof(float));
			network.layers[i].neuron = (float*)calloc(size_of_layers[i], sizeof(float));
			for (int j = 0; j < size_of_layers[i - 1] * size_of_layers[i]; j++) {
				network.layers[i].w[j] = (float)rand() / RAND_MAX * 2 - 1.0F;	//[-1,1] �� �ʱ�ȭ
			}
		}
	}
	return network;
}
/*
M*K��� A�� K*N��� B�� ���ؼ� AB (M*N)�� ����� ����, ���������� C���ٰ� alpha*AB + beta*C���� ���� ����� ����Դϴ�.
������ �����鿡 ���ؼ� �Ʒ��� �ڼ��� ������ �Ǿ� �ֽ��ϴ�.
*/
inline void my_sgemm(int major, int transA, int transB, int M, int N, int K, float alpha, float* A, int lda, float* B, int ldb, float beta, float* C, int ldc) {
	//aAB+bC=C
	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {
			float c = C[m*ldc + n];
			C[m*ldc + n] = 0.0F;
			for (int k = 0; k < K; k++) {
				float a, b;
				a = transA == CblasTrans ? A[k*lda + m] : A[m*lda + k];
				b = transB == CblasTrans ? B[n*ldb + k] : B[k*ldb + n];
				C[m*ldc + n] += a*b;
			}
			C[m*ldc + n] = alpha*C[m*ldc + n] + beta*c;
		}
	}
}
 
//�����׿����� ReLU�� ���� ����ϳ�, 
//������ �ǽ��̴� Sigmoid�� ���
inline float Sigmoid(float x) {
	return 1.0F / (1.0F + expf(-x));
}
inline float Sigmoid_Derivative(float x) {
	return x*(1.0F - x);
}
inline int Forward(Network* network, float* input) {
	/*
	*	@TODO
	*	1. ù��° ���̾��� neuron ���� input 
	*	2. ���������� ���̾ ��ȸ�ϸ鼭 Neuron�� ������ ���
	*	3. ���� ���̾��� ������ ���� ���� ���̾��� ������ ����ġ�� ��İ����� ǥ���� �� �ִ�
	*	@example
	*	[100][784] ����� W�� [784][1] ����� ���� �������� ��İ��Ͽ� [100][1]�� ���� ������ ���� ����� �� �ִ�.
	*	@gemm references
	*		gemm�� A,B,C�� ��� a,b�� ��Į�� ���϶� aAB+bC�� ����մϴ�. �� A,B,C�� ��� �Է� ��� �̰� C�� ��� ���
	*		major : ����� RowMajor���� ColMajor ���� �����մϴ�. C���� RowMajor �̹Ƿ� CblasRowMajor�� �Է��Ѵ�.
	*		transA : A����� ��ġ��ķ� ����� ������, ��ġ����̸� CblasTrans, �״�� ����� ���̸� CblasNoTrans�� �Է� �Ѵ�
	*		transB : B����� ��ġ��ķ� ����� ������
	*		M,N,K : [M][K] ũ���� ��İ� [K][N]�� ��� �� ���� [M][N]�� C����� ����
	*		alpha : aAB+bC �� ����Ҷ� �������� a(��Į��) ���Դϴ�. �ܼ��� AB �� ����ϰ� ������ alpha=1.0, beta�� 0.0 ���� �Է�
	*		A : �Է���� A
	*		lda : A����� 2��° ������ ��. 5x4�� 1�������� ǥ���� ����� i,j ������ A[i*4+j] �� ǥ���Ѵ�. �̶� 4�� lda 
	*		B : �Է���� B
	*		ldb : B����� 2��° ������ ��
	*		beta : b�� ��
	*		C : ����� ��� C
	*		ldc : C����� 2��° ������ ��
	*/

	network->layers[0].neuron = input;					
	for (int i = 1; i < network->depth; i++) {
		//���� ���̾��� ������ ���� ���� ���̾��� ������ ����ġ�� ������� ���´�. aAB+bC
		my_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans
					, network->layers[i].n      // M
					, 1                         // N
					, network->layers[i - 1].n  // K
					, 1.0F    // alpha
					, network->layers[i].w, network->layers[i - 1].n    // A, lda
					, network->layers[i - 1].neuron, 1      // B, ldb
					, 0.0F    // beta
					, network->layers[i].neuron, 1);        // C, ldc
		for (int j = 0; j < network->layers[i].n; j++) {
			network->layers[i].neuron[j] = Sigmoid(network->layers[i].neuron[j]);
		}
	}
	////////////////////////////////////////////////////////////////////////////////
	//
	//
	// PROBLEM 1: ADD YOUR CODE BELOW
	//
	// ������ 10���� ���� �� ���� ū ���� �ε����� ã�� �� �ε����� �����Ѵ�.
	// �ش� �ε����� MLP�� prediction �̴�.
	//
	// �Ʒ��� �ڵ带 �ϼ���Ű�ø� �˴ϴ�. 
	//
	//
	////////////////////////////////////////////////////////////////////////////////
	int a = 0;
	float max_value = network->layers [ network->depth - 1 ].neuron [ 0 ];

	// ADD YOUR CODE HERE. max_value�� ������
	for (int i = 1; i < network->layers[network->depth - 1].n; i++) {
		if (network->layers[network->depth - 1].neuron[i] > max_value) {
			max_value = network->layers[network->depth - 1].neuron[i];
			a = i;
		}
	}

	return a;
}
inline void Backward(Network* network, int label, float learning_rate) {
	/*
	*	@TODO
	*	error�� Gradient�� ���
	*	������������ ������ one-hot vectorȭ �� ����� ��� ����� �A ��
	*/
	//Calculate last layer's error
	for ( int i = 0; i < network->layers [ network->depth - 1 ].n; i++ ) {
		network->layers [ network->depth - 1 ].error [ i ] = 0.0F - network->layers [ network->depth - 1 ].neuron [ i ];
	}
	network->layers [ network->depth - 1 ].error [ label ] = 1.0F - network->layers [ network->depth - 1 ].neuron [ label ];
	/*
	*	@TODO
	*	������ ��ȸ�ϸ鼭 �� ���̾��� ������ ����Ѵ�.
	*	���� ���̾��� ������ ���� ���̾��� ����ġ(��ġ)��, ���� ���̾��� ������ �̿��� ����Ѵ�.
	*	@example
	*	[100][10] �� ��ġ�� ����ġ�� [10][1]�� ������ ��İ� �Ͽ� [100][1] �� ���� ���̾��� ������ ����� �� �ִ�.
	*	@other
	*	��� �Է����� ������ ����� �ʿ䰡 �����ϴ�. �ٸ� ���Ŀ� Convolution�� �տ� ���̸� �Է����� ������ �ʿ��ϴ�.
	*	���� �Է����� ������ �̸� ����� �д�.
	*/
	////////////////////////////////////////////////////////////////////////////////
	// PROBLEM 2: ADD YOUR CODE BELOW
	//
	// Output layer���� ������ ��ȸ�ϸ鼭 ������ ���̾��� ������ ����մϴ�.
	//
	// Hint: ���� ���̾�Y(1)�� ���� = ��(Z(i)�� ���� * W(i,1))
	//
	// �Ʒ��� NULL �κ� �ڵ带 �ϼ���Ű�ø� �˴ϴ�. 
	////////////////////////////////////////////////////////////////////////////////

	//Calculate other layer's error
	/*
	* inline void my_sgemm(int major, int transA, int transB, int M, int N, int K, float alpha,
	float* A, int lda, float* B, int ldb, float beta, float* C, int ldc) {
	//aAB+bC=C
	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {
			float c = C[m*ldc + n];
			C[m*ldc + n] = 0.0F;
			for (int k = 0; k < K; k++) {
				float a, b;
				a = transA == CblasTrans ? A[k*lda + m] : A[m*lda + k];
				b = transB == CblasTrans ? B[n*ldb + k] : B[k*ldb + n];
				C[m*ldc + n] += a*b;
			}
			C[m*ldc + n] = alpha*C[m*ldc + n] + beta*c;
		}
	}
	for (int i = 1; i < network->depth; i++) {
		//���� ���̾��� ������ ���� ���� ���̾��� ������ ����ġ�� ������� ���´�. aAB+bC
		my_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans
					, network->layers[i].n      // M
					, 1                         // N
					, network->layers[i - 1].n  // K
					, 1.0F    // alpha
					, network->layers[i].w, network->layers[i - 1].n    // A, lda
					, network->layers[i - 1].neuron, 1      // B, ldb
					, 0.0F    // beta
					, network->layers[i].neuron, 1);        // C, ldc
	*/
	for ( int i = network->depth - 1; i > 0; i-- ) {
		my_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans  //ORDER
					, network->layers [ i - 1 ].n, 1, network->layers [ i ].n // M N K
					, 1.0F													 // alpha
					, network->layers[i].w/*ADD YOUR CODE HERE*/ , network->layers [i - 1].n		// A, lda
					, network->layers[i].error/*ADD YOUR CODE HERE*/, 1								// B, ldb
					, 0.0F													// beta
					, network->layers [ i - 1 ].error, 1);					// C, ldc
	}
	/*
	*	@TODO
	*	����ġ�� �����ϱ� ���ؼ��� Gradient��, ���� ���̾��� ��°��� �ʿ��ϴ�.
	*	Gradient�� ����ϱ� ���ؼ��� ���� ���̾��� ������, ���� ���̾��� �������� �̺а��� �ʿ��ϴ�.
	*	�ܼ��� ������ ������ �̺а��� ���Ͽ�(��Į���) Gradient�� ����� �� �ִ�.
	*	@Warning
	*	Gradient�� ����Ҷ� ������ �����ϴ� ���� error�� ����� ���� ���ÿ�.
	*	(Convolution�� �������Ҷ��� ���������� �������� �����ϱ� ����)
	*	@hint
	*	���� Gradient ���� [10][1] ��� 
	*	[10][1] Gradient�� [1][100]�� �������̾��� �������� ��İ��Ͽ� [10][100]�� ������Ʈ�� ����ġ�� ����� �� �ִ�.
	*	��İ����� ���� [10][100]�� learning_rate�� ���� ���� Weight�� ���ϸ� �� ���� ����ġ�� �����̴�.
	*	@tip
	*	gemm�� alpha�� beta�� ����Ͽ� �ѹ��� learning_rate�� ���ؼ� ���ϴ� ȿ���� �� �� �ִ�.
	*/

	////////////////////////////////////////////////////////////////////////////////
	// PROBLEM 3: ADD YOUR CODE BELOW
	//
	// ��� ����ġ W(a,b)�� ���ؼ� update�� �����մϴ�.
	//
	// Hint:
	// ���ο� W(a,b) = learning rate * gradient(a) * neuron(b) + ���� W(a,b)
	// ���������� �ڵ尡 ����ȴٸ� W(1,1), W(1,2), W(1,3) .... W(2,1), W(2,2), W(2,3) .... W(10,100) ������ update �˴ϴ�.
	// �Ʒ��� NULL �κ� �ڵ带 �ϼ���Ű�ø� �˴ϴ�. 
	////////////////////////////////////////////////////////////////////////////////
	/*
	* inline void my_sgemm(int major, int transA, int transB, int M, int N, int K, float alpha,
	float* A, int lda, float* B, int ldb, float beta, float* C, int ldc) {
	//aAB+bC=C
	M*K��� A�� K*N��� B�� ���ؼ� AB (M*N)�� ����� ����, ���������� C���ٰ� alpha*AB + beta*C���� ���� ����� ����Դϴ�.
������ �����鿡 ���ؼ� �Ʒ��� �ڼ��� ������ �Ǿ� �ֽ��ϴ�.

	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {
			float c = C[m*ldc + n];
			C[m*ldc + n] = 0.0F;
			for (int k = 0; k < K; k++) {
				float a, b;
				a = transA == CblasTrans ? A[k*lda + m] : A[m*lda + k];
				b = transB == CblasTrans ? B[n*ldb + k] : B[k*ldb + n];
				C[m*ldc + n] += a*b;
			}
			C[m*ldc + n] = alpha*C[m*ldc + n] + beta*c;
		}
	}
	for (int i = 1; i < network->depth; i++) {
		//���� ���̾��� ������ ���� ���� ���̾��� ������ ����ġ�� ������� ���´�. aAB+bC
		my_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans
					, network->layers[i].n      // M
					, 1                         // N
					, network->layers[i - 1].n  // K
					, 1.0F    // alpha
					, network->layers[i].w, network->layers[i - 1].n    // A, lda
					, network->layers[i - 1].neuron, 1      // B, ldb
					, 0.0F    // beta
					, network->layers[i].neuron, 1);        // C, ldc
	*/
	//Update weights
	for ( int i = network->depth - 1; i >= 1; i-- ) {
		float* Gradient = ( float* ) calloc(network->layers [ i ].n, sizeof(float));
		for ( int j = 0; j < network->layers [ i ].n; j++ ) {
			//������ �̺а��� ���Ͽ�(��Į���) gradient ���� ���
			Gradient[j] = network->layers[i].error[j] * Sigmoid(network->layers[i].neuron[j])/*ADD YOUR CODE HERE*/;
		}
		my_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans
					, network->layers [ i ].n, network->layers [ i - 1 ].n, 1		// M N K
					, learning_rate/*ADD YOUR CODE HERE*/							// alpha = ��ī�� = learning rate
					, Gradient/*ADD YOUR CODE HERE*/, 1									// A, lda
					, network->layers[i-1].neuron/*ADD YOUR CODE HERE*/, 1									// B, ldb
					, 1.0F															// beta
					, network->layers [ i ].w, network->layers [ i - 1 ].n);        // C, ldc = ���̾� ����
		free(Gradient);
	}
}

#endif