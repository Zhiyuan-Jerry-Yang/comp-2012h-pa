#include <fstream>
#include <iomanip>
#include <iostream>
#include "Database.h"
#include "String.h"
#include "Table.h"

using namespace std;



////////////////////    11/10/2022 TODO inner_join()
///////////////////// 13/10/2022 deleteTable() changed, not tested



void Database::printTable(Table *table) const
{
    if (table == nullptr)
    {
        cout << "No such table exists in the database." << endl;
        return;
    }

    for (Field *cur = table->getFieldHead(); cur != nullptr; cur = cur->next)
    {
        cout << setw(15) << left;
        String curPrintName = (cur == table->getPrimaryKey() ? "*" : "") + cur->name + ' ' + (cur->type == INT ? "0" : "1");
        cout << curPrintName;
    }
    cout << endl;
    for (int i = 0; i < table->getNumRows(); ++i)
    {
        for (int j = 0; j < table->getNumCols(); ++j)
        {
            cout << setw(15) << left;
            cout << (*table)[j][i];
        }
        cout << endl;
    }

    return;
}

Database::Database(const String &name, int numTables){
    this->name = name;
    currentTable = nullptr;
    this->numTables = numTables;
    String nums[100] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18",
    "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37",
    "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56",
    "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75",
    "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94",
    "95", "96", "97", "98", "99", "100"};
    if (numTables > 0){
        String start_table_name = "Table_" + nums[0];
        String this_table_name;
        Table* this_table = new Table (start_table_name);
        tableHead = this_table;
        Table* working_ptr = tableHead;
        for (int i = 2; i <= numTables; i++){
            this_table_name = "Table_" + nums[i - 1];
            working_ptr->next = new Table (this_table_name);
            working_ptr = working_ptr->next;
            if (i == numTables) working_ptr->next = nullptr;
        }
    }
    else tableHead = nullptr;
}

Database::Database(const String &filename){
    ifstream ifs (filename.getStr());
    String num_tables, table_name;
    getline(ifs, this->name, '\n');
    getline(ifs, num_tables, '\n');
    this->numTables = stoi(num_tables);
    this->currentTable = nullptr;
    getline(ifs, table_name, '\n');
    this->tableHead = new Table (ifs, table_name);
    Table* workingptr = this->tableHead;
    while (!ifs.eof()){
        getline(ifs, table_name, '\n');
        if (!ifs.eof()){
            workingptr->next = new Table (ifs, table_name);
            workingptr = workingptr->next;
        }
    }
    workingptr->next = nullptr;
    ifs.close();
}

Database::~Database(){
    Table* tableptr1 = this->tableHead;
    Table* tableptr2 = this->tableHead;
    if (tableptr1 == nullptr) return;
    //Field* workingptr1 = tableptr1->getFieldHead();
    //Field* workingptr2 = tableptr1->getFieldHead();
    while (tableptr1 != nullptr){
        tableptr1 = tableptr1->next;
        //if (workingptr1 == nullptr) return;
        /* while (workingptr1 != nullptr){
            workingptr1 = workingptr1->next;
            delete [] workingptr2->column;
            delete workingptr2;
            workingptr2 = workingptr1;
        } */
        delete tableptr2;
        tableptr2 = tableptr1;
    }
    //tableptr1 = nullptr; tableptr2 = nullptr;
}

bool Database::addTable(Table *table){
    if (table == nullptr) {
        cout << "Table is a null pointer.\n";
        return false;
    }
    Table* tableptr = this->tableHead; Table* workingptr = this->tableHead;
    while (tableptr != nullptr){
        if (tableptr->getName() == table->getName()){
            cout << "Table with given name already exists in the database.\n";
            return false;
        }
        workingptr = tableptr;
        tableptr = tableptr->next;
    }

    if (this->tableHead != nullptr) workingptr->next = table;
    else this->tableHead = table;  //working pointer is nullptr and is not moving -> no tables
    table->next = nullptr;
    this->numTables++;
    return true;
}

void Database::addTable(const String &name){
    Table* tableptr1 = this->tableHead;
    Table* tableptr2 = this->tableHead;
    while (tableptr1 != nullptr){
        if (tableptr1->getName() == name){
            cout << "Table with given name already exists in the database.\n";
            return;
        }
        tableptr2 = tableptr1;
        tableptr1 = tableptr1->next;
    }

    if (tableptr2 != nullptr) {
        tableptr2->next = new Table (name);
        tableptr2->next->next = nullptr;
    }
    else {
        this->tableHead = new Table (name);
        this->tableHead->next = nullptr;
    }
    //tableptr2->next->next = nullptr;
    this->numTables++;
}

Table* Database::findTable(const String &name) const {
    Table* tableptr = this->tableHead;
    while (tableptr != nullptr){
        if (tableptr->getName() == name) return tableptr;
        tableptr = tableptr->next;
    }
    return tableptr;
}

void Database::listTables() const {
    Table* tableptr = this->tableHead;
    cout << "The tables currently existing in the database are:\n";
    while (tableptr != nullptr){
        cout << tableptr->getName() << '\n';
        tableptr = tableptr->next;
    }
}

void Database::deleteTable(const String &name){
    bool found = false;
    Table* tableptr1 = this->tableHead; Table* tableptr2 = this->tableHead;
    while (tableptr1 != nullptr){
        if (tableptr1->getName() == name){
            found = true;
            break;
        }
        tableptr2 = tableptr1;
        tableptr1 = tableptr1->next;
    }
    if (!found){
        cout << "No such table exists in the database.\n";
        return;
    }
    else if (this->numTables == 1) this->tableHead = nullptr;
    else if (this->numTables != 1 && tableptr1 != tableptr2) tableptr2->next = tableptr1->next;
    else if (this->numTables != 1 && tableptr1 == tableptr2) this->tableHead = tableptr1->next;
    //(*tableptr1).~Table();
    delete tableptr1;
    this->numTables--;
}

void Database::setCurrentTable(const String &name){
    Table* tableptr = this->tableHead;
    bool found = false;
    while (tableptr != nullptr){
        if (tableptr->getName() == name){
            found = true;
            break;
        }
        tableptr = tableptr->next;
    }
    if (!found){
        cout << "No such table exists in the database.\n";
        this->currentTable = nullptr;
        return;
    }
    this->currentTable = tableptr;
}

void Database::saveDatabase(const String &filename) const{
    ofstream ofs (filename.getStr());
    ofs << this->name << '\n';
    ofs << this->numTables << '\n';

    Table* tableptr = this->tableHead;
    Field* fieldptr; String* columnptr;
/*     if (tableptr->getNumRows() != 0) {
        fieldptr = tableptr->getFieldHead();
        columnptr = fieldptr->column;
    } */

    while (tableptr != nullptr){
        ofs << tableptr->getName() << '\n';
        ofs << tableptr->getNumCols() << '\n' << tableptr->getNumRows() << '\n';
        if (tableptr->getNumCols() > 0) { //some fields, possibly no record
            fieldptr = tableptr->getFieldHead();
            columnptr = fieldptr->column;
        }
        else { //no fields, definitely no record
            tableptr = tableptr->next;
            continue;
        }
        while (fieldptr != nullptr){
            if (fieldptr == tableptr->getPrimaryKey()){
                ofs << "*";
            }
            ofs << fieldptr->name << " " << fieldptr->type;
            if (fieldptr->next != nullptr) ofs << ", ";
            else ofs << '\n';
            fieldptr = fieldptr->next;
        }
        if (tableptr->getNumRows() > 0) fieldptr = tableptr->getFieldHead();
        else {
            tableptr = tableptr->next;
            continue; //no records
        }
        for (int i = 0; i < tableptr->getNumRows(); i++){
            for (int j = 0; j < tableptr->getNumCols(); j++){
                ofs << *(columnptr + i);
                if (fieldptr->next != nullptr){
                    ofs << ", ";
                    fieldptr = fieldptr->next;
                    columnptr = fieldptr->column;
                }
                else {
                    ofs << '\n';
                    fieldptr = tableptr->getFieldHead();
                    columnptr = fieldptr->column;
                }
            }
        }
        tableptr = tableptr->next;
    }
    ofs.close();
}

void Database::innerJoin(Table* table1, Table* table2){
    //orz
    if (table1 == nullptr || table2 == nullptr){
        cout << "No such table exists in the database.\n";
        return;
    }
    if (table1->getPrimaryKey()->type != table2->getPrimaryKey()->type){
        cout << "Type mismatch between target fields.\n";
        return;
    }

    //key field
    String inner_name = table1->getName() + "+" + table2->getName();
    String key_name = table1->getPrimaryKey()->name + "+" + table2->getPrimaryKey()->name;
    Table* innerptr = new Table (inner_name);
    this->addTable(innerptr);
    innerptr->addField(0, key_name, table1->getPrimaryKey()->type);

    String* columnptr1 = table1->getPrimaryKey()->column; String* columnptr2 = table2->getPrimaryKey()->column;
    for (int i = 0; i < table1->getNumRows(); i++){
        for (int j = 0; j < table2->getNumRows(); j++){
            if (*(columnptr1 + i) != *(columnptr2 + j)) continue;
            else {
                innerptr->addRecord(innerptr->getNumRows(), (columnptr1 + i));
                break;
            }
        }
    }

    //table1
    Field* workingptr1 = table1->getFieldHead(); Field* workingptr2 = table2->getFieldHead();
    int col_index = 0;
    for (int i = 0; i < table1->getNumCols(); i++){
        if (workingptr1 == table1->getPrimaryKey()){
            workingptr1 = workingptr1->next; col_index++;
            continue;
        }
        innerptr->addField(innerptr->getNumCols(), workingptr1->name, workingptr1->type);
        String* keyptr = innerptr->getPrimaryKey()->column;
        for (int j = 0; j < innerptr->getNumRows(); j++){
            for (int k = 0; k < table1->getNumRows(); k++){
                if (*(keyptr + j) != *(columnptr1 + k)){
                    continue;
                }
                else {
                    innerptr->modifyRecord(j, innerptr->getNumCols() - 1, (*table1)[i][k]);
                    break;
                }
            }
        }
        workingptr1 = workingptr1->next;

    }
    
    //table2
    workingptr1 = table1->getFieldHead();
    String t2_name;
    bool duplicate = false;
    for (int i = 0; i < table2->getNumCols(); i++){
        if (workingptr2 == table2->getPrimaryKey()){
            workingptr2 = workingptr2->next;
            continue;
        }
        for (int j = 0; j < table1->getNumCols(); j++){
            //if (workingptr1 == table1->getPrimaryKey()) workingptr1 = workingptr1->next; //skip comparison with key field 
            if (workingptr2->name == workingptr1->name){
                t2_name = workingptr2->name + "(T2)";
                duplicate = true;
                break;
            }
            workingptr1 = workingptr1->next;
            
        }
        workingptr1 = table1->getFieldHead();
        if (duplicate) {
            innerptr->addField(innerptr->getNumCols(), t2_name, workingptr2->type);
            duplicate = false;
        }
        else innerptr->addField(innerptr->getNumCols(), workingptr2->name, workingptr2->type);
        
        
        String* keyptr2 = innerptr->getPrimaryKey()->column;
        for (int j = 0; j < innerptr->getNumRows(); j++){
            for (int k = 0; k < table2->getNumRows(); k++){
                if (*(keyptr2 + j) != *(columnptr2 + k)){
                    continue;
                }
                else {
                    innerptr->modifyRecord(j, innerptr->getNumCols() - 1, (*table2)[i][k]);
                    break;
                }
            }
        }

        workingptr2 = workingptr2->next;
    }

    
}

/*
find primary keys of both tables, do validity check
create an empty table, add one field which is the merged primary key field
    of the original two tables
use a (nested) loop to find all matching keys,
    modify record in the key column of the new table
get the remaining fields of table1 and table2, respectively,
    and add them as new fields to the new table
get the corresponding record in those fields and
    modify the records in the new table accordingly

*/