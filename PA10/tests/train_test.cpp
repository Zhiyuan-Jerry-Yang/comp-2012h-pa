#include <algorithm>
#include <numeric>
#include "dataset.h"
#include "nn.h"
#include<bits/stdc++.h>

#include <iostream>

using namespace std;

void training(NN&, dataset&, const size_t&);
void testing(NN&, dataset&);

void nn_training_testing(dataset& data){		
	NN nn {
		new LayerLinear(PIXELS, 32),
		new LayerSigmoid,
		new LayerLinear(32   , 16),
		new LayerSigmoid,
		new LayerLinear(16   , 10),
		new LayerSigmoid,
	};

	for (size_t epoch = 0; epoch < 10; epoch++)
	{	
		training(nn, data, epoch);
		testing(nn, data);
	}	
}


void training(NN& nn, dataset& data, const size_t& epoch){
	vector<size_t> Sequence(data.get_data_size(TRAIN_LABEL));
	iota(Sequence.begin(), Sequence.end(), 0);
	random_shuffle(Sequence.begin(), Sequence.end());

	printf("================ Epoch %lu ================\n", epoch+1);

	for (size_t i = 0; i < Sequence.size(); i++) {
		vector<float> input = data.get_a_normalized_image(TRAIN_IMAGE, Sequence[i]);
		vector<float> one_hot_label(10);
		one_hot_label[data.get_a_label(TRAIN_LABEL, Sequence[i])] = 1;
		
		nn.backprop(input, one_hot_label);

		if ((i + 1) % 10 == 0)
			nn.apply();

		if ((i + 1) % 500 == 0) {
			printf("Epoch %lu: %lu / %lu\r", epoch+1, i+1, Sequence.size());
			fflush(stdout);
		}
	}
}


void testing(NN& nn, dataset& data){
	// START OF YOUR IMPLEMENTATION
	int size = data.get_data_size(TEST_IMAGE);
	vector<float> probs; vector<float> class_count(10);
	int label; vector<int> labels;
	for (int i = 0; i < 10; i++) class_count[i] = 0;
	for (int i = 0; i < size; i++) {
		probs = nn(data.get_a_normalized_image(TEST_IMAGE, i));
		label = static_cast<int>(data.get_a_label(TEST_LABEL, i));
		labels.push_back(label);
		if (std::distance(probs.begin(), std::max_element(probs.begin(), probs.end())) == label)
			class_count[label]++;
	}

	float correct_classes = std::accumulate(class_count.begin(), class_count.end(), 0);
	cout << "Overall accuracy: " << fixed << setprecision(2) << (correct_classes / data.get_data_size(TEST_LABEL)) * 100.0 << "%\n";

	for (int i = 0; i < 10; i++) {
		cout << "Accuracy for digit "<< i << ": " << fixed << setprecision(2) << (class_count[i] / std::count(labels.begin(), labels.end(), i)) * 100.0 << "%\n";
	}


	// END OF YOUR IMPLEMENTATION
}
