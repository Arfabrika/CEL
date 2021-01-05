/* FILE NAME: console.cpp
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 05.01.2020
 * PERPOSE: console functions file
 */

#include "main_header.h"

/* Print menu function
   ARGUMENTS:
     None;
   RETURNS:
      None.
*/
void console::Menu(void)
{
    printf("��� ������ ������������ ������ ���� ������� �� ��������������� �������\n"
        "0 - �����\n"
        "1 - ������ ����� �����\n"
        "2 - �������� � ��������� ������� ����\n"
        "3 - �������� ����������\n"
        "4 - �������� ����\n"
        "5 - ��������� ������ ���� � ����\n"
        "6 - ��������� ������ ���� �� �����\n"
        "9 - ������/� ���������\n");
} /* End of 'Menu' function */

/* Print menu of temporary array function
   ARGUMENTS:
     None;
   RETURNS:
      None.
*/
void console::ArrayMenu(void)
{
    printf("0 - ����������� � ������� ����\n"
        "1 - ����������� ��������� ������\n"
        "2 - ������� ����� �� ���������� �������\n"
        "3 - �������� ������� �����\n"
        "4 - �������� �������� �����\n"
        "5 - ������� ��������� ������\n");
} /* End of 'Menu' function */

/* Print head text function
   ARGUMENTS:
     None;
   RETURNS:
      None.
*/
void console::HeadText(void)
{
    printf("Console English Learning, ver 1.00\n"
        "**********************************\n");
} /* End of 'HeadText' function */

/* Throw error message function
   ARGUMENTS:
     - None;
   RETURNS:
     None.
*/
void console::MyError(string s)
{
    cout << "������ ��� ���������� ��������: " << s << "\n��������� ������������ ��������� ������\n";
} /*End of 'MyError' function */

/* Print helping text about program function
   ARGUMENTS:
     None;
   RETURNS:
      None.
*/
void console::Help(void)
{
    printf("Console English Learning - ���������, ���������� � ���������� ���� ������ ������\n"
        "��� �� ������������?\n"
        "��� ������ ����� ������ ������������ ���������� ����. ����� ������ '1' � ������� ����, �� ��������� � ����� ���������� �����.\n"
        "���������� ��� ���������� ����� �����, ����� ������ '2' � ������� ����, � ����� ����� ������ '1' � ��������������� ����. � ��� �� ���� ����� ������� ����� �� ������ ��� �������� ��� �������.\n"
        "��� ����� ��������� ����������� ���� �� ������ ������ ����������, ����� ������ '3' � ������� ����.\n"
        "�� ��������� ��������� ����� � ����! � ��������� ������, ����� ������ �� ��������� ������ ���� ����� �������. ��� ���������� ������ ���� � ���� ������� ������ '4' � ������� ����.\n"
        "������ ��������� � ������ ������? ��������� ����� �� �����, ����� ������ '5' � ������� �����\n"
        "������� � ��������!\n");
} /* End of 'Help' function */

/* Read word function
   ARGUMENTS:
     - Word *mas: pointer to word array;
   RETURNS:
     (int) - 1 if successed, 0 if failed
*/
int console::ReadWord( vector<Word>* mas )
{
    Word W;
    string s;

    HeadText();
    printf("������� �����:\n");
    getline(cin, s);
    W.Name = s;
    printf("������� �������:\n");
    getline(cin, s);
    W.Translate = s;

    for (int i = 0; i < mas->size(); i++)
    {
      if (W.Name == mas->at(i).Name && W.Translate == mas->at(i).Translate)
      {
        MyError("�������� ����� ��� ���� � �������.");
        return 0;
      }
    }

    W.NumOfUses = 0;
    W.NumOfWrongAnswers = 0;
    W.ErrorKoef = 0;
    mas->push_back(W);
    return 1;
} /* End of 'ReadWord' function */

/* Clear and refill console function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::ConsoleResetWithMessage( string s )
{
    cout << s << '\n';
    if (_getch())
    {
        system("cls");
        return;
    }
    /* Old variant with timer
    printf("����������� � ������� ���� ����� %i", ConsoleResetWithMessageTime / 1000);
    for (int i = ConsoleResetWithMessageTime - 1; i > 1000; i-= 1000)
    {
        printf(", %i", i / 1000);
        Sleep(1000);
    }
    system("cls");*/
} /* End of 'ConsoleResetWithMessage' function */

/* Output array function
   ARGUMENTS:
     - Word *mas: pointer to word array
   RETURNS:
     None.
*/
void console::OutputArray(vector<Word>* mas) 
{
    HeadText();
    if (mas->size() == 0)
    {
        printf("������ ���� ����!\n");
        return;
    }
    cout << left << setw(MaxOutputWordSize) << "�����" << setw(MaxOutputWordSize) << "�������" << "���������� �������� �����  ���������� ������ � �����  \n"
        ;// "����������� ���������� ������� �����\n";
    for (int i = 0; i < mas->size(); i++)
        cout << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate
        << setw(15) << " " << mas->at(i).NumOfUses << setw(20) << "    " << mas->at(i).NumOfWrongAnswers << "\n";//<< setw(30) << "            " << mas->at(i).ErrorKoef << "\n";
} /* End of 'OutputArray' function */

/* Delete word from temporary array function
   ARGUMENTS:
     - Word *mas: pointer to word array
     - string s: key word;
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::DeleteWord(vector<Word>* mas, string s)
{
    if (mas->size() == 0)
    {
        MyError("��������� ������ ����.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas->size(); i++)
    {
        if (mas->at(i).Name == s)
        {
            mas->erase(mas->begin() + i);
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("��������� ����� �� ������� � �������.");
        return 0;
    }
    return 1;
} /* End of 'DeleteWord' function*/

/* Edit word in temporary array function
   ARGUMENTS:
     - Word *mas: pointer to word array
     - string s: key word;
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::EditWord(vector<Word>* mas, string s)
{
    system("cls");
    HeadText();
    if (mas->size() == 0)
    {
        MyError("��������� ������ ����.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas->size(); i++)
    {
        if (mas->at(i).Name == s)
        {
            string newtr;

            printf("������� ����� �������:\n");
            cin >> newtr;
            mas->at(i).Translate = newtr;
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("��������� ����� �� ������� � �������.");
        return 0;
    }
    return 1;
} /*End of 'EditWord' function */

/* Clear word's parameters in temporary array function
   ARGUMENTS:
     - Word *mas: pointer to word array
     - string s: key word;
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::ResetProgress(vector<Word>* mas, string s)
{
    if (mas->size() == 0)
    {
        MyError("��������� ������ ����.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas->size(); i++)
    {
        if (mas->at(i).Name == s)
        {
            mas->at(i).NumOfUses = 0;
            mas->at(i).ErrorKoef = 0;
            mas->at(i).NumOfWrongAnswers = 0;
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("��������� ����� �� ������� � �������.");
        return 0;
    }
    return 1;
} /*End of 'ResetProgress' function */

/* Clear temporary array function
   ARGUMENTS:
     - Word *mas: pointer to word array
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::ClearArray(vector<Word>* mas)
{
    system("cls");
    HeadText();
    if (mas->size() == 0)
        return 0;
    printf("�� ������������� ������ �������� ��������� ������? ������ � ��� ������ ����� ������������\n"
    "��� ������������� �������� ������� ������� Y\n"
    "��� ������ � ������� ���� ������� ����� ������ ������\n");
    switch(_getch())
    {
    case 'y':
    case 'Y':
    case '�':
    case '�':
      mas->clear();
      return 1;
    default:
      return 0;
    }
} /*End of 'ClearArray' function */

/* Training mode function
   ARGUMENTS:
     - Word *mas: pointer to trainig word array
   RETURNS:
     None.
*/
void console::TrainingMode(vector<Word>* mas)
{
    int i, is_wrong, Right = 0;
    string UserTranslate;

    if (mas->size() == 0)
    {
        console::MyError("��� ������ ���������� ������� ���� �� ���� �����");
        return;
    }

    console::HeadText();
    printf("����������� ������������ �� ���������� �������:\n");
    for (i = 0; i < mas->size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    ConsoleResetWithMessage("��� ������ ���������� ������� ����� ������");
    for (i = 0; i < mas->size(); i++)
    {
        vector <int> help_indexes;
        int current_help_index, is_help = 0;

        console::HeadText();
        is_wrong = 1;
        while (is_wrong)
        {
            /* Help module */
            if (is_help)
            {
                current_help_index = rand() % mas->at(i).Name.size();
                help_indexes.push_back(current_help_index);
                printf("���������: ");
                for (int j = 0; j < mas->at(i).Name.size(); j++)
                {
                    if (std::find(help_indexes.begin(), help_indexes.end(), j) == help_indexes.end())
                        cout << "*";
                    else
                        cout << mas->at(i).Name.at(j);
                }
                cout << "\n";
            }

            cout << "������� ������� ����� " << mas->at(i).Translate << "\n";
            cin >> UserTranslate;

            transform(UserTranslate.begin(), UserTranslate.end(), UserTranslate.begin(), tolower);
            transform(mas->at(i).Name.begin(), mas->at(i).Name.end(), mas->at(i).Name.begin(), tolower);
            if (UserTranslate == mas->at(i).Name)
            {
                printf("�����!\n");
                is_wrong = 0;
            }
            else
            {
                printf("� ���������, �������\n");
                is_help = 1;
                ConsoleResetWithMessage("\n��� ����� ������� ������� ����� ������");
                console::HeadText();
            }
        }
        if (!is_help)
          Right++;
        ConsoleResetWithMessage("��� �������� � ���������� ����� ������� ����� ������");
    }
    console::HeadText();
    printf("�����������!\n�� ����� �������� %i ���� �� %i � ������ �������!\n", Right, mas->size());
} /* End of 'TrainingMode' function */

/* Print head in test function
   ARGUMENTS:
     - int: cuurent word position;
     - int: number of all answers;
   RETURNS:
     None.
*/
void TestHead(int cur, int all)
{
  printf("\n---------%i/%i----------\n", cur, all);
} /* End of 'ShowResults' function */

/* Exam mode function
   ARGUMENTS:
     - Word *mas: pointer to trainig word array
   RETURNS:
     None.
*/
void console::ExamMode(vector<Word>* mas)
{
    int i, Right = 0, ArraySize = (int)mas->size();
    string UserTranslate;
    vector <int> ErrorIndexes;

    if (ArraySize == 0)
    {
        console::MyError("��� ������ ������������ ������� ���� �� ���� �����");
        return;
    }

    /* Menu before test */
    console::HeadText();
    printf("����������� ������������ �� ���������� �������:\n");
    for (i = 0; i < ArraySize; i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    printf("������� ������� 'd', ���� ������ ������� �����-���� �����\n"
           "������� ������� '0', ���� ������ ����� � ������� ����\n"
           "������� ����� ������ �������, ���� �� ������ ������ ����\n");
    switch (_getch())
    {
    case 'd':
    case 'D':
    case '�':
    case '�':
        printf("������� �����, ������� ������ �������:");
        cin >> UserTranslate;
        console::DeleteWord(mas, UserTranslate);
        system("cls");
        console::ExamMode(mas);
        return;
    case '0':
        is_exit = 1;
        system("cls");
        return;
    default:
        system("cls");
        break;
    }

    /* Testing words */
    for (i = 0; i < ArraySize; i++)
    {
      console::HeadText();
      TestHead(i + 1, ArraySize);
      cout << "������� ������� ����� " << mas->at(i).Name << ":\n";
      cin >> UserTranslate;

      mas->at(i).NumOfUses++;
      if (UserTranslate == mas->at(i).Name) 
      {
        printf("�����\n");
        Right++;
      }
      else
      {
        printf("�������\n");
        mas->at(i).NumOfWrongAnswers++;
        mas->at(i).ErrorKoef = mas->at(i).NumOfWrongAnswers / mas->at(i).NumOfUses;
        ErrorIndexes.push_back(i);
      }
      printf("��� �������� � ���������� ����� ������� ����� ������\n");
      if (_getch())
        system("cls");
    }
    console::HeadText();
    if (Right == ArraySize)
      printf("�������\n");
    else if (Right >= 0.8 * ArraySize)
      printf("������\n");
    else if (Right >= 0.6 * ArraySize)
      printf("���������\n");
    else
      printf("�����\n");
    printf("�� ������ ���� � ��������� �������� %i ���� �� %i \n", Right, ArraySize);
    if (Right != ArraySize)
    {
      printf("������ ����, � ������� �� ������� ������:\n");
      for (i = 0; i < ErrorIndexes.size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    }
} /* End of 'ExamMode' function */

/* END OF 'console.cpp' FILE */