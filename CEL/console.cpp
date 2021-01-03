/* FILE NAME: console.cpp
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 21.12.2020
 * PERPOSE: console functions file
 */

#include "main_header.h"

/* Print menu function
   ARGUMENTS:
     None;
   RETURNS:
      None. */
void console::Menu(void)
{
    printf("Для выбора необходимого пункта меню нажмите на соответственную клавишу\n"
        "0 - выход\n"
        "1 - ввести новое слово\n"
        "2 - действия с временным списком слов\n"
        "3 - провести тренеровку\n"
        "4 - провести тест\n"
        "5 - сохранить список слов в файл\n"
        "6 - загрузить список слов из файла\n"
        "9 - помощь/о программе\n");
} /* End of 'Menu' function */

/* Print menu of temporary array function
   ARGUMENTS:
     None;
   RETURNS:
      None. */
void console::ArrayMenu(void)
{
    printf("0 - возвращение в главное меню\n"
        "1 - просмотреть временный массив\n"
        "2 - удалить слово из временного массива\n"
        "3 - изменить перевод слова\n"
        "4 - сбросить прогресс слова\n"
        "5 - удалить временный массив\n"
        /*"2 - удалить слово из временного массива\n"
        "2 - удалить слово из временного массива\n"
        "2 - удалить слово из временного массива\n"*/);
} /* End of 'Menu' function */

/* Print head text function
   ARGUMENTS:
     None;
   RETURNS:
      None. */
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
    cout << "Ошибка при выполнении операции: " << s << "\nПроверьте корректность введенных данных\n";
} /*End of 'MyError' function */

/* Print helping text about program function
   ARGUMENTS:
     None;
   RETURNS:
      None. */
void console::Help(void)
{
    printf("Console English Learning - программа, помогающая в заучивании слов и других языков\n"
        "Как ей пользоваться?\n"
        "Для начала нужно ввести определенное количество слов. Нажав кнопку '1' в главном меню, Вы перейдете в режим добавления слова.\n"
        "Посмотреть уже введеннные слова можно, нажав кнопку '3' в главном меню, а затем нажав кнопку '1' в вспомогательном меню. В том же меню можно удалить слово из списка или изменить его перевод.\n"
        "Чтобы проверить себя, Вы можете пройти тест, нажав кнопку '2' в главном меню.\n"
        "Не забывайте сохранять слова в файл! В противном случае, после выхода из программы список слов будет потерян. Для сохранения списка слов в файл нажмите кнопку '4' в главном меню.\n"
        "Хотите вернуться к старым словам? Загрузите слова из файла, нажав кнопку '5' в главном менюю\n"
        "Успехов в обучении!\n");
} /* End of 'Help' function */

/* Read word function
   ARGUMENTS:
     None;
   RETURNS:
     (Word) - new world structure */
Word console::ReadWord(void)
{
    Word W;
    string s;

    system("cls");
    HeadText();
    printf("Введите слово:\n");
    getline(cin, s);
    W.Name = s;
    printf("Введите перевод:\n");
    getline(cin, s);
    W.Translate = s;
    W.NumOfUses = 0;
    W.NumOfWrongAnswers = 0;
    W.ErrorKoef = 0;
    return W;
} /* End of 'ReadWord' function */

/* Clear and refill console function
   ARGUMENTS:
     None;
   RETURNS:
     None. */
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

/* Output array function
   ARGUMENTS:
     - Word *mas: pointer to word array
   RETURNS:
     None.
*/
void console::OutputArray(vector<Word>* mas) 
{
    system("cls");
    HeadText();
    if (mas->size() == 0)
    {
        printf("Массив слов пуст!\n");
        return;
    }
    cout << left << setw(MaxOutputWordSize) << "Слово" << setw(MaxOutputWordSize) << "Перевод" << "Количество проверок слова  Количество ошибок в слове  \n"
        ;// "Коэффициент правильных ответов слова\n";
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
        MyError("Временный массив пуст.");
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
        MyError("Введенное слово не найдено в массиве.");
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
        MyError("Временный массив пуст.");
        return 0;
    }
    int flag = 1;

    for (int i = 0; i < mas->size(); i++)
    {
        if (mas->at(i).Name == s)
        {
            string newtr;

            printf("Введите новый перевод:\n");
            cin >> newtr;
            mas->at(i).Translate = newtr;
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
     - Word *mas: pointer to word array
     - string s: key word;
   RETURNS:
     1 - if competed successfully, 0 - if error
*/
int console::ResetProgress(vector<Word>* mas, string s)
{
    if (mas->size() == 0)
    {
        MyError("Временный массив пуст.");
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
        MyError("Введенное слово не найдено в массиве.");
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
    printf("Вы действительно хотите очистить временный массив? Данные в нем нельзя будет восстановить\n"
    "Для подтверждения операции нажмите клавишу Y\n");
    if (_getch() == 'y' || _getch() == 'Y' || _getch() == 'н' || _getch() == 'Н')
        mas->clear();
    return 1;
} /*End of 'ClearArray' function */

/* Training mode function
   ARGUMENTS:
     - Word *mas: pointer to trainig word array
   RETURNS:
     None.
*/
void console::TrainingMode(vector<Word>* mas)
{
    int i, is_wrong;
    string UserTranslate;

    if (mas->size() == 0)
    {
        console::MyError("Для начала тренеровки введите хотя бы одно слово");
        return;
    }

    printf("Внимательно ознакомьтесь со следующими словами:\n");
    for (i = 0; i < mas->size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
    ConsoleResetWithMessage("Для начала тренеровки нажмите любую кнопку");
    for (i = 0; i < mas->size(); i++)
    {
        vector <int> help_indexes;
        int current_help_index, is_help = 0;

        is_wrong = 1;
        while (is_wrong)
        {
            /* Help module */
            if (is_help)
            {
                current_help_index = rand() % mas->at(i).Name.size();
                help_indexes.push_back(current_help_index);
                printf("Подсказка: ");
                for (int j = 0; j < mas->at(i).Name.size(); j++)
                {
                    if (std::find(help_indexes.begin(), help_indexes.end(), j) == help_indexes.end())
                        cout << "*";
                    else
                        cout << mas->at(i).Name.at(j);
                }
                cout << "\n";
            }

            cout << "Введите перевод слова " << mas->at(i).Translate << "\n";
            cin >> UserTranslate;

            transform(UserTranslate.begin(), UserTranslate.end(), UserTranslate.begin(), tolower);
            transform(mas->at(i).Name.begin(), mas->at(i).Name.end(), mas->at(i).Name.begin(), tolower);
            if (UserTranslate == mas->at(i).Name)       
            {
                printf("Верно!\n");
                is_wrong = 0;
            }
            else
            {
                printf("К сожалению, неверно\n");
                is_help = 1;
                ConsoleResetWithMessage("\nДля новой попытки нажмите любую кнопку");
            }
        }
        ConsoleResetWithMessage("Для перехода к следующему слову нажмите любую кнопку");
    }
} /* End of 'TrainingMode' function */

/* Test mode function
   ARGUMENTS:
     - Word *mas: pointer to trainig word array
   RETURNS:
     None.
*/
void console::TestMode(vector<Word>* mas)
{
    int i, is_wrong;
    string UserTranslate;

    if (mas->size() == 0)
    {
        console::MyError("Для начала тестирования введите хотя бы одно слово");
        return;
    }

    printf("Внимательно ознакомьтесь со следующими словами:\n");
    for (i = 0; i < mas->size(); i++)
        cout << left << setw(MaxOutputWordSize) << mas->at(i).Name << setw(MaxOutputWordSize) << mas->at(i).Translate << "\n";
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
        console::DeleteWord(mas, UserTranslate);
        console::TestMode(mas);
        return;
    case '0':
        //is_exit = 1;
        return;
    default:
        system("cls");
        break;
    }
    printf("a");
} /* End of 'TestMode' function */

/* END OF 'console.cpp' FILE */