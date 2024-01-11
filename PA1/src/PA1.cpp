#include <iostream>
using namespace std;

bool is_leapyear(int year);
void first_weekday_update(int& day_index, int curr_year, int target_year, int curr_month, int target_month, int month_days[13]);
void print_horizontal_calendar(int year, string month_literal, int month_num, char first_day, bool leap_year, int month_days[13]);
void print_vertical_calendar(int year, string month_literal, int month_num, char first_day, bool leap_year, int month_days[13], const string header[]);
void print_line(int& starting_val, int days_in_month);


int main()
{
    cout << "Enter year (in range 1800-9999): ";
    int year, month;
    char first_day, aspect;
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
        if (month >= 1 && month <= 12){
            break;
        }
        else {
            cout << "Enter month (in range 1-12): ";
        }
    }
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

    // Leap year test
    bool leap_year = is_leapyear(year);

    //Month conversion
    string month_literal = "";
    const string month_array[13] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    month_literal = month_array[month];

    //Days in respective month
    int month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                          //  1   2   3   4   5   6   7   8   9   10  11  12
    if (is_leapyear(year)){
        month_days[2] = 29;
    }

    // FUNCTION CALL
    if (aspect == 'h'){
        print_horizontal_calendar(year, month_literal, month, first_day, leap_year, month_days);
    }
    else if (aspect == 'v'){
        const string header_s[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
        const string header_m[7] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
        if (first_day == 's'){
            print_vertical_calendar(year, month_literal, month, first_day, leap_year, month_days, header_s);
        }
        else if (first_day == 'm'){
            print_vertical_calendar(year, month_literal, month, first_day, leap_year, month_days, header_m);
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
        if (day_index > 7) {
            day_index %= 7;
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
        if (day_index > 7){
            day_index %= 7;
        }
        curr_month++;
    }

}

bool is_leapyear(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 400 == 0);
}

void print_line(int& starting_val, int days_in_month){
    for (int j = starting_val; j <= days_in_month; j += 7){
        if (j < 10){
            cout << " ";
        }
        cout << j << " ";
    }
    cout << endl;
    starting_val += 1;
}

void print_horizontal_calendar(int year, string month_literal, int month_num, 
char first_day, bool leap_year, int month_days[13]){
    //Prints the calendar of a specified month horizontally.
    //cout << "horizontal calendar";
    string header = "";
    if (first_day == 's'){
        header = "Su Mo Tu We Th Fr Sa";
    }
    else if (first_day == 'm'){
        header = "Mo Tu We Th Fr Sa Su";
    }
    cout << month_literal << " " << year << endl;
    cout << header << endl;

    //TODO
    int day_index = 3;
    first_weekday_update(day_index, 1800, year, 1, month_num, month_days);
    int days_in_month = month_days[month_num];
    if (first_day == 's' && day_index == 7){}
    else if (first_day == 's'){
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
char first_day, bool leap_year, int month_days[13], const string header[]){
    //TODO
    //cout << "vertical calendar";
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
    }
}