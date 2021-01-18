/* FILE NAME: console.cpp
 * PROGRAMMER: Fabrika Artem
 * DATE: 16.01.2021
 * PERPOSE: console functions file
 */

#include "main_header.h"

/* Console class default constructor
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
console::console()
{
  RandomTime = clock();
  is_exit = 0;
  TaskTime = 0;

  Tasks[0] = &console::ExamMode;
  Tasks[1] = &console::TestMode;
  Tasks[2] = &console::ConstructorMode;
} /* End of console default constructor */

/* Console class default constructor
   ARGUMENTS:
     - int time: time for random functions;
     - int myexit: need to exit in main menu;
     - StringVector ma: word array;
     - int task_time: time of completing a task;
   RETURNS:
     None.
*/
console::console(int time, int myexit, vector<Word> ma, int task_time)
{
  Word W;

  RandomTime = time;
  is_exit = myexit;
  mas = ma;
  TaskTime = task_time;

  Tasks[0] = &console::ExamMode;
  Tasks[1] = &console::TestMode;
  Tasks[2] = &console::ConstructorMode;
} /* End of console constructor */

/* Read word function
   ARGUMENTS:
     None;
   RETURNS:
     (int) - 1 if successed, 0 if failed
*/
int console::ReadWord( void )
{
    Word W;
    string s;

    HeadText();
    printf("Введите слово:\n");
    getline(cin, s);
    if (s == "")
    {
      ConsoleResetWithMessage("Введенное слово явлется пустым! Введите корректное слово\n");
      return ReadWord();
    }
    W.Name = s;

    printf("Введите перевод:\n");
    getline(cin, s);
    while (s == "")
    {
      printf("Введенное слово явлется пустым! Введите корректное слово\n");
      getline(cin, s);
    }
    W.Translate = s;

    for (int i = 0; i < mas.size(); i++)
    {
      if (W.Name == mas.at(i).Name)
      {
        MyError("Вводимое слово уже есть в массиве.");
        return 0;
      }
      else if (W.Translate == mas.at(i).Translate)
      {
        cout << "У слова " << mas.at(i).Name << " есть уже такой перевод! Измените перевод вводимого слова: ";
        getline(cin, s);
        W.Translate = s;
      }
    }

    W.NumOfUses = 0;
    W.NumOfWrongAnswers = 0;
    W.ErrorKoef = 0;
    mas.push_back(W);
    return 1;
} /* End of 'ReadWord' function */

/* Output array function
   ARGUMENTS:
     None.
   RETURNS:
     None.
*/
void console::OutputArray( void )
{
    HeadText();
    if (mas.size() == 0)
    {
        printf("Массив слов пуст!\n");
        return;
    }
    cout << left << setw(MaxOutputWordSize) << "Слово" << setw(MaxOutputWordSize) << "Перевод" << "Количество проверок слова  Количество ошибок в слове  \n"
        ;// "Коэффициент правильных ответов слова\n";
    for (int i = 0; i < mas.size(); i++)
        cout << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate
        << setw(15) << " " << mas.at(i).NumOfUses << setw(20) << "    " << mas.at(i).NumOfWrongAnswers << "\n";//<< setw(30) << "            " << mas.at(i).ErrorKoef << "\n";
} /* End of 'OutputArray' function */

/* Delete word from temporary array function
   ARGUMENTS:
     - string s: key word;
   RETURNS:
     1 - if completed successfully, 0 - if error
*/
int console::DeleteWord( string s )
{
    if (mas.size() == 0)
    {
        MyError("Временный массив пуст.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas.size(); i++)
    {
        if (mas.at(i).Name == s)
        {
            mas.erase(mas.begin() + i);
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("Введенное слово не найдено в массиве.");
        return 0;
    }
    return 1;
} /* End of 'DeleteWord' function*/

/* Edit word in temporary array function
   ARGUMENTS:
     - string s: key word;
   RETURNS:
     1 - if completed successfully, 0 - if error
*/
int console::EditWord( string s )
{
    system("cls");
    HeadText();
    if (mas.size() == 0)
    {
        MyError("Временный массив пуст.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas.size(); i++)
    {
        if (mas.at(i).Name == s)
        {
            string newtr;

            printf("Введите новый перевод:\n");
            cin >> newtr;
            mas.at(i).Translate = newtr;
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("Введенное слово не найдено в массиве.");
        return 0;
    }
    return 1;
} /*End of 'EditWord' function */

/* Clear word's parameters in temporary array function
   ARGUMENTS:
     - string s: key word;
   RETURNS:
     1 - if completed successfully, 0 - if error
*/
int console::ResetProgress( string s )
{
    if (mas.size() == 0)
    {
        MyError("Временный массив пуст.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas.size(); i++)
    {
        if (mas.at(i).Name == s)
        {
            mas.at(i).NumOfUses = 0;
            mas.at(i).ErrorKoef = 0;
            mas.at(i).NumOfWrongAnswers = 0;
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("Введенное слово не найдено в массиве.");
        return 0;
    }
    return 1;
} /*End of 'ResetProgress' function */

/* Clear temporary array function
   ARGUMENTS:
     None.
   RETURNS:
     1 - if completed successfully, 0 - if error
*/
int console::ClearArray( void )
{
    if (mas.size() == 0)
        return 0;
    printf("Вы действительно хотите очистить временный массив? Данные в нем нельзя будет восстановить\n"
    "Для подтверждения операции нажмите клавишу Y\n"
    "Для выхода в главное меню нажмите любую другую кнопку\n");
    switch(_getch())
    {
    case 'y':
    case 'Y':
    case 'н':
    case 'Н':
      mas.clear();
      db->storage.clear();
      return 1;
    default:
      return 0;
    }
} /*End of 'ClearArray' function */

/* Mix words in random order function
   ARGUMENTS:
     None.
   RETURNS:
     1 - if completed successfully, 0 - if error
*/
int console::MixWords( void )
{
  int random, ArraySize = (int)mas.size(), WordFlag = 1, IndexCounter;
  vector <int> ArrayIndexes;
  string UserTranslate;

  if (ArraySize == 0)
    return 0;
  for (int i = 0; i < ArraySize; i++)
    ArrayIndexes.push_back(1000);
  
  for (IndexCounter = 0; IndexCounter < ArraySize; IndexCounter++)
  {
    random = MyRand(0, ArraySize, (rand() + 1) % 2 + 19 + rand() % 58 + rand() + ArraySize);
    while(WordFlag)
    {
      WordFlag = 0;
      if(IndexCounter <= 3 * ArraySize / 4 - 1)
      {
        for(int q = 0; q < IndexCounter; q++)
        {
          if(random == ArrayIndexes.at(q))
          {
            WordFlag = 1;
            random = MyRand(0, ArraySize, (rand() + 1) % 2 + 19 + rand() % 58 + rand() + ArraySize);
            break;
          }
        }
      }
      else

        /* Find last elements */
      {
        random = 0;
        while(random < ArraySize)
        {
          if(ArrayIndexes.at(random) != random)
          {
            WordFlag = 0;
            break;
          }
          random++;
        }
      }
    }
    WordFlag = 1;
    if (IndexCounter < ArraySize)
      ArrayIndexes.at(IndexCounter) = random;

    Word tmp = mas.at(IndexCounter);

    mas.at(IndexCounter) = mas.at(random);
    mas.at(random) = tmp;
  }
  return 1;
} /* End of 'MixWords' function */

/* Sort words in alphabet order function
   ARGUMENTS:
     None.
   RETURNS:
     1 - if completed successfully, 0 - if error
*/
int console::SortAlpha( void )
{
  int ArraySize = (int)mas.size();

  if (ArraySize == 0)
    return 0;
  
  for (int i = 0; i < ArraySize; i++)
    for (int j = i; j < ArraySize; j++)
    {
      if (mas.at(i).Name > mas.at(j).Name)
      {
        Word tmp = mas.at(i);

        mas.at(i) = mas.at(j);
        mas.at(j) = tmp;
      }
    }
  return 1;
} /* End of 'SortAlpha' function */

/* Sort words in back alphabet order function
   ARGUMENTS:
     None.
   RETURNS:
     1 - if completed successfully, 0 - if error
*/
int console::SortAlphaBack( void )
{
  int ArraySize = (int)mas.size();

  if (ArraySize == 0)
    return 0;
  
  for (int i = 0; i < ArraySize; i++)
    for (int j = i; j < ArraySize; j++)
    {
      if (mas.at(i).Name < mas.at(j).Name)
      {
        Word tmp = mas.at(i);

        mas.at(i) = mas.at(j);
        mas.at(j) = tmp;
      }
    }
  return 1;
} /* End of 'SortAlphaBack' function */

/* END OF 'console.cpp' FILE */
