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
#include <stdint.h>
#include <array>
#include <vector>
#include <deque>
#include <stdio.h>

using namespace std;


    void print_image(const array<uint8_t, 28*28>& img_ar) {
	// START OF YOUR IMPLEMENTATION
	array<uint8_t, 28*28>::const_iterator iter = img_ar.begin();
	int i{0}; int prev_digits;
	if (img_ar[0] >= 0 && img_ar[0] <= 9) prev_digits = 1;
	else if (img_ar[0] <= 99) prev_digits = 2;
	else prev_digits = 3;
	while (iter != img_ar.end()) {
		for (int j = 0; j < 4 - prev_digits; j++) cout << " ";
		cout << img_ar[i];
		if (img_ar[i] >= 0 && img_ar[i] <= 9) prev_digits = 1;
		else if (img_ar[i] <= 99) prev_digits = 2;
		else prev_digits = 3;

		i++;
		iter++;
		if (i % 28 == 0) cout << '\n';
	}

	// END OF YOUR IMPLEMENTATION
}

struct A{
    int i;
    A(int a=3): i{a} {}
    ~A() {cout << "In Destructor:" << i << endl;}
};

A bar() {A a; return a;}

int main() {
    
    A&& ir = bar();
    ir = 19;
    cout << "End of main\n";
    return 0;
}
/*
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0  55 148 210 253 253 113  87 148  55   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0  87 232 252 253 189 210 252 252 253 168   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   4  57 242 252 190  65   5  12 182 252 253 116   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0  96 252 252 183  14   0   0  92 252 252 225  21   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0 132 253 252 146  14   0   0   0 215 252 252  79   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
 126 253 247 176   9   0   0   8  78 245 253 129   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
 232 252 176   0   0   0  36 201 252 252 169  11   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
 252 252  30  22 119 197 241 253 252 251  77   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
 231 252 253 252 252 252 226 227 252 231   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
  55 235 253 217 138  42  24 192 252 143   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0  62 255 253 109   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0  71 253 252  21   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0 253 252  21   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0  71 253 252  21   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0 106 253 252  21   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0  45 255 253  21   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0 218 252  56   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0  96 252 189  42   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0  14 184 252 170  11   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0   0  14 147 252  42   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0



*/