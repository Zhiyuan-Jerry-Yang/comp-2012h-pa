#include <iostream>
using namespace std;

//This code was last updated to fix the problem of erroneous output when input "1992 3 m v"

bool is_leapyear(int year);
void first_weekday_update(int& day_index, int curr_year, int target_year, int curr_month, int target_month, int month_days[13]);
void print_horizontal_calendar(int year, string month_literal, int month_num, char first_day, int month_days[13]);
void print_vertical_calendar(int year, string month_literal, int month_num, char first_day, int month_days[13], const string header[]);
void print_line(int& starting_val, int days_in_month);

void one_row_in_a_month(int year, int& day_index, int& print_index, int month_num, int days_in_month, int month_days[13]);
void three_months_in_a_row(int year, int starting_month_num, int month_days[13]);


int main()
{
    int year, month;
    char first_day, aspect;
    cout << "Enter year (in range 1800-9999): ";
    while (cin >> year){
        if (year >= 1800 && year <= 9999){
            break;
        }
        else {
            cout << "Enter year (in range 1800-9999): ";
        }
    }
    cout << "Enter month (in range 1-12): ";
    while (cin >> month){
        if ((month >= 1 && month <= 12) || month == -1 || month == -3){
            break;
        }
        else {
            cout << "Enter month (in range 1-12): ";
        }
    }
    if (month != -1 && month != -3){
        cout << "Enter the first day of week ('s' for Sunday, 'm' for Monday): ";
        while (cin >> first_day){
            if (first_day == 's' || first_day == 'm'){
                break;
            }
            else {
                cout << "Enter the first day of week ('s' for Sunday, 'm' for Monday): ";
            }
        }
        cout << "Print horizontally (h) or vertically (v): "; 
        while (cin >> aspect){
            if (aspect == 'h' || aspect == 'v'){
                break;
            }
            else {
                cout << "Print horizontally (h) or vertically (v): "; 
            }
        }
    }
    //Month conversion
    string month_literal = "";
    const string month_array[13] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    if (month >=1) month_literal = month_array[month];

    //Days in respective month
    int month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                          //  1   2   3   4   5   6   7   8   9   10  11  12
    if (is_leapyear(year)){
        month_days[2] = 29;
    }

    // FUNCTION CALL
    if (month == -1){
        cout << "Year " << year << endl;
     /*    const string blank = "                    ";
        for (int i = 1; i <= 13; i++){
            int remaining = month_array[i].length() - blank.length();
            cout << month_array[i];
            for (int j = 1; j <= remaining; j++) cout << " ";
            cout << endl << "Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa" << endl;
        } */
        for (int x = 1; x < 13; x += 3){
            switch (x)
            {
            case 1:
                cout << "January               February              March" << endl;
                break;
            case 4:
                cout << "April                 May                   June" << endl;
                break;
            case 7:
                cout << "July                  August                September" << endl;
                break;
            case 10:
                cout << "October               November              December" << endl;
                break;
            default:
                break;
            }
            cout << "Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa" << endl;
            three_months_in_a_row(year, x, month_days);
            
        }
        return 0;
    }
    else if (month == -3){
        int first, second, third;
        const string blank = "                    ";
        cout << "Enter the month in the center (in range 1-12): ";
        while (cin >> second){
            if ((year == 9999 && second == 12) || (year == 1800 && second == 1) || (second < 1 || second > 12)){
                cout << "Enter the month in the center (in range 1-12): ";
            }
            else break;
        }
        first = second - 1;
        third = second + 1;
     
            int month_lenth[] = {0, 7, 8, 5, 5, 3, 4, 4, 6, 9, 7, 8, 8};
            for (int i = first; i <= third; i++){
                if (second == 12 && i == third) cout << month_array[1] << " " << year + 1;
                else if (second == 1 && i == first) cout << month_array[12] << " " << year - 1;
                else cout << month_array[i] << " " << year;
                
                if (second == 1 && i == first) {
                    for (int j = 0; j < 7; j++){
                        cout << " ";
                    }
                }
                else {int len_space = 20 - month_lenth[i] - 1 - 4;
                    for (int j = 0; j < len_space; j++){
                        cout << " ";
                    }
                }
                cout << "  ";
            }
            cout << endl;
            cout << "Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa" << endl;
            three_months_in_a_row(year, first, month_days);
        
    }
    if (aspect == 'h'){
        print_horizontal_calendar(year, month_literal, month, first_day, month_days);
    }
    else if (aspect == 'v'){
        const string header_s[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
        const string header_m[7] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
        if (first_day == 's'){
            print_vertical_calendar(year, month_literal, month, first_day, month_days, header_s);
        }
        else if (first_day == 'm'){
            print_vertical_calendar(year, month_literal, month, first_day, month_days, header_m);
        }
    }
}


void first_weekday_update(int& day_index, int curr_year, int target_year, int curr_month, 
int target_month, int month_days[13]){
    //Updates the day of the week where the first day of the month in interest is in.
    //The current year defaults to 1800, the current month Jan, and the day index 3.
    while (curr_year != target_year){
        if (is_leapyear(curr_year)){
            day_index += 2;
        }
        else {
            day_index++;
        }
        while (day_index > 7) {
            day_index -= 7;
        }
        curr_year++;
    }

    while (curr_month != target_month){
        int days_in_month = month_days[curr_month];
        int curr_date = 1;
        while ((curr_date + 7) < days_in_month){
            curr_date += 7;
        }
        day_index += days_in_month - curr_date + 1;
        while (day_index > 7){
            day_index -= 7;
        }
        curr_month++;
    }

}

bool is_leapyear(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 400 == 0);
}

void print_line(int& starting_val, int days_in_month){
    //This function is only called in vertical calendar tasks
    for (int j = starting_val; j <= days_in_month; j += 7){
        if (j < 10){
            cout << " ";
        }
        cout << j << " ";
    }
    starting_val += 1;
}

void print_horizontal_calendar(int year, string month_literal, int month_num, 
char first_day, int month_days[13]){
    //Prints the calendar of a specified month horizontally.
    string header = "";
    if (first_day == 's'){
        header = "Su Mo Tu We Th Fr Sa";
    }
    else if (first_day == 'm'){
        header = "Mo Tu We Th Fr Sa Su";
    }
    cout << month_literal << " " << year << endl;
    cout << header << endl;

    int day_index = 3;
    first_weekday_update(day_index, 1800, year, 1, month_num, month_days);
    int days_in_month = month_days[month_num];
    if (first_day == 's' && day_index != 7){
        for (int i = 0; i < day_index; i++){
            cout << "  " << " ";
        }
    }
    else if (first_day == 'm'){
        for (int i = 1; i < day_index; i++){
            cout << "  " << " ";
        }
    }

    for (int i = 1; i <= days_in_month; i++){
        if (i < 10){
            cout << " " << i << " ";
        }
        else{
            cout << i << " ";
        }
        day_index++;
        if (first_day == 's') {
            if (day_index == 7){
                cout << endl;
            }
            else if(day_index > 7){
                day_index %= 7;
            }
        }
        else if (first_day == 'm') {
            if (day_index > 7) {
                cout << endl;
                day_index %= 7;
            }
        } 
        }
}

void print_vertical_calendar(int year, string month_literal, int month_num, 
char first_day, int month_days[13], const string header[]){
    //Prints the calendar of a specified month vertically.
    cout << month_literal << " " << year << endl;
    int day_index = 3;
    first_weekday_update(day_index, 1800, year, 1, month_num, month_days);
    int num_blank = day_index;
    if (first_day == 'm'){
        num_blank = day_index - 1;
    }
    int with_blank = 7 - num_blank + 1;
    int without_blank = 1;
    int days_in_month = month_days[month_num];

    for (int i = 0; i < 7; i++){
        cout << header[i] << " ";
        if (num_blank > 0 && num_blank != 7){
            cout << "  " << " ";
            print_line(with_blank, days_in_month);
            num_blank--;
        }
        else if (num_blank == 0 || num_blank == 7){
            print_line(without_blank, days_in_month);
        }
        if ((header[0] == "Su" && header[i] != "Sa") || (header[0] == "Mo" && header[i] != "Su")){
            cout << endl;
        }
    }
}

void one_row_in_a_month(int year, int& day_index, int& print_index, int month_num, int days_in_month, int month_days[13]){
    if (print_index > days_in_month){
        cout << "                      ";
    }
    else{
        if (print_index == 1) {
            first_weekday_update(day_index, 1800, year, 1, month_num, month_days);
        }

        if (print_index == 1 && day_index != 7) {
            for(int a = 1; a <= day_index; a++){
                cout << "   ";
            }
        }

        if ((day_index == 7)  && (print_index <= days_in_month)){
            if (print_index < 10){
                cout << " ";
            }
            cout << print_index << " ";
            print_index++;
            day_index = 1;
        }
        
        

        while ((print_index <= days_in_month) && (day_index != 7)){
            if (print_index < 10){
                cout << " ";
            }
            cout << print_index << " ";
            print_index++;
            day_index++;
        }

        if ((print_index > days_in_month)){
                for (int b = 1; b <= (7 - day_index); b++){
                    cout << "   ";
                }
        }
        cout << " ";
    }
}

void three_months_in_a_row(int year, int starting_month_num, int month_days[13]){
    int i = 1, j = 1, k = 1, day_index1 = 3, day_index2 = 3, day_index3 = 3;
    int days_in_month1 = month_days[starting_month_num], days_in_month2 = month_days[starting_month_num + 1], days_in_month3 = month_days[starting_month_num + 2];
    
    while ((i <= days_in_month1) || (j <= days_in_month2) || (k <= days_in_month3)){
        if (starting_month_num < 1){
            days_in_month1 = month_days[12];
            one_row_in_a_month(year - 1, day_index1, i, 12, days_in_month1, month_days);
        }
        else one_row_in_a_month(year, day_index1, i, starting_month_num, days_in_month1, month_days);
        one_row_in_a_month(year, day_index2, j, starting_month_num + 1, days_in_month2, month_days);
        if (starting_month_num + 2 > 12){
            days_in_month3 = month_days[1];
            one_row_in_a_month(year + 1, day_index3, k, 1, days_in_month3, month_days);
        }
        else one_row_in_a_month(year, day_index3, k, starting_month_num + 2, days_in_month3, month_days);
        cout << endl;
    }
    cout << endl;
    }