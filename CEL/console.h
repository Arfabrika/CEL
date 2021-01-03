/* FILE NAME: console.h
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 21.12.2020
 * PERPOSE: work with console header file
 */

#ifndef __CONSOLE_H
#define __CONSOLE_H
#include "main_header.h"

using namespace std;

struct Word;
//int is_exit;

/* class console */
class console
{
public:
    /* Print menu function
       ARGUMENTS:
         None;
       RETURNS:
          None. */
    static void Menu(void);

    /* Print menu of temporary array function
       ARGUMENTS:
         None;
       RETURNS:
          None. */
    static void ArrayMenu(void);

    /* Print head text function
       ARGUMENTS:
         None;
       RETURNS:
          None. */
    static void HeadText(void);

    /* Throw error message function
       ARGUMENTS:
         - None;
       RETURNS:
         None.
    */
    static void MyError(string s);

    /* Print helping text about program function
       ARGUMENTS:
         None;
       RETURNS:
          None. */
    static void Help(void);

    /* Clear and refill console function
       ARGUMENTS:
         None;
       RETURNS:
         None. */
    static void ConsoleResetWithMessage(string s);

    /* Read word function
       ARGUMENTS:
         None;
       RETURNS:
          (Word) created from input data word.
    */
    static Word ReadWord(void);

    /* Output array function
       ARGUMENTS:
         - Word *mas: pointer to word array
       RETURNS:
         None.
    */
    static void OutputArray( std::vector<Word>* mas );

    /* Delete word from temporary array function
       ARGUMENTS:
         - Word *mas: pointer to word array
         - string s: key word;
       RETURNS:
         1 - if competed successfully, 0 - if error
    */
    static int DeleteWord(std::vector<Word>* mas, std::string s);

    /* Edit word in temporary array function
       ARGUMENTS:
         - Word *mas: pointer to word array
         - string s: key word;
       RETURNS:
         1 - if competed successfully, 0 - if error
    */
    static int EditWord(vector<Word>* mas, string s);

    /* Clear word's parameters in temporary array function
       ARGUMENTS:
         - Word *mas: pointer to word array
         - string s: key word;
       RETURNS:
         1 - if competed successfully, 0 - if error
    */
    static int ResetProgress(vector<Word>* mas, string s);

    /* Clear temporary array function
       ARGUMENTS:
         - Word *mas: pointer to word array
       RETURNS:
         1 - if competed successfully, 0 - if error
    */
    static int ClearArray(vector<Word>* mas);

    /* Training mode function
       ARGUMENTS:
         - Word *mas: pointer to trainig word array
       RETURNS:
         None.
    */
    static void TrainingMode(vector<Word>* mas);

    /* Test mode function
       ARGUMENTS:
         - Word *mas: pointer to trainig word array
       RETURNS:
         None.
    */
    static void TestMode(vector<Word>* mas);

}; /* end of 'console' class */

#endif /*__CONSOLE_H*/
/* END OF 'console.h' FILE */



