#include <iostream>
using namespace std;

int gcd(long long int a, long long int b){
    if (b == 0){
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

int g(long long int x, long long int n){
    return (x * x + 1) % n;
}


int factorization(long long int n){
    int x = 2 , y = 2, d = 1;
    while (d == 1){
        x = g(x, n);
        y = g(g(y, n), n);
        long int a = std::abs(x - y);
        d = ((n > a) ? gcd(n, a) : gcd(a, n));
    }
    if (d > 1) return d;
    else return n;
}

int main(){
    cout << "factorizing: " << endl;
    cout << factorization(141804745219);
}
/*
while not all ns are factorized:
    check whether 2 or 3 divides n, if yes pushback 2 or 3
    while n is not prime:
        check whether n is in map, if yes read from map
        while no divisor is found:
            apply rho algorithm
            if one divisor of n is found, pushback & break
    (n is prime now) pushback
    push the factorization of this n into the map?
    proceed to next n
print prime factorizations of all ns
*/