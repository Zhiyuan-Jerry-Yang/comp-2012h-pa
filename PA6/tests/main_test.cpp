#include <iostream>
#include <limits>
#include "Database.h"
#include "String.h"

using namespace std;



int main(){

    Database db ("sample_database.txt");
    //db.innerJoin(db.findTable("Table_7"), db.findTable("Table_8"));
    //db.printTable(db.findTable("Table_7+Table_8"));
    String arr[5] = {"2", "KK", "24", "USA", "ECE"};
    String* record = arr;
    db.findTable("Table_1")->addRecord(3, record);
    db.printTable(db.findTable("Table_1"));

    String arr2[5] = {"2", "KKefq", "24", "USA", "ECE"};
    record = arr2;
    db.findTable("Table_1")->addRecord(5, record);
    db.printTable(db.findTable("Table_1"));

    db.findTable("Table_1")->deleteField("Year");
    db.printTable(db.findTable("Table_1"));
}