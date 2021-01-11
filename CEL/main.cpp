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
          printf("Введите название файла для сохранения слов (без расширения): ");
          cin >> UserName;
          db->wordfiledir = UserName + ".txt";
          printf("Введите название файла для сохранения статистики (без расширения): ");
          cin >> UserName;
          db->marksfiledir = UserName + ".txt";
          db->storage = cons->mas;
          db->save();
          break;
      case '7':
          system("cls");
          cons->HeadText();
          printf("Введите название файла для загрузки слов (без расширения): ");
          cin >> UserName;
          db->wordfiledir = UserName + ".txt";
          printf("Введите название файла для загрузки статистики (без расширения): ");
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
          printf("Ввведена некорректная программа. Пожалуйста, повторите ваш запрос\n");
      }
      if (!cons->is_exit)
        cons->ConsoleResetWithMessage("Для возвращения в главное меню нажмите любую кнопку");
  }
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */