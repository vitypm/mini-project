#include <iostream>
#include <algorithm>
#include <fstream> 
#include <vector>
#include <cstdio>     

#define import "text.txt"

using namespace std;






void writeFile(string nameTheFile, string writeline) {
    ofstream vmdelet_out;                    //������� ����� 
    vmdelet_out.open(nameTheFile, ios::app);  // ��������� ���� ��� ������ � �����
    vmdelet_out << writeline;                        // ���� ������
    vmdelet_out.close();
}

int main(int argc, char* argv[])  //  ���������� ������� main
{
    string inputText = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    string str;

    int file_name;
    vector<int> ListFiles;

    /* �������� ������������ ����� */
    ifstream filee("SAVE_FILES.txt");
    if (filee) {
        while (!filee.eof())
        {
            getline(filee, str);
            if (remove(str.c_str()) != 0)             // �������� ����� file.txt
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
        //������� ��������
        for (int i = 0; i <= inputText.size(); i++)
        {
            if (str[0] == inputText[i])
            {
                string temp = to_string(i);
                /*--------------------------------------------------------------------------------*/
                writeFile(temp, str);
                /*--------------------------------------------------------------------------------*/
               //��������� ������ ����������� ������
                ListFiles.push_back(i);
            }
            else if (str[0] = inputText[i])
        }
    };
    file.close();


    sort(ListFiles.begin(), ListFiles.end());
    //� ������� ���������
    ListFiles.erase(unique(ListFiles.begin(), ListFiles.end()), ListFiles.end());

    cout << "-----------------------" << endl;
    //��������� ���� � �������� �� ���������� ��������
    for (size_t i = 0; i < ListFiles.size(); i++)
    {
        //  FilesRecord(ListFiles[i], "SAVE_FILES.txt");
        string tempStr = to_string(ListFiles[i]) + "\n";
        writeFile("SAVE_FILES.txt", tempStr);                       
        // ��������� ����
    }
    cout << "-----------------------" << endl;
    /* ����� ������ � ��������� !*/
    cout << endl << "End of program records!" << endl << endl;


    /* MERGE FILES */

    string line;

    ifstream in("SAVE_FILES.txt"); // �������� ���� ��� ������
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
            in_temp.close();     // ��������� ����
        }
    }
    in.close();     // ��������� ����

    cout << "End of program" << endl;

}