#include <iostream>

using namespace std;



class Base{
    private:
        int x;
    public:
        Base(int n=7): x(n) {;}
        int get_num(){return x;}
};

class Derived: public Base{
    friend class foo;
    private:
        int y;
    public:
        Derived(int m){y = m;}
        int get_num(){return y;}
        void print_num(){cout << y;}
};

int main(){
    int arr[4] = {0, 1, 2, 33};
    int* arrptr = arr;
    cout << arrptr[3];
}