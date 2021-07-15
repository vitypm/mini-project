#include <iostream>
#include <algorithm>
#include <fstream> 
#include <vector>
#include <cstdio>                               // ��� ������� remove


#define import "text.txt"
#define export "outText.txt"



using namespace std;


int main(int argc, char* argv[])  //  ���������� ������� main
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
        str.clear();
     
    ifstream file(import);
    //��������� �� �����
    while (!file.eof())
    {
        lines++;
        getline(file, str); 
        //������� ��������
        for (int i = 0; i <= Total; i++)
        {
            //���� ������� �������� ���
            /* if (str[0] == lower[i]|| str[0] == upper[i])*/


            if (str[0] == lower[i])
            {
                //����������� ��� � �����
                file_name  = to_string(i);
                //cout << i << endl;
                /*--------------------------------------------------------------------------------*/

                ofstream vmdelet_out;                    //������� ����� 
                vmdelet_out.open(file_name, ios::app);  // ��������� ���� ��� ������ � �����
                vmdelet_out << str;                        // ���� ������
                vmdelet_out.close();                          // ��������� ����
                 /*--------------------------------------------------------------------------------*/
                //��������� ������ ����������� ������
                ListFiles.push_back(file_name);
            }  

            if (str[0] == upper[i]) {
                //����������� ��� � ����� � ���������� + 26 � �������� ����� �������� ��������� �� ������� ����
                file_name = to_string(i+Total);
                //cout << i << endl;
                /*--------------------------------------------------------------------------------*/

                ofstream vmdelet_out;                    //������� ����� 
                vmdelet_out.open(file_name, ios::app);  // ��������� ���� ��� ������ � �����
                vmdelet_out << str;                        // ���� ������
                vmdelet_out.close();                          // ��������� ����
                 /*--------------------------------------------------------------------------------*/
                //��������� ������ ����������� ������
                ListFiles.push_back(file_name);
            }

        } 
    };
    file.close();
    //���������� �� ����� �������� � ������� ��� ���, ListFiles, �������� string. ��� ���� ����� �������� ����� ��������� � int.
    //���������
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


    //� ������� ���������
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
    //��������� ���� � �������� �� ���������� ��������
    for (size_t i = 0; i < ListFiles.size(); i++)
    {   
        ofstream vmdelet_out;                    //������� ����� 
        vmdelet_out.open("SAVE_FILES.txt", ios::app);  // ��������� ���� ��� ������ � �����
        vmdelet_out << ListFiles[i] << endl;                        // ���� ������
        vmdelet_out.close();                          // ��������� ����
    }
 
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
                    ofstream vmdelet_outt;                    //������� ����� 
                    vmdelet_outt.open("FILES.txt", ios::app);  // ��������� ���� ��� ������ � �����
                    vmdelet_outt << line_temp << endl;                        // ���� ������
                    vmdelet_outt.close();                          // ��������� ����
                }
            }
            in_temp.close();     // ��������� ����
        }
    }
    in.close();     // ��������� ����

    cout << "End of program" << endl;




    


 


    return 0;
}