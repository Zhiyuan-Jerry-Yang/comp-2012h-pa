#include <fstream>
#include "Table.h"
#include "String.h"

using namespace std;



/////         11/10/2022: addField problematic
////// 12/10/2022 modification at line 371
////////////                           195
  



bool isInteger(const String &test)
{
    if (!test.length())
        return false;

    if (test[0] != '-' && !isdigit(test[0]))
        return false;

    for (int i = 1; i < test.length(); ++i)
    {
        if (!isdigit(test[i]))
            return false;
    }
    return true;
}

String *Table::operator[](int index) const
{

    if (index >= numCols || index < 0)
    {
        cout << "Table column index is out of bounds." << endl;
        return nullptr;
    }

    Field *cur = fieldHead;
    for (int count = 0; count < index; cur = cur->next, ++count)
        ;
    return cur->column;
}

Table::Table(const String &name){
    this->primaryKey = nullptr;
    this->fieldHead = nullptr;
    this->next = nullptr;
    this->numRows = 0; this->numCols = 0; this->tableSize = 100;
    this->name = name;
}

Table::Table(ifstream &ifs, const String &name){
    this->name = name;
    this->primaryKey = nullptr;
    this->fieldHead = nullptr;
    this->next = nullptr;
    this->tableSize = 100;
    String this_line, fields, records;
/*     getline(ifs, this_line, '\n');
    while (this_line != name) {
        getline(ifs, this_line, '\n');
    } */

    getline(ifs, this_line, '\n');
    this->numCols = stoi(this_line);
    getline(ifs, this_line, '\n');
    this->numRows = stoi(this_line);

    if (this->numRows != 0 && this->numCols != 0){
        getline(ifs, fields, '\n');
        Field* fieldptr = new Field;
        this->fieldHead = fieldptr;
        this->fieldHead->column = new String[tableSize];
        for (int i = 1; i < numCols; i++){
            fieldptr->next = new Field;
            fieldptr = fieldptr->next;
            fieldptr->column = new String[tableSize];   
        }
        fieldptr->next = nullptr;

        fieldptr = this->fieldHead;
        int count = 0, begin = 0;
        for (int i = 0; ; i++){
            if ((fields[i + 1] == '0' || fields[i + 1] == '1') && fields[i] == ' '){
                if (fields[i + 1] == '0') fieldptr->type = INT;
                else fieldptr->type = STRING;
                fieldptr->name = fields.substr(begin, count);
                if (fields[i + 2] == '\0') break;
                fieldptr = fieldptr->next;
                begin += (count + 4);
                count = 0;
                i += 3;
            }
            else if (fields[i] == '*'){
                begin++;
                this->primaryKey = fieldptr;
            }
            else count++;
        }

        
        String* strptr;
        
        for (int j = 0; j < this->numRows; j++){
            count = 0; begin = 0;
            getline(ifs, records, '\n');
            fieldptr = fieldHead;
            strptr = fieldptr->column + j;
            for (int k = 0; ; k++){
                if ((records[k] == ',' && records[k + 1] == ' ') || records[k] == '\0'){
                    
                    *strptr = records.substr(begin, count);
                    if (records[k] == '\0') break;
                    fieldptr = fieldptr->next;
                    strptr = fieldptr->column + j;
                    begin += (count + 2);
                    count = 0;
                    k++;
                }
                else count++;
            }
        }
    }
}

Table::~Table(){
    Field* workingptr1 = this->fieldHead;
    Field* workingptr2 = this->fieldHead;
    if (workingptr1 == nullptr) return;
    while (workingptr1 != nullptr){
        workingptr1 = workingptr1->next;
        if (workingptr2->column != nullptr) delete [] workingptr2->column;
        delete workingptr2;
        workingptr2 = workingptr1;
    }
}

void Table::addRecord(int index, String *record){
    Field* fieldptr = this->fieldHead;
    String* strptr = record; String* columnptr;
    if (this->numRows != 0) columnptr = fieldptr->column + this->numRows - 1;
    else columnptr = fieldptr->column;

    if (record == nullptr){
        cout << "Record is empty.\n";
        return;
    }
    if (index > this->numRows || index < 0){
        cout << "Table row index is out of bounds.\n";
        return;
    }

    while (fieldptr != this->primaryKey){
        fieldptr = fieldptr->next;
        strptr++;
    }
    //now *strptr holds the value corresponding to the primary key field of the table
    if (*strptr == "") {
        cout << "Empty or duplicate primary key.\n";
        return;
    }
    else if (*strptr != ""){
        for (int i = 0; i < this->numRows; i++){
            if (*strptr == this->primaryKey->column[i]){
                cout << "Empty or duplicate primary key.\n";
                return;
            }
        }
    }
    fieldptr = fieldHead;
    strptr = record;
    for (int i = 0; i < this->numCols; i++){
        if (fieldptr->type == INT && !isInteger(*strptr)){
            cout << "Cannot insert non-integer in integer field.\n";
            return;
        }
        fieldptr = fieldptr->next;
        strptr++;
    }

    fieldptr = fieldHead;

    

    if (index != this->numRows ){
       
        for (int i = 0; i < this->numCols; i++){
            for (int j = this->numRows - 1; j >= index; j--){
                *(columnptr + 1) = *(columnptr);
                if (j != index) columnptr--;
            }
            *(columnptr) = *(record + i);
            fieldptr = fieldptr->next;
            if (fieldptr != nullptr) columnptr = fieldptr->column + this->numRows - 1;
        }
    }
    else {
        if (this->numRows != 0) columnptr++;        
        for (int i = 0; i < this->numCols; i++){
            *(columnptr) = *(record + i);

            fieldptr = fieldptr->next;
            if (fieldptr != nullptr) columnptr = fieldptr->column + this->numRows;
        }
    }
    
    this->numRows++;
    if (this->numRows == this->tableSize){
        fieldptr = fieldHead;
        for (int k = 0; k < this->numCols; k++){
            String* new_strptr = new String[this->tableSize + 100];
            this->tableSize += 100;
            for (int m = 0; m < this->numRows; m++){
                *(new_strptr + m) = *(fieldptr->column + m);
            }
            delete [] fieldptr->column;
            fieldptr->column = new_strptr;
            new_strptr = nullptr;
        }
    }
}

void Table::addField(int index, const String &name, TYPE type){ 
    if (index > this->numCols || index < 0){
        cout << "Table column index is out of bounds.\n";
        return;
    }
    for (Field* fieldptr = this->fieldHead; fieldptr != nullptr; fieldptr = fieldptr->next){
        if (fieldptr->name == name){
            cout << "Field with given name already exists in table.\n";
            return;
        }
    }
    Field* new_fieldptr = new Field; Field* fieldptr = this->fieldHead;
    new_fieldptr->name = name;
    new_fieldptr->type = type;
    new_fieldptr->column = new String[this->numRows];
    
    this->numCols++;

    if (this->numCols == 1) this->primaryKey = new_fieldptr;

    for (int i = 0; i < index - 1; i++) fieldptr = fieldptr->next;

    if (index > 0 && index < this->numCols){
        new_fieldptr->next = fieldptr->next;
        fieldptr->next = new_fieldptr;
    }
    else if (index == 0){
        new_fieldptr->next = fieldptr;
        this->fieldHead = new_fieldptr;
    }
    else if (index == this->numCols){
        fieldptr->next = new_fieldptr;
        new_fieldptr->next = nullptr;
    }

    if (type == INT){
        for (int i = 0; i < this->numRows; i++){
            *(new_fieldptr->column + i) = "0";
        }
    }
    else {
        for (int i = 0; i < this->numRows; i++){
            *(new_fieldptr->column + i) = "";
        }
    }
}

void Table::deleteRecord(int row){
    if (row >= this->numRows || row < 0){
        cout << "Table row index is out of bounds.\n";
        return;
    }
    Field* fieldptr = this->fieldHead;
    if (row != this->numRows - 1){
        String* columnptr = fieldptr->column + row + 1;
        for (int i = 0; i < this->numCols; i++){
            for (int j = row + 1; j < this->numRows; j++){
                *(columnptr - 1) = *(columnptr);
                /* if (i != this->numRows - 1)  */columnptr++;
            }
            fieldptr = fieldptr->next;
            if (fieldptr != nullptr) columnptr = fieldptr->column + row + 1;
        }
    }
    this->numRows--;
}

void Table::modifyRecord(int row, int column, const String &newVal){
    if (row >= this->numRows || row < 0){
        cout << "Table row index is out of bounds.\n";
        return;
    }
    if (column >= this->numCols || column < 0){
        cout << "Table column index is out of bounds.\n";
        return;
    }

    Field* fieldptr = this->fieldHead;
    for (int i = 0; i < column; i++) fieldptr = fieldptr->next;
    if (fieldptr == this->primaryKey){
        if (newVal == ""){
            cout << "Empty or duplicate primary key.\n";
            return;
        }
        String* columnptr = fieldptr->column;
        for (int i = 0; i < this->numRows; i++){
            if (i == row) {
                columnptr++;
                continue;
            }
            if (*columnptr == newVal){
                cout << "Empty or duplicate primary key.\n";
                return;
            }
            else columnptr++;
        }
    }
    if (!isInteger(newVal) && (fieldptr->type == INT)){
        cout << "Cannot insert non-integer in integer field.\n";
        return;
    }

    (*this)[column][row] = newVal;
}

void Table::setPrimaryKey(const String &name){
    bool found = false;
    Field* primaryptr = nullptr;
    for(Field* fieldptr = this->fieldHead; fieldptr != nullptr; fieldptr = fieldptr->next){
        if (fieldptr->name == name) {
            found = true;
            primaryptr = fieldptr;
        }
    }
    if (!found){
        cout << "No such field with provided name exists.\n";
        return;
    }
    else{
        String* columnptr = primaryptr->column; String* recordptr = primaryptr->column;
        for (int i = 0; i < this->numRows - 1; i++){
            for (int j = i + 1; j < this->numRows; j++){
                if (*(columnptr + j) == *recordptr){
                    cout << "Cannot set field with duplicate elements as primary key.\n";
                    return;
                }
            }
        }
        columnptr = primaryptr->column;
        for (int k = 0; k < numRows; k++){
            if (*(columnptr + k) == ""){
                cout << "Cannot set field with empty data as primary key.\n";
                return;
            }
        }
    }

    this->primaryKey = primaryptr;
}

void Table::setColumnIndex(int index, const String &target){
    bool found = false; int col_idx = 0;
    Field* fieldptr1 = this->fieldHead; Field* fieldptr2 = this->fieldHead;
    for (int j = 0; j < this->numCols; j++){
        if (fieldptr1->name != target){
            fieldptr2 = fieldptr1;
        }
        else if (fieldptr1->name == target) {
            found = true;
            break;
        }
        fieldptr1 = fieldptr1->next;
        col_idx++;
    }
    if (!found){
        cout << "No such field with provided name exists.\n";
        return;
    }
    if (index >= this->numCols || index < 0){
        cout << "Table column index is out of bounds.\n";
        return;
    }

    Field* idxptr1 = this->fieldHead; Field* idxptr2 = this->fieldHead;
    for (int i = 0; i < index; i++){
        idxptr1 = idxptr1->next;
        if (i != index - 1) idxptr2 = idxptr2->next;
    }

    if (fieldptr1 == fieldptr2 && index != 0){
        this->fieldHead = fieldptr1->next;
        fieldptr1->next = idxptr1->next;
        idxptr1->next = fieldptr1;

        /* fieldptr2->next = fieldptr1->next;
        fieldptr1->next = workingptr->next;
        workingptr->next = fieldptr1; */
    }
    else if (index == col_idx){;}
    else if (fieldptr1 != fieldptr2 && index == 0){
        fieldptr2->next = fieldptr1->next;
        fieldptr1->next = this->fieldHead;
        this->fieldHead = fieldptr1;

    }
    else if (index > col_idx){
        fieldptr2->next = fieldptr1->next;
        fieldptr1->next = idxptr1->next;
        idxptr1->next = fieldptr1;
    }
    else if (index < col_idx){
        fieldptr2->next = fieldptr1->next;
        fieldptr1->next = idxptr2->next;
        idxptr2->next = fieldptr1;
    }

}

void Table::deleteField(const String &name){
    bool found = false;
    Field* fieldptr1 = this->fieldHead; Field* fieldptr2 = this->fieldHead;
    for (int j = 0; j < this->numCols; j++){
        if (fieldptr1->name != name){
            fieldptr2 = fieldptr1;
        }
        else if (fieldptr1->name == name) {
            found = true;
            break;
        }
        fieldptr1 = fieldptr1->next;
    }
    if (!found){
        cout << "No such field with provided name exists.\n";
        return;
    }
    else if (fieldptr1 == this->primaryKey){
        cout << "Cannot delete primary key field.\n";
        return;
    }

    if (fieldptr1 != this->fieldHead) fieldptr2->next = fieldptr1->next;
    else this->fieldHead = fieldptr1->next;
    delete [] fieldptr1->column;
    delete fieldptr1;
    this->numCols--;
    fieldptr1 = nullptr; fieldptr2 = nullptr;
}

Field* Table::findField(const String &name) const {
    bool found = false;
    Field* fieldptr = this->fieldHead;
    for (int i = 0; i < this->numCols; i++){
        if (fieldptr->name == name){
            found = true;
            break;
        }
        fieldptr = fieldptr->next;
    }
    if (!found){
        cout << "No such field with provided name exists.\n";
        return nullptr;
    }
    return fieldptr;
}

void Table::sortTable(Field* field){
    if (field == nullptr){
        cout << "Invalid field provided.\n";
        return;
    }

    if (this->numRows == 1) return;

    Field* workingptr = this->fieldHead;
    String* workingptr1 = this->fieldHead->column; String* workingptr2 = this->fieldHead->column + 1;
    String temp;

    String* columnptr1 = field->column; String* columnptr2 = field->column + 1;
    
    if (field->type == INT){
        for (int i = 0; i < this->numRows - 1; i++){
            columnptr1 = field->column; columnptr2 = field->column + 1;
            workingptr1 = workingptr->column; workingptr2 = workingptr->column+ 1;
            for (int j = 0; j < this->numRows - 1 - i; j++){
                if (stoi(*columnptr1) > stoi(*columnptr2)) {
                    for (int k = 0; k < this->numCols; k++){
                        temp = *(workingptr1);
                        *(workingptr1) = *(workingptr2);
                        *(workingptr2) = temp;
                        workingptr = workingptr->next;
                        if (workingptr != nullptr){
                        workingptr1 = workingptr->column + j;
                        workingptr2 = workingptr->column + j + 1;
                        }
                    }
                    workingptr = this->fieldHead;
                    workingptr1 = workingptr->column + j; workingptr2 = workingptr->column + j + 1;
                }
                columnptr1++; columnptr2++; workingptr1++; workingptr2++;
                
            }
        }
    }
    else if (field->type == STRING){
        for (int i = 0; i < this->numRows - 1; i++){
            columnptr1 = field->column; columnptr2 = field->column + 1;
            workingptr1 = workingptr->column; workingptr2 = workingptr->column+ 1;
            for (int j = 0; j < this->numRows - 1 - i; j++){
                if (*columnptr1 > *columnptr2) {
                    for (int k = 0; k < this->numCols; k++){
                        temp = *(workingptr1);
                        *(workingptr1) = *(workingptr2);
                        *(workingptr2) = temp;
                        workingptr = workingptr->next;
                        if (workingptr != nullptr){
                        workingptr1 = workingptr->column + j;
                        workingptr2 = workingptr->column + j + 1;
                        }
                    }
                    workingptr = this->fieldHead;
                    workingptr1 = workingptr->column + j; workingptr2 = workingptr->column + j + 1;
                }
                columnptr1++; columnptr2++; workingptr1++; workingptr2++;
                
            }
        }
    }

}