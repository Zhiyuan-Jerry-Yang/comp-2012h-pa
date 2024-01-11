#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <stack>
#include <cstring>
#include <iomanip>
#include <stdexcept>
#include <random>

#include <map>

#include "dataset.h"
using namespace std;


const char* PATH_TRAIN_LABELS = "train-labels-idx1-ubyte";
const char* PATH_TRAIN_IMAGES = "train-images-idx3-ubyte";
const char* PATH_TEST_LABELS = "t10k-labels-idx1-ubyte";
const char* PATH_TEST_IMAGES = "t10k-images-idx3-ubyte";


dataset::dataset(){;}


dataset::~dataset(){;}


void dataset::load_dataset() {
	ifstream fin;
	uint32_t MN, N, A, B;

	/*---------------------*\
	\*---------------------*/

	fin = ifstream(PATH_TRAIN_LABELS, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	N = __builtin_bswap32(N)/3;
	
	if (MN != 0x01080000) {
		cerr << "Invalid database" << endl;
		exit(1);
	}

	train_labels.resize(N);
	fin.read((char*)train_labels.data(), N * sizeof(uint8_t));

	/*---------------------*\
	\*---------------------*/

	fin = ifstream(PATH_TRAIN_IMAGES, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	fin.read((char*)&A, sizeof(A));
	fin.read((char*)&B, sizeof(B));

	N = __builtin_bswap32(N)/3;
	A = __builtin_bswap32(A);
	B = __builtin_bswap32(B);

	if (MN != 0x03080000 || A != COLS || B != ROWS) {
		cerr << "invalid database" << endl;
		exit(1);
	}

	train_images.resize(N);
	fin.read((char*)train_images.data(), N * sizeof(array<uint8_t, PIXELS>));

	/*---------------------*\
	\*---------------------*/

	fin = ifstream(PATH_TEST_LABELS, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	N = __builtin_bswap32(N)/3;

	if (MN != 0x01080000) {
		cerr << "Invalid database" << endl;
		exit(1);
	}

	test_labels.resize(N);
	fin.read((char*)test_labels.data(), N * sizeof(uint8_t));

	/*---------------------*\
	\*---------------------*/

	fin = ifstream(PATH_TEST_IMAGES, ios_base::binary);
	fin.read((char*)&MN, sizeof(MN));
	fin.read((char*)&N, sizeof(N));
	fin.read((char*)&A, sizeof(A));
	fin.read((char*)&B, sizeof(B));

	N = __builtin_bswap32(N)/3;
	A = __builtin_bswap32(A);
	B = __builtin_bswap32(B);

	if (MN != 0x03080000 || A != COLS || B != ROWS) {
		cerr << "invalid database" << endl;
		exit(1);
	}

	test_images.resize(N);
	fin.read((char*)test_images.data(), N * sizeof(array<uint8_t, PIXELS>));
}


void dataset::remove_some_train_data(const uint8_t digit, const size_t size){
	// START OF YOUR IMPLEMENTATION
	vector<array<uint8_t, PIXELS>>::iterator im_iter = train_images.end() - 1;
	vector<uint8_t>::iterator iter = train_labels.end() - 1;
	int remaining = size;
	while (remaining) {
		if (*iter == digit) {
			iter = train_labels.erase(iter);
			im_iter = train_images.erase(im_iter);
			remaining--;
		}
		iter--; im_iter--;
	}
	// END OF YOUR IMPLEMENTATION
}


void dataset::append_some_augmented_train_data(const uint8_t digit, const size_t size){
    vector<size_t> indices;
	unsigned int counter = 0;

    for (vector<uint8_t>::iterator it = train_labels.begin(); it != train_labels.end(); it++) {
        if (*it == digit){
			indices.push_back(distance(train_labels.begin(), it));
		}
    }

	vector<size_t>::iterator it2 = indices.begin();
	while(counter<size){	
		++counter;

		train_images.push_back(this->compound_augment_image(train_images[*it2]));
		train_labels.push_back(digit);
		
		it2++;
		if(it2 == indices.end())
			it2 = indices.begin();
	}
}


array<uint8_t, PIXELS> dataset::compound_augment_image(array<uint8_t, PIXELS>& img_ar){
	img_dt img = convert_image_dt(img_ar);
	size_t rand_num = rand()% 8;
	this->shift_image(img, shift_type(rand_num), rand()% 4);

	rand_num = rand()% 9 + ROWS - 4;
	this->resize_image(img, rand_num, rand_num);
	if(rand_num>ROWS){
		this->crop_image(img, (rand_num-ROWS)/2, (rand_num-COLS)/2, ROWS, COLS);
	}
	else{
		this->padding_image(img, (ROWS-rand_num)/2, ROWS-(ROWS-rand_num)/2-rand_num, (COLS-rand_num)/2, COLS-(COLS-rand_num)/2-rand_num);
	}

	array<uint8_t, PIXELS> img_ar_out = convert_image_dt(img);

	return img_ar_out;
}


void dataset::shift_image(img_dt& img, const enum shift_type dir, const size_t p, const uint8_t value){
	// START OF YOUR IMPLEMENTATION
	deque<uint8_t> new_line(img[0].size());
	if (dir != LEFT && dir != RIGHT) {
		if (dir == UP || dir == UPLEFT || dir == UPRIGHT) {
			for (int i = 0; i < p && i < img.size(); i++) {
				img.pop_front();
				for (int j = 0; j < img[0].size(); j++) new_line[j] = value;
				img.push_back(new_line);
			}
		}
		else {
			for (int i = 0; i < p && i < img.size(); i++) {
				img.pop_back();
				for (int j = 0; j < img[0].size(); j++) new_line[j] = value;
				img.push_front(new_line);
			}
		}
	}
	if (dir != UP && dir != DOWN) {	
			if (dir == LEFT || dir == DOWNLEFT ||dir == UPLEFT) {
				for (int i = 0; i < img.size(); i++) {
				for (int j = 0; j < p && j < img[0].size(); j++) {
					img[i].pop_front();
					img[i].push_back(value);
				}
				}
			}
			else if (dir == RIGHT || dir == DOWNRIGHT || dir == UPRIGHT) {
				for (int i = 0; i < img.size(); i++) {
					for (int j = 0; j < p && j < img[0].size(); j++) {
						img[i].pop_back();
						img[i].push_front(value);
					}
				}
			}
	}
	// END OF YOUR IMPLEMENTATION
}


//(0.5, 0.5), (1.5, 0.5), ..., (27.5, 0.5), (0.5, 1.5), ..., ... , (27.5, 27.5)
void dataset::resize_image(img_dt& img, const size_t new_rows, const size_t new_cols){
	// START OF YOUR IMPLEMENTATION
	// > 1 -> shrinking, < 1 -> enlarging
	double num_rows = static_cast<double>(img.size()); double num_cols = static_cast<double>(img[0].size());
	double row_resize_fac = num_rows / new_rows; double col_resize_fac = num_cols / new_cols;
	const double EPSILSON = 1e-5;
	img_dt new_img;
	vector<double> dists;
	double min_dist = INFINITY; double this_dist; int min_row_idx = 0; int min_col_idx = 0;
	for (double i = 0.5 * row_resize_fac; i < num_rows; i += 1.0 * row_resize_fac) {
		deque<uint8_t> new_row;
		new_img.push_back(new_row);
		for (double j = 0.5 * col_resize_fac; j < num_cols; j += 1.0  * col_resize_fac) {
			for (double i1 = 0.5; i1 < num_rows; i1 += 1.0) {
				for (double j1 = 0.5; j1 < num_cols; j1 += 1.0) {
					//compute Euclidean distance for a particular pixel
					this_dist = sqrt(pow(i - i1, 2) + pow(j - j1, 2));
					if (min_dist == INFINITY || this_dist <= min_dist || std::abs(this_dist - min_dist) <= EPSILSON) {
						min_dist = this_dist;
						min_row_idx = static_cast<int>(i1);
						min_col_idx = static_cast<int>(j1);
					}
				}
			}

			//printf("i: %f; min_row_idx: %d; min_col_idx: %d\n", i, min_row_idx, min_col_idx);
			
			new_img[static_cast<int>(i / (row_resize_fac))].push_back(img[min_row_idx][min_col_idx]);
			min_dist = INFINITY;
		}
	}
			
	img.clear();
	img = new_img;
	// END OF YOUR IMPLEMENTATION
}


void dataset::crop_image(img_dt& img, const size_t y0, const size_t x0, const size_t new_rows, const size_t new_cols){
	// START OF YOUR IMPLEMENTATION
	for (int i = 0; i < y0; i++) {
		img.pop_front();
	}
	for (int i = 0; i < img.size(); i++) {
		for (int j = 0; j < x0; j++) img[i].pop_front();
	}
	int remaining_rows, remaining_cols;
	remaining_rows = img.size(); remaining_cols = img[0].size();
	for (int i = new_rows; i < remaining_rows; i++) {
		img.pop_back();
	}
	for (int i = 0; i < img.size(); i++) {
		for (int j = new_cols; j < remaining_cols; j++) img[i].pop_back();
	}
	// END OF YOUR IMPLEMENTATION
}


void dataset::padding_image(img_dt& img, const size_t top, const size_t down, const size_t left, const size_t right, const uint8_t value){
	// START OF YOUR IMPLEMENTATION
	for (int i = 0; i < img.size(); i++) {
		for (int j = 0; j < left; j++) img[i].push_front(value);
		for (int k = 0; k < right; k++) img[i].push_back(value);
	}
	deque<uint8_t> new_rows;
	for (int i = 0; i < img[0].size(); i++) new_rows.push_back(value);

	for (int j = 0; j < top; j++) img.push_front(new_rows);
	for (int j = 0; j < down; j++) img.push_back(new_rows);
	
	// END OF YOUR IMPLEMENTATION
}


uint8_t	dataset::get_a_label(const data_type mode, const size_t index) const{
	switch(mode){
		case TRAIN_LABEL: 
			return train_labels[index];		break;
		case TEST_LABEL: 
			return test_labels[index];		break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}


img_dt dataset::convert_image_dt(const array<uint8_t, PIXELS>& img) const {
	// START OF YOUR IMPLEMENTATION
	img_dt converted; deque<uint8_t> this_row(28);
	for (int j = 0; j < ROWS; j++) {
		for (int i = 0; i < COLS; i++) {
			//cout << static_cast<unsigned int>(img[i]) << '\t';
			this_row[i] = img[j * 28 + i];
		}
		converted.push_back(this_row);
	}
	return converted;
	// END OF YOUR IMPLEMENTATION
}


array<uint8_t, PIXELS>  dataset::convert_image_dt(const img_dt& img) const {
	// START OF YOUR IMPLEMENTATION
	array<uint8_t, PIXELS> converted;
	for (int i = 0; i < img.size(); i++) {
		for (int j = 0; j < img[i].size(); j++) {
			converted[i * 28 + j] = img[i][j];
		}
	}
	return converted;
	
	// END OF YOUR IMPLEMENTATION
}


array<uint8_t, PIXELS>	dataset::get_an_image(const enum data_type mode, const size_t index) const{
	switch(mode){
		case TRAIN_IMAGE:
			return train_images[index];		break;
		case TEST_IMAGE: 
			return test_images[index];		break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}


vector<float>	dataset::get_a_normalized_image(const enum data_type mode, const size_t index) const{
	const array<uint8_t, PIXELS>& img = this->get_an_image(mode, index);
	vector<float> img_normalized(PIXELS);

	transform(img.begin(), img.end(), img_normalized.begin(), normalize(255.0f));
	return img_normalized;
}


size_t	dataset::get_data_size(const enum data_type mode) const{
	switch(mode){
		case TRAIN_LABEL: 
			return train_labels.size();		break;
		case TEST_LABEL:
			return test_labels.size();		break;
		case TRAIN_IMAGE: 
			return train_images.size();		break;
		case TEST_IMAGE: 
			return test_images.size();		break;
		default:
			throw invalid_argument( "Invalid mode!");
	}
}


void dataset::print_image(const array<uint8_t, PIXELS>& img_ar) const {
	// START OF YOUR IMPLEMENTATION
	array<uint8_t, PIXELS>::const_iterator iter = img_ar.begin();
	int i{0}; int prev_digits;
	while (iter != img_ar.end()) {
		if (static_cast<unsigned int>(img_ar[i]) >= 0 && static_cast<unsigned int>(img_ar[i]) <= 9) prev_digits = 1;
		else if (static_cast<unsigned int>(img_ar[i]) <= 99) prev_digits = 2;
		else prev_digits = 3;
		for (int j = 0; j < 4 - prev_digits; j++) cout << " ";
		cout << static_cast<unsigned int>(img_ar[i]);
		
		i++;
		iter++;
		if (i % 28 == 0) cout << '\n';
	}

	// END OF YOUR IMPLEMENTATION
}


void dataset::print_image(const img_dt& img) const {
	// START OF YOUR IMPLEMENTATION
	int prev_digits;
	for (int i = 0; i < img.size(); i++) {
		for (int j = 0; j < img[i].size(); j++) {
			if (static_cast<unsigned int>(img[i][j]) >= 0 && static_cast<unsigned int>(img[i][j]) <= 9) prev_digits = 1;
			else if (static_cast<unsigned int>(img[i][j]) <= 99) prev_digits = 2;
			else prev_digits = 3;
			for (int k = 0; k < 4 - prev_digits; k++) cout << " ";
			cout << static_cast<unsigned int>(img[i][j]);
			
		}
		cout << '\n';
	}

	// END OF YOUR IMPLEMENTATION
}


void dataset::print_statistic(const enum data_type mode) const{
	// START OF YOUR IMPLEMENTATION
	int num_images;
	if (mode == TRAIN_IMAGE) {
		for (int i = 0; i < 10; i++) {
			num_images = std::count(train_labels.begin(), train_labels.end(), i);
			cout << "Number of train images for digit " << i << ": " << num_images << endl;
		}
	}
	else {
		for (int i = 0; i < 10; i++) {
			num_images = std::count(test_labels.begin(), test_labels.end(), i);
			cout << "Number of test images for digit " << i << ": " << num_images << endl;
		}
	}
	// END OF YOUR IMPLEMENTATION
}
