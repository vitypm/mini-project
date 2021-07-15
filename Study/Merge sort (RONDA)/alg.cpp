#include <iostream>
#include <algorithm>
#include <fstream> 
#include <vector>
#include <cstdio>                               // для функции remove


#define import "text.txt"
#define export "outText.txt"



using namespace std;


int main(int argc, char* argv[])  //  определяем функцию main
{
    string str;
    string lower = "abcdefghijklmnopqrstuvwxyz";
    string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string file_name;
    size_t Total = upper.size();
   // cout << Total;
   
    vector<string> ListFiles;
 
    int n = 1;//desired row number
    int lines = 0; //number of lines

   /* Удаление специального файла */
        ifstream filee("SAVE_FILES.txt");
        if (filee) {
            while (!filee.eof())
            {
                getline(filee, str);
                if (remove(str.c_str()) != 0)             // удаление файла file.txt
                    cout << "Error file: " << str << endl;
                else
                    cout << "File deleted: " << str << endl;
            }
        }

        filee.close();
        remove("SAVE_FILES.txt");
        str.clear();
     
    ifstream file(import);
    //Считываем до конца
    while (!file.eof())
    {
        lines++;
        getline(file, str); 
        //Перебор Алфавита
        for (int i = 0; i <= Total; i++)
        {
            //Если захотим скливать все
            /* if (str[0] == lower[i]|| str[0] == upper[i])*/


            if (str[0] == lower[i])
            {
                //Присваиваем имя к файлу
                file_name  = to_string(i);
                //cout << i << endl;
                /*--------------------------------------------------------------------------------*/

                ofstream vmdelet_out;                    //создаем поток 
                vmdelet_out.open(file_name, ios::app);  // открываем файл для записи в конец
                vmdelet_out << str;                        // сама запись
                vmdelet_out.close();                          // закрываем файл
                 /*--------------------------------------------------------------------------------*/
                //Сохраняем список сохраненных файлов
                ListFiles.push_back(file_name);
            }  

            if (str[0] == upper[i]) {
                //Присваиваем имя к файлу и прибавляем + 26 к значению чтобы отделить маленькие от больших букв
                file_name = to_string(i+Total);
                //cout << i << endl;
                /*--------------------------------------------------------------------------------*/

                ofstream vmdelet_out;                    //создаем поток 
                vmdelet_out.open(file_name, ios::app);  // открываем файл для записи в конец
                vmdelet_out << str;                        // сама запись
                vmdelet_out.close();                          // закрываем файл
                 /*--------------------------------------------------------------------------------*/
                //Сохраняем список сохраненных файлов
                ListFiles.push_back(file_name);
            }

        } 
    };
    file.close();
    //Сортировка не будет работать с числами так как, ListFiles, является string. Для того чтобы поменять нужно перевести в int.
    //сортируем
    sort
    (
        ListFiles.begin(), ListFiles.end(),
        [](std::string x, std::string y)
        {
            std::string xy = x + y;
            std::string yx = y + x;
            return xy > yx;
        }
    );


    //и удаляем дубликаты
    ListFiles.resize(unique(ListFiles.begin(), ListFiles.end()) - ListFiles.begin());

    vector<int> int_numbers;

    cout << "-----------------------" << endl;
    for (auto i : ListFiles) {
        int_numbers.push_back(atoi(i.c_str()));
    }
    ListFiles.clear();
    sort(int_numbers.begin(), int_numbers.end());
    for (auto i : int_numbers)
        ListFiles.push_back(to_string(i));
    int_numbers.clear();


    cout << "-----------------------" << endl;
    //Сохраняем файл с записями об созданными записями
    for (size_t i = 0; i < ListFiles.size(); i++)
    {   
        ofstream vmdelet_out;                    //создаем поток 
        vmdelet_out.open("SAVE_FILES.txt", ios::app);  // открываем файл для записи в конец
        vmdelet_out << ListFiles[i] << endl;                        // сама запись
        vmdelet_out.close();                          // закрываем файл
    }
 
    /* Конец записи в программе !*/
    cout << endl << "End of program records!" << endl << endl;
   
    /* MERGE FILES */


    string line;

    ifstream in("SAVE_FILES.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
          //  cout << line << endl;
            string line_temp;
            ifstream in_temp(line);
            if (in_temp.is_open())
            {
                while (!in_temp.eof()) {
                    getline(in_temp, line_temp);
                 //   cout << line_temp;
                    ofstream vmdelet_outt;                    //создаем поток 
                    vmdelet_outt.open("FILES.txt", ios::app);  // открываем файл для записи в конец
                    vmdelet_outt << line_temp << endl;                        // сама запись
                    vmdelet_outt.close();                          // закрываем файл
                }
            }
            in_temp.close();     // закрываем файл
        }
    }
    in.close();     // закрываем файл

    cout << "End of program" << endl;




    


 


    return 0;
}