/* FILE NAME: main.cpp
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 21.12.2020
 * PERPOSE: main project file
 */

#include "main_header.h"

int is_exit;

/* Main program function 
   ARGUMENTS:
     None;
   RETURNS:
      - 1 if all okey, 0 if error.*/
int main( void )
{
    vector<Word> WordArray;
    Word W;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    while (1)
    {
        string s;

        is_exit = 0;
        console::HeadText();
        console::Menu();
        switch (_getch())
        {
        case '0':
            return 1;
        case '1':
            W = console::ReadWord();
            WordArray.push_back(W);
            printf("Слово успешно добавлено в временный массив!\n");
            break;
        case '2':
            system("cls");
            console::HeadText();
            console::ArrayMenu();
            switch (_getch())
            {
            case '0':
                is_exit = 1;
                system("cls");
                break;
            case '1':
                console::OutputArray(&WordArray);
                break;
            case '2':
                printf("Введите слово, которое собираетесь удалить:\n");
                cin >> s;
                if (console::DeleteWord(&WordArray, s))
                    cout << "Слово " << s << " успешно удалено!\n";
                break;
            case '3':
                printf("Введите слово, перевод которого собираетесь изменить:\n");
                cin >> s;
                if (console::EditWord(&WordArray, s))
                    cout << "Перевод слова " << s << " успешно изменен!\n";
                break;
            case '4':
                printf("Введите слово, прогресс которого собираетесь сбросить:\n");
                cin >> s;
                if (console::ResetProgress(&WordArray, s))
                    cout << "Прогресс слова """ << s << """ успешно сброшен!\n";
                break;
            case '5':
                if (console::ClearArray(&WordArray))
                    cout << "Временный массив успешно очищен!\n";
                break;
            }
            break;
        case '3':
            system("cls");
            console::TrainingMode(&WordArray);
            break;
        case '4':
            system("cls");
            console::TestMode(&WordArray);
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '9':
            system("cls");
            console::Help();
            break;
        default:
            printf("Ввведена некорректная программа. Пожалуйста, повторите ваш запрос\n");
        }
        if (!is_exit)
          console::ConsoleResetWithMessage("Для возвращения в главное меню нажмите любую кнопку");
    }
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */