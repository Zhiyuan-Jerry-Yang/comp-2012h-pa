#include <iostream>
#include <climits>
#include <cstdio>


using namespace std;

const int MAX_STRLEN = 1000;
const int NUM_CHARS_PER_LINE = 50;
const int MAX_LINES = 15;

int countCharacters(const char str[]);
int countWords(const char str[]);
int countNumOccurences(const char str[], const char target[]);

void swapString(char str[], const char target[], const char to[]);
void encryptText(char str[], int shift);

void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE]);
void printRightJustified(const char str[]);
void printLeftJustified(const char str[]);

void convertStrToPigLatin(char word[]);
void printPigLatin(const char str[]);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// You codes start here. Please do not modify codes above
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++


void encrypt_helper(int i, int shift, char str[], const char alphabet[]){
    while (shift < 0) shift += 26;
    if (shift > 26) shift %= 26;
    int j = 0;
    while (j < 26 && str[i] != '\0'){
        if (str[i] == alphabet[j]) {
            if ((j + shift) < 26) {
                str[i] = alphabet[j + shift];
                break;
            }
            else {
                str[i] = alphabet[shift - (25 - j) - 1];
                break;
            }
        }
        else j++;
    }
}

int get_length(char arr[]){
    int i = 0;
    while (arr[i] != '\0'){
        i++;
    }
    return i;
}

int get_const_length(const char arr[]){
    int i = 0;
    while (arr[i] != '\0'){
        i++;
    }
    return i;
}

void move_for_blank(char arr[], int starting_index){
    int last_index = get_length(arr);  //this includes '\0'
    int k = 0;
    while(last_index - k >= starting_index){
        arr[last_index - k + 1] = arr[last_index - k];
        k++;
    }
}

int num_blanks(const char arr[]){
    int i = 0, count = 0;
    while (arr[i] != '\0'){
        while ((arr[i] != ' ') && (arr[i] != '\0')) i++;
        if (arr[i] == '\0') return count;
        count++;
        while (arr[i] == ' ') i++;
    }
    return count;
}

void blanks_indices(const char read[], int write[]){
    int i = 0, j = 0;
    while (read[i] != '\0'){
        while ((read[i] != ' ') && (read[i] != '\0')) i++;
        if (read[i] == '\0') break;
        write[j] = i;
        while (read[i] == ' ') i++;
        j++;
    }
}


void move_backward(char arr[], int starting_index, int num_blanks){
    int last_index = get_length(arr);  //this includes '\0'
    int k = 0;
    while(last_index - k >= starting_index){
        arr[last_index - k + num_blanks] = arr[last_index - k];
        k++;
    }
}

void move_forward(char arr[], int starting_index, int num_forward=1){
    int last_index = get_length(arr);  //this includes '\0'
    int k = 0;
    while (starting_index + k < last_index){
        arr[starting_index + k] = arr[starting_index + k + num_forward];
        k++;
    }
}

int countCharacters(const char str[])
{
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

int countWords(const char str[])
{
    int i = 0, words = 0;
    while (str[i] != '\0'){
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.'){
            if ((i - 1 >= 0) && str[i - 1] != ' ' && str[i - 1] != ',' && str[i - 1] != '.'){
                words++;
            }
        }
        i++;
    }
    if (str[i] == '\0' && str[i - 1] != ' ' && str[i - 1] != ',' && str[i - 1] != '.') words++;
    return words;
}

void swapString(char str[], const char target[], const char to[])
{
    int i = 0, j = 0, curr_index = 0;
    int target_length = get_const_length(target);
    int replace_length = get_const_length(to);
    while (str[i] != '\0'){
        while (str[i] != target[j] && str[i] != '\0') i++;
        if (str[i] == '\0') break;
        curr_index = i;
        while (str[i] == target[j] && target[j] != '\0' && str[i] != '\0'){
            i++; j++;
        }
        if (target[j] == '\0') { //target loacted
            j = 0;
        }
        else if (str[i] != '\0'){ //not the target
            j = 0;
            continue;
        }
        
        if (target_length == replace_length){
            int k = 0;
            while (to[k] != '\0'){
                str[curr_index] = to[k];
                k++; curr_index++;
            }
        }
        else if (target_length > replace_length){
            int backward = target_length - replace_length;
            int k = 0;
            while (to[k] != '\0'){ //replace
                str[curr_index] = to[k];
                k++; curr_index++;
            }

            k = i;
            while (str[k] != '\0'){ //fill in the blank
                str[k - backward] = str[k];
                k++;
            }
            if (str[k] == '\0') str[k - backward] = str[k]; //adjust null char position

            i = i - backward; //set i back to the first unchecked position
        }
        else {
            int forward = replace_length - target_length;
            int k = get_length(str) + 1;
            while (k != (i - 1)){ //move for more blanks
                str[k + forward] = str[k];
                k--;
            }

            k = 0;
            while (to[k] != '\0') {//replace
                str[curr_index] = to[k];
                k++; curr_index++;
            }
            i = i + forward;
    }

}
}

void encryptText(char str[], int shift)
{
    const char lower_case[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    const char upper_case[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int i = 0;
    while (str[i] != '\0'){
        if (str[i] >= 'a' && str[i] <= 'z'){
            encrypt_helper(i, shift, str, lower_case);            
        }
        else if (str[i] >= 'A' && str[i] <= 'Z'){
            encrypt_helper(i, shift, str, upper_case);
        }
        i++;
    }
}

int countNumOccurences(const char str[], const char target[])
{
    int i = 0, j = 0, num_occurrence = 0;
    while (str[i] != '\0'){
        while (str[i] != target[j] && str[i] != '\0') i++; //advance the index of str[] if element does not match
        while (str[i] == target[j] && target[j] != '\0' && str[i] != '\0'){ //keep checking the next element if the current elements are the same
            i++; j++;
        }
        if (target[j] == '\0'){
            num_occurrence++;
            if (str[i] != '\0') j = 0;
        }
        else if (str[i] != '\0'){
            j = 0;
        }
    }
    return num_occurrence;
}

void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE])
{
    int i = 0, counter = 0, starting_index = 0, ending_index = 0, temp_index = starting_index, line_counter = 0;
    while (str[i] != '\0'){
        while ((counter < NUM_CHARS_PER_LINE - 1) && (str[i + counter] != '\0')){
            if ((str[i + counter + 1] == ' ' && str[i + counter] != ' ') || 
            (str[i + counter + 1] == '.' && str[i + counter] != '.') || 
            (str[i + counter + 1] == ',' && str[i + counter] != ',')) temp_index = i + counter;
            counter++;
        }
        if (str[i + counter] == ' ' || str[i + counter] == ','
        ||str[i + counter] == '.' || str[i + counter] == '\0') {
            while (str[i + counter - 1] == ' ') counter--;
            ending_index = i + counter - 1;
        }
        else if ((str[i + counter] >= 'a' && str[i + counter] <= 'z')
            || (str[i + counter] >= 'A' && str[i + counter] <= 'Z') || (str[i + counter] == '-')){
            ending_index = temp_index;
        }

        int j = 0, k = i;
        while (k <= ending_index){
            lines[line_counter][j] = str[k];
            k++; j++;
        }
        lines[line_counter][j] = '\0';
        
        while (str[ending_index + 1] == ' ') ending_index++;
        i = ending_index + 1;
        line_counter++;
        counter = 0;

    }
    if (line_counter <= MAX_LINES){
        for (int i = line_counter; i < MAX_LINES; i++){
            if (lines[i][0] != '\0') lines[i][0] = '\0';
        }
    }
}

void printLeftJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE]{'0'};
    convertIntoLines(str, lines);
    int i = 0;
    while (i < MAX_LINES){
        int j = 0;
        while (j < NUM_CHARS_PER_LINE){
            if (lines[i][j] == '\0') {
                if (j != 0) cout << endl;
                break;
            }
            cout << lines[i][j];
            j++;
        }
        i++;
    }
}

void printRightJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE]{'0'};
    convertIntoLines(str, lines);
    int i = 0;
    while (i < MAX_LINES && lines[i][0] != '\0'){
        int j = 0;
        int num_spaces = NUM_CHARS_PER_LINE - 1 - countCharacters(lines[i]);
        for (int k = 0; k < num_spaces; k++) cout << " ";
        while (j < NUM_CHARS_PER_LINE){
            if (lines[i][j] == '\0') {
                if (j != 0) cout << endl;
                break;
            }
                
            cout << lines[i][j];
            j++;
        }
        i++;
    }
}

void printJustified(const char str[])
{
    char lines[MAX_LINES][NUM_CHARS_PER_LINE]{'0'};
    convertIntoLines(str, lines);
    int i = 0;
    int blank_indices[NUM_CHARS_PER_LINE] = {};
    for (int i = 0; i < NUM_CHARS_PER_LINE; i++) blank_indices[i] = -1;
    while (lines[i][0] != '\0' && lines[i][0] != '\0'){
        if (i < (MAX_LINES - 1) && lines[i + 1][0] != '\0') {
        blanks_indices(lines[i], blank_indices);
        int num_blank = num_blanks(lines[i]);
        int j = 0;
        while (countCharacters(lines[i]) < NUM_CHARS_PER_LINE - 1) {
            if (num_blank != 0) move_for_blank(lines[i], blank_indices[j % num_blank]);
            for (int k = j % num_blank; blank_indices[k] != -1; k++){
                blank_indices[k]++;
            }
            j++;
        }
        }

        int b = 0;
        while (b < NUM_CHARS_PER_LINE){
            if (lines[i][b] == '\0') {
                if (b != 0) cout << endl;
                break;
            }
            cout << lines[i][b];
            b++;
        }

        i++;
    }

}

void convertStrToPigLatin(char str[])
{
    char first_char = '0';
    int first_char_index = 0, last_index = 0;
    bool moved = false;
    const char with_y[3] = {'y', 'a', 'y'};
    const char without_y[2] = {'a', 'y'};
    while (str[last_index] != '\0' || moved){
        //advance to the first word
        if (!moved){
            while (str[last_index] == ' ' || str[last_index] == ',' || str[last_index] == '.') last_index++;
            first_char_index = last_index;
            first_char = str[first_char_index];
            //set last_index
            while (str[last_index] != ' ' && str[last_index] != ','
                && str[last_index] != '.' && str[last_index] != '\0') last_index++;
        }
        //append "yay" or "ay" accordingly
        if (first_char == 'a' || first_char == 'e' || first_char == 'i' ||
            first_char == 'o' || first_char == 'u' || first_char == 'A' ||
            first_char == 'E' || first_char == 'I' ||
            first_char == 'O' || first_char == 'U'){
            if (!moved){
                move_backward(str, last_index, 3);
                for (int i = 0; i < 3; i++){
                    str[last_index + i] = with_y[i];
                }
                last_index += 3;
            }
            else if (moved){
                move_backward(str, last_index, 2);
                for (int i = 0; i < 2; i++){
                    str[last_index + i] = without_y[i];
                }
                last_index += 2;
            }
            moved = false;
            while (str[last_index] == ' ' || str[last_index] == ','
                || str[last_index] == '.') last_index++;
            if (str[last_index] == '\0') break;
            else continue;
        }
        //first char is not a vowel--modify the word
        else {
            moved = true;
            while (first_char != 'a' && first_char != 'e' && first_char != 'i' &&
            first_char != 'o' && first_char != 'u'){
                move_backward(str, last_index, 1);
                str[last_index] = first_char;
                move_forward(str, first_char_index);
                first_char = str[first_char_index];
            }
        }
    }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// You codes end here. Please do not modify codes below
// ++++++++++++++++++++++++++++++++++++++++++++++++++++

void printPigLatin(const char str[])
{
    char pigLatin[MAX_STRLEN];
    for (int i = 0; i < MAX_STRLEN; ++i)
    {
        pigLatin[i] = str[i];
    }
    convertStrToPigLatin(pigLatin);
    int strLen = countCharacters(pigLatin);
    for (int i = 0; i < strLen; ++i)
    {
        if (pigLatin[i] >= 'A' && pigLatin[i] <= 'Z')
        {
            pigLatin[i] = 'a' + pigLatin[i] - 'A';
        }
    }
    cout << pigLatin << endl;
}

void printMainDisplay(const char str[])
{
    cout << str << endl
         << "===================================\n"
         << "1. Character Count\n"
         << "2. Word Count\n"
         << "3. Encrypt (Caeser Cipher)\n"
         << "4. Find and Replace String Globally\n"
         << "5. Find Frequency of String\n"
         << "6. Print Left Align Text\n"
         << "7. Print Right Align Text\n"
         << "8. Print Left-Right Align Text\n"
         << "9. Print Pig Latin\n"
         << "Please make your choice: ";
}

int main()
{
    int choice = 0;
    char str[MAX_STRLEN];

    cout << "Enter text: ";
    cin.getline(str, MAX_STRLEN, '\n');

    do
    {
        printMainDisplay(str);
        cin >> choice;
    } while (choice < 1 || choice > 9);

    if (choice == 1)
    {
        cout << "Total character count: " << countCharacters(str) << endl;
    }
    else if (choice == 2)
    {
        cout << "Total word count: " << countWords(str) << endl;
    }
    else if (choice == 3)
    {
        cout << "Enter the shift amount for the caeser cipher encryption (rotation encryption): ";
        int shift;
        cin >> shift;
        encryptText(str, shift);
        cout << str << endl;
    }
    else if (choice == 4)
    {
        cout << "Enter the string to find and replace: ";
        char target[MAX_STRLEN];
        cin.ignore(INT_MAX, '\n');
        cin.getline(target, MAX_STRLEN, '\n');

        cout << "Enter the string to replace it with: ";
        char to[MAX_STRLEN];
        cin.getline(to, MAX_STRLEN, '\n');

        swapString(str, target, to);
        cout << str << endl;
    }
    else if (choice == 5)
    {
        cout << "Enter the string to count the occurences of: ";
        char target[MAX_STRLEN];
        cin.ignore(INT_MAX, '\n');
        cin.getline(target, MAX_STRLEN, '\n');

        cout << '"' << target << '"' << " appears in the text " << countNumOccurences(str, target) << " time(s).\n";
    }
    else if (choice == 6)
    {
        printLeftJustified(str);
    }
    else if (choice == 7)
    {
        printRightJustified(str);
    }
    else if (choice == 8)
    {
        printJustified(str);
    }
    else if (choice == 9)
    {
        printPigLatin(str);
    }
}
