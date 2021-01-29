/* FILE NAME: main.cpp
 * PROGRAMMER: Fabrika Artem
 * DATE: 26.01.2021
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

  db->LoadSettings("Sys\\sets.cel");
  if (db->Set->StartLoad)
  {
    db->wordfiledir = "Data\\" + db->Set->LastFileName + ".txt";
    db->marksfiledir = "Data\\" + db->Set->LastFileName + ".db";
    db->loadWords();
    db->loadMarks();
    cons->mas = db->storage;
  }

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
        if (db->Set->ExitSave)
          db->ExitSave();
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
            system("cls");
            cons->HeadText();
            if (cons->ClearArray())
                cout << "��������� ������ ������� ������!\n";
            else
            {
              cons->is_exit = 1;
              system("cls");
            }
            break;
        case '6':
            system("cls");
            cons->HeadText();
            if (cons->MixWords())
                cout << "��������� ������ ������� ���������!\n";
            break;
        case '7':
            system("cls");
            cons->HeadText();
            cons->SortMenu();
            switch(_getch())
            {
            case '0':
              cons->is_exit = 1;
              system("cls");
              break;
            case '1':
              system("cls");
              cons->HeadText();
              if(cons->SortAlpha())
                cout << "��������� ������ ������� ������������ �� ��������!\n";
              break;
            case '2':
              system("cls");
              cons->HeadText();
              if(cons->SortAlphaBack())
                cout << "��������� ������ ������� ������������ �� �������� � �������� �������!\n";
              break;
            case '3':
              system("cls");
              cons->HeadText();
              if(cons->SortErrorKoef())
                cout << "��������� ������ ������� ������������ �� ���������� ������������ ������ ����!\n";
              break;
            case '4':
              system("cls");
              cons->HeadText();
              if(cons->SortErrorKoefBack())
                cout << "��������� ������ ������� ������������ �� ���������� ������������ ������ ����!\n";
              break;
            }
            break;
        case '8':
           system("cls");
           cons->HeadText();
           if (cons->ResetAllProgress())
               cout << "�������� ���� ���� ������� �������!\n";
           break;
        }
        break;
    case '3':
        system("cls");
        cons->HeadText();
        cons->TaskMenu();
        switch (_getch())
        {
        case '0':
            cons->is_exit = 1;
            system("cls");
            break;
        case '1':
            system("cls");
            cons->MainCommonMode(4);
            break;
        case '2':
            system("cls");
            cons->MainCommonMode(0);
            break;
        case '3':
            system("cls");
            cons->MainCommonMode(1);
            break;
        case '4':
            system("cls");
            cons->MainCommonMode(2);
            break;
        case '5':
            system("cls");
            cons->MainMixedMode();
            break;
        case '6':
            system("cls");
            cons->MainCommonMode(3);
            break;
        }
        break;
    case '4':
        system("cls");
        if (db->GeneralSave())
          cout << "���������� � ���� " << db->wordfiledir.substr(5) << " ������� ���������!\n";
        break;
    case '5':
        system("cls");
        if (db->GeneralLoad())
          cout << "�������� �� ����� " << db->wordfiledir.substr(5) << " ������� ���������!\n";
        break;
    case '7':
        system("cls");
        cons->HeadText();
        cons->SettingMenu();
        switch(_getch())
        {
        case '0':
          cons->is_exit = 1;
          system("cls");
          break;
        case '1':
          system("cls");
          cons->HeadText();
          if (!db->ChangeSettings(1))
          {
            cons->is_exit = 1;
            system("cls");
          }
          break;
        case '2':
          system("cls");
          cons->HeadText();
          if (!db->ChangeSettings(2))
          {
            cons->is_exit = 1;
            system("cls");
          }
          break;
        case '3':
          system("cls");
          cons->HeadText();
          if (!db->ChangeSettings(3))
          {
            cons->is_exit = 1;
            system("cls");
          }
          break;
        }
        break;
    case '8':
        system("cls");
        cons->HeadText();
        cons->PrintTextFile("Sys\\ver.cel");
        break;
    case '9':
        system("cls");
        cons->Help();
        break;
    default:
        printf("�������� ������������ ���������. ����������, ��������� ��� ������\n");
    }
    if (!cons->is_exit)
      cons->ConsoleResetWithMessage("��� ����������� � ������� ���� ������� ����� ������");
  }
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */