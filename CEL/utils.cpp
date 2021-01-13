/* FILE NAME: utils.cpp
 * PROGRAMMER: Fabrika Artem
 * DATE: 13.01.2021
 * PERPOSE: utilits and output text functions file
 */

#include "main_header.h"

/* Upgraded random function
   ARGUMENTS:
     - int mi: minimum random number;
     - int ma: maximum random number;
     - int param: random parameter
   RETURNS:
     (int) random number.
*/
int console::MyRand(int mi, int ma, int param )
{
  int num;

  if (mi == 0)
    mi = 1;
  if (ma == 0)
    ma = 1;
  if (param == 0)
    param = rand() % 5648 + 19;
  num = (((mi * ma + ma / param) / mi) + RandomTime % 13 + (rand() % param) * param + param % ma * rand()) % ma;
  if (num < mi)
    num = MyRand(mi, ma, param * rand() % 256);
  return num;
} /* End of 'MyRand' function */

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
        "3 - ����� �������\n"
        "4 - ��������� ������ ���� � ����\n"
        "5 - ��������� ������ ���� �� �����\n"
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

/* Print menu of task functions
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::TaskMenu(void)
{
    printf("0 - ����������� � ������� ����\n"
        "1 - ���������� � �����������\n"
        "2 - ������� �����\n"
        "3 - ����\n"
        "4 - ����������� ����\n"
        /*"5 - ������� ��������� ������\n"*/);
} /* End of 'Menu' function */

/* Print begin task menu function
   ARGUMENTS:
     - string name: type of task;
   RETURNS:
     None.
*/
void console::BeginMenu( string name )
{
    printf("0 - ����������� � ������� ����\n"
        "1 - ���������� � �����������\n"
        "2 - ������� �����\n"
        "3 - ����\n"
        "4 - ����������� ����\n"
        /*"5 - ������� ��������� ������\n"*/);
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
     - string s: error message;
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
           "��� �������� ����� ������ �� ������ ������ �������, ����� ������ '4'\n"
           "����� ��������, ��������� ������ ����� � � ������ ����� (������ '5')\n"
           "�� ��������� ��������� ����� � ����! � ��������� ������, ����� ������ �� ��������� ������ ���� ����� �������. ��� ���������� ������ ���� � ���� ������� ������ '6' � ������� ����.\n"
           "������ ��������� � ������ ������? ��������� ����� �� �����, ����� ������ '7' � ������� �����\n"
           "������� � ��������!\n");
} /* End of 'Help' function */

/* Clear and refill console function
   ARGUMENTS:
     - string s: output message;
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

/* Print head in test function
   ARGUMENTS:
     - int: current word position;
     - int: number of all answers;
   RETURNS:
     None.
*/
void console::TestHead( int cur, int all )
{
  printf("\n---------%i/%i----------\n", cur, all);
} /* End of 'TestHead' function */

/* END OF 'utils.cpp' FILE */
