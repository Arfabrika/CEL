/* FILE NAME: tasks.cpp
 * PROGRAMMER: Fabrika Artem
 * DATE: 04.02.2021
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
  int i, ArraySize = (int)mas.size(), Right = 0, IndexCounter = 0;
  vector<int> ErrorIndexes;

  if (ArraySize < 4 && TaskID == 1)
  {
      MyError("Для начала задания введите хотя бы 4 словa");
      return;
  }
  if (ArraySize == 0)
  {
     MyError("Для начала задания введите хотя бы одно слово");
     return;
  }

  if (TaskID == 5)
  {
    string alph = "abcdefghijklmnopqrstuvwxyz";

    printf("Aнглийский алфавит\n");
    for (int i = 1; i <= 26; i++)
      printf("%c - %02i-я буква\n", alph[i-1], i);
    ConsoleResetWithMessage("Для перехода к заданию нажмите любую кнопку");
  }
  else
    if (!BeginTaskMenu())
    {
      MyError("Ошибка в меню перед заданием.");
      return;
    }
  if (!MixWords())
  {
    MyError("Ошибка при перемешивании слов.");
    return;
  }
  TaskTime = clock();
  for (i = 0; i < ArraySize; i++)
  {
    switch((this->*Tasks[TaskID])(i))
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
      case 3:
        printf("Проверка слова\n");
        break;
       case 4:
        printf("Тренировка\n");
        break;
       case 5:
         printf("Проверка алфавита\n");
         printf("Вы досрочно завершили задание и запомнили %i из %i букв\n"
                "Правильно запомнено %i букв\n", IndexCounter >= 1 ? IndexCounter - 1 : 0, ArraySize, Right);
         return;
      }
      printf("Вы досрочно завершили задание и перевели %i из %i слов\n"
             "Правильно переведено %i слов\n", IndexCounter >= 1 ? IndexCounter - 1 : 0, ArraySize, Right);
      return;
    case 0:
      ErrorIndexes.push_back(i);
      break;
    case 1:
      Right++;
    }
    IndexCounter++;
    ConsoleResetWithMessage("\nДля перехода к следующему слову нажмите любую кнопку");
  }
  TaskTime = clock() - TaskTime;
  FinishTaskMenu(Right, &ErrorIndexes);
} /* End of 'MainCommonMode' function */

/* Training mode for one word function
   ARGUMENTS:
     - int IndexCounter: number of used words;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::TrainingMode( int IndexCounter )
{
    int is_wrong, ArraySize = (int)mas.size(), current_help_index, is_help = 0, cnt = 0, WordSize;
    string UserTranslate;
    vector <int> help_indexes;

    HeadText();
    printf("Тренировка\n"
      "Для выхода из задания нажмите '0'\n");
    TestHead(IndexCounter + 1, ArraySize);
    TaskTime = clock() - TaskTime;
    is_wrong = 1;

    WordSize = (int)mas.at(IndexCounter).Name.size();
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
                    cout << mas.at(IndexCounter).Name.at(j);
            }
            cout << "\n";
        }

        cout << "Введите перевод слова " << mas.at(IndexCounter).Translate << "\n";
        cin >> UserTranslate;

        /* Exit case */
        if (UserTranslate == "0")
          return -1;

        transform(UserTranslate.begin(), UserTranslate.end(), UserTranslate.begin(), tolower);
        transform(mas.at(IndexCounter).Name.begin(), mas.at(IndexCounter).Name.end(), mas.at(IndexCounter).Name.begin(), tolower);
        if (UserTranslate == mas.at(IndexCounter).Name)
        {
            printf("Верно!\n");
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
            TestHead(IndexCounter + 1, ArraySize);
        }
    }
    return 0;
} /* End of 'TrainingMode' function */

/* Exam mode for one word function
   ARGUMENTS:
     - int IndexCounter: number of used words;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::ExamMode( int IndexCounter )
{
  int ArraySize = (int)mas.size();
  string UserTranslate;

  HeadText();
  printf("Экзамен\n"
         "Для выхода из задания нажмите '0'\n");
  TestHead(IndexCounter + 1, ArraySize);

  cout << "Введите перевод слова " << mas.at(IndexCounter).Name << ":\n";
  cin >> UserTranslate;

  /* Exit case */
  if (UserTranslate == "0")
    return -1;

  mas.at(IndexCounter).NumOfUses++;
  if (UserTranslate == mas.at(IndexCounter).Translate) 
  {
    printf("Верно\n");
    return 1;
  }
  else
  {
    printf("Неверно\n");
    mas.at(IndexCounter).NumOfWrongAnswers++;
    mas.at(IndexCounter).ErrorKoef = (double)mas.at(IndexCounter).NumOfWrongAnswers / mas.at(IndexCounter).NumOfUses;
  }
   return 0;
} /* End of 'ExamMode' function */

/* Test mode for one word function
   ARGUMENTS:
     - int IndexCounter: number of used words;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::TestMode( int IndexCounter )
{
  int ArraySize = (int)mas.size(), random, cnt = 0;
  string tmpstr, Answer = mas.at(IndexCounter).Name;

  HeadText();
  printf("Тест\n"
         "Для выхода из задания нажмите '0'\n");
  TestHead(IndexCounter + 1, ArraySize);

  cout << "Выберите правильный перевод слова " << mas.at(IndexCounter).Name << ":\n";
  printf("Вводите номер правильного перевода\n");

  /* Creating test */
  vector <string> Variants;
  vector <int> TestIndexes;
  int AnswerIndex = 0, UserAnswer;

  RandomTime = clock();
  for (int j = 0; j < 4; j++)
  {
    Variants.push_back("empty");
    TestIndexes.push_back(8);
  }

  Variants.at(0) = Answer;
  TestIndexes[0] = IndexCounter;
  for (int j = 1; j < 4; j++)
  {
    int flag = 1;
    random = rand() % ArraySize;
    do
    {
      if ((mas.at(random).Translate == Variants[0] || mas.at(random).Translate == Variants[1] ||
        mas.at(random).Translate == Variants[2] || mas.at(random).Translate == Variants[3]) && (j != 3 || ArraySize > 4))
        random = rand() % ArraySize;
      else if (j == 3 && ArraySize == 4)
      {
        int LastFlag;

        for (int m = 0; m < 4; m++)
        {
          LastFlag = 1;
          for (int v = 0; v < 3; v++)
          {
            if (mas.at(m).Translate == Variants.at(v))
            {
              LastFlag = 0;
              break;
            }
          }
          if (LastFlag)
          {
            random = m;
            break;
          }
        }
        flag = 0;
      }
      else
        flag = 0;
    } while (flag);

    Variants.at(j) = mas.at(random).Translate;
    TestIndexes.at(j) = random;
  }

  for (int j = 0; j < 4; j++)
  {
    random = rand() % 4;
    int tmp = TestIndexes.at(random), rand2 = rand() % 4;
    string s = Variants.at(random);

    Variants.at(random) = Variants.at(rand2);
    Variants.at(rand2) = s;
    TestIndexes.at(random) = TestIndexes.at(rand2);
    TestIndexes.at(rand2) = tmp;
  }

  for (int j = 0; j < 4; j++)
  {
    if (Variants.at(j) == Answer)
      AnswerIndex = j;
  }

  for (int j = 0; j < 4; j++)
    cout << j + 1 << ") " << Variants.at(j) << "\n";

  cin >> tmpstr;
  UserAnswer = tmpstr[0] - '0';

  /* Exit case */
  if (UserAnswer == 0)
    return -1;
  
  RandomTime = clock() - RandomTime;
  mas.at(IndexCounter).NumOfUses++;
  if (UserAnswer - 1 == AnswerIndex)
  {
    printf("Верно\n");
    return 1;
  }
  else
  {
    printf("Неверно\n");
    mas.at(IndexCounter).NumOfWrongAnswers++;
    mas.at(IndexCounter).ErrorKoef = (double)mas.at(IndexCounter).NumOfWrongAnswers / mas.at(IndexCounter).NumOfUses;
  }
  return 0;
} /* End of 'TestMode' function */

/* Test mode for one word function
   ARGUMENTS:
     - int IndexCounter: number of used words;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::ConstructorMode( int IndexCounter )
{
  int i, ArraySize = (int)mas.size(), WordCounter = 0, WordFlag = 1;
  string UserTranslate;

  HeadText();
  printf("Конструктор слов\n"
         "Для выхода из задания нажмите '0'\n");
  TestHead(IndexCounter + 1, ArraySize);

  /* Make random order of letters */
  string CurWord = mas.at(IndexCounter).Name, RandLetters = "";
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

  mas.at(IndexCounter).NumOfUses++;
  if (UserTranslate == mas.at(IndexCounter).Translate)
  {
    printf("Верно\n");
    return 1;
  }
  else
  {
    printf("Неверно\n");
    mas.at(IndexCounter).NumOfWrongAnswers++;
    mas.at(IndexCounter).ErrorKoef = (double)mas.at(IndexCounter).NumOfWrongAnswers / mas.at(IndexCounter).NumOfUses;
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
  int i, ArraySize = (int)mas.size(), Right = 0, CurTask, IndexCounter = 0, TestFlag = 1;
  vector<int> ErrorIndexes;

  if (ArraySize == 0)
  {
    MyError("Временный массив пуст.");
    return;
  }
  if (ArraySize < 4)
  {
    HeadText();
    printf("Во временном массиве меньше 4 слов, и тест провести нельзя\n"
           "Нажмите Y, если все равно хотите выполнять задания, но тест среди них не встретится\n"
           "Для выхода нажмите клавишу '0'\n");
    char param = _getch();
    switch(param)
    {
    case 'Y':
    case 'y':
    case 'Н':
    case 'н':
      TestFlag = 0;
      system("cls");
      break;
    default:
      system("cls");
      return;
    }
  }
  if (!BeginTaskMenu())
  {
    MyError("Ошибка в меню перед заданием.");
    return;
  }
  if (!MixWords())
  {
    MyError("Ошибка в перемешивании массива.");
    return;
  }
  TaskTime = clock();
  for (i = 0; i < ArraySize; i++)
  {
    CurTask = (rand() % NumOfTasks + NumOfTasks / 2) % NumOfTasks;
    if (CurTask == 1 && !TestFlag)
      CurTask = 2;
    switch((this->*Tasks[CurTask])(i))
    {
    case -1:
      /* Finish menu */
      system("cls");
      HeadText();
      printf("Смешанный режим\n"
             "Вы досрочно завершили задание и перевели %i из %i слов\n"
             "Правильно переведено %i слов\n", IndexCounter >= 1 ? IndexCounter - 1 : 0, ArraySize, Right);
      return;
    case 0:
      ErrorIndexes.push_back(i);
      break;
    case 1:
      Right++;
    }
    ConsoleResetWithMessage("\nДля перехода к следующему слову нажмите любую кнопку");
    IndexCounter++;
  }
  TaskTime = clock() - TaskTime;
  FinishTaskMenu(Right, &ErrorIndexes);
} /* End of 'MainMixedMode' function */

/* Check spelling word mode for one word function
   ARGUMENTS:
     - int IndexCounter: number of used words;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::CheckMode( int IndexCounter )
{
  int ArraySize = (int)mas.size(), WrongLetterIndex, WordSize = (int)mas.at(IndexCounter).Name.size(),
      is_wrong = (rand() % 2 + rand() % 2 + rand() % 2) % 2, ErrorID = (rand() % 2 + rand() % 2 + rand() % 2) % 2;
  string UserAnswer;
  Word CurWord = mas.at(IndexCounter);

  HeadText();
  printf("Проверка слова\n"
         "Для выхода из задания нажмите '0'\n");
  TestHead(IndexCounter + 1, ArraySize);
  if (is_wrong == 0)
  {
    WrongLetterIndex = MyRand(0, WordSize, IndexCounter * WordSize);

    /* Type of error */
    switch(CurWord.Name.at(WrongLetterIndex))
    {
    case 'a':
      if (WrongLetterIndex > 0)
      {
        if (CurWord.Name.at(WrongLetterIndex) == 'a' && CurWord.Name.at((long long)WrongLetterIndex - 1) == 'a')
          if (ErrorID)
            CurWord.Name.erase(WrongLetterIndex, 1);
          else
            CurWord.Name.at(WrongLetterIndex) = 'a';
        break;
      }
      if (WrongLetterIndex < WordSize - 2)
      {
        if (CurWord.Name.at(WrongLetterIndex) == 'o' && CurWord.Name.at((long long)WrongLetterIndex + 1) == 'o')
          if (ErrorID)
            CurWord.Name.erase(WrongLetterIndex, 1);
          else
            CurWord.Name.at(WrongLetterIndex) = 'a';
      }
      break;

    case 'o':
      if (WrongLetterIndex > 0)
      {
        if (CurWord.Name.at(WrongLetterIndex) == 'o' && CurWord.Name.at((long long)WrongLetterIndex - 1) == 'o')
          if (ErrorID)
            CurWord.Name.erase(WrongLetterIndex, 1);
          else
            CurWord.Name.at(WrongLetterIndex) = 'a';
        break;
      }
      if (WrongLetterIndex < WordSize - 2)
      {
        if (CurWord.Name.at(WrongLetterIndex) == 'o' && CurWord.Name.at((long long)WrongLetterIndex + 1) == 'o')
          if (ErrorID)
            CurWord.Name.erase(WrongLetterIndex, 1);
          else
            CurWord.Name.at(WrongLetterIndex) = 'a';
      }
      break;

    case 'b':
      if (WrongLetterIndex > 0)
      {
        if (CurWord.Name.at(WrongLetterIndex) == 'b' && CurWord.Name.at((long long)WrongLetterIndex - 1) == 'b')
          if (ErrorID)
            CurWord.Name.erase(WrongLetterIndex, 1);
          else
            CurWord.Name.at(WrongLetterIndex) = 'd';
        break;
      }
      if (WrongLetterIndex < WordSize - 2)
      {
        if (CurWord.Name.at(WrongLetterIndex) == 'b' && CurWord.Name.at((long long)WrongLetterIndex + 1) == 'b')
          if (ErrorID)
            CurWord.Name.erase(WrongLetterIndex, 1);
          else
            CurWord.Name.at(WrongLetterIndex) = 'd';
      }
      break;

    case 'd':
      if (WrongLetterIndex > 0)
      {
        if (CurWord.Name.at(WrongLetterIndex) == 'd' && CurWord.Name.at((long long)WrongLetterIndex - 1) == 'd')
          if (ErrorID)
            CurWord.Name.erase(WrongLetterIndex, 1);
          else
            CurWord.Name.at(WrongLetterIndex) = 'b';
        break;
      }
      if (WrongLetterIndex < WordSize - 2)
      {
        if (CurWord.Name.at(WrongLetterIndex) == 'd' && CurWord.Name.at((long long)WrongLetterIndex + 1) == 'd')
          if (ErrorID)
            CurWord.Name.erase(WrongLetterIndex, 1);
          else
            CurWord.Name.at(WrongLetterIndex) = 'b';
      }
      break;

    case 'y':
      if (ErrorID)
        CurWord.Name.at(WrongLetterIndex) = 'i';
      else
        CurWord.Name.at(WrongLetterIndex) = 'e';
      break;

    case 'w':
      CurWord.Name.at(WrongLetterIndex) = 'v';
      break;

    case 'v':
      CurWord.Name.at(WrongLetterIndex) = 'w';
      break;

    case 'k':
      CurWord.Name.at(WrongLetterIndex) = 'c';
      break;

    case 'c':
      if (ErrorID)
        CurWord.Name.at(WrongLetterIndex) = 's';
      else
        CurWord.Name.at(WrongLetterIndex) = 'k';
      break;

    case 'm':
      CurWord.Name.at(WrongLetterIndex) = 'n';
      break;

    case 'n':
      CurWord.Name.at(WrongLetterIndex) = 'm';
      break;

    case 'i':
      if (ErrorID)
        CurWord.Name.at(WrongLetterIndex) = 'e';
      else
        CurWord.Name.at(WrongLetterIndex) = 'y';
      break;

    case 'e':
      if (ErrorID)
        CurWord.Name.at(WrongLetterIndex) = 'i';
      else
        CurWord.Name.at(WrongLetterIndex) = 'y';
      break;

    default:
      CurWord.Name.erase(WrongLetterIndex, 1);
    }
  }

  cout << "Есть ли ошибки в слове: " << CurWord.Name << "?\n";
  cout << "Перевод данного слова: " << CurWord.Translate << "\n";
  cout << "Если вы нашли ошибку, нажмите кнопку 'Y', если ошибок нет, нажмите кнопку 'N'\n";
  cin >> UserAnswer;

  switch(UserAnswer.at(0))
  {
  case 'Y':
  case 'y':
  case 'Н':
  case 'н':
    if (is_wrong == 0)
    {
      printf("Верно\n");
      return 1;
    }
    printf("Неверно\n");
    return 0;
  case 'N':
  case 'n':
  case 'И':
  case 'и':
    if (is_wrong == 0)
    {
      printf("Неверно\n");
      return 0;
    }
    printf("Верно\n");
    return 1;
  case '0':
    return -1;
  default:
    printf("Неверно\n");
    return 0;
  }
} /* End of 'CheckMode' function */

/* Check spelling word mode for one word function
   ARGUMENTS:
     - int LetterIndex: index ot testing letter;
   RETURNS:
     (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
*/
int console::AlphabetMode( int LetterIndex )
{
  string lets = "abcdefghijklmnopqrstuvwxyz", UserAnswer;
  
  HeadText();
  printf("Для выхода из задания нажмите '0'\n");
  TestHead(LetterIndex + 1, 28);
  LetterIndex = (LetterIndex + rand() % 28 + 19 + rand() % 28) % 28;
  printf("Введите %i-ю букву английского алфавита:", LetterIndex + 1);
  cin >> UserAnswer;
  if (UserAnswer[0] == '0')
     return -1;
  else if (UserAnswer[0] == lets[LetterIndex])
  {
    printf("Верно!\n");
    return 1;
  }
  printf("Неверно!\n");
  return 0;
} /* End of 'AlphabetMode' function */

/* END OF 'tasks.cpp' FILE */
