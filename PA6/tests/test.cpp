#include <iostream>
#include <fstream>
#include "String.h"

using namespace std;

int main(){
    /* String a, b, c, d;
    fstream ifs ("test.txt");
    getline(ifs, a, '\n');
    cout << a;
    cout << endl;

    
    getline(ifs, b, '\n');
    cout << b;
    cout << endl;

    getline(ifs, c, '\n');
    cout << c;
    cout << endl;

    getline(ifs, d, '\n');
    cout << d;
    cout << endl;


    String* arrptr = new String[2];
    String* workingptr = arrptr;
    int count = 0, begin = 0;
    for (int i = 0; ; i++){
        if (d[i] == ',' || d[i] == '\0') {
            *workingptr = d.substr(begin, count);
            workingptr++;
            begin += (count + 2);
            count = 0;
            if (d[i] == '\0') break;
        }
        else if (d[i] == '*'){
            begin++;
        }
        else if (d[i] == ' ') continue;
        else count++;
    }
    cout << *(arrptr) << '\n' << *(arrptr + 1) << '\n';
    delete [] arrptr;

    getline(ifs, d, '\n');

    arrptr = new String[2];
    workingptr = arrptr;
    int count2 = 0, begin2 = 0;
    for (int i = 0; ; i++){
        if (d[i] == ',' || d[i] == '\0') {
            *workingptr = d.substr(begin2, count2);
            workingptr++;
            begin2 += (count2 + 2);
            count2 = 0;
            if (d[i] == '\0') break;
        }
        else if (d[i] == '*'){
            begin2++;
        }
        else if (d[i] == ' ') continue;
        else count2++;
    }
    cout << *(arrptr) << '\n' << *(arrptr + 1);
    delete [] arrptr;
    ifs.close();


    cout << endl;
    fstream ifs1 ("test.txt");
    String this_line;
    while (!ifs1.eof()){
        getline(ifs1, this_line, '\n');
        if (!ifs1.eof()) cout << this_line << '\n';
    }
    ifs1.close(); */
/*     fstream ifs ("test.txt");
    String this_line;
    getline(ifs, this_line, '\n');
    cout << "the first line: " << this_line << endl;
        while (!ifs.eof()){
        getline(ifs, this_line, '\n');
        
        if (!ifs.eof()){
            cout << "this line: " << this_line << endl;
            cout << "advance pointer" << endl;
        }
    } */

    String a = "Table";
    String b = a;
    cout << b;
}