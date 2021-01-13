/* FILE NAME: main.cpp
 * PROGRAMMER: Fabrika Artem
 * DATE: 13.01.2020
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

  /* Test section */
  db->wordfiledir = "qqq.txt";
  db->marksfiledir = "qqq.db";
  db->loadWords();
  db->loadMarks();
  cons->mas = db->storage;
  /* End of test section */

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
            if (cons->ClearArray())
                cout << "Временный массив успешно очищен!\n";
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
            cons->TrainingMode();
            break;
        case '2':
            system("cls");
            cons->ExamMode();
            break;
        case '3':
            system("cls");
            cons->TestMode();
            break;
        case '4':
            system("cls");
            cons->ConstructorMode();
            break;
        }
        break;
    case '4':
        system("cls");
        if (db->GeneralSave())
          cout << "Сохранение в файл " << db->wordfiledir << " успешно завершено!\n";
        break;
    case '5':
        system("cls");
        if (db->GeneralLoad())
          cout << "Загрузка из файла " << db->wordfiledir << " успешно завершена!\n";
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