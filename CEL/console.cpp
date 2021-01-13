/* FILE NAME: console.cpp
 * PROGRAMMER: Fabrika Artem
 * DATE: 12.01.2020
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
} /* End of console default constructor */

/* Console class default constructor
   ARGUMENTS:
     - int time: time for random functions;
     - int myexit: need to exit in main menu;
     - StringVector ma: word array;
   RETURNS:
     None.
*/
console::console(int time, int myexit, vector<Word> ma)
{
  Word W;

  RandomTime = time;
  is_exit = myexit;
  mas = ma;
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
     1 - if competed successfully, 0 - if error
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
     1 - if competed successfully, 0 - if error
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
     1 - if competed successfully, 0 - if error
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
     1 - if competed successfully, 0 - if error
*/
int console::ClearArray( void )
{
    system("cls");
    HeadText();
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

/* Training mode for all words in array function
   ARGUMENTS:
     None
   RETURNS:
     None.
*/
void console::MainTrainingMode( void )
{
  int i, ArraySize = (int)mas.size();

  if (ArraySize == 0)
   {
       console::MyError("Для начала тренеровки введите хотя бы одно слово");
       return;
   }
} /* End of 'MainTrainingMode' function */

/* Training mode function
   ARGUMENTS:
     None
   RETURNS:
     None.
*/
void console::TrainingMode( void )
{
    int i, is_wrong, Right = 0, ArraySize = (int)mas.size(), IndexCounter = 0;
    string UserTranslate;
    vector<int> ArrayIndexes;

    if (ArraySize == 0)
    {
        console::MyError("Для начала тренеровки введите хотя бы одно слово");
        return;
    }

    for (i = 0; i < ArraySize; i++)
      ArrayIndexes.push_back(1000);

    /* Menu before training */
    console::HeadText();
    printf("Внимательно ознакомьтесь со следующими словами:\n");
    for (i = 0; i < ArraySize; i++)
        cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
     printf("Нажмите клавишу 'd', если хотите удалить какое-либо слово\n"
           "Нажмите клавишу '0', если хотите выйти в главное меню\n"
           "Нажмите любую другую клавишу, если Вы готовы пройти тест\n");
    switch (_getch())
    {
    case 'd':
    case 'D':
    case 'в':
    case 'В':
        printf("Введите слово, которое хотите удалить:");
        cin >> UserTranslate;
        console::DeleteWord(UserTranslate);
        system("cls");
        console::TrainingMode();
        return;
    case '0':
        is_exit = 1;
        system("cls");
        return;
    default:
        system("cls");
        break;
    }

    for (int j = 0; j < ArraySize; j++)
    {
        vector <int> help_indexes;
        int current_help_index, is_help = 0, cnt = 0, WordSize, WordFlag = 1;

        console::HeadText();
        printf("Тренировка\n"
               "Для выхода из задания нажмите '0'\n");
        TestHead(j + 1, ArraySize);
        is_wrong = 1;

        /* Creating random list of words */
        i = MyRand(0, ArraySize, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize);
        while (WordFlag)
        {
          WordFlag = 0;
          if (IndexCounter <= 2 * ArraySize / 3 - 1)
          for (int q = 0; q < IndexCounter; q++)
          {
            if(i == ArrayIndexes.at(q))
            {
              WordFlag = 1;
              i = MyRand(0, ArraySize, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize);
              break;
            }
          }

          /* Find last elements */
          else
          {
            i = 0;
            while (i < ArraySize)
            {
              if (ArrayIndexes.at(i) != i)
              {
                WordFlag = 0;
                break;
              }
              i++;
            }
          }
        }
        if (IndexCounter < ArraySize)
        {
          ArrayIndexes.at(IndexCounter) = i;
          IndexCounter++;
          sort(ArrayIndexes.begin(), ArrayIndexes.end());
        }

        WordSize = (int)mas.at(i).Name.size();
        for (int q = 0; q < WordSize; q++)
          help_indexes.push_back(1000);

        while (is_wrong)
        {
            int flag = 1, is_open = 0;

            /* Help module */
            if (is_help)
            {
                current_help_index = rand() % WordSize;
                while (flag && !is_open)
                {
                  flag = 0;
                  if (help_indexes.at((long long)WordSize - 1) == 1000)
                    is_open = 0;
                  else
                    is_open = 1;
                  for (int j = 0; j < WordSize; j++)
                  {
                    if (current_help_index == help_indexes.at(j))
                    {
                      flag = 1;
                      current_help_index = rand() % WordSize;
                      break;
                    }
                  }
                }

                if (cnt < help_indexes.size())
                {
                  help_indexes.at(cnt) = current_help_index;
                  cnt++;
                }
                printf("Подсказка: ");
                for (int j = 0; j < WordSize; j++)
                {
                    if (std::find(help_indexes.begin(), help_indexes.end(), j) == help_indexes.end())
                        cout << "*";
                    else
                        cout << mas.at(i).Name.at(j);
                }
                cout << "\n";
            }

            cout << "Введите перевод слова " << mas.at(i).Translate << "\n";
            cin >> UserTranslate;

            /* Exit case */
            if (UserTranslate == "0")
            {
              system("cls");
              console::HeadText();
              printf("Тренировка\n"
                     "Вы досрочно завершили тест и перевели %i из %i слов\n"
                     "Правильно переведено %i слов\n", IndexCounter >= 1 ? IndexCounter - 1 : 0, ArraySize, Right);
              return;
            }

            transform(UserTranslate.begin(), UserTranslate.end(), UserTranslate.begin(), tolower);
            transform(mas.at(i).Name.begin(), mas.at(i).Name.end(), mas.at(i).Name.begin(), tolower);
            if (UserTranslate == mas.at(i).Name)
            {
                printf("Верно!\n");
                is_wrong = 0;
            }
            else
            {
                printf("К сожалению, неверно\n");
                is_help = 1;
                ConsoleResetWithMessage("\nДля новой попытки нажмите любую кнопку");
                console::HeadText();
                printf("Тренировка\n"
                "Для выхода из теста нажмите '0'\n");
                TestHead(j + 1, ArraySize);
            }
        }
        if (!is_help)
          Right++;
        ConsoleResetWithMessage("Для перехода к следующему слову нажмите любую кнопку");
    }
    console::HeadText();
    printf("Поздравляем!\nВы верно перевели %i слов из %i с первой попытки!\n", Right, ArraySize);
} /* End of 'TrainingMode' function */

/* Exam mode function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::ExamMode( void )
{
    int i, Right = 0, ArraySize = (int)mas.size(), IndexCounter = 0, WordFlag = 1;
    string UserTranslate, Answer;
    vector <int> ErrorIndexes, ArrayIndexes;

    if (ArraySize == 0)
    {
        console::MyError("Для начала экзамена введите хотя бы одно слово");
        return;
    }
    for (i = 0; i < ArraySize; i++)
      ArrayIndexes.push_back(1000);

    /* Menu before test */
    console::HeadText();
    printf("Внимательно ознакомьтесь со следующими словами:\n");
    for (i = 0; i < ArraySize; i++)
        cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
    printf("Нажмите клавишу 'd', если хотите удалить какое-либо слово\n"
           "Нажмите клавишу '0', если хотите выйти в главное меню\n"
           "Нажмите любую другую клавишу, если Вы готовы пройти тест\n");
    switch (_getch())
    {
    case 'd':
    case 'D':
    case 'в':
    case 'В':
        printf("Введите слово, которое хотите удалить:");
        cin >> UserTranslate;
        console::DeleteWord(UserTranslate);
        system("cls");
        console::ExamMode();
        return;
    case '0':
        is_exit = 1;
        system("cls");
        return;
    default:
        system("cls");
        break;
    }

    /* Testing words */
    for (int j = 0; j < ArraySize; j++)
    {
      console::HeadText();
      printf("Экзамен\n"
             "Для выхода из задания нажмите '0'\n");
      TestHead(j + 1, ArraySize);

      i = MyRand(0, ArraySize, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize);
      srand(i * i + IndexCounter);
      while (WordFlag)
      {
        WordFlag = 0;
        if (IndexCounter <= 2 * ArraySize / 3 - 1)
        {
          for (int q = 0; q < IndexCounter; q++)
          {
            if (i == ArrayIndexes.at(q))
            {
              WordFlag = 1;
              i = MyRand(0, ArraySize, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize);
              break;
            }
          }
        }
        else
        /* Find last elements */
        {
          i = 0;
          while (i < ArraySize)
          {
            if (ArrayIndexes.at(i) != i)
            {
              WordFlag = 0;
              break;
            }
            i++;
          }
        }
      }
      WordFlag = 1;
      if (IndexCounter < ArraySize)
      {
        ArrayIndexes.at(IndexCounter) = i;
        IndexCounter++;
        sort(ArrayIndexes.begin(), ArrayIndexes.end());
      }

      cout << "Введите перевод слова " << mas.at(i).Name << ":\n";
      cin >> UserTranslate;

     /* Exit case */
     if (UserTranslate == "0")
     {
       system("cls");
       console::HeadText();
       printf("Экзамен\n"
              "Вы досрочно завершили тест и перевели %i из %i слов\n"
              "Правильно переведено %i слов\n", IndexCounter >= 1 ? IndexCounter - 1 : 0, ArraySize, Right);
       return;
     }

      mas.at(i).NumOfUses++;
      if (UserTranslate == mas.at(i).Translate) 
      {
        printf("Верно\n");
        Right++;
      }
      else
      {
        printf("Неверно\n");
        mas.at(i).NumOfWrongAnswers++;
        mas.at(i).ErrorKoef = (double)mas.at(i).NumOfWrongAnswers / mas.at(i).NumOfUses;
        ErrorIndexes.push_back(i);
      }
      printf("Для перехода к следующему слову нажмите любую кнопку\n");
      if (_getch())
        system("cls");
    }

    /* Finish menu */
    console::HeadText();
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
    printf("Вы прошли экзамен и правильно перевели %i слов из %i \n", Right, ArraySize);
    if (Right != ArraySize)
    {
      printf("Список слов, в которых Вы сделали ошибки:\n");
      for (i = 0; i < ErrorIndexes.size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
    }
} /* End of 'ExamMode' function */

/* Test mode function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::TestMode( void )
{
    int i, Right = 0, ArraySize = (int)mas.size(), random, cnt, IndexCounter = 0;
    string tmpstr;
    vector <int> ErrorIndexes, ArrayIndexes;

    if (ArraySize < 4)
    {
        console::MyError("Для создания теста необходимо минимум 4 слова.");
        return;
    }
    for (i = 0; i < ArraySize; i++)
      ArrayIndexes.push_back(1000);

    /* Menu before test */
    console::HeadText();
    printf("Внимательно ознакомьтесь со следующими словами:\n");
    for (i = 0; i < ArraySize; i++)
        cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
    printf("Нажмите клавишу 'd', если хотите удалить какое-либо слово\n"
           "Нажмите клавишу '0', если хотите выйти в главное меню\n"
           "Нажмите любую другую клавишу, если Вы готовы пройти тест\n");
    switch (_getch())
    {
    case 'd':
    case 'D':
    case 'в':
    case 'В':
        printf("Введите слово, которое хотите удалить:");
        cin >> tmpstr;
        console::DeleteWord(tmpstr);
        system("cls");
        console::ExamMode();
        return;
    case '0':
        is_exit = 1;
        system("cls");
        return;
    default:
        system("cls");
        break;
    }

    /* Testing words */
    for (int j = 0; j < ArraySize; j++)
    {
      int WordFlag = 1;

      console::HeadText();
      printf("Тест\n"
             "Для выхода из задания нажмите '0'\n");
      TestHead(j + 1, ArraySize);

      i = MyRand(0, ArraySize, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize);
      srand(i * i + IndexCounter);
      while (WordFlag)
      {
        WordFlag = 0;
        if (IndexCounter <= 2 * ArraySize / 3 - 1)
        {
          for (int q = 0; q < IndexCounter; q++)
          {
            if (i == ArrayIndexes.at(q))
            {
              WordFlag = 1;
              i = MyRand(0, ArraySize, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize);
              break;
            }
          }
        }
        else

        /* Find last elements */
        {
          i = 0;
          while (i < ArraySize)
          {
            if (ArrayIndexes.at(i) != i)
            {
              WordFlag = 0;
              break;
            }
            i++;
          }
        }
      }
      WordFlag = 1;
      if (IndexCounter < ArraySize)
      {
        ArrayIndexes.at(IndexCounter) = i;
        IndexCounter++;
        sort(ArrayIndexes.begin(), ArrayIndexes.end());
      }

      cout << "Выберите правильный перевод слова " << mas.at(i).Name << ":\n";
      printf("Вводите номер правильного перевода\n");

      /* Creating test */
      string Answer = mas.at(i).Translate;
      vector <string> Variants;
      vector <int> TestIndexes;
      int AnswerIndex, UserAnswer;

      cnt = 0;
      RandomTime = clock();
      for (int j = 0; j < 4; j++)
      {
        Variants.push_back("empty");
        TestIndexes.push_back(8);
      }

      random = (MyRand(0, 4, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize) + rand() % 4) % 4;
      Variants.at(random) = Answer;
      AnswerIndex = random;
      TestIndexes.at(cnt) = random;
      cnt++;

      for (int j = 0; j < 3; j++)
      {
        string Wrong;
        int flag = 1;

        random = rand() % ArraySize;
        while (flag)
        {
          if (mas.at(random).Translate == Variants[0] || mas.at(random).Translate == Variants[1] ||
              mas.at(random).Translate == Variants[2] || mas.at(random).Translate == Variants[3] || mas.at(random).Translate == Answer)
            random = MyRand(0, ArraySize, Right * rand() + i + rand());
          else
            flag = 0;
        }
        flag = 1;
        Wrong = mas.at(random).Translate;

        random = MyRand(0, 4, Right * rand() + i + rand() * random);
        while (flag)
        {
          if (TestIndexes.at(0) == random || TestIndexes.at(1) == random || TestIndexes.at(2) == random || TestIndexes.at(3) == random)
            random = rand() % 4;
          else
            flag = 0;
        }
        Variants.at(random) = Wrong;
        TestIndexes.at(cnt) = random;
        cnt++;
      }
      for (int j = 0; j < 4; j++)
        cout << j + 1 << ") " << Variants.at(j) << "\n";

      cin >> UserAnswer;

     /* Exit case */
     if (UserAnswer == 0)
     {
       system("cls");
       console::HeadText();
       printf("Тест\n"
              "Вы досрочно завершили тест и перевели %i из %i слов\n"
              "Правильно переведено %i слов\n", IndexCounter >= 1 ? IndexCounter - 1 : 0, ArraySize, Right);
       return;
     }

      RandomTime = clock() - RandomTime;
      mas.at(i).NumOfUses++;
      if (UserAnswer - 1 == AnswerIndex)
      {
        printf("Верно\n");
        Right++;
      }
      else
      {
        printf("Неверно\n");
        mas.at(i).NumOfWrongAnswers++;
        mas.at(i).ErrorKoef = (double)mas.at(i).NumOfWrongAnswers / mas.at(i).NumOfUses;
        ErrorIndexes.push_back(i);
      }
      printf("Для перехода к следующему слову нажмите любую кнопку\n");
      if (_getch())
        system("cls");
    }

    /* Finish menu */
    console::HeadText();
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
    printf("Вы прошли тест и правильно перевели %i слов из %i \n", Right, ArraySize);
    if (Right != ArraySize)
    {
      printf("Список слов, в которых Вы сделали ошибки:\n");
      for (i = 0; i < ErrorIndexes.size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
    }
} /* End of 'ExamMode' function */

/* Constructor mode function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void console::ConstructorMode( void )
{
    int i, Right = 0, ArraySize = (int)mas.size(), IndexCounter = 0, WordFlag = 1;
    string UserTranslate, Answer;
    vector <int> ErrorIndexes, ArrayIndexes;

    if (ArraySize == 0)
    {
        console::MyError("Для начала задания введите хотя бы одно слово");
        return;
    }
    for (i = 0; i < ArraySize; i++)
      ArrayIndexes.push_back(1000);

    /* Menu before test */
    console::HeadText();
    printf("Внимательно ознакомьтесь со следующими словами:\n");
    for (i = 0; i < ArraySize; i++)
        cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
    printf("Нажмите клавишу 'd', если хотите удалить какое-либо слово\n"
           "Нажмите клавишу '0', если хотите выйти в главное меню\n"
           "Нажмите любую другую клавишу, если Вы готовы пройти тест\n");
    switch (_getch())
    {
    case 'd':
    case 'D':
    case 'в':
    case 'В':
        printf("Введите слово, которое хотите удалить:");
        cin >> UserTranslate;
        console::DeleteWord(UserTranslate);
        system("cls");
        console::ConstructorMode();
        return;
    case '0':
        is_exit = 1;
        system("cls");
        return;
    default:
        system("cls");
        break;
    }

    /* Testing words */
    for (int j = 0; j < ArraySize; j++)
    {
      int WordCounter = 0;

      console::HeadText();
      printf("Конструктор слов\n"
             "Для выхода из задания нажмите '0'\n");
      TestHead(j + 1, ArraySize);

      i = MyRand(0, ArraySize, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize);
      srand(i * i + IndexCounter);
      while (WordFlag)
      {
        WordFlag = 0;
        if (IndexCounter <= 2 * ArraySize / 3 - 1)
        {
          for (int q = 0; q < IndexCounter; q++)
          {
            if (i == ArrayIndexes.at(q))
            {
              WordFlag = 1;
              i = MyRand(0, ArraySize, Right * i / ((rand() + 1) % (Right + 2) + 19) + i * (rand() % 58) + rand() + ArraySize);
              break;
            }
          }
        }
        else

        /* Find last elements */
        {
          i = 0;
          while (i < ArraySize)
          {
            if (ArrayIndexes.at(i) != i)
            {
              WordFlag = 0;
              break;
            }
            i++;
          }
        }
      }
      WordFlag = 1;
      if (IndexCounter < ArraySize)
      {
        ArrayIndexes.at(IndexCounter) = i;
        IndexCounter++;
        sort(ArrayIndexes.begin(), ArrayIndexes.end());
      }

      /* Make random order of letters */
      string CurWord = mas.at(i).Name, RandLetters = "";
      vector <int> LetterIndexes;

      cout << "Введите перевод слова " << CurWord << ", которое состоит из следующих букв:\n";
      for (int q = 0; q < CurWord.size(); q++)
      {
        RandLetters.push_back(8);
        LetterIndexes.push_back(1000);
      }
      for (int q = 0; q < CurWord.size(); q++)
      {
        i = (rand() % CurWord.size() * 5 + rand() % CurWord.size() / 3 + 2) % CurWord.size();
        srand(i * i + IndexCounter);

        while (WordFlag)
        {
          WordFlag = 0;
          for (int d = 0; d < WordCounter; d++)
          {
            if (i == LetterIndexes.at(d))
            {
              WordFlag = 1;
              i = (rand() % CurWord.size() + 2 * (rand() % CurWord.size()) + 1) % CurWord.size();
              break;
            }
          }
        }
        WordFlag = 1;
        if (WordCounter < CurWord.size())
        {
          LetterIndexes.at(WordCounter) = i;
          RandLetters.at(WordCounter) = CurWord.at(i);
          WordCounter++;
        }
      }

      for (int q = 0; q < WordCounter; q++)
      {
        cout << RandLetters.at(q);
        printf(q == WordCounter - 1 ? "\n" : ", ");
      }
      cin >> UserTranslate;

     /* Exit case */
     if (UserTranslate == "0")
     {
       system("cls");
       console::HeadText();
       printf("Конструктор слов\n"
              "Вы досрочно завершили задание и перевели %i из %i слов\n"
              "Правильно переведено %i слов\n", IndexCounter >= 1 ? IndexCounter - 1 : 0, ArraySize, Right);
       return;
     }

      mas.at(i).NumOfUses++;
      if (UserTranslate == mas.at(i).Translate) 
      {
        printf("Верно\n");
        Right++;
      }
      else
      {
        printf("Неверно\n");
        mas.at(i).NumOfWrongAnswers++;
        mas.at(i).ErrorKoef = (double)mas.at(i).NumOfWrongAnswers / mas.at(i).NumOfUses;
        ErrorIndexes.push_back(i);
      }
      printf("Для перехода к следующему слову нажмите любую кнопку\n");
      if (_getch())
        system("cls");
    }

    /* Finish menu */
    console::HeadText();
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
    if (Right != ArraySize)
    {
      printf("Список слов, в которых Вы сделали ошибки:\n");
      for (i = 0; i < ErrorIndexes.size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas.at(i).Name << setw(MaxOutputWordSize) << mas.at(i).Translate << "\n";
    }
} /* End of 'ExamMode' function */

/* END OF 'console.cpp' FILE */
