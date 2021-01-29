/* FILE NAME: utils.cpp
 * PROGRAMMER: Fabrika Artem
 * DATE: 29.01.2021
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
    ma = 2;
  if (param == 0)
    param = rand() % 5648 + 19;
  num = (((mi * ma + ma / param) / mi) + RandomTime % 13 + (rand() % param) * param + param % (ma + 3) * (rand() % (7 + mi))) % ma;
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
         "7 - ���������\n"
         "8 - ������ ����������\n"
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
  printf("��� ������ ������������ ������ ���� ������� �� ��������������� �������\n"
         "0 - ����������� � ������� ����\n"
         "1 - ����������� ��������� ������\n"
         "2 - ������� ����� �� ���������� �������\n"
         "3 - �������� ������� �����\n"
         "4 - �������� �������� �����\n"
         "5 - ������� ��������� ������\n"
         "6 - ���������� ����� � �������\n"
         "7 - ������������� ������\n"
         "8 - �������� �������� ���� ���� � �������\n");
} /* End of 'Menu' function */

/* Print menu of task functions
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::TaskMenu(void)
{
  printf("��� ������ ������������ ������ ���� ������� �� ��������������� �������\n"
         "0 - ����������� � ������� ����\n"
         "1 - ���������� � �����������\n"
         "2 - ������� �����\n"
         "3 - ����\n"
         "4 - ����������� ����\n"
         "5 - ��������� �����\n"
         "6 - �������� ��������� �����\n");
} /* End of 'TaskMenu' function */

/* Print setting menu functions
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::SettingMenu( void )
{
  printf("��� ������ ������������ ������ ���� ������� �� ��������������� �������\n"
         "0 - ����������� � ������� ����\n");
  cout << "1 - ���������� ���� � ���� ����� ���������:          " << ((int)db->Set->ExitSave == 1 ? "��������" : "���������") << "\n";
  cout << "2 - �������� ���� �� ����� � ������ ������:          " << ((int)db->Set->StartLoad == 1 ? "��������" : "���������") << "\n";
  cout << "3 - �������� �����, �� �������� ���������� ��������: " << db->Set->LastFileName;
} /* End of 'SettingMenu' function */

/* Print menu of sort function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::SortMenu( void )
{
    printf("��� ������ ������������ ������ ���� ������� �� ��������������� �������\n"
           "0 - ����������� � ������� ����\n"
           "1 - ���������� �� ��������\n"
           "2 - ���������� �� �������� � �������� �������\n"
           "3 - ���������� �� ���������� ������������ ������ ����\n"
           "4 - ���������� �� ���������� ������������ ������ ����\n");
} /* End of 'SortMenu' function */

/* Print begin task menu function
   ARGUMENTS:
     None;
   RETURNS:
     (int) 0 if need to exit, 1 if continue task.
*/
int console::BeginTaskMenu( void )
{
  string UserData;

  HeadText();
  printf("����������� ������������ �� ���������� �������:\n");
  for (int i = 0; i < mas.size(); i++)
      cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
   printf("������� ������� 'd', ���� ������ ������� �����-���� �����\n"
         "������� ������� '0', ���� ������ ����� � ������� ����\n"
         "������� ����� ������ �������, ���� �� ������ ������ ����\n");
  char param = _getch();
  switch(param)
  {
  case 'd':
  case 'D':
  case '�':
  case '�':
      printf("������� �����, ������� ������ �������:");
      cin >> UserData;
      if (!DeleteWord(UserData))
      {
        ConsoleResetWithMessage("��� ����������� � ���� ����� �������� ������� ����� ������\n");
        return BeginTaskMenu();
      }
      if (mas.size() == 0)
      {
        ConsoleResetWithMessage("������ ���� ����!\n��� ����������� � ���� ����� �������� ������� ����� ������\n");
        return 0;
      }
      system("cls");
      return BeginTaskMenu();
  case '0':
      is_exit = 1;
      system("cls");
      return 0;
  default:
      system("cls");
      return 1;
  }
} /* End of 'BeginTaskMenu' function */

/* Print finish task menu function
   ARGUMENTS:
     - int Right: number of correct answers;
     - vector <int> *ErrorIndexes: pointer to array of word with wrong answers indexes
   RETURNS:
     None.
*/
void console::FinishTaskMenu( int Right, vector <int> *ErrorIndexes )
{
  int ArraySize = (int)mas.size();

  HeadText();
  if (Right == ArraySize)
    printf("�������\n");
  else if (Right >= 0.8 * ArraySize)
    printf("������\n");
  else if (Right >= 0.6 * ArraySize)
    printf("���������\n");
  else if (Right >= 0.4 * ArraySize)
    printf("����� ���� � �����...\n");
  else
    printf("�����\n");
  printf("�� ��������� ������� � ��������� �������� %i ���� �� %i \n", Right, ArraySize);
  printf("�����, ����������� �� ���������� �������: %02i:%02i\n", TaskTime / CLOCKS_PER_SEC / 60, (TaskTime / CLOCKS_PER_SEC) % 60);
  if (Right != ArraySize)
  {
    printf("������ ����, � ������� �� ������� ������:\n");
    for (int i = 0; i < ErrorIndexes->size(); i++)
      cout << left << setw(MaxOutputWordSize) << mas.at(ErrorIndexes->at(i)).Name << setw(MaxOutputWordSize) << mas.at(ErrorIndexes->at(i)).Translate << "\n";
  }
} /* End of 'FinishTaskMenu' function */

/* Print head text function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::HeadText(void)
{
    printf("Console English Learning, ver 1.02\n"
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
           "���������� ��� ���������� ����� �����, ����� ������ '2' � ������� ����, � ����� ����� ������ '1' � ��������������� ����. � ��� �� ���� ����� ������� ����� �� ������ ��� �������� ��� �������, � ����� ���������� ��� ������������� ������ � ������ �������\n"
           "��� ������� ��������� � ���� �������, ������� ����������� �������� �� ������ '3' � ������� ����.\n"
           "��� ����� ��������� ����������� ���� �� ������ ������ ����������, ����� ������ '1' � ���� �������.\n"
           "��� �������� ����� ������ �� ������ ������ �������, ����� ������ '2' � ���� �������\n"
           "����� ��������, ��������� ������ ����� � � ������ ����� (������ '3' � ���� �������)\n"
           "� ������ '����������� ����' ��� ����� ������� ����� �� ������ ���� � �������� ��� ������� (������ '4' � ���� �������)\n"
           "� ������ '��������� �����' �� ������ ����� ��� ��������� ��������� ���� �� ��������� ������� ��������� ������� (������ '5' � ���� �������)\n"
           "�� ��������� ��������� ����� � ����! � ��������� ������, ����� ������ �� ��������� ������ ���� ����� �������. ��� ���������� ������ ���� � ���� ������� ������ '4' � ������� ����.\n"
           "������ ��������� � ������ ������? ��������� ����� �� �����, ����� ������ '5' � ������� �����\n"
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

/* Print text from file function
   ARGUMENTS:
     string name: name of version log file;
   RETURNS:
     None.
*/
void console::PrintTextFile( string name )
{
  ifstream in(name);
  string s;

  setlocale(LC_ALL, "Russian");
  for (getline(in, s); !in.eof(); getline(in, s)) 
    cout << s << "\n";
  cout << s << "\n";
} /* End of 'PrintTextFile' functions */

/* END OF 'utils.cpp' FILE */
