#include <iostream> /* File: test-lscs.cpp */
#include <algorithm>
#include <vector>
using namespace std;

namespace apple
{
class Stack { /* incomplete */ };
class Some_Class { /* incomplete */ };
void safari() { cout << "Apple's browser" << endl; };
void app(int x) { cout << "Apple's app: " << x << endl; };
}

// Part (a):
class LSCS
{
    int max_so_far;
    int max_ending_here;
    int** iptr;
public:
    LSCS(): max_so_far{0}, max_ending_here{0}, iptr(new int*[10]) {}
    int get_result() const {return max_so_far;}
    void operator()(int a) {
        max_ending_here += a;
        if (max_so_far < max_ending_here) max_so_far = max_ending_here;
        if (max_ending_here < 0) max_ending_here = 0;
    }
};

enum class OS {MS, MAC} choice;

int main() {
vector<int> arr { -2, -3, 4, -1, -2, 1, 5, -3 };
// Part (b):
// Call for_each with a function object of LSCS defined
// in part (a) to find the largest sum contiguous
// subsequence of arr.
// Your code here
choice = OS::MAC;
LSCS lscs;
lscs = for_each(arr.begin(), arr.end(), lscs);
cout << lscs.get_result() << endl; // Outputs 7
return 0;
}