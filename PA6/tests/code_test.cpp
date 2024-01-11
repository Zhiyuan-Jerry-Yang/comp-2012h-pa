#include <iostream>

using namespace std;

int sum_digits(int x){
    int sum{0};
    while (x != 0){
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main(){
    int input, x;
    cin >> input;
    for (x = input + 1; sum_digits(x) != input || (x % input != 0); x++){;}
    cout << x;
}