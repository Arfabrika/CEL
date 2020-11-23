/* FILE NAME: console.cpp
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 23.11.2020
 * PERPOSE: console functions file
 */

#include "main_header.h"

/* Print menu function
   ARGUMENTS:
     None;
   RETURNS:
      None. */
void console::Menu(void)
{
    printf("0 - �����\n"
        "1 - ������ ����� �����\n"
        "2 - �������� ����\n"
        "3 - �������� � ��������� ������� ����\n"
        "4 - ��������� ������ ���� � ����\n"
        "5 - ��������� ������ ���� �� �����\n"
        "9 - ������/� ���������\n");
} /* End of 'Menu' function */

/* Print menu of temporary array function
   ARGUMENTS:
     None;
   RETURNS:
      None. */
void console::ArrayMenu(void)
{
    printf("0 - ����������� � ������� ����\n"
        "1 - ����������� ��������� ������\n"
        "2 - ������� ����� �� ���������� �������\n"
        "3 - �������� ������� �����\n"
        "4 - �������� �������� �����\n"
        "5 - ������� ��������� ������\n"
        /*"2 - ������� ����� �� ���������� �������\n"
        "2 - ������� ����� �� ���������� �������\n"
        "2 - ������� ����� �� ���������� �������\n"*/);
} /* End of 'Menu' function */

/* Print head text function
   ARGUMENTS:
     None;
   RETURNS:
      None. */
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
      None. */
void console::Help(void)
{
    printf("Console English Learning - ���������, ���������� � ���������� ���� � ������ ������\n"
        "��� �� ������������?\n"
        "��� ������ ����� ������ ������������ ���������� ����. ����� ������ '1' � ������� ����, �� ��������� � ����� ���������� �����.\n"
        "���������� ��� ���������� ����� �����, ����� ������ '3' � ������� ����, � ����� ����� ������ '1' � ��������������� ����. � ��� �� ���� ����� ������� ����� �� ������ ��� �������� ��� �������.\n"
        "����� ��������� ����, �� ������ ������ ����, ����� ������ '2' � ������� ����.\n"
        "�� ��������� ��������� ����� � ����! � ��������� ������, ����� ������ �� ��������� ������ ���� ����� �������. ��� ���������� ������ ���� � ���� ������� ������ '4' � ������� ����.\n"
        "������ ��������� � ������ ������? ��������� ����� �� �����, ����� ������ '5' � ������� �����\n"
        "������� � ��������!\n");
} /* End of 'Help' function */

/* Read word function
   ARGUMENTS:
     None;
   RETURNS:
     (Word) - new world structure */
Word console::ReadWord(void)
{
    Word W;
    string s;

    system("cls");
    HeadText();
    printf("������� �����:\n");
    getline(cin, s);
    W.Name = s;
    printf("������� �������:\n");
    getline(cin, s);
    W.Translate = s;
    W.NumOfUses = 0;
    W.NumOfWrongAnswers = 0;
    W.ErrorKoef = 0;
    return W;
} /* End of 'ReadWord' function */

/* Clear and refill console function
   ARGUMENTS:
     None;
   RETURNS:
     None. */
void console::ConsoleReset(void)
{
    printf("��� ����������� � ������� ���� ������� ����� ������\n");
    if (_getch())
    {
        system("cls");
        return;
    }
    /* Old variant with timer
    printf("����������� � ������� ���� ����� %i", ConsoleResetTime / 1000);
    for (int i = ConsoleResetTime - 1; i > 1000; i-= 1000)
    {
        printf(", %i", i / 1000);
        Sleep(1000);
    }
    system("cls");*/
} /* End of 'ConsoleReset' function */

/* Output array function
   ARGUMENTS:
     - Word *mas: pointer to word array
   RETURNS:
     None.
*/
void console::OutputArray(vector<Word>* mas) 
{
    system("cls");
    HeadText();
    if (mas->size() == 0)
    {
        printf("������ ���� ����!\n");
        return;
    }
    cout << left << setw(MaxOutputWordSize) <<"�����" << setw(MaxOutputWordSize) << "�������" << "���������� �������� �����  ���������� ������ � �����  " 
        "����������� ���������� ������� �����\n";
    for (int i = 0; i < mas->size(); i++)
        cout << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate
        << setw(15) << " " << mas->at(i).NumOfUses << setw(20) << "    " << mas->at(i).NumOfWrongAnswers << setw(30) << "            " << mas->at(i).ErrorKoef << "\n";
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
    "��� ������������� �������� ������� ������� Y\n");
    if (_getch() == 'y' || _getch() == 'Y' || _getch() == '�' || _getch() == '�')
        mas->clear();
    return 1;
} /*End of 'ClearArray' function */

/* END OF 'console.cpp' FILE */