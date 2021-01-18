/* FILE NAME: tasks.cpp
 * PROGRAMMER: Fabrika Artem
 * DATE: 16.01.2021
 * PERPOSE: task functions file
 */

#include "main_header.h"

/* Common mode for all task function
   ARGUMENTS:
     int TaskID: index of task type;
   RETURNS:
     None.
*/
void console::MainCommonMode( int TaskID )
{
  int i, ArraySize = (int)mas.size(), Right = 0;
  vector<int> ArrayIndexes, IndexCounter, ErrorIndexes;

  if (ArraySize < 5 && TaskID == 2)
   {
       MyError("Для начала задания введите хотя бы 5 слов");
       return;
   }
  else if (ArraySize == 0)
  {
     MyError("Для начала задания введите хотя бы одно слово");
     return;
  }
  for (i = 0; i < ArraySize; i++)
    ArrayIndexes.push_back(1000);
  IndexCounter.push_back(0);
  if (!BeginTaskMenu())
    return;

  for (i = 0; i < ArraySize; i++)
  {
    switch((this->*Tasks[TaskID])(&ArrayIndexes, &IndexCounter, &ErrorIndexes))
    {
    case -1:
      /* Finish menu */
      system("cls");
      HeadText();
      switch(TaskID)
      {
      case 0:
        printf("Экзамен\n");
        break;
      case 1:
        printf("Тест\n");
        break;
      case 2:
        printf("Конструктор слов\n");
        break;
      }
      printf("Вы досрочно завершили задание и перевели %i из %i слов\n"
             "Правильно переведено %i слов\n", IndexCounter.at(0) >= 1 ? IndexCounter.at(0) - 1 : 0, ArraySize, Right);
      return;
    case 1:
      Right++;
    }
    ConsoleResetWithMessage("\nДля перехода к следующему слову нажмите любую кнопку");
  }
  FinishTaskMenu(Right, &ErrorIndexes);
} /* End of 'MainMixedMode' function */

/* Training mode for all words in array function
   ARGUMENTS:
     None
   RETURNS:
     None.
*/
void console::MainTrainingMode( void )
{
  int i, ArraySize = (int)mas.size(), Right = 0;
  vector<int> ArrayIndexes, IndexCounter;

  if (ArraySize == 0)
   {
       MyError("Для начала задания введите хотя бы одно слово");
       return;
   }
  for (i = 0; i < ArraySize; i++)
    ArrayIndexes.push_back(1000);
  IndexCounter.push_back(0);
  if (!BeginTaskMenu())
    return;

  for (i = 0; i < ArraySize; i++)
  {
    switch(TrainingMode(&ArrayIndexes, &IndexCounter))
    {
    case -1:
      /* Finish menu */
      system("cls");
      HeadText();
      printf("Тренировка\n"
             "Вы досрочно завершили задание и перевели %i из %i слов\n"
             "Правильно переведено %i слов\n", IndexCounter.at(0) >= 1 ? IndexCounter.at(0) - 1 : 0, ArraySize, Right);
      return;
    case 1:
      Right++;
    }
  }

  HeadText();
  printf("Поздравляем!\nВы верно перевели %i слов из %i с первой попытки!\n", Right, ArraySize);
} /* End of 'MainTrainingMode' function */

/* Training mode for one word function
   ARGUMENTS:
     - vector<int> *ArrayIndexes: pointer to array of word indexes;
     - vector<int> *IndexCounter: pointer to number of used words;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::TrainingMode( vector<int> *ArrayIndexes,  vector<int> *IndexCounter )
{
    int Random = rand() % 19 + 2, is_wrong, ArraySize = (int)mas.size(), current_help_index, is_help = 0, cnt = 0, WordSize, WordFlag = 1;
    string UserTranslate;
    vector <int> help_indexes;

    HeadText();
    printf("Тренировка\n"
      "Для выхода из задания нажмите '0'\n"
    ); //"Время выполнения задания: %p:%p\n", TaskTime / (double)CLOCKS_PER_SEC / 60, TaskTime / (double)CLOCKS_PER_SEC);
    TestHead(IndexCounter->at(0) + 1, ArraySize);
    TaskTime = clock() - TaskTime;
    is_wrong = 1;

    /* Creating random list of words */
    Random = MyRand(0, ArraySize, (rand() % (IndexCounter->at(0) + 2)) * Random / ((rand() + 1) % ((rand() % (IndexCounter->at(0) + 2)) + 2) + 19) 
      + Random * (rand() % 58) + rand() + ArraySize);
    while (WordFlag)
    {
      WordFlag = 0;
      if (IndexCounter->at(0) <= 2 * ArraySize / 3 - 1)
      for (int q = 0; q < IndexCounter->at(0); q++)
      {
        if(Random == ArrayIndexes->at(q))
        {
          WordFlag = 1;
          Random = MyRand(0, ArraySize, (rand() % (IndexCounter->at(0) + 2)) * Random / ((rand() + 1) % ((rand() % (IndexCounter->at(0) + 2)) + 2) + 19)
            + Random * (rand() % 58) + rand() + ArraySize);
          break;
        }
      }

      /* Find last elements */
      else
      {
        Random = 0;
        while (Random < ArraySize)
        {
          if (ArrayIndexes->at(Random) != Random)
          {
            WordFlag = 0;
            break;
          }
          Random++;
        }
      }
    }
    if (IndexCounter->at(0) < ArraySize)
    {
      ArrayIndexes->at(IndexCounter->at(0)) = Random;
      IndexCounter->at(0)++;
      sort(ArrayIndexes->begin(), ArrayIndexes->end());
    }

    WordSize = (int)mas.at(Random).Name.size();
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
                if (find(help_indexes.begin(), help_indexes.end(), j) == help_indexes.end())
                    cout << "*";
                else
                    cout << mas.at(Random).Name.at(j);
            }
            cout << "\n";
        }

        cout << "Введите перевод слова " << mas.at(Random).Translate << "\n";
        cin >> UserTranslate;

        /* Exit case */
        if (UserTranslate == "0")
          return -1;

        transform(UserTranslate.begin(), UserTranslate.end(), UserTranslate.begin(), tolower);
        transform(mas.at(Random).Name.begin(), mas.at(Random).Name.end(), mas.at(Random).Name.begin(), tolower);
        if (UserTranslate == mas.at(Random).Name)
        {
            printf("Верно!\n");
            ConsoleResetWithMessage("\nДля перехода к следующему слову нажмите любую кнопку");
            if (!is_help)
              return 1;
            return 0;
        }
        else
        {
            printf("К сожалению, неверно\n");
            is_help = 1;
            ConsoleResetWithMessage("\nДля новой попытки нажмите любую кнопку");
            HeadText();
            printf("Тренировка\n"
            "Для выхода из теста нажмите '0'\n");
            TestHead(IndexCounter->at(0), ArraySize);
        }
    }
    return 0;
} /* End of 'TrainingMode' function */

#if 0
/* Exam mode for all words in array function
   ARGUMENTS:
     None
   RETURNS:
     None.
*/
void console::MainExamMode( void )
{
  int i, ArraySize = (int)mas.size(), Right = 0;
  vector<int> ArrayIndexes, IndexCounter, ErrorIndexes;

  if (ArraySize == 0)
   {
       MyError("Для начала задания введите хотя бы одно слово");
       return;
   }
  for (i = 0; i < ArraySize; i++)
    ArrayIndexes.push_back(1000);
  IndexCounter.push_back(0);
  if (!BeginTaskMenu())
    return;

  for (i = 0; i < ArraySize; i++)
  {
    switch(ExamMode(&ArrayIndexes, &IndexCounter, &ErrorIndexes))
    {
    case -1:
      /* Finish menu */
      system("cls");
      HeadText();
      printf("Экзамен\n"
             "Вы досрочно завершили задание и перевели %i из %i слов\n"
             "Правильно переведено %i слов\n", IndexCounter.at(0) >= 1 ? IndexCounter.at(0) - 1 : 0, ArraySize, Right);
      return;
    case 1:
      Right++;
    }
    ConsoleResetWithMessage("\nДля перехода к следующему слову нажмите любую кнопку");
  }
  FinishTaskMenu(Right, &ErrorIndexes);
} /* End of 'MainTrainingMode' function */
#endif 0
/* Exam mode for one word function
   ARGUMENTS:
     - vector<int> *ArrayIndexes: pointer to array of word indexes;
     - vector<int> * IndexCounter: pointer to number of used words;
     - vector<int> * ErrorIndexes: pointer to array of wrong word indexes;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::ExamMode( vector<int> *ArrayIndexes, vector<int> *IndexCounter,  vector<int> *ErrorIndexes )
{
  int Random = rand() % 19 + 1, ArraySize = (int)mas.size(), WordFlag = 1;
  string UserTranslate, Answer;

  console::HeadText();
  printf("Экзамен\n"
         "Для выхода из задания нажмите '0'\n");
  TestHead(IndexCounter->at(0) + 1, ArraySize);

  Random = MyRand(0, ArraySize, (rand() % 19 + 2) * Random / ((rand() + 1) % ((rand() % 19 + 2) + 2) + 19) + Random * (rand() % 58) + rand() + ArraySize);
  srand(Random * Random + IndexCounter->at(0));
  while (WordFlag)
  {
    WordFlag = 0;
    if (IndexCounter->at(0) <= 2 * ArraySize / 3 - 1)
    {
      for (int q = 0; q < IndexCounter->at(0); q++)
      {
        if (Random == ArrayIndexes->at(q))
        {
          WordFlag = 1;
          Random = MyRand(0, ArraySize, (rand() % 19 + 2) * Random / ((rand() + 1) % ((rand() % 19 + 2) + 2) + 19) + Random * (rand() % 58) + rand() + ArraySize);
          break;
        }
      }
    }
    else
    /* Find last elements */
    {
      Random = 0;
      while (Random < ArraySize)
      {
        if (ArrayIndexes->at(Random) != Random)
        {
          WordFlag = 0;
          break;
        }
        Random++;
      }
    }
  }
  WordFlag = 1;
  if (IndexCounter->at(0) < ArraySize)
  {
    ArrayIndexes->at(IndexCounter->at(0)) = Random;
    IndexCounter->at(0)++;
    sort(ArrayIndexes->begin(), ArrayIndexes->end());
  }

  cout << "Введите перевод слова " << mas.at(Random).Name << ":\n";
  cin >> UserTranslate;

  /* Exit case */
  if (UserTranslate == "0")
    return -1;

  mas.at(Random).NumOfUses++;
  if (UserTranslate == mas.at(Random).Translate) 
  {
    printf("Верно\n");
    return 1;
  }
  else
  {
    printf("Неверно\n");
    mas.at(Random).NumOfWrongAnswers++;
    mas.at(Random).ErrorKoef = (double)mas.at(Random).NumOfWrongAnswers / mas.at(Random).NumOfUses;
    ErrorIndexes->push_back(Random);
  }
   return 0;
} /* End of 'ExamMode' function */

#if 0
/* Test mode for all words in array function
   ARGUMENTS:
     None
   RETURNS:
     None.
*/
void console::MainTestMode( void )
{
  int i, ArraySize = (int)mas.size(), Right = 0;
  vector<int> ArrayIndexes, IndexCounter, ErrorIndexes;

  if (ArraySize <= 4)
   {
       MyError("Для начала теста введите хотя бы четыре слова");
       return;
   }
  for (i = 0; i < ArraySize; i++)
    ArrayIndexes.push_back(1000);
  IndexCounter.push_back(0);
  if (!BeginTaskMenu())
    return;

  for (i = 0; i < ArraySize; i++)
  {
    switch(TestMode(&ArrayIndexes, &IndexCounter, &ErrorIndexes))
    {
    case -1:
      /* Finish menu */
      system("cls");
      HeadText();
      printf("Тест\n"
             "Вы досрочно завершили задание и перевели %i из %i слов\n"
             "Правильно переведено %i слов\n", IndexCounter.at(0) >= 1 ? IndexCounter.at(0) - 1 : 0, ArraySize, Right);
      return;
    case 1:
      Right++;
    }
    ConsoleResetWithMessage("\nДля перехода к следующему слову нажмите любую кнопку");
  }
  FinishTaskMenu(Right, &ErrorIndexes);
} /* End of 'MainTrainingMode' function */
#endif 0

/* Test mode for one word function
   ARGUMENTS:
     - vector<int> *ArrayIndexes: pointer to array of word indexes;
     - vector<int> * IndexCounter: pointer to number of used words;
     - vector<int> * ErrorIndexes: pointer to array of wrong word indexes;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::TestMode( vector<int> *ArrayIndexes, vector<int> *IndexCounter,  vector<int> *ErrorIndexes )
{
  int i, ArraySize = (int)mas.size(), random, cnt, WordFlag = 1;
  string tmpstr;

  HeadText();
  printf("Тест\n"
         "Для выхода из задания нажмите '0'\n");
  TestHead(IndexCounter->at(0) + 1, ArraySize);

  i = MyRand(0, ArraySize, ((rand() + 1) % (rand() % 19 + 2) + 19) + (rand() % 58) + rand() + ArraySize);
  srand(i * i + IndexCounter->at(0));
  while (WordFlag)
  {
    WordFlag = 0;
    if (IndexCounter->at(0) <= 2 * ArraySize / 3 - 1)
    {
      for (int q = 0; q < IndexCounter->at(0); q++)
      {
        if (i == ArrayIndexes->at(q))
        {
          WordFlag = 1;
          i = MyRand(0, ArraySize, ((rand() + 1) % (rand() % 19 + 2) + 19) + (rand() % 58) + rand() + ArraySize);
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
        if (ArrayIndexes->at(i) != i)
        {
          WordFlag = 0;
          break;
        }
        i++;
      }
    }
  }
  WordFlag = 1;
  if (IndexCounter->at(0) < ArraySize)
  {
    ArrayIndexes->at(IndexCounter->at(0)) = i;
    IndexCounter->at(0)++;
    sort(ArrayIndexes->begin(), ArrayIndexes->end());
  }

  cout << "Выберите правильный перевод слова " << mas.at(i).Name << ":\n";
  printf("Вводите номер правильного перевода\n");

  /* Creating test */
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

  random = (MyRand(0, 4, i / ((rand() + 1) % (rand() % 5 + 2) + 19) + i * (rand() % 58) + rand() + ArraySize) + rand() % 4) % 4;
  Variants.at(random) = mas.at(i).Translate;
  AnswerIndex = random;
  TestIndexes.at(cnt) = random;
  cnt++;

  for(int j = 0; j < 3; j++)
  {
    string Wrong;
    int flag = 1;

    random = rand() % ArraySize;
    while(flag)
    {
      if (mas.at(random).Translate == Variants[0] || mas.at(random).Translate == Variants[1] ||
        mas.at(random).Translate == Variants[2] || mas.at(random).Translate == Variants[3])
        random = MyRand(0, ArraySize, 3 * rand() + i + rand());
      else
        flag = 0;
    }
    flag = 1;
    Wrong = mas.at(random).Translate;

    random = MyRand(0, 4, 2 * rand() + i + rand() * random);
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
    return -1;
  
  RandomTime = clock() - RandomTime;
  mas.at(i).NumOfUses++;
  if (UserAnswer - 1 == AnswerIndex)
  {
    printf("Верно\n");
    return 1;
  }
  else
  {
    printf("Неверно\n");
    mas.at(i).NumOfWrongAnswers++;
    mas.at(i).ErrorKoef = (double)mas.at(i).NumOfWrongAnswers / mas.at(i).NumOfUses;
    ErrorIndexes->push_back(i);
  }
  return 0;
} /* End of 'TestMode' function */

#if 0
/* Constructor mode for all words in array function
   ARGUMENTS:
     None
   RETURNS:
     None.
*/
void console::MainConstructorMode( void )
{
  int i, ArraySize = (int)mas.size(), Right = 0;
  vector<int> ArrayIndexes, IndexCounter, ErrorIndexes;

  if (ArraySize == 0)
   {
       MyError("Для начала задания введите хотя бы одно слово");
       return;
   }
  for (i = 0; i < ArraySize; i++)
    ArrayIndexes.push_back(1000);
  IndexCounter.push_back(0);
  if (!BeginTaskMenu())
    return;

  for (i = 0; i < ArraySize; i++)
  {
    switch(ConstructorMode(&ArrayIndexes, &IndexCounter, &ErrorIndexes))
    {
    case -1:
      /* Finish menu */
      system("cls");
      HeadText();
      printf("Конструктор слов\n"
             "Вы досрочно завершили задание и перевели %i из %i слов\n"
             "Правильно переведено %i слов\n", IndexCounter.at(0) >= 1 ? IndexCounter.at(0) - 1 : 0, ArraySize, Right);
      return;
    case 1:
      Right++;
    }
    ConsoleResetWithMessage("\nДля перехода к следующему слову нажмите любую кнопку");
  }
  FinishTaskMenu(Right, &ErrorIndexes);
} /* End of 'MainTrainingMode' function */
#endif 0

/* Test mode for one word function
   ARGUMENTS:
     - vector<int> *ArrayIndexes: pointer to array of word indexes;
     - vector<int> * IndexCounter: pointer to number of used words;
     - vector<int> * ErrorIndexes: pointer to array of wrong word indexes;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::ConstructorMode( vector<int> *ArrayIndexes, vector<int> *IndexCounter,  vector<int> *ErrorIndexes )
{
  int i, ArraySize = (int)mas.size(), WordFlag = 1, WordCounter = 0, AnswerIndex;
  string UserTranslate;

  HeadText();
  printf("Конструктор слов\n"
         "Для выхода из задания нажмите '0'\n");
  TestHead(IndexCounter->at(0) + 1, ArraySize);

  i = MyRand(0, ArraySize, (rand() + 1) % 2 + 19 + rand() % 58 + rand() + ArraySize);
  srand(i * i + IndexCounter->at(0));
  while (WordFlag)
  {
    WordFlag = 0;
    if (IndexCounter->at(0) <= 2 * ArraySize / 3 - 1)
    {
      for (int q = 0; q < IndexCounter->at(0); q++)
      {
        if (i == ArrayIndexes->at(q))
        {
          WordFlag = 1;
          i = MyRand(0, ArraySize, (rand() + 1) % 2 + 19 + rand() % 58 + rand() + ArraySize);
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
        if (ArrayIndexes->at(i) != i)
        {
          WordFlag = 0;
          break;
        }
        i++;
      }
    }
  }
  WordFlag = 1;
  if (IndexCounter->at(0) < ArraySize)
  {
    ArrayIndexes->at(IndexCounter->at(0)) = i;
    IndexCounter->at(0)++;
    sort(ArrayIndexes->begin(), ArrayIndexes->end());
  }

  /* Make random order of letters */
  string CurWord = mas.at(i).Name, RandLetters = "";
  vector <int> LetterIndexes;

  AnswerIndex = i;
  cout << "Введите перевод слова " << CurWord << ", которое состоит из следующих букв:\n";
  for (int q = 0; q < CurWord.size(); q++)
  {
    RandLetters.push_back(8);
    LetterIndexes.push_back(1000);
  }
  for (int q = 0; q < CurWord.size(); q++)
  {
    i = (rand() % CurWord.size() * 5 + rand() % CurWord.size() / 3 + 2) % CurWord.size();

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
    return -1;

  mas.at(AnswerIndex).NumOfUses++;
  if (UserTranslate == mas.at(AnswerIndex).Translate)
  {
    printf("Верно\n");
    return 1;
  }
  else
  {
    printf("Неверно\n");
    mas.at(AnswerIndex).NumOfWrongAnswers++;
    mas.at(AnswerIndex).ErrorKoef = (double)mas.at(AnswerIndex).NumOfWrongAnswers / mas.at(AnswerIndex).NumOfUses;
    ErrorIndexes->push_back(AnswerIndex);
  }
  return 0;
} /* End of 'ConstructorMode' function */

/* Mixed mode for all words in array function
   ARGUMENTS:
     None
   RETURNS:
     None.
*/
void console::MainMixedMode( void )
{
  int i, ArraySize = (int)mas.size(), Right = 0, CurTask;
  vector<int> ArrayIndexes, IndexCounter, ErrorIndexes;

  if (ArraySize < 5)
   {
       MyError("Для начала задания введите хотя бы 5 слов");
       return;
   }
  for (i = 0; i < ArraySize; i++)
    ArrayIndexes.push_back(1000);
  IndexCounter.push_back(0);
  if (!BeginTaskMenu())
    return;

  for (i = 0; i < ArraySize; i++)
  {
    CurTask = (rand() % NumOfTasks + NumOfTasks / 2) % NumOfTasks;
    switch((this->*Tasks[CurTask])(&ArrayIndexes, &IndexCounter, &ErrorIndexes))
    {
    case -1:
      /* Finish menu */
      system("cls");
      HeadText();
      printf("Смешанный режим\n"
             "Вы досрочно завершили задание и перевели %i из %i слов\n"
             "Правильно переведено %i слов\n", IndexCounter.at(0) >= 1 ? IndexCounter.at(0) - 1 : 0, ArraySize, Right);
      return;
    case 1:
      Right++;
    }
    ConsoleResetWithMessage("\nДля перехода к следующему слову нажмите любую кнопку");
  }
  FinishTaskMenu(Right, &ErrorIndexes);
} /* End of 'MainMixedMode' function */

/* END OF 'tasks.cpp' FILE */
