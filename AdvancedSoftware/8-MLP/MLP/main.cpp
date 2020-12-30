/*
*	Multi-Layer Perceptron example
*/
#include "mlp.h"
#include <mnist.h>

int num_of_epoch = 2;

int main() {
	int num_of_train, num_of_valid;
	MNIST* valid = ReadMNIST("./mnist/t10k-images.idx3-ubyte", "./mnist/t10k-labels.idx1-ubyte", &num_of_valid, 0); // validation data
	MNIST* train = ReadMNIST("./mnist/train-images.idx3-ubyte", "./mnist/train-labels.idx1-ubyte", &num_of_train, 0); // training data
	//입력층 784=28*28
	//은닉층 100
	//출력층 10 개인 MLP를 생성
	int layers[] = { 28 * 28, 100, 10 };
	Network network = CreateNetwork(layers, sizeof(layers) / sizeof(int));

	num_of_train /= 10;				//계산시간 관계로 실습 진행시에는 1/10값을 사용해서 Accuracy가 올라가는지 확인. 실습 검사시에는 이 문장 주석처리 후 실행 결과 확인.

	float learning_rate = 0.03F;
	for (int e = 1; e <= num_of_epoch; e++) {
		int answer = 0;
		for (int j = 0; j < num_of_train; j++) {
			int a = Forward(&network, train[j].image);
			if (a == train[j].label) {
				answer++;
			}
			Backward(&network, train[j].label, learning_rate);
		}
		printf("epoch = %d\ttrain : %f\t", e, (float)answer / num_of_train);
		answer = 0;
		for (int j = 0; j < num_of_valid; j++) {
			int a = Forward(&network, valid[j].image);
			if (a == valid[j].label) {
				answer++;
			}
		}
		printf("valid : %f\n", (float)answer / num_of_valid);
	}
	return 0;
}