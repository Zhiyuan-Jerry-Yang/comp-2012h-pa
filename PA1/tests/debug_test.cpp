#include <iostream>

using namespace std;

void bug(int* arrptr){
    cout << *arrptr;
}


int main(){
    int arr[5] = {1, 224, 25, 747, 24};
    int*arrptr = nullptr;
    bug(arrptr);
    cout << "last";
}