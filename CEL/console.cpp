/* FILE NAME: console.cpp
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 08.01.2020
 * PERPOSE: console functions file
 */

#include "main_header.h"

console cons;

/* Upgraded random function
   ARGUMENTS:
     - int mi: minimum random number;
     - int ma: maximum random number;
     - int param: random parameter
   RETURNS:
     (int) random number.
*/
int MyRand(int mi, int ma, int param )
{
  int num;

  if (mi == 0)
    mi = 1;
  if (ma == 0)
    ma = 1;
  if (param == 0)
    param = rand() % 5648 + 19;
  num = (((mi * ma + ma / param) / mi) * cons.RandomTime + (rand() % param) * param) % ma;
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
    printf("��� ������ ������������ ������ ���� ������� �� ��������������� �������\n"
        "0 - �����\n"
        "1 - ������ ����� �����\n"
        "2 - �������� � ��������� ������� ����\n"
        "3 - �������� ����������\n"
        "4 - �������� �������\n"
        "5 - �������� ����\n"
        "6 - ��������� ������ ���� � ����\n"
        "7 - ��������� ������ ���� �� �����\n"
        "9 - ������/� ���������\n");
} /* End of 'Menu' function */

/* Print menu of temporary array function
   ARGUMENTS:
     None;
   RETURNS:
      None.
*/
void console::ArrayMenu(void)
{
    printf("0 - ����������� � ������� ����\n"
        "1 - ����������� ��������� ������\n"
        "2 - ������� ����� �� ���������� �������\n"
        "3 - �������� ������� �����\n"
        "4 - �������� �������� �����\n"
        "5 - ������� ��������� ������\n");
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
     - None;
   RETURNS:
     None.
*/
void console::MyError(string s)
{
    cout << "������ ��� ���������� ��������: " << s << "\n��������� ������������ ��������� ������\n";
} /*End of 'MyError' function */

/* Print helping text about program function
   ARGUMENTS:
     None;
   RETURNS:
      None.
*/
void console::Help(void)
{
    printf("Console English Learning - ���������, ���������� � ���������� ���� ������ ������\n"
        "��� �� ������������?\n"
        "��� ������ ����� ������ ������������ ���������� ����. ����� ������ '1' � ������� ����, �� ��������� � ����� ���������� �����.\n"
        "���������� ��� ���������� ����� �����, ����� ������ '2' � ������� ����, � ����� ����� ������ '1' � ��������������� ����. � ��� �� ���� ����� ������� ����� �� ������ ��� �������� ��� �������.\n"
        "��� ����� ��������� ����������� ���� �� ������ ������ ����������, ����� ������ '3' � ������� ����.\n"
        "�� ��������� ��������� ����� � ����! � ��������� ������, ����� ������ �� ��������� ������ ���� ����� �������. ��� ���������� ������ ���� � ���� ������� ������ '4' � ������� ����.\n"
        "������ ��������� � ������ ������? ��������� ����� �� �����, ����� ������ '5' � ������� �����\n"
        "������� � ��������!\n");
} /* End of 'Help' function */

/* Read word function
   ARGUMENTS:
     - Word *mas: pointer to word array;
   RETURNS:
     (int) - 1 if successed, 0 if failed
*/
int console::ReadWord( vector<Word>* mas )
{
    Word W;
    string s;

    HeadText();
    printf("������� �����:\n");
    getline(cin, s);
    W.Name = s;
    printf("������� �������:\n");
    getline(cin, s);
    W.Translate = s;

    for (int i = 0; i < mas->size(); i++)
    {
      if (W.Name == mas->at(i).Name && W.Translate == mas->at(i).Translate)
      {
        MyError("�������� ����� ��� ���� � �������.");
        return 0;
      }
    }

    W.NumOfUses = 0;
    W.NumOfWrongAnswers = 0;
    W.ErrorKoef = 0;
    mas->push_back(W);
    return 1;
} /* End of 'ReadWord' function */

/* Clear and refill console function
   ARGUMENTS:
     None;
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
    printf("����������� � ������� ���� ����� %i", ConsoleResetWithMessageTime / 1000);
    for (int i = ConsoleResetWithMessageTime - 1; i > 1000; i-= 1000)
    {
        printf(", %i", i / 1000);
        Sleep(1000);
    }
    system("cls");*/
} /* End of 'ConsoleResetWithMessage' function */

/* Output array function
   ARGUMENTS:
     - Word *mas: pointer to word array
   RETURNS:
     None.
*/
void console::OutputArray(vector<Word>* mas) 
{
    HeadText();
    if (mas->size() == 0)
    {
        printf("������ ���� ����!\n");
        return;
    }
    cout << left << setw(MaxOutputWordSize) << "�����" << setw(MaxOutputWordSize) << "�������" << "���������� �������� �����  ���������� ������ � �����  \n"
        ;// "����������� ���������� ������� �����\n";
    for (int i = 0; i < mas->size(); i++)
        cout << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate
        << setw(15) << " " << mas->at(i).NumOfUses << setw(20) << "    " << mas->at(i).NumOfWrongAnswers << "\n";//<< setw(30) << "            " << mas->at(i).ErrorKoef << "\n";
} /* End of 'OutputArray' function */

/* Delete word from temporary array function
   ARGUMENTS:
     - Word *mas: pointer to word array
     - string s: key word;
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::DeleteWord(vector<Word>* mas, string s)
{
    if (mas->size() == 0)
    {
        MyError("��������� ������ ����.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas->size(); i++)
    {
        if (mas->at(i).Name == s)
        {
            mas->erase(mas->begin() + i);
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("��������� ����� �� ������� � �������.");
        return 0;
    }
    return 1;
} /* End of 'DeleteWord' function*/

/* Edit word in temporary array function
   ARGUMENTS:
     - Word *mas: pointer to word array
     - string s: key word;
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::EditWord(vector<Word>* mas, string s)
{
    system("cls");
    HeadText();
    if (mas->size() == 0)
    {
        MyError("��������� ������ ����.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas->size(); i++)
    {
        if (mas->at(i).Name == s)
        {
            string newtr;

            printf("������� ����� �������:\n");
            cin >> newtr;
            mas->at(i).Translate = newtr;
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("��������� ����� �� ������� � �������.");
        return 0;
    }
    return 1;
} /*End of 'EditWord' function */

/* Clear word's parameters in temporary array function
   ARGUMENTS:
     - Word *mas: pointer to word array
     - string s: key word;
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::ResetProgress(vector<Word>* mas, string s)
{
    if (mas->size() == 0)
    {
        MyError("��������� ������ ����.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas->size(); i++)
    {
        if (mas->at(i).Name == s)
        {
            mas->at(i).NumOfUses = 0;
            mas->at(i).ErrorKoef = 0;
            mas->at(i).NumOfWrongAnswers = 0;
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        MyError("��������� ����� �� ������� � �������.");
        return 0;
    }
    return 1;
} /*End of 'ResetProgress' function */

/* Clear temporary array function
   ARGUMENTS:
     - Word *mas: pointer to word array
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::ClearArray(vector<Word>* mas)
{
    system("cls");
    HeadText();
    if (mas->size() == 0)
        return 0;
    printf("�� ������������� ������ �������� ��������� ������? ������ � ��� ������ ����� ������������\n"
    "��� ������������� �������� ������� ������� Y\n"
    "��� ������ � ������� ���� ������� ����� ������ ������\n");
    switch(_getch())
    {
    case 'y':
    case 'Y':
    case '�':
    case '�':
      mas->clear();
      return 1;
    default:
      return 0;
    }
} /*End of 'ClearArray' function */

/* Training mode function
   ARGUMENTS:
     - Word *mas: pointer to training word array
   RETURNS:
     None.
*/
void console::TrainingMode(vector<Word>* mas)
{
    int i, is_wrong, Right = 0;
    string UserTranslate;

    if (mas->size() == 0)
    {
        console::MyError("��� ������ ���������� ������� ���� �� ���� �����");
        return;
    }

    console::HeadText();
    printf("����������� ������������ �� ���������� �������:\n");
    for (i = 0; i < mas->size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    ConsoleResetWithMessage("��� ������ ���������� ������� ����� ������");
    for (i = 0; i < mas->size(); i++)
    {
        vector <int> help_indexes;
        int current_help_index, is_help = 0;

        console::HeadText();
        is_wrong = 1;
        while (is_wrong)
        {
            /* Help module */
            if (is_help)
            {
                current_help_index = rand() % mas->at(i).Name.size();
                help_indexes.push_back(current_help_index);
                printf("���������: ");
                for (int j = 0; j < mas->at(i).Name.size(); j++)
                {
                    if (std::find(help_indexes.begin(), help_indexes.end(), j) == help_indexes.end())
                        cout << "*";
                    else
                        cout << mas->at(i).Name.at(j);
                }
                cout << "\n";
            }

            cout << "������� ������� ����� " << mas->at(i).Translate << "\n";
            cin >> UserTranslate;

            transform(UserTranslate.begin(), UserTranslate.end(), UserTranslate.begin(), tolower);
            transform(mas->at(i).Name.begin(), mas->at(i).Name.end(), mas->at(i).Name.begin(), tolower);
            if (UserTranslate == mas->at(i).Name)
            {
                printf("�����!\n");
                is_wrong = 0;
            }
            else
            {
                printf("� ���������, �������\n");
                is_help = 1;
                ConsoleResetWithMessage("\n��� ����� ������� ������� ����� ������");
                console::HeadText();
            }
        }
        if (!is_help)
          Right++;
        ConsoleResetWithMessage("��� �������� � ���������� ����� ������� ����� ������");
    }
    console::HeadText();
    printf("�����������!\n�� ����� �������� %i ���� �� %i � ������ �������!\n", Right, mas->size());
} /* End of 'TrainingMode' function */

/* Print head in test function
   ARGUMENTS:
     - int: cuurent word position;
     - int: number of all answers;
   RETURNS:
     None.
*/
void TestHead(int cur, int all)
{
  printf("\n---------%i/%i----------\n", cur, all);
} /* End of 'ShowResults' function */

/* Exam mode function
   ARGUMENTS:
     - Word *mas: pointer to checking word array
   RETURNS:
     None.
*/
void console::ExamMode(vector<Word>* mas)
{
    int i, Right = 0, ArraySize = (int)mas->size();
    string UserTranslate;
    vector <int> ErrorIndexes;

    if (ArraySize == 0)
    {
        console::MyError("��� ������ ������������ ������� ���� �� ���� �����");
        return;
    }

    /* Menu before test */
    console::HeadText();
    printf("����������� ������������ �� ���������� �������:\n");
    for (i = 0; i < ArraySize; i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    printf("������� ������� 'd', ���� ������ ������� �����-���� �����\n"
           "������� ������� '0', ���� ������ ����� � ������� ����\n"
           "������� ����� ������ �������, ���� �� ������ ������ ����\n");
    switch (_getch())
    {
    case 'd':
    case 'D':
    case '�':
    case '�':
        printf("������� �����, ������� ������ �������:");
        cin >> UserTranslate;
        console::DeleteWord(mas, UserTranslate);
        system("cls");
        console::ExamMode(mas);
        return;
    case '0':
        cons.is_exit = 1;
        system("cls");
        return;
    default:
        system("cls");
        break;
    }

    /* Testing words */
    for (i = 0; i < ArraySize; i++)
    {
      console::HeadText();
      TestHead(i + 1, ArraySize);
      cout << "������� ������� ����� " << mas->at(i).Name << ":\n";
      cin >> UserTranslate;

      mas->at(i).NumOfUses++;
      if (UserTranslate == mas->at(i).Name) 
      {
        printf("�����\n");
        Right++;
      }
      else
      {
        printf("�������\n");
        mas->at(i).NumOfWrongAnswers++;
        mas->at(i).ErrorKoef = mas->at(i).NumOfWrongAnswers / mas->at(i).NumOfUses;
        ErrorIndexes.push_back(i);
      }
      printf("��� �������� � ���������� ����� ������� ����� ������\n");
      if (_getch())
        system("cls");
    }
    console::HeadText();
    if (Right == ArraySize)
      printf("�������\n");
    else if (Right >= 0.8 * ArraySize)
      printf("������\n");
    else if (Right >= 0.6 * ArraySize)
      printf("���������\n");
    else
      printf("�����\n");
    printf("�� ������ ���� � ��������� �������� %i ���� �� %i \n", Right, ArraySize);
    if (Right != ArraySize)
    {
      printf("������ ����, � ������� �� ������� ������:\n");
      for (i = 0; i < ErrorIndexes.size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    }
} /* End of 'ExamMode' function */

/* Test mode function
   ARGUMENTS:
     - Word *mas: pointer to testing word array
   RETURNS:
     None.
*/
void console::TestMode(vector<Word>* mas)
{
    int i, Right = 0, ArraySize = (int)mas->size(), random, cnt;
    string tmpstr;
    vector <int> ErrorIndexes;

    if (ArraySize == 0)
    {
        console::MyError("��� ������ ������������ ������� ���� �� ���� �����.");
        return;
    }
    if (ArraySize < 4)
    {
        console::MyError("��� �������� ����� ���������� ������� 4 �����.");
        return;
    }

    /* Menu before test */
    console::HeadText();
    printf("����������� ������������ �� ���������� �������:\n");
    for (i = 0; i < ArraySize; i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    printf("������� ������� 'd', ���� ������ ������� �����-���� �����\n"
           "������� ������� '0', ���� ������ ����� � ������� ����\n"
           "������� ����� ������ �������, ���� �� ������ ������ ����\n");
    switch (_getch())
    {
    case 'd':
    case 'D':
    case '�':
    case '�':
        printf("������� �����, ������� ������ �������:");
        cin >> tmpstr;
        console::DeleteWord(mas, tmpstr);
        system("cls");
        console::ExamMode(mas);
        return;
    case '0':
        cons.is_exit = 1;
        system("cls");
        return;
    default:
        system("cls");
        break;
    }

    /* Testing words */
    for (i = 0; i < ArraySize; i++)
    {
      console::HeadText();
      TestHead(i + 1, ArraySize);
      cout << "�������� ���������� ������� ����� " << mas->at(i).Name << ":\n";
      printf("������� ����� ����������� ��������\n");

      /* Creating test */
      string Answer = mas->at(i).Translate;
      vector <string> Variants;
      vector <int> TestIndexes;
      int AnswerIndex, UserAnswer;

      cnt = 0;
      cons.RandomTime = clock();
      for (int j = 0; j < 4; j++)
      {
        Variants.push_back("empty");
        TestIndexes.push_back(8);
      }

      // Make normal random
      // ************
      // ************
      // ************

      srand((int)ArraySize * i * 10 + Right * 5);
      random = MyRand(0, 4, Right + rand() + ArraySize);
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
          if (mas->at(random).Translate == Variants[0] || mas->at(random).Translate == Variants[1] ||
              mas->at(random).Translate == Variants[2] || mas->at(random).Translate == Variants[3] || mas->at(random).Translate == Answer)
            random = MyRand(0, ArraySize, Right * rand() + i + rand());
          else
            flag = 0;
        }
        flag = 1;
        Wrong = mas->at(random).Translate;

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

      cons.RandomTime = clock() - cons.RandomTime;
      mas->at(i).NumOfUses++;
      if (UserAnswer - 1 == AnswerIndex)
      {
        printf("�����\n");
        Right++;
      }
      else
      {
        printf("�������\n");
        mas->at(i).NumOfWrongAnswers++;
        mas->at(i).ErrorKoef = mas->at(i).NumOfWrongAnswers / mas->at(i).NumOfUses;
        ErrorIndexes.push_back(i);
      }
      printf("��� �������� � ���������� ����� ������� ����� ������\n");
      if (_getch())
        system("cls");
    }

    /* Finish menu */
    console::HeadText();
    if (Right == ArraySize)
      printf("�������\n");
    else if (Right >= 0.8 * ArraySize)
      printf("������\n");
    else if (Right >= 0.6 * ArraySize)
      printf("���������\n");
    else
      printf("�����\n");
    printf("�� ������ ���� � ��������� �������� %i ���� �� %i \n", Right, ArraySize);
    if (Right != ArraySize)
    {
      printf("������ ����, � ������� �� ������� ������:\n");
      for (i = 0; i < ErrorIndexes.size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    }
} /* End of 'ExamMode' function */

/* END OF 'console.cpp' FILE */