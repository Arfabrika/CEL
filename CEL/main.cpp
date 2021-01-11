/* FILE NAME: main.cpp
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 10.01.2020
 * PERPOSE: main project file
 */

#include "main_header.h"

console *cons;
Database *db;

/* Main program function 
   ARGUMENTS:
     None;
   RETURNS:
      - 1 if all okey, 0 if error.
*/
int main( void )
{
  string UserName;

  cons = new console();
  db = new Database();

  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  while (1)
  {
      string s;

      cons->is_exit = 0;
      cons->HeadText();
      cons->Menu();
      switch (_getch())
      {
      case '0':
          return 1;
      case '1':
            system("cls");
          if (cons->ReadWord())
            printf("����� ������� ��������� � ��������� ������!\n");
          break;
      case '2':
          system("cls");
          cons->HeadText();
          cons->ArrayMenu();
          switch (_getch())
          {
          case '0':
              cons->is_exit = 1;
              system("cls");
              break;
          case '1':
              system("cls");
              cons->OutputArray();
              break;
          case '2':
              system("cls");
              cons->HeadText();
              printf("������� �����, ������� ����������� �������:\n");
              cin >> s;
              if (cons->DeleteWord(s))
                  cout << "����� " << s << " ������� �������!\n";
              break;
          case '3':
              system("cls");
              cons->HeadText();
              printf("������� �����, ������� �������� ����������� ��������:\n");
              cin >> s;
              if (cons->EditWord(s))
                  cout << "������� ����� " << s << " ������� �������!\n";
              break;
          case '4':
              system("cls");
              cons->HeadText();
              printf("������� �����, �������� �������� ����������� ��������:\n");
              cin >> s;
              if (cons->ResetProgress(s))
                  cout << "�������� ����� """ << s << """ ������� �������!\n";
              break;
          case '5':
              if (cons->ClearArray())
                  cout << "��������� ������ ������� ������!\n";
              else
              {
                cons->is_exit = 1;
                system("cls");
              }
              break;
          }
          break;
      case '3':
          system("cls");
          cons->TrainingMode();
          break;
      case '4':
          system("cls");
          cons->ExamMode();
          break;
      case '5':
          system("cls");
          cons->TestMode();
          break;
      case '6':
          system("cls");
          cons->HeadText();
          printf("������� �������� ����� ��� ���������� ���� (��� ����������): ");
          cin >> UserName;
          db->wordfiledir = UserName + ".txt";
          printf("������� �������� ����� ��� ���������� ���������� (��� ����������): ");
          cin >> UserName;
          db->marksfiledir = UserName + ".txt";
          db->storage = cons->mas;
          db->save();
          break;
      case '7':
          system("cls");
          cons->HeadText();
          printf("������� �������� ����� ��� �������� ���� (��� ����������): ");
          cin >> UserName;
          db->wordfiledir = UserName + ".txt";
          printf("������� �������� ����� ��� �������� ���������� (��� ����������): ");
          cin >> UserName;
          db->marksfiledir = UserName + ".txt";
          db->loadWords();
          db->loadMarks();
          cons->mas = db->storage;
          break;
      case '9':
          system("cls");
          //cons->Help();
          break;
      default:
          printf("�������� ������������ ���������. ����������, ��������� ��� ������\n");
      }
      if (!cons->is_exit)
        cons->ConsoleResetWithMessage("��� ����������� � ������� ���� ������� ����� ������");
  }
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */