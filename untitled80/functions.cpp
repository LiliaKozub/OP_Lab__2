#include "functions.h"
#include "correct_input.h"

/*функція для зчитування ім'я файлу*/
string get_filename(){
    string filename;
    cout << "Enter file name you want to open (without expansion):";
    getline(cin, filename);
    filename = filename + ".bin";
    return filename;
}


/*функції для виводу деяких елементів інтерфейсу програми*/
void output_interface1(){
    cout << "---------------------YOUR_SCHEDULE-----------------------" << endl;
}

void output_interface2(){
    cout << "----------------------12:45__17:30-----------------------" << endl;
}


/*функція для створення розкладу*/
void create_schedule(string filename, Schedule &b){
    b.finish_hour = b.start_hour + b.duration_hour;
    if(60 - b.start_minute < b.duration_minute){
        b.finish_hour++;
        b.finish_minute = b.duration_minute - (60 - b.start_minute);
    }
    else{
        b.finish_minute = b.start_minute + b.duration_minute;
        if(b.finish_minute == 60){
            b.finish_hour++;
            b.finish_minute = 0;
        }
    }
}


/*функція для запису даних у файл*/
string write_to_file(string filename){
    cout << "--------------------CREATING_SCHEDULE---------------------" << endl;
    Schedule affair;
    char c;
    int comparison = 0;
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    do{
        input_tittle(affair.tittle);
        cout << "Input the hour of start(0-23):";
        input_hour(affair.start_hour);
        cout << "Input the minute of start(0-59):";
        input_minute(affair.start_minute);
        cout << "Input the number of hours of duration(0-23):";
        input_hour(affair.duration_minute);
        cout << "Input the number of minute of duration(0-59):";
        input_minute(affair.duration_minute);
        cout << "Continue?(Y/N)";
        cin >> c;
        valid_char(c);
        cin.ignore();
        if(comparison > affair.start_hour){
            cout << "There are errors in your schedule.\nIf you want to make the schedule correctly, restart the program.\n";
            exit(EXIT_FAILURE);
        }
        create_schedule(filename,affair);
        file.write((char*)&affair, sizeof(Schedule));
        comparison = affair.finish_hour;
    }while((c!='n')&&(c!='N'));
    file.close();
    return filename;
}


/*функція для зчитування даних з файлу та їх виведення на екран*/
void output_data_from_file(string filename){
    Schedule affair;
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    int n = 1;
    file.clear();
    file.seekg(0, ios::beg);
    while(file.read((char*)&affair, sizeof(Schedule))){
        cout << n << ". ";
        cout << affair.start_hour << ":" << affair.start_minute << " - ";
        cout << affair.finish_hour << ":" << affair.finish_minute << "  ";
        cout << affair.tittle << endl;
        cout << "Duration: " << affair.duration_hour << " hour  " << affair.duration_minute << " minute\n" << endl;
        n++;
    }
    file.clear();
    file.seekg(0, ios::end);
    streampos size = file.tellg();
    if(size == 0){
        cout << "The file is empty\n";
    }
    file.close();
}


/*функція для доповнення файлу даними*/
string append_file(string name){
    cout << "--------------------ADDITION_SCHEDULE--------------------" << endl;
    Schedule affair;
    char c;
    ofstream file(name, ios::binary | ios::app);
    if (!file) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    do{
        input_tittle(affair.tittle);
        cout << "Input the hour of start(0-23):";
        input_hour(affair.start_hour);
        cout << "Input the minute of start(0-59):";
        input_minute(affair.start_minute);
        cout << "Input the number of hours of duration(0-23):";
        input_hour(affair.duration_minute);
        cout << "Input the number of minute of duration(0-59):";
        input_minute(affair.duration_minute);
        cout << "Continue?(Y/N)";
        cin >> c;
        valid_char(c);
        cin.ignore();
        create_schedule(name,affair);
        file.write((char*)&affair, sizeof(Schedule));
    }while((c!='n')&&(c!='N'));
    file.close();
    return name;
}


/*функція для вводу даних користувачем та запису їх у файл*/
string input_data(string filename){
    int choice;
    string name;
    cout << "If you want to create a new file - enter \"1\"\nIf you want to add data to an existing file - enter \"2\"\n";
    cin >> choice;
    cin.ignore();
    if (choice == 1){
       return write_to_file(filename);
    }
    if (choice == 2){
        name = get_filename();
        output_interface1();
        output_data_from_file(name);
        return append_file(name);
    }
}


/*функція, що створює новий файл та записує у нього рішення*/
void make_file_for_solution(string filename1, string filename2){
    Schedule b;
    ifstream file1(filename1, ios::binary);
    if (!file1) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    ofstream file2(filename2, ios::binary);
    if (!file2) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    while(file1.read((char*)&b, sizeof(Schedule))){
        if ((b.start_hour >= 12) && (b.finish_hour <= 17) && (b.finish_hour > 12) && (b.start_hour < 17)
            || ((b.start_hour == 12) && (b.start_minute >= 45) && (b.finish_hour <= 17))
            || ((b.start_hour == 17) && (b.start_minute <= 30) && (b.finish_hour == 17) && (b.finish_minute <= 30))
            || ((b.start_hour == 12) && (b.start_minute >= 45) && (b.finish_hour == 12) && (b.finish_minute >= 45))
            || ((b.start_hour > 12) && (b.finish_hour == 17) && (b.finish_minute <= 30))
            || ((b.start_hour == 17) && (b.finish_minute <= 30) && (b.start_minute >= 45))){
            file2.write((char *) &b, sizeof(Schedule));
        }
    }
    file2.close();
    file1.close();
}


/*функція, що виводить інформацію про відпочинок*/
void output_information_about_rest(string filename){
    cout << "------------------------YOUR_REST------------------------" << endl;
    Schedule b;
    void count_duration(int finish_hour, int finish_minute, int start_hour, int start_minute);
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Unable to open file!\n";
        exit(EXIT_FAILURE);
    }
    int finish_affair_h = 0;
    int finish_affair_m = 0;
    int n = 0;
    bool flag = false;
    while(file.read((char*)&b, sizeof(Schedule))){
        if((n>0) && ((b.start_hour != finish_affair_h) || (b.start_minute != finish_affair_m))){
            cout << n << ". ";
            cout << finish_affair_h << ":" << finish_affair_m << " - ";
            cout << b.start_hour << ":" << b.start_minute << endl;
            //cout << "Duration: " << b.duration_hour << " hour  " << b.duration_minute << " minute\n" << endl;
            count_duration(finish_affair_h, finish_affair_m, b.start_hour, b.start_minute);
            flag = true;
        }
        finish_affair_h = b.finish_hour;
        finish_affair_m = b.finish_minute;
        n++;
    }
    if(!flag){
        cout << "No information about rest\n";
    }
}


/*фунуція для обрахунку тривалості*/
void count_duration(int finish_hour, int finish_minute, int start_hour, int start_minute){
    int hour_duration;
    int minute_duration;
    if(finish_minute < start_minute){
        hour_duration = start_hour - finish_hour;
        minute_duration = start_minute - finish_minute;
    }
    else{
        hour_duration = start_hour - finish_hour - 1;
        minute_duration = 60 - finish_minute + start_minute;
    }
    if(minute_duration == 60){
        hour_duration++;
        minute_duration = 0;
    }
    cout << "Duration: " << hour_duration << " hour  " << minute_duration << " minute\n" << endl;
}


