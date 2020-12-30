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
	//�Է��� 784=28*28
	//������ 100
	//����� 10 ���� MLP�� ����
	int layers[] = { 28 * 28, 100, 10 };
	Network network = CreateNetwork(layers, sizeof(layers) / sizeof(int));

	num_of_train /= 10;				//���ð� ����� �ǽ� ����ÿ��� 1/10���� ����ؼ� Accuracy�� �ö󰡴��� Ȯ��. �ǽ� �˻�ÿ��� �� ���� �ּ�ó�� �� ���� ��� Ȯ��.

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