#include <iostream>
using namespace std;

int gcd(int a, int b){
    if (b == 0){
        return a;
    }
    else {
        return gcd(b, a - b);
    }
}

int g(int x){
    return x * x + 1;
}


int factorization(int n){
    int x = 2, y = 2, d = 1;
    while (d == 1){
        x = g(x);
        y = g(g(y));
        d = ((x > y) ? gcd((x - y), n) : gcd((y - x), n));
    }
    if (d == n) return false;
    else return d;
}

int main(){
    cout << "factorize: " << endl;
    //cout << factorization(8051);
}