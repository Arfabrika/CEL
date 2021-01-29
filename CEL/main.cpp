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
          printf("Слово успешно добавлено в временный массив!\n");
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
            printf("Введите слово, которое собираетесь удалить:\n");
            cin >> s;
            if (cons->DeleteWord(s))
                cout << "Слово " << s << " успешно удалено!\n";
            break;
        case '3':
            system("cls");
            cons->HeadText();
            printf("Введите слово, перевод которого собираетесь изменить:\n");
            cin >> s;
            if (cons->EditWord(s))
                cout << "Перевод слова " << s << " успешно изменен!\n";
            break;
        case '4':
            system("cls");
            cons->HeadText();
            printf("Введите слово, прогресс которого собираетесь сбросить:\n");
            cin >> s;
            if (cons->ResetProgress(s))
                cout << "Прогресс слова """ << s << """ успешно сброшен!\n";
            break;
        case '5':
            system("cls");
            cons->HeadText();
            if (cons->ClearArray())
                cout << "Временный массив успешно очищен!\n";
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
                cout << "Временный массив успешно перемешан!\n";
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
                cout << "Временный массив успешно отсортирован по алфавиту!\n";
              break;
            case '2':
              system("cls");
              cons->HeadText();
              if(cons->SortAlphaBack())
                cout << "Временный массив успешно отсортирован по алфавиту в обратном порядке!\n";
              break;
            case '3':
              system("cls");
              cons->HeadText();
              if(cons->SortErrorKoef())
                cout << "Временный массив успешно отсортирован по увеличению коэффициента ошибок слов!\n";
              break;
            case '4':
              system("cls");
              cons->HeadText();
              if(cons->SortErrorKoefBack())
                cout << "Временный массив успешно отсортирован по уменьшению коэффициента ошибок слов!\n";
              break;
            }
            break;
        case '8':
           system("cls");
           cons->HeadText();
           if (cons->ResetAllProgress())
               cout << "Прогресс всех слов успешно сброшен!\n";
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
          cout << "Сохранение в файл " << db->wordfiledir.substr(5) << " успешно завершено!\n";
        break;
    case '5':
        system("cls");
        if (db->GeneralLoad())
          cout << "Загрузка из файла " << db->wordfiledir.substr(5) << " успешно завершена!\n";
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
        printf("Ввведена некорректная программа. Пожалуйста, повторите ваш запрос\n");
    }
    if (!cons->is_exit)
      cons->ConsoleResetWithMessage("Для возвращения в главное меню нажмите любую кнопку");
  }
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */