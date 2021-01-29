/* FILE NAME: console.h
 * PROGRAMMER: Fabrika Artem
 * DATE: 26.01.2021
 * PERPOSE: work with console header file
 */

#ifndef __CONSOLE_H
#define __CONSOLE_H

#include "main_header.h"

using namespace std;

/* Word struct defenition */
struct Word;

/* User settings struct defenition */
struct Settings;

/* class console */
class console
{
  
public:
    int RandomTime;         /* Time for random functions */
    int is_exit;            /* Variable for exit */
    vector<Word> mas;       /* Word array */
    int TaskTime;           /* Time of completing a task */
    string LastFileName;    /* Name of last opened file */

    /* Array of task functions for one word */
    int (console::*Tasks[NumOfTasks])(int IndexCounter) = {};

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
         - int task_time: time of completing a task;
         - string FileName: name of last opened file;
       RETURNS:
         None.
    */
    console( int time, int myexit, vector<Word> ma, int task_time, string FileName );

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
         1 - if completed successfully, 0 - if error
    */
    int DeleteWord( std::string s );

    /* Edit word in temporary array function
       ARGUMENTS:
         - string s: key word;
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int EditWord(string s );

    /* Clear word's parameters in temporary array function
       ARGUMENTS:
         - string s: key word;
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int ResetProgress( string s );

    /* Clear all word's parameters in temporary array function
       ARGUMENTS:
         None;
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int ResetAllProgress(void);

    /* Clear temporary array function
       ARGUMENTS:
         None;
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int ClearArray( void );

    /* Mix words in random order function
       ARGUMENTS:
         None.
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int MixWords(void);

    /* Sort words in alphabet order function
       ARGUMENTS:
         None.
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int SortAlpha(void);

    /* Sort words in back alphabet order function
       ARGUMENTS:
         None.
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int SortAlphaBack(void);

    /* Sort words in error coefficient order function
       ARGUMENTS:
         None.
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int SortErrorKoef(void);

    /* Sort words in back error coefficient order function
       ARGUMENTS:
         None.
       RETURNS:
         1 - if completed successfully, 0 - if error
    */
    int SortErrorKoefBack(void);

    /* Common mode for all task function
       ARGUMENTS:
         int TaskID: index of task type;
       RETURNS:
         None.
    */
    void MainCommonMode(int TaskID);

    /* Training mode for one word function
       ARGUMENTS:
         - int IndexCounter: number of used words;
       RETURNS:
         (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
    */
    int TrainingMode(int IndexCounter);

    /* Exam mode for one word function
       ARGUMENTS:
         - int IndexCounter: number of used words;
       RETURNS:
         (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
    */
    int ExamMode(int IndexCounter);

    /* Test mode for one word function
       ARGUMENTS:
         - int IndexCounter: number of used words;
       RETURNS:
         (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
    */
    int TestMode(int IndexCounter);

    /* Test mode for one word function
       ARGUMENTS:
         - int IndexCounter: number of used words;
       RETURNS:
         (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
    */
    int ConstructorMode(int IndexCounter);

    /* Mixed mode for all words in array function
       ARGUMENTS:
         None
       RETURNS:
         None.
    */
    void MainMixedMode(void); 

    /* Check spelling word mode for one word function
       ARGUMENTS:
         - int IndexCounter: number of used words;
       RETURNS:
         (int) - -1 if exit, 0 if wrong answer, 1 if correct answer
    */
    int CheckMode(int IndexCounter);

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

    /* Print menu of sort functions
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void SortMenu(void);

    /* Print setting menu functions
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void SettingMenu(void);

    /* Print begin task menu function
       ARGUMENTS:
         None;
       RETURNS:
         (int) 0 if need to exit, 1 if continue task.
    */
    int BeginTaskMenu(void);

    /* Print finish task menu function
       ARGUMENTS:
         - int Right: number of correct answers;
         - vector <int> *ErrorIndexes: pointer to array of word with wrong answers indexes
       RETURNS:
         None.
    */
    void FinishTaskMenu(int Right, vector <int>* ErrorIndexes);

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

    /* Print text from file function
       ARGUMENTS:
         string name: name of version log file;
       RETURNS:
         None.
    */
    void PrintTextFile(string name);

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
