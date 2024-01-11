#include <iostream>
using namespace std;

// some constraints for board
const int MAX_ROW = 15, MAX_COL = 15;
const int MAX_CONSTRAINT_NUM = 15;  // constraint cannot exceed MAX_ROW/MAX_COL

// board and its size
int num_rows = 0, num_cols = 0;
char board[MAX_ROW][MAX_COL] = {{0}};

// constraints and their sizes
int num_row_constraints[MAX_ROW] = {0}, num_col_constraints[MAX_COL] = {0};
int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM] = {{0}};
int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM] = {{0}};

/**********************************
 * Part 1: Initialize the board   *
 **********************************/

/**
 **********  Task 1  **********
 *
 * This function reads the board size and constraints from user input,
 * store the information in global variables and init the board.
 *
 * Don't forget to check whether row/column constraints are valid.
 * Please refer to webpage for a detailed description.
 *
 * For simplicity, we assume the user's other inputs are always valid.
 */

bool is_valid(const int arr[], int num_cols_rows){
    //for task 1
    int i = 0, total = 0;
    if (arr[0] == -1) return true;
    while (arr[i] != -1){
        total += arr[i];
        if (arr[i + 1] != -1) total++;
        i++;
    }
    return total <= num_cols_rows;
}

int get_max_length(const int arr[][MAX_CONSTRAINT_NUM]){
    //for task 2
    int i = 0, j = 0, length = 0, largest = 0;
    while (i < num_rows){
        length = 0;
        while (arr[i][j] != 0) {
            length++;
            j++;
        }
        //if (arr[i][0] == 0) length = 0;
        if (length > largest) largest = length;
        i++;
        j = 0;
    }
    return largest;
}

int get_curr_length(const int arr[][MAX_CONSTRAINT_NUM], int i){
    //for task 2, 4
    if (arr[i][0] == 0) return 0;
    int counter = 0;
    for (int j = 0; arr[i][j] != 0 && j < MAX_COL; j++) counter++;
    return counter;
}

int get_char_length(const char board[][MAX_CONSTRAINT_NUM], int i){
    //for the helper of task 4
    if (board[i][0] == 0) return 0;
    int counter = 0;
    for (int j = 0; board[i][j] != 0 && j < MAX_COL; j++) counter++;
    return counter;
}

int get_char_length(const char arr[]){
    if (arr[0] == 0) return 0;
    int counter = 0;
    for (int j = 0; arr[j] != 0 && j < MAX_COL; j++) counter++;
    return counter;
}

bool all_zero_one(const int arr[][MAX_CONSTRAINT_NUM], int j, int num){
    //for task 2. Check whether the only element in a row of the column constraint is 0.
    int i = 0;
    while (i < MAX_CONSTRAINT_NUM){
        if (arr[i][j] != num) return false;
        i++;
    }
    return true;
}


int get_x_coordinate(char input1, const char upper_case[]){
    //for task 3
    int i = 0;
    while (upper_case[i] != input1) i++;
    return i;
}

void update_board(int x_coor, int y_coor) {
    //for task 3. update the board accoding to a valid input
    if (board[y_coor][x_coor] == '.') board[y_coor][x_coor] = 'X';
    else if (board[y_coor][x_coor] == 'X') board[y_coor][x_coor] = '.';
}

bool check_row(const char board[][MAX_CONSTRAINT_NUM], const int row_constraints[][MAX_CONSTRAINT_NUM], int num_row=0){
    //the array row_contraint is a copy of a specific row of the global array row_constraints and is to be modified
    //inside this function
/*     int row_constraint[MAX_CONSTRAINT_NUM] = {};
    for (int i = 0; i < num_row_constraints[num_row]; i++){
        row_constraint[i] = row_constraints[num_row][i];
    } */

    //int row_length = get_char_length(board, num_row);
    if (row_constraints[num_row][0] == 0) {
        for (int i = 0; i < num_cols; i++) {
            if (board[num_row][i] != '.') return false;
        }
        return true;
    }
    else {
        int i = 0, a = 0, b = 0;
        int this_block = 0;
        while (true){
            while (board[num_row][i + a] == '.') a++;
            if (board[num_row][i + a] == 0 || i >= num_cols) return false;
            while ((board[num_row][i + a] == 'X') && (i + a < num_cols)){
                this_block++;
                if (this_block > row_constraints[num_row][b]) {
                    return false;
                }
                a++;

            }
            if (this_block < row_constraints[num_row][b]){
                return false;
            }
            else if (this_block == row_constraints[num_row][b] && (board[num_row][i + a] != 'X' || (i + a >= num_cols))){
                if (b < num_row_constraints[num_row] - 1 && board[num_row][i + a] == '.'){
                    b++;
                    this_block = 0;
                }
                else if (b == num_row_constraints[num_row] - 1){
                    while (board[num_row][i + a] == '.' && ((i + a) < num_cols)) a++;
                    if ((board[num_row][i + a] == 0) || ((i + a) == num_cols)) return true;
                    else if (board[num_row][i + a] == 'X') return false;
                }
            }
        }
    }
}

bool check_row(char this_row[], const int row_constraints[][MAX_CONSTRAINT_NUM], int num_row){
    //for task 6, an overloaded function
/*     int row_constraint[MAX_CONSTRAINT_NUM] = {};
    for (int i = 0; i < num_row_constraints[num_row]; i++){
        row_constraint[i] = row_constraints[num_row][i];
    } //make a copy of the constraints of this row */

    //int row_length = get_char_length(this_row); //call the overloaded version
    if (row_constraints[num_row][0] == 0) {
        for (int i = 0; i < num_cols; i++) {
            if (this_row[i] != '.') return false;
        }
        return true;
    }
    else {
        int i = 0, a = 0, b = 0;
        int this_block = 0;
        while (true){
            while (this_row[i + a] == '.') a++;
            if (this_row[i + a] == 0 || i + a >= num_cols) return false;
            while (this_row[i + a] == 'X'){
                this_block++;
                if (this_block > row_constraints[num_row][b]) {
                    return false;
                }
                a++;

            }
            if (this_block < row_constraints[num_row][b]){
                return false;
            }
            else if (this_block == row_constraints[num_row][b] && (this_row[i + a] != 'X' || (i + a) >= num_cols)){
                if (b < num_row_constraints[num_row] - 1 && this_row[i + a] == '.'){
                    b++;
                    this_block = 0;
                }
                else if (b == num_row_constraints[num_row] - 1){
                    while (this_row[i + a] == '.' && ((i + a) < num_cols)) a++;
                    if ((this_row[i + a] == 0) || ((i + a) >= num_cols)) return true;
                    else if (this_row[i + a] == 'X') return false;
                }
            }
        }
    }
}


bool check_column(const char board[][MAX_CONSTRAINT_NUM], const int col_constraints[][MAX_CONSTRAINT_NUM], int num_col=0){
    //for task 4
/*     char this_column[MAX_CONSTRAINT_NUM] = {};
    for (int i = 0; i < num_rows; i++){
        this_column[i] = board[i][num_col];
    } */

/*     int col_constraint[MAX_CONSTRAINT_NUM] = {};
    for (int i = 0; i < num_rows; i++){
        col_constraint[i] = col_constraints[num_col][i];
    } */

    //int col_length = get_char_length(this_column);
    if (col_constraints[num_col][0] == 0) {
        for (int i = 0; i < num_rows; i++) {
            if (board[i][num_col] != '.') return false;
        }
        return true;
    }
    else {
        int i = 0, a = 0, b = 0;
        int this_block = 0;
        while (true){
            while (board[i + a][num_col] == '.') a++;
            if (board[i + a][num_col] == 0 || i + a >= num_rows) return false;
            while ((board[i + a][num_col] == 'X') && (i + a < num_rows)){
                this_block++;
                if (this_block > col_constraints[num_col][b]) {
                    return false;
                }
                a++;

            }
            if (this_block < col_constraints[num_col][b]){
                return false;
            }
            else if (this_block == col_constraints[num_col][b] && (board[i + a][num_col] != 'X' || (i + a >= num_rows))){
                if (b < num_col_constraints[num_col] - 1 && board[i + a][num_col] == '.'){
                    b++;
                    this_block = 0;
                }
                else if (b == num_col_constraints[num_col] - 1){
                    while (board[i + a][num_col] == '.' && ((i + a) < num_rows)) a++;
                    if ((board[i + a][num_col] == 0) || ((i + a) == num_rows)) return true;
                    else if (board[i + a][num_col] == 'X') return false;
                }
            }
        }
    }
}

void get_input_board() {
    // START YOUR CODES HERE
    cout << "Enter the number of rows: ";
    cin >> num_rows;
    cout << "Enter the number of columns: ";
    cin >> num_cols;
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            board[i][j] = '.';
        }
    }
    int row_input = 0, col_input = 0, i = 0, j = 0, x = 0, y = 0, counter = 0;
    int row_temp[MAX_ROW] = {};
    int col_temp[MAX_COL] = {};
    cout << "Enter the number of constraints for row " << i << " (end with -1): ";
    while (cin >> row_input){
        row_temp[j] = row_input;
        j++;
        num_row_constraints[i]++;
        if (row_input == -1){
            num_row_constraints[i]--;
            if (!is_valid(row_temp, num_cols)){
            j = 0; num_row_constraints[i] = 0;
            cout << "Invalid row constraint, please try again." << endl;
            cout << "Enter the number of constraints for row " << i << " (end with -1): ";
            continue;
            }
            else {
                if (row_temp[0] == -1) {
                    row_constraints[i][0] = 0;
                    //cout << endl << "num_row_constraints[" << x << "] is " << num_row_constraints[i] << endl;
                }
                else {
                    int k = 0;
                    while (row_temp[k] != -1){
                        row_constraints[i][k] = row_temp[k];
                        k++;
                    }


                }

                //cout << endl << "num_row_constraints[" << i << "] is " << num_row_constraints[i] << endl;


                if (i + 1 < num_rows){
                    i++;
                    j = 0;
                    //for (int i = 0; i < MAX_COL; i++) row_temp[i] = 0;
                    cout << "Enter the number of constraints for row " << i << " (end with -1): ";
                    continue;
                }
                else break;
            }
        }
    }

    cout << "Enter the number of constraints for column " << x << " (end with -1): ";
    while (cin >> col_input){
        col_temp[y] = col_input;
        y++;
        num_col_constraints[x]++;
        if (col_input == -1){
            num_col_constraints[x]--;
            if (!is_valid(col_temp, num_rows)){
                y = 0; num_col_constraints[x] = 0;
                cout << "Invalid row constraint, please try again." << endl;
                cout << "Enter the number of constraints for column " << x << " (end with -1): ";
                continue;
            }
            else {
                int m = 0;
                if (col_temp[0] == -1) {
                    col_constraints[x][0] = 0;
                    //cout << endl << "num_col_constraints[" << x << "] is " << num_col_constraints[i] << endl;
                }
                else{
                    while (col_temp[m] != -1){
                        col_constraints[x][m] = col_temp[m];
                        m++;
                    }

                }


                //cout << endl << "num_col_constraints[" << x << "] is " << num_col_constraints[x] << endl;


                if (x + 1 < num_cols){
                    x++;
                    y = 0;
                    //for (int i = 0; i < MAX_ROW; i++) col_temp[i] = 0;
                    cout << "Enter the number of constraints for column " << x << " (end with -1): ";
                    continue;
                }
                else break;
            }
        }
    }
    // END YOUR CODES HERE
}


/**
 **********  Task 2  **********
 *
 * This function prints the board and the constraints for each row and column.
 * Constraints should be printed on the bottom of each column and on the left of each row.
 *
 * You may find an example in webpage.
 */
void print_board() {
    // START YOUR CODES HERE
    const char upper_case[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O'};
    int max_length = get_max_length(row_constraints);
    int num_spaces = 0;
    for (int i = 0; i < max_length; i++) cout << "  ";
    cout << "     ";
    for (int i = 0; i < num_cols; i++){
        cout << upper_case[i] << " ";
    }
    cout << endl;
    int i = 0, j = 0;
    while (i < num_rows){
        int curr_length = get_curr_length(row_constraints, i);
        num_spaces = max_length - curr_length;
        for (int k = 0; k < num_spaces; k++) cout << "  ";
        if (row_constraints[i][0] != 0){
            while (j < num_row_constraints[i] ){
                cout << row_constraints[i][j] << " ";
                j++;
            }
        }
        cout << "| ";
        if (i < 10) cout << " ";
        cout << i << " ";
        for (int m = 0; m < num_cols; m++) {
            cout << board[i][m] << " ";
        }
        cout << endl;
        i++;
        j = 0;
    }

    int a = 0, b = 0;
    while ((!all_zero_one(col_constraints, b, 0)) /* && (!all_zero_one(col_constraints, b, 1)) */){
        for (int i = 0; i < max_length; i++) cout << "  ";
        cout << "     "; //5 spaces
        while (a < num_cols){
            if (col_constraints[a][b] > 0) cout << col_constraints[a][b] << " ";
            else cout << "  "; //2 spaces
            a++;
        }
        cout << endl;
        b++;
        a = 0;
    }
    // END YOUR CODES HERE
}


/********************************
 * Part 2: User play on board   *
 ********************************/

/**
 **********  Task 3  **********
 *
 * This function will be called when user choose to set/unset a cell.
 *
 * You need to:
 * 1. Ask user to input which cell he/she wants to modify
 * 2. Check if the user input is a valid cell(i.e., it is within the board)
 *    If invalid, keep asking the user to input.
 * 3. Set/unset the cell
 * 4. Print the new board
 */
void user_operate_board() {
    // START YOUR CODES HERE
    char input1;
    int input2;
    const char upper_case[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O'};
    char max_column = upper_case[num_cols - 1];
    cout << "Enter the cell you want to modify (e.g. A 2): ";
    while (cin >> input1 >> input2){
        if (input1 > max_column && input1 <= 'Z') {
            cout << "Invalid row or column. Try again." << endl;
            cout << "Enter the cell you want to modify (e.g. A 2): ";
            continue;
        }
        if (input2 < 0 || input2 > num_rows - 1){
            cout << "Invalid row or column. Try again." << endl;
            cout << "Enter the cell you want to modify (e.g. A 2): ";
            continue;
        }
        break;
    }

    int x_coor = get_x_coordinate(input1, upper_case), y_coor = input2;
    update_board(x_coor, y_coor);

    // some code snippets that you can directly copy and paste.
    /* cout << "Enter the cell you want to modify (e.g. A 2): ";
    cout << "Invalid row or column. Try again." << endl; */

    // END YOUR CODES HERE
}


/**
 **********  Task 4  **********
 *
 * This function will be called after user finish filling the whole board.
 * You need to check whether his/her solution is correct,
 * i.e., follow all constraints.
 *
 * Return true if his/her solution is correct; false otherwise.
 */
bool check_whole_board_valid() {
    // START YOUR CODES HERE

    for (int i = 0; i < num_rows; i++){
        if (!check_row(board, row_constraints, i)) return false;
    }

    for (int i = 0; i < num_cols; i++){
        if (!check_column(board, col_constraints, i)) return false;
    }
    return true;

    // END YOUR CODES HERE
}


/*******************************
 * Part 3: A nonogram solver   *
 *******************************/

/**
 **********  Task 5  **********
 *
 * This function coverts a position vector of a row into a real row.
 *
 * For example, if num_col = 8, position vector = {0, 3, 5},
 * row_constraint for this row is {2, 1, 1}, then the row should be:
 * [X X . X . X . .]
 * It will store the result row in variable 'result_row[]'
 *
 * You may assume the parameters given are always valid.
 */
void positions_to_row(int row_idx, const int positions[], int num_pos, char result_row[]) {
    // START YOUR CODES HERE
    for (int i = 0; i < num_cols; i++){
        result_row[i] = '.';
    }
    for (int i = 0; i < num_pos; i++){
        for (int j = positions[i]; j < positions[i] + row_constraints[row_idx][i]; j++){
            result_row[j] = 'X';
        }
    }
    // END YOUR CODES HERE
}


/**
 **********  Task 6  **********
 *
 * This function checks if the given block on given row can be shifted right
 * for one cell.
 * For example, if the position vector is {0, 4, 6}, num_col = 8
 * then the row is: [X X . . X . X .], and there are 3 blocks
 * then block_can_shift(row_idx, 0, {0, 4, 6}) = true,
 *      block_can_shift(row_idx, 1, {0, 4, 6}) = false, since it will hit 2nd block after shift
 *      block_can_shift(row_idx, 2, {0, 4, 6}) = true.
 *
 * More details can be found on webpage.
 */
bool block_can_shift(int row_idx, int block_idx, const int positions[], int num_pos) {
    // START YOUR CODES HERE

    if (block_idx < 0) return false;
    char this_row[MAX_CONSTRAINT_NUM] = {};
    positions_to_row(row_idx, positions, num_pos, this_row);
    this_row[positions[block_idx]] = '.';
    int a = 1; //start checking from the next position
    while ((this_row[positions[block_idx] + a] == 'X') && (positions[block_idx] + a < num_cols)) a++;
    if (positions[block_idx] + a >= num_cols) return false;
    else this_row[positions[block_idx] + a] = 'X';
    return check_row(this_row, row_constraints, row_idx);

    // END YOUR CODES HERE
}

// this array stores all valid permutations for each row
// it's expected that num of permutations for each row should not exceed 2^(num_cols)
const int MAX_PERM = 1 << MAX_COL;     // A way to calculate 2^(num_cols)
char row_perms[MAX_ROW][MAX_PERM][MAX_COL];
// this array stores num of permutations for each row
int num_row_perms[MAX_ROW] = {0};


/**
 **********  Task 7  **********
 *
 * This function gets all valid permutations for a row,
 * and store all results in global variables 'row_perms' and 'num_row_perms'.
 *
 * Hint: You may use recursion to do that, with the help of helper functions
 * 'block_can_shift()', etc.
 *
 */

void get_position(int row_idx, int positions[]){
    //for task 7
    positions[0] = 0;
    for (int i = 0; i < num_row_constraints[row_idx] - 1; i++){
        positions[i + 1] = row_constraints[row_idx][i] + positions[i] + 1;
    }
}

void print_array(const char arr[]){
    int i = 0;
    while ((arr[i] != 0) || i < num_cols) {
        cout << arr[i] << " ";
        i++;
    }
}


bool this_row_can_shift(int row_idx, int block_idx, const int positions[], int num_pos, const char this_row[]) {
    // START YOUR CODES HERE

    if (block_idx < 0) return false;
    char check_this_row[MAX_CONSTRAINT_NUM] = {};
    for (int i = 0; i < MAX_CONSTRAINT_NUM; i++){
        check_this_row[i] = this_row[i];
    }

    int a = 1; //start checking from the next position
    if (positions[block_idx] + row_constraints[row_idx][block_idx] - 1 + a < num_cols){
        check_this_row[positions[block_idx]] = '.';
        while (check_this_row[positions[block_idx] + a] == 'X' && (positions[block_idx] + a < num_cols)) a++;
        check_this_row[positions[block_idx] + a] = 'X';
        return check_row(check_this_row, row_constraints, row_idx);
    }
    else return false;

    // END YOUR CODES HERE
}


bool can_shift(int row_idx, int block_idx, const int positions[], int num_pos, char this_row[]) {

    if (block_idx < 0) return false;

    int a = 1; //start checking from the next position
    if ((positions[block_idx] + row_constraints[row_idx][block_idx] - 1 + a ) < num_cols){
        this_row[positions[block_idx]] = '.';
        while ((this_row[positions[block_idx] + a] == 'X') && (positions[block_idx] + a < num_cols)) a++;
        this_row[positions[block_idx] + a] = 'X';
        return check_row(this_row, row_constraints, row_idx);
    }
    else return false;

}

int num_shift(int row_idx, int block_idx, const int positions[], const char this_row[]){
    int counter = 0;
    char check_row[MAX_CONSTRAINT_NUM] = {};
    int check_position[MAX_CONSTRAINT_NUM] = {};
    if (block_idx < 0) {
        //cout << "num_shift for row_idx " << row_idx << " block_idx " << block_idx << ": "<< counter << endl;
        return 0;
    }
    for (int i = 0; i < MAX_CONSTRAINT_NUM; i++){
        check_row[i] = this_row[i];
    }
    for (int i = 0; i < MAX_CONSTRAINT_NUM; i++){
        check_position[i] = positions[i];
    }
    while (can_shift(row_idx, block_idx, check_position, num_row_constraints[row_idx], check_row)){
        check_position[block_idx]++;
        counter++;
    }
    //cout << "num_shift for row_idx " << row_idx << " block_idx " << block_idx << ": "<< counter << endl;
    return counter;
}

void shift_right(char this_row[], int row_idx, int num_shift, int positions[], int block_idx){
    int constraint_length = row_constraints[row_idx][block_idx];
    for (int i = positions[block_idx]; i < positions[block_idx] + constraint_length; i++){
        this_row[i] = '.';
    }
    positions[block_idx] += num_shift;
    for (int i = positions[block_idx]; i < positions[block_idx] + constraint_length; i++){
        this_row[i] = 'X';
    }

}

void shift_left(char this_row[], int row_idx, int num_shift, int positions[], int block_idx){
    int constraint_length = row_constraints[row_idx][block_idx];
    for (int i = positions[block_idx]; i < positions[block_idx] + constraint_length; i++){
        this_row[i] = '.';
    }
    positions[block_idx] -= num_shift;
    for (int i = positions[block_idx]; i < positions[block_idx] + constraint_length; i++){
        this_row[i] = 'X';
    }

}

void get_row_perms_helper(int row_idx, int positions[], int block_idx, char this_row[], int& num_perm){
    //for task 7, a helper function that uses recursion
    if (block_idx < 0){
        for (int j = 0; j < num_cols; j++){
                row_perms[row_idx][num_perm][j] = this_row[j];
            }
            num_perm++;
            num_row_perms[row_idx]++;
    }
    if (block_idx >= 0) {
        //return;
        int max_shift = num_shift(row_idx, block_idx, positions, this_row);

        for (int j = 0; j < num_cols; j++){
                row_perms[row_idx][num_perm][j] = this_row[j];
            }

        /* cout << "row_perms[" << row_idx <<"][" << num_perm <<"] = ";
            print_array(row_perms[row_idx][num_perm]);
            cout << endl; */
            num_perm++;
            num_row_perms[row_idx]++;
        /* for (int i = 0; i < MAX_CONSTRAINT_NUM; i++){
            row_perms[row_idx][num_perm][i] = this_row[i];
        }


        cout << "row_perms[" << row_idx <<"][" << num_perm <<"] = ";
        print_array(row_perms[row_idx][num_perm]);
        cout << endl;


        num_perm++; */

        //return;
        for (int i = 1; i <= max_shift; i++){
            shift_right(this_row, row_idx, i, positions, block_idx);
            get_row_perms_helper(row_idx, positions, block_idx - 1, this_row, num_perm);
            shift_left(this_row, row_idx, i, positions, block_idx);
        }
        /* while (block_can_shift(row_idx, block_idx, positions, num_row_constraints[row_idx])){
            for (int i = 0; i < MAX_CONSTRAINT_NUM; i++){
                row_perms[row_idx][num_perm][i] = this_row[i];
            }


        cout << "row_perms[" << row_idx <<"][" << num_perm <<"] = ";
        print_array(row_perms[row_idx][num_perm]);
        cout << endl;


            num_perm++;
            this_row[positions[block_idx]] = '.';
            int a = 1; //start checking from the next position
            while (this_row[positions[block_idx] + a] == 'X') a++;
            this_row[positions[block_idx] + a] = 'X';

            positions[block_idx]++;
            get_row_perms_helper(row_idx, positions, block_idx - 1, this_row, num_perm);
            //block_idx++;

        } */
    }
}

void get_row_perms(int row_idx) {
    // START YOUR CODES HERE
    int positions[MAX_CONSTRAINT_NUM] = {};
    get_position(row_idx, positions);
    char this_row[MAX_CONSTRAINT_NUM] = {};
    for (int i = 0; i < num_cols; i++) this_row[i] = '.';
    for (int i = 0; i < num_row_constraints[row_idx]; i++){
        for (int j = 0; j < row_constraints[row_idx][i]; j++){
            this_row[positions[i] + j] = 'X';
        }
    }
    int num_perm = 0;
    get_row_perms_helper(row_idx, positions, num_row_constraints[row_idx] - 1, this_row, num_perm);
    // END YOUR CODES HERE
}

/**
 **********  Task 8  **********
 *
 * This function checks if current state is valid, after
 * we finish filling 'num_complete_rows' rows.
 *
 * For example, if num_complete_rows = 2, it will only check
 * if the first two rows (with index 0 and 1) do not
 * break column constraints.
 *
 * Note that this function is different from 'check_whole_board_valid()'
 * in 2 ways:
 * 1. We don't check whole board here, only check the first 'num_complete_rows' rows.
 * 2. We don't (need to) check row_constraints here, only check column_constraints.
 *    This is because this function will only be called during solver,
 *    so the rows are generated in permutation process, which must be valid.
 */
int blocks_left(const int col_constraints[][MAX_CONSTRAINT_NUM], int num_block, int num_col){
    int blocks = 0;
    for (int i = num_block; i < num_col_constraints[num_col]; i++){
        blocks += col_constraints[num_col][i];
        if (i != num_col_constraints[num_col] - 1) blocks++;
    }
    return blocks;
}


bool check_row_valid_helper(const char board[][MAX_CONSTRAINT_NUM], const int col_constraints[][MAX_CONSTRAINT_NUM], int num_col, int num_complete_rows){
    //for task 8

/*     int col_constraint[num_col_constraints[num_col]] = {};
    for (int i = 0; i < num_col_constraints[num_col]; i++){
        col_constraint[i] = col_constraints[num_col][i];
    } */

    //int col_length = num_complete_rows;
    if (col_constraints[num_col][0] == 0) {
        for (int i = 0; i < num_complete_rows; i++) {
            if (board[i][num_col] != '.') return false;
        }
        return true;
    }
    else {
        int i = 0, a = 0, b = 0;
        int this_block = 0;
        while (true){
            while (board[i + a][num_col] == '.' && i + a < num_complete_rows) a++;
            if (/* this_column[i + a] == 0 ||  */i + a >= num_complete_rows) {
                if ((num_rows - num_complete_rows) < blocks_left(col_constraints, b, num_col)) return false;
                return true; //inconclusive -> true
            }
            while (board[i + a][num_col] == 'X' && (i + a < num_complete_rows)){
                this_block++;
                if (this_block > col_constraints[num_col][b] ) {
                    return false; //number of consecutive colored blocks exceed constraint
                }
                a++;
            }
            if ((i + a == num_complete_rows) && this_block <= col_constraints[num_col][b]){
                if ((num_rows - num_complete_rows) < (col_constraints[num_col][b] - this_block + blocks_left(col_constraints, b + 1, num_col))) return false;
                return true; // inconclusive -> true
            }
            else if (this_block == col_constraints[num_col][b] && board[i + a][num_col] != 'X'){
                if (b < num_col_constraints[num_col] - 1 && board[i + a][num_col] == '.') {
                    b++;
                    this_block = 0;
                }
                else if (b == num_col_constraints[num_col] - 1){
                    while (board[i + a][num_col] == '.' && ((i + a) < num_complete_rows)) a++;
                    if (/* (this_column[i + a] == 0) ||  */((i + a) == num_complete_rows)){
                        if ((num_rows - num_complete_rows) < (col_constraints[num_col][b] - this_block + blocks_left(col_constraints, b + 1, num_col))) return false;
                        return true;  //the current checkboard is already valid; might turn invalid later
                    }
                    else if (board[i + a][num_col] == 'X') return false;
                }
            }
        }
    }
}

bool check_rows_valid(int num_complete_rows) {
    // START YOUR CODES HERE

/*     char check_board[MAX_ROW][MAX_COL] = {};
    for (int i = 0; i < num_complete_rows; i++){
        for (int j = 0; j < num_cols; j++){
            check_board[i][j] = board[i][j];
        }
    }
 */
    for (int i = 0; i < num_cols; i++){
        if (!check_row_valid_helper(board, col_constraints, i, num_complete_rows)) return false;
    }
    return true;


    // END YOUR CODES HERE
}


/**
 **********  Task 9  **********
 *
 * This function will solve the board, and store the solution
 * into board[][] directly.
 *
 * Hint: You may use recursion to do that, with the help of helper functions
 * 'get_row_perms()', ‘check_rows_valid()’, etc.
 */
void solve_helper(int curr_perm, int curr_row, int temp_perm[], bool& checked){
        for (int i = 0; i < num_row_perms[curr_row]; i++){
            for (int j = 0; j < num_cols; j++){
                board[curr_row][j] = row_perms[curr_row][i][j];
            }


/*             cout << "curr_row: " << curr_row << "curr_perm: " << i << "board: ";
            print_array(board[curr_row]);
            cout << endl;
 */

            if (curr_row < num_rows - 1){
                if (check_rows_valid(curr_row + 1)) {
                    solve_helper(0, curr_row + 1, temp_perm, checked);
                }
                else if (curr_perm + 1 < num_row_perms[curr_row]){
                    continue;
                }
            }
            else if (!checked && check_whole_board_valid()) {
                checked = true;
                return;
            }
            if (checked) return;
        }
}

void solve() {
    // START YOUR CODES HERE
    for (int i = 0; i < num_rows; i++){
        get_row_perms(i);
    }
    int temp_perm[MAX_ROW] = {};
    bool checked = false;
    solve_helper(0, 0, temp_perm, checked);
    // END YOUR CODES HERE
}


int main() {
    get_input_board();
    print_board();

    while (true) {
        cout << "===== Welcome to Nonogram Game =====" << endl;
        cout << "Please enter your choice:" << endl;
        cout << "Enter 'p' to print the current board." << endl;
        cout << "Enter 'm' to modify a cell." << endl;
        cout << "Enter 'c' to check your solution." << endl;
        cout << "Enter 's' to invoke solver." << endl;
        cout << "Enter 'q' to quit." << endl;
        cout << "Your choice: ";
        char input;
        cin >> input;
        if (input == 'p') {
            print_board();
        } else if (input == 'm') {
            user_operate_board();
        } else if (input == 'c') {
            if (check_whole_board_valid()) {
                cout << "Congratulations! Your solution is correct!" << endl;
            } else {
                cout << "Ahh, your solution is incorrect, try again." << endl;
            }
        } else if (input == 's') {
            cout << "Generating solution:" << endl;
            solve();
            print_board();
        } else if (input == 'q') {
            cout << "Bye!" << endl;
            break;
        } else {
            cout << "Invalid input. Try again." << endl;
        }
    }
    return 0;
}


/*  int main_t(){
    get_input_board();
    char resulting_row[15] = {};
    int position_vec[3] = {0, 5, 7};
    cout << boolalpha << block_can_shift(0, 1, position_vec, 3);
}
 *//*
base cases: for one or zero blank grid with no restrictions on both its row and column, return true
            for one blank grid with at least one of its row or column restrictions nonzero, return false
            for one colored grid with no restrictions on both its row and column, return false
recursive call:
            examine exactly one row and one column at a time and see if they meet the restrictions
                if yes, continue; else, return false
            tickle out that row and column, pass the new board to the recursive call
            eliminate the topmost restriction row and leftmost restriction column
            for each restriction row below the topmost one, perform decrement if the
                second row of the examined column is colored
            similar process for columns

*/
/*
base case: if the whole board is valid
    do nothing
else:
    record the current state of the board
    if the rows finished so far are all valid
        recursive call: proceed to fill the next row
    else if there are still permutations not tired for this row:
        recursive call: try to fill the same row with the remaining permutation(s)
    else if all the possible permutations have been tried
        recursive call (or simply "go back" to the previous row?): try to fill the previous row with yet-tried permutations


*/
