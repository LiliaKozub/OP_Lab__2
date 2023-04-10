#include <iostream>
#include <fstream>
#include <string>
#include "Schedule.h"
using namespace std;

string get_filename();   //функція для зчитування ім'я файлу
void output_interface1();   //функції для виводу деяких елементів інтерфейсу програми
void output_interface2();
string write_to_file(string filename);   //функція для запису даних у файл
string append_file(string name);    //функція для доповнення файлу даними
string input_data(string filename);   //функція для вводу даних користувачем та запису їх у файл
void create_schedule(string filename, Schedule &b);   //функція для створення розкладу
void output_data_from_file(string filename);   //функція для зчитування даних з файлу та їх виведення на екран
void make_file_for_solution(string filename1, string filename2);   //функція, що створює новий файл та записує у нього рішення
void output_information_about_rest(string filename);    //функція, що виводить інформацію про відпочинок
