#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <utility>


using namespace std;

class A {};

class Base
{
    
private:
    int x;
    int y;
    char* ptr;
    A* aptr;
public:
    int z;
    Base(): x(2), y(3), z(5) {}; //default
    Base(int _x, int _y): z(5) {x = _x; y = _y;}
    Base(const char* cptr, int _x=7, int _y=7): z(5) {ptr = new char[strlen(cptr) + 1]; strcpy(ptr, cptr);}
    Base(Base&& b) {
        x = std::move(x);
        y = std::move(y);
        ptr = b.ptr;
        b.ptr = nullptr;
    };
    ~Base() {
        cout << "inside Base destructor:\n";
        delete [] ptr;
    };
    void print() {cout << x << '\t' << y << '\t' << ptr;};
    void fun(ostream& o) const;
    void foo() const {A* ptr = aptr;}
};


void Base::fun(ostream& o) const {
    auto f = [&](int a, int b) {o << "(" << a << ", " << b << ")\n";};
    f(x, y);
    
}

ostream& operator<<(ostream& o, const Base& b) {
    b.fun(cout);
    return o;
}
template <typename T>
void f(T a, T b) {cout << "generic case\n";}

void f(int a, int b) {cout << "special case\n";}
void tower_of_hanoi(int num_discs, char pegA, char pegB, char pegC)
{
if (num_discs == 0) // Base case
return;
tower_of_hanoi(num_discs-1, pegA, pegC, pegB);
cout << "move disc " << num_discs
<< " from peg " << pegA << " to peg " << pegC << endl;
tower_of_hanoi(num_discs-1, pegB, pegA, pegC);
}

template <typename T, int N>
void func(T(&arr)[N]) {
    cout << "general\n";
}
template <>
void func(int(&arr)[5]) {
    cout << "specialized\n";
}

int main() {
    /* Base b("x", 777, 999); Base aa("d", 565, 123);
    cout << b << aa;
    char arr[] = "hello";
    cout << strlen(arr);
    cout << strlen("hello");
    Base* bptr = new Base("world");
    delete bptr;
    cout << "end of main\n"; */
    tower_of_hanoi(3, '1', '2', '3');
    string s;
    getline(cin, s);
    cout << s;
}