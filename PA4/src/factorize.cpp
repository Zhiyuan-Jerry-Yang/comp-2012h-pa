/*
Reference:
1. The Pollard's rho algorithm is referred to and implemented in this program, the idea of which can be foud at https://en.wikipedia.org/wiki/Pollard's_rho_algorithm
2. The core concept of this answer on Stackoverflow is utilized to find out whether a number is a prime: https://stackoverflow.com/questions/62150130/algorithm-of-checking-if-the-number-is-prime
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;


const vector<long long int> PRIME = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 
101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331,
337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457,
461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 
809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 
1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 
1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 649657, 715827883, 2147483647};


const long long int LLMAX = 9223372036854775807;

unordered_map<long long int, vector<long long int>> factorizations = {{4, {2, 2}}, {6, {2, 3}}, {8, {2, 2, 2}}, {49, {7, 7}}, {121, {11, 11}}, {169, {13, 13}}, {289, {17, 17}}, {361, {19, 19}}, 
{1001, {7, 11, 13}}, {2431, {11, 13, 17}}, {4199, {13, 17, 19}}};

vector<vector<long long int>> factorized = {};

inline long long int gcd(long long int a, long long int b){
    long long int temp = 0;
    while (b != 0){
        temp = a;
        a = b; b = temp % b;
    }
    return a;
}

inline int g(long long int x, long long int n){
    long long int g = (x * x + 1) % n;
    return g;
}


inline long long int find_factor(long long int n){
    long long int temp = 2;
    long long int x = temp, y = temp, d = 1;
    while (true){
    while (d == 1){
        x = g(x, n);
        y = g(g(y, n), n);
        long long int a = std::abs(x - y);
        d = ((n > a) ? gcd(n, a) : gcd(a, n));
    }
    if (d > 1 && d < n) return d;
    else {
        temp++; x = temp; y = temp; d = 1;
        continue;
    }
    }
}


inline bool is_prime(long long int n) {
    if (n == 1) return false;
    else if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    else if (n % 2 == 0 || n % 3 == 0) return false;
    for(long long int i = 6; i * i <= n; i = i + 6){
        if(n % (i + 1) == 0 || n % (i + 5) == 0) return false;
    }
    return true;
}



void factorization(long long int lower, long long int upper){
    long long int num = lower, reference = 0;
    long long int i = 0;
    while (num <= upper){
        factorized.push_back({});
        reference = num;

        //cout << "size of factorized: " << factorized.size() << '\n';
        
        while (reference % 2 == 0){
            reference /= 2;
            factorized[i].push_back(2);
        }

        while (reference % 3 == 0){
            reference /= 3;
            factorized[i].push_back(3);
        }

        while (reference % 5 == 0){
            reference /= 5;
            factorized[i].push_back(5);
        }

        if (factorizations.count(reference) > 0) {
            factorized[i].insert(factorized[i].end(), factorizations[reference].begin(), factorizations[reference].end());
            factorizations.insert({num, factorized[i]});
            if (num < LLMAX){
            num++;
            i++;
            }
            else break;
            continue;
        }

        if (binary_search(PRIME.begin(), PRIME.end(), reference) || is_prime(reference)) {
            factorized[i].push_back(reference);
            factorizations.insert({num, factorized[i]});
            if (num < LLMAX){
            num++;
            i++;
            }
            else break;
            continue;
        }
        else if (reference == 1) {
            factorizations.insert({num, factorized[i]});
            if (num < LLMAX){
            num++;
            i++;
            }
            else break;
            continue;
        }

        long long int factor = reference;
        while (true){
            factor = find_factor(reference);
            while (!binary_search(PRIME.begin(), PRIME.end(), reference) && !is_prime(factor)) factor = find_factor(factor);
            reference /= factor;
            factorized[i].push_back(factor);

            if (!binary_search(PRIME.begin(), PRIME.end(), reference) && (!is_prime(reference) && reference != 1)) {
                continue;
            }
            else {
                factorized[i].push_back(reference);
                break;
            }
        }
        factorizations.insert({num, factorized[i]});
        if (num < LLMAX) num++;
        else break;
        //for (int a: factorized[i]) cout << a << " ";
        i++;
        //cout << "num = " << num << endl;
    }
    //cout << "size of factorized: " << factorized.size() << '\n';
    //cout << "exit successfully" << endl;
}

void print_factorization(long long int lower, long long int upper){
    for (long long int i = 0; i <= upper - lower; i++){
        sort(factorized[i].begin(), factorized[i].end());
        cout << lower + i << "=";
        for (long unsigned int j = 0; j <= factorized[i].size() - 1; j++){
            cout << factorized[i][j];
            if (j != factorized[i].size() - 1) cout << "*";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]){
    long long int lower_bound = atoll(argv[1]), upper_bound = atoll(argv[argc - 1]);
    //long long int lower_bound = 57209147598298 , upper_bound = 57209147598317;
    auto start = high_resolution_clock::now();

    factorization(lower_bound, upper_bound);
    print_factorization(lower_bound, upper_bound);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "time taken (micorseconds): " << duration.count() << endl;

}