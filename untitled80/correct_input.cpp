#include "correct_input.h"
#include <iostream>

void input_tittle(char* tittle){
    cout << "Input tittle (maximum 49 characters):";
    cin.getline(tittle, 50);
    while (cin.fail()) {
        cout << "Invalid input. Please enter a valid tittle (maximum 49 characters): ";
        cin.clear();
        fflush(stdin);
        cin.getline(tittle, 50);
        fflush(stdin);
    }
}


void input_hour(int &hour){
    cin >> hour;
    while(cin.fail() || hour < 0 || hour > 23){
        cout << "Invalid input. Try again:";
        cin.clear();
        fflush(stdin);
        cin >> hour;
        fflush(stdin);
    }
}


void input_minute(int &minute){
    cin >> minute;
    while(cin.fail() || minute < 0 || minute > 59){
        cout << "Invalid input. Try again:";
        cin.clear();
        fflush(stdin);
        cin >> minute;
        fflush(stdin);
    }
}


void valid_char(char &c){
    if (cin.fail() || (c != 'n' && c != 'N' && c != 'y' && c != 'Y')) {
        cout << "Invalid input. Please enter 'y' or 'n'" << endl;
        cin.clear();
        cin.ignore();
    }
}
