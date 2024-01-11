#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include "dataset.h"
#include "nn.h"
using namespace std;

void nn_training_testing(dataset&);

int main() {
	srand(100);
	
	// 	Define a dataset object and load the dataset
	dataset data;
	data.load_dataset();

	//data.print_image(converted);
	cout << static_cast<int>(data.get_a_label(TRAIN_LABEL, 4)) << endl;
	img_dt converted = data.convert_image_dt(data.get_an_image(TRAIN_IMAGE, 4));
	data.print_image(converted);
	cout << endl;

	data.resize_image(converted, 20, 40);
	data.print_image(converted);
	cout << endl;
	

	//cout << endl;
	//data.resize_image(converted, 22, 22);
	//data.print_image(converted);
	/** Step 1: Train a network with the complete and class-balanced "train" data,
	 *  test it on the "test" data and report the statistic about accuracy.
	**/
	/* cout << endl << "================ Step 1: Train a network with the complete dataset. ================" << endl;
	data.print_statistic(TRAIN_IMAGE);
	nn_training_testing(data);


	cout << endl << "================ Step 2: Train a network with the class-imbalanced dataset. ================" << endl;
	//const size_t imbalanced_digit = rand()% 10;
	const size_t imbalanced_digit = 4;	// To keep a fixed digit for cross-platfrom consistency
	const size_t size = 1600;
	data.remove_some_train_data(imbalanced_digit, size);
	data.print_statistic(TRAIN_IMAGE);
	nn_training_testing(data);

	
	cout << endl << "================ Step 3: Train a network with the augmented dataset. ================" << endl;
	data.append_some_augmented_train_data(imbalanced_digit, size);
	data.print_statistic(TRAIN_IMAGE);
	nn_training_testing(data); */

	return 0;
}