#include <iostream>
#include <vector>
#include <unordered_map>
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

bool is_prime(long long int n) {
    if (n == 1) return false;
    else if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    else if (n % 2 == 0 || n % 3 == 0) return false;
    for(long long int i = 6; i * i <= n; i = i + 6){
        if(n % (i + 1) == 0 || n % (i + 5) == 0) return false;
    }
    return true;
}

long long int gcd(long long int a, long long int b){
    long long int temp = 0;
    while (b != 0){
        temp = a;
        a = b; b = temp % b;
    }
    return a;
}


long long int gcd_withrecursion(long long int a, long long int b, int calls){
    if (b == 0){
        cout << calls << " calls";
        return a;
    }
    else {
        return gcd_withrecursion(b, a % b, calls + 1);
    }
}


bool isPrime(long long int n) {
    // Corner cases
    if(n <= 1) return false;
    if(n <= 3) return true;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if(n % 2 == 0 || n % 3 == 0) return false;

    for(long long int i = 5; i * i <= n; i = i + 6)
        if(n % i == 0 || n % (i + 2) == 0) return false;

    return true;
}
int g(long long int x, long long int n){
    return (x * x + 1) % n;
}

long long int find_factor(long long int n){
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


unordered_map<int, vector<int>> known_factorizations = {{4, {2, 2}}, {49, {7, 7}}};

void foo(){
        long long int a = 68769878978979;
    for (int i = 0; i < 5; i++){
        if (known_factorizations.count(a) == 0) cout << "not here";
    }
}

vector<vector<long long int>> factorized = {{2, 2}, {5}, {2, 3}, {7}, {2, 2, 2}, {3, 3}, {2, 5}};

void print_factorization(long long int lower, long long int upper){
    for (int i = 0; i <= factorized.size() - 1; i++){
        cout << lower + i << "=";
        for (int j = 0; j < factorized[i].size(); j++){
            cout << factorized[i][j];
            if (j != factorized[i].size() - 1) cout << "*";
        }
        cout << endl;
    }
}
// Driver Program to test above function
int main() {
   /*  std::cout << std::boolalpha
        << isPrime(1) << '\n'
        << isPrime(1740232237) << '\n'; */
/*     for (int i = 0; i < 5; i++){
        cout << known_factorizations.count(a);
    }
 */  
//cout << boolalpha << is_prime(649657) << " " << isPrime(649657);

/* vector <vector<int>> vec = {{}, {}, {}};
cout << vec.size() << endl;
vec.push_back({});
cout << vec.size() << endl;
vec[3].push_back(7);
vec[vec.size() - 1].push_back(2);
cout << vec[3].size(); */

//cout << find_factor(9223372036854775807);
//cout << 9223372036854775806 / 6;


cout << find_factor(9223371994482243049);
}