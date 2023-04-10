#include <string>
#include "functions.h";
using namespace std;

int main() {
    string filename1;
    string name1 = "my_schedule.bin";    //ім'я файлу за замовчуванням для запису вхідних даних
    string name2 = "solution.bin";    //iм'я файлу, в який буде буде записуватись рішення завдання
    filename1 = input_data(name1);    //присвоюємо iм'я для файлу з вхідними даними
    output_interface1();
    output_data_from_file(filename1);
    make_file_for_solution(filename1, name2);   //створюємо файл для рішення та записуємо у нього дані
    output_interface2();
    output_data_from_file(name2);
    output_information_about_rest(filename1);    //виводимо інформацію про відпочинок

    return 0;
}
