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
  printf("Для выбора необходимого пункта меню нажмите на соответственную клавишу\n"
         "0 - выход\n"
         "1 - ввести новое слово\n"
         "2 - действия с временным списком слов\n"
         "3 - выбор заданий\n"
         "4 - сохранить список слов в файл\n"
         "5 - загрузить список слов из файла\n"
         "7 - настройки\n"
         "8 - журнал обновлений\n"
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
  printf("Для выбора необходимого пункта меню нажмите на соответственную клавишу\n"
         "0 - возвращение в главное меню\n"
         "1 - просмотреть временный массив\n"
         "2 - удалить слово из временного массива\n"
         "3 - изменить перевод слова\n"
         "4 - сбросить прогресс слова\n"
         "5 - удалить временный массив\n"
         "6 - перемешать слова в массиве\n"
         "7 - отсортировать массив\n"
         "8 - сбросить прогресс всех слов в массиве\n");
} /* End of 'Menu' function */

/* Print menu of task functions
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::TaskMenu(void)
{
  printf("Для выбора необходимого пункта меню нажмите на соответственную клавишу\n"
         "0 - возвращение в главное меню\n"
         "1 - тренировка с подсказками\n"
         "2 - перевод слова\n"
         "3 - тест\n"
         "4 - конструктор слов\n"
         "5 - смешанный режим\n"
         "6 - проверка написания слова\n");
} /* End of 'TaskMenu' function */

/* Print setting menu functions
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::SettingMenu( void )
{
  printf("Для выбора необходимого пункта меню нажмите на соответственную клавишу\n"
         "0 - возвращение в главное меню\n");
  cout << "1 - сохранение слов в файл перед закрытием:          " << ((int)db->Set->ExitSave == 1 ? "Включено" : "Выключено") << "\n";
  cout << "2 - загрузка слов из файла в начале работы:          " << ((int)db->Set->StartLoad == 1 ? "Включено" : "Выключено") << "\n";
  cout << "3 - название файла, из которого происходит загрузка: " << db->Set->LastFileName;
} /* End of 'SettingMenu' function */

/* Print menu of sort function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::SortMenu( void )
{
    printf("Для выбора необходимого пункта меню нажмите на соответственную клавишу\n"
           "0 - возвращение в главное меню\n"
           "1 - сортировка по алфавиту\n"
           "2 - сортировка по алфавиту в обратном порядке\n"
           "3 - сортировка по увеличению коэффициента ошибок слов\n"
           "4 - сортировка по уменьшению коэффициента ошибок слов\n");
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
  printf("Внимательно ознакомьтесь со следующими словами:\n");
  for (int i = 0; i < mas.size(); i++)
      cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
   printf("Нажмите клавишу 'd', если хотите удалить какое-либо слово\n"
         "Нажмите клавишу '0', если хотите выйти в главное меню\n"
         "Нажмите любую другую клавишу, если Вы готовы пройти тест\n");
  char param = _getch();
  switch(param)
  {
  case 'd':
  case 'D':
  case 'в':
  case 'В':
      printf("Введите слово, которое хотите удалить:");
      cin >> UserData;
      if (!DeleteWord(UserData))
      {
        ConsoleResetWithMessage("Для возвращения в меню перед заданием нажмите любую кнопку\n");
        return BeginTaskMenu();
      }
      if (mas.size() == 0)
      {
        ConsoleResetWithMessage("Массив слов пуст!\nДля возвращения в меню перед заданием нажмите любую кнопку\n");
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
    printf("Отлично\n");
  else if (Right >= 0.8 * ArraySize)
    printf("Хорошо\n");
  else if (Right >= 0.6 * ArraySize)
    printf("Нормально\n");
  else if (Right >= 0.4 * ArraySize)
    printf("Могло быть и лучше...\n");
  else
    printf("Плохо\n");
  printf("Вы выполнили задание и правильно перевели %i слов из %i \n", Right, ArraySize);
  printf("Время, потраченное на выполнение задания: %02i:%02i\n", TaskTime / CLOCKS_PER_SEC / 60, (TaskTime / CLOCKS_PER_SEC) % 60);
  if (Right != ArraySize)
  {
    printf("Список слов, в которых Вы сделали ошибки:\n");
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
           "Посмотреть уже введеннные слова можно, нажав кнопку '2' в главном меню, а затем нажав кнопку '1' в вспомогательном меню. В том же меню можно удалить слово из списка или изменить его перевод, а также перемешать или отсортировать массив в нужном порядке\n"
           "Все задания находятся в меню заданий, которое открывается нажатием на кнопку '3' в главном меню.\n"
           "Для более успешного запоминания слов Вы можете пройти тренеровку, нажав кнопку '1' в меню заданий.\n"
           "Для проверки своих знаний вы можете пройти экзамен, нажав кнопку '2' в меню заданий\n"
           "Кроме экзамена, проверить знания можно и в режиме теста (кнопка '3' в меню заданий)\n"
           "В режиме 'Конструктор слов' Вам нужно собрать слово из набора букв и учитывая его перевод (кнопка '4' в меню заданий)\n"
           "В режиме 'Смешанный режим' на каждое слово Вам предстоит выполнить одно из случайным образом выбранных заданий (кнопка '5' в меню заданий)\n"
           "Не забывайте сохранять слова в файл! В противном случае, после выхода из программы список слов будет потерян. Для сохранения списка слов в файл нажмите кнопку '4' в главном меню.\n"
           "Хотите вернуться к старым словам? Загрузите слова из файла, нажав кнопку '5' в главном менюю\n"
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
