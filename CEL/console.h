/* FILE NAME: console.h
 * PROGRAMMER: Fabrika Artem
 * DATE: 13.01.2020
 * PERPOSE: work with console header file
 */

#ifndef __CONSOLE_H
#define __CONSOLE_H

#include "main_header.h"

using namespace std;

struct Word;

/* class console */
class console
{
  
public:
    int RandomTime;   /* Time for random functions */
    int is_exit;      /* Variable for exit */
    vector<Word> mas; /* Word array */

    /* Console class default constructor
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    console();

    /* Console class default constructor
       ARGUMENTS:
         - int time: time for random functions;
         - int myexit: need to exit in main menu;
         - StringVector ma: word array;
       RETURNS:
         None.
    */
    console( int time, int myexit, vector<Word> ma );

    /* Read word function
    ARGUMENTS:
      None;
    RETURNS:
      (int) - 1 if successed, 0 if failed
    */
    int ReadWord( void );

    /* Output array function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void OutputArray( void );

    /* Delete word from temporary array function
       ARGUMENTS:
         - string s: key word;
       RETURNS:
         1 - if competed successfully, 0 - if error
    */
    int DeleteWord( std::string s );

    /* Edit word in temporary array function
       ARGUMENTS:
         - string s: key word;
       RETURNS:
         1 - if competed successfully, 0 - if error
    */
    int EditWord(string s );

    /* Clear word's parameters in temporary array function
       ARGUMENTS:
         - string s: key word;
       RETURNS:
         1 - if competed successfully, 0 - if error
    */
     int ResetProgress( string s );

    /* Clear temporary array function
       ARGUMENTS:
         None;
       RETURNS:
         1 - if competed successfully, 0 - if error
    */
     int ClearArray( void );

    /* Training mode function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
     void TrainingMode( void );

     /* Training mode for all words in array function
        ARGUMENTS:
          None
        RETURNS:
          None.
     */
     void MainTrainingMode( void );

    /* Exam mode function
       ARGUMENTS:
         - Word *mas: pointer to trainig word array
       RETURNS:
         None.
    */
     void ExamMode( void );

    /* Test mode function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void TestMode( void );

    /* Constructor mode function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void ConstructorMode(void);

    /****
     *    Utilits and output text functions
     ****/

    /* Print menu function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void Menu( void );

    /* Print menu of temporary array function
       ARGUMENTS:
         None;
       RETURNS:
          None.
    */
    void ArrayMenu( void );

    /* Print menu of task functions
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void TaskMenu( void );

    /* Print begin task menu function
       ARGUMENTS:
         - string name: type of task;
       RETURNS:
         None.
    */
    void BeginMenu( string name );

    /* Print head text function
       ARGUMENTS:
         None;
       RETURNS:
          None.
    */
    void HeadText( void );

    /* Throw error message function
       ARGUMENTS:
         - string s: error message;
       RETURNS:
         None.
    */
    void MyError( string s );

    /* Print helping text about program function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void Help( void );

    /* Clear and refill console function
       ARGUMENTS:
         - string s: output message;
       RETURNS:
         None.
    */
    void ConsoleResetWithMessage( string s );

    /* Print head in test function
       ARGUMENTS:
         - int: current word position;
         - int: number of all answers;
       RETURNS:
         None.
    */
    void TestHead(int cur, int all);

    /* Upgraded random function
       ARGUMENTS:
         - int mi: minimum random number;
         - int ma: maximum random number;
         - int param: random parameter
       RETURNS:
         (int) random number.
    */
    int MyRand( int mi, int ma, int param );

}; /* end of 'console' class */

#endif /*__CONSOLE_H*/

/* END OF 'console.h' FILE */
