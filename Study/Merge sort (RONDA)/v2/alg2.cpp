#include <iostream>
#include <algorithm>
#include <fstream> 
#include <vector>
#include <cstdio>     

#define import "text.txt"

using namespace std;






void writeFile(string nameTheFile, string writeline) {
    ofstream vmdelet_out;                    //создаем поток 
    vmdelet_out.open(nameTheFile, ios::app);  // открываем файл для записи в конец
    vmdelet_out << writeline;                        // сама запись
    vmdelet_out.close();
}

int main(int argc, char* argv[])  //  определяем функцию main
{
    string inputText = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    string str;

    int file_name;
    vector<int> ListFiles;

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
    remove("FILES.txt");
    str.clear();

    ifstream file(import);
    while (!file.eof())
    {
        getline(file, str);
        //Перебор Алфавита
        for (int i = 0; i <= inputText.size(); i++)
        {
            if (str[0] == inputText[i])
            {
                string temp = to_string(i);
                /*--------------------------------------------------------------------------------*/
                writeFile(temp, str);
                /*--------------------------------------------------------------------------------*/
               //Сохраняем список сохраненных файлов
                ListFiles.push_back(i);
            }
            else if (str[0] = inputText[i])
        }
    };
    file.close();


    sort(ListFiles.begin(), ListFiles.end());
    //и удаляем дубликаты
    ListFiles.erase(unique(ListFiles.begin(), ListFiles.end()), ListFiles.end());

    cout << "-----------------------" << endl;
    //Сохраняем файл с записями об созданными записями
    for (size_t i = 0; i < ListFiles.size(); i++)
    {
        //  FilesRecord(ListFiles[i], "SAVE_FILES.txt");
        string tempStr = to_string(ListFiles[i]) + "\n";
        writeFile("SAVE_FILES.txt", tempStr);                       
        // закрываем файл
    }
    cout << "-----------------------" << endl;
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
                    writeFile("FILES.txt", line_temp);                  
                }
            }
            in_temp.close();     // закрываем файл
        }
    }
    in.close();     // закрываем файл

    cout << "End of program" << endl;

}