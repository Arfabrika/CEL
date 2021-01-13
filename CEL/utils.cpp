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
    printf("Для выбора необходимого пункта меню нажмите на соответственную клавишу\n"
        "0 - выход\n"
        "1 - ввести новое слово\n"
        "2 - действия с временным списком слов\n"
        "3 - выбор заданий\n"
        "4 - сохранить список слов в файл\n"
        "5 - загрузить список слов из файла\n"
        "9 - помощь/о программе\n");
} /* End of 'Menu' function */

/* Print menu of temporary array function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::ArrayMenu(void)
{
    printf("0 - возвращение в главное меню\n"
        "1 - просмотреть временный массив\n"
        "2 - удалить слово из временного массива\n"
        "3 - изменить перевод слова\n"
        "4 - сбросить прогресс слова\n"
        "5 - удалить временный массив\n");
} /* End of 'Menu' function */

/* Print menu of task functions
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::TaskMenu(void)
{
    printf("0 - возвращение в главное меню\n"
        "1 - тренировка с подсказками\n"
        "2 - перевод слова\n"
        "3 - тест\n"
        "4 - конструктор слов\n"
        /*"5 - удалить временный массив\n"*/);
} /* End of 'Menu' function */

/* Print begin task menu function
   ARGUMENTS:
     - string name: type of task;
   RETURNS:
     None.
*/
void console::BeginMenu( string name )
{
    printf("0 - возвращение в главное меню\n"
        "1 - тренировка с подсказками\n"
        "2 - перевод слова\n"
        "3 - тест\n"
        "4 - конструктор слов\n"
        /*"5 - удалить временный массив\n"*/);
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
    cout << "Ошибка при выполнении операции: " << s << "\nПроверьте корректность введенных данных\n";
} /*End of 'MyError' function */

/* Print helping text about program function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::Help(void)
{
    printf("Console English Learning - программа, помогающая в заучивании слов других языков\n"
           "Как ей пользоваться?\n"
           "Для начала нужно ввести определенное количество слов. Нажав кнопку '1' в главном меню, Вы перейдете в режим добавления слова.\n"
           "Посмотреть уже введеннные слова можно, нажав кнопку '2' в главном меню, а затем нажав кнопку '1' в вспомогательном меню. В том же меню можно удалить слово из списка или изменить его перевод.\n"
           "Для более успешного запоминания слов Вы можете пройти тренеровку, нажав кнопку '3' в главном меню.\n"
           "Для проверки своих знаний вы можете пройти экзамен, нажав кнопку '4'\n"
           "Кроме экзамена, проверить знания можно и в режиме теста (кнопка '5')\n"
           "Не забывайте сохранять слова в файл! В противном случае, после выхода из программы список слов будет потерян. Для сохранения списка слов в файл нажмите кнопку '6' в главном меню.\n"
           "Хотите вернуться к старым словам? Загрузите слова из файла, нажав кнопку '7' в главном менюю\n"
           "Успехов в обучении!\n");
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
    printf("Возвращение в главное меню через %i", ConsoleResetWithMessageTime / 1000);
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
