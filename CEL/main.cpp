/* FILE NAME: main.cpp
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 16.11.2020
 * PERPOSE: main project file
 */

#include "main_header.h"

/* Main program function 
   ARGUMENTS:
     None;
   RETURNS:
      - 1 if all okey, 0 if error.*/
int main( void )
{
    vector<Word> WordArray;
    Word W;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    while (1)
    {
        int flag = 1;
        string s;

        console::HeadText();
        console::Menu();
        switch (_getch())
        {
        case '0':
            return 1;
        case '1':
            W = console::ReadWord();
            WordArray.push_back(W);
            printf("����� ������� ��������� � ��������� ������!\n");
            break;
        case '2':
            break;
        case '3':
            system("cls");
            console::HeadText();
            console::ArrayMenu();
            switch (_getch())
            {
            case '0':
                flag = 0;
                system("cls");
                break;
            case '1':
                console::OutputArray(&WordArray);
                break;
            case '2':
                printf("������� �����, ������� ����������� �������:\n");
                cin >> s;
                if (console::DeleteWord(&WordArray, s))
                    cout << "����� " << s << " ������� �������!\n";
                break;
            case '3':
                printf("������� �����, ������� �������� ����������� ��������:\n");
                cin >> s;
                if (console::EditWord(&WordArray, s))
                    cout << "������� ����� " << s << " ������� �������!\n";
                break;
            case '4':
                printf("������� �����, �������� �������� ����������� ��������:\n");
                cin >> s;
                if (console::ResetProgress(&WordArray, s))
                    cout << "�������� ����� """ << s << """ ������� �������!\n";
                break;
            case '5':
                if (console::ClearArray(&WordArray))
                    cout << "��������� ������ ������� ������!\n";
                break;
            }
            break;
        case '4':
            break;
        default:
            printf("�������� ������������ ���������. ����������, ��������� ��� ������\n\n");
        }
        if (flag)
          console::ConsoleReset();
    }
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */