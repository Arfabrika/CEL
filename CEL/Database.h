/* FILE NAME: Database.h
 * PROGRAMMER: Novikov Gordey
 * DATE: 03.02.2021
 * PERPOSE: database header file
 */

#ifndef __DATABASE_H
#define __DATABASE_H

#include "main_header.h"

/* Word struct defenition */
struct Word;

/* User settings struct defenition */
struct Settings;

/* Word array defenition */
typedef std::vector <Word> StringVector;

/* Database class */
class Database
{
public:
    StringVector storage;     /* Word array */
    std::string wordfiledir;  /* File name with words */
	  std::string marksfiledir; /* File name with statistic */
    Settings* Set;            /* User settings struct */

    /* Database class default constructor
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    Database();

    /* Database class constructor
       ARGUMENTS:
         - Name of file with words:
            std::string word_file;
         - Name of file with statistic:
            std::string stat_file;
         - Settings struct:
            Settings Sets; 
       RETURNS:
          None.
     */
    Database(std::string word_file,std::string stat_file, Settings *Sets);
    /*
     * Использование
     * Database* DB = new Database();
     * DB->loadWords();
     * DB->loadMarks();
    */

    /* Load words function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void loadWords();

    /* Load statistic function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
    void loadMarks();
	
    /* Save data function
       ARGUMENTS:
         None;
       RETURNS:
         None.
    */
	  void save();

    /* Load data from files with user's name function
       ARGUMENTS:
         None;
       RETURNS:
         (int) 1 - if completed successfully, 0 - if error
    */
    int GeneralSave( void );

    /* Save data in files with user's name function
       ARGUMENTS:
         None;
       RETURNS:
         (int) 1 - if completed successfully, 0 - if error
    */
    int GeneralLoad(void);

    /* Save data in files when exit function
       ARGUMENTS:
         None;
       RETURNS:
         (int) 1 - if completed successfully, 0 - if error
    */
    int ExitSave(void);

    /* Save user settings in file function
       ARGUMENTS:
         -string name: settings file name;
       RETURNS:
         (int) 1 - if completed successfully, 0 - if error
    */
    int LoadSettings(string name);

    /* Save user settings in file function
       ARGUMENTS:
         -string name: settings file name;
       RETURNS:
         (int) 1 - if completed successfully, 0 - if error
    */
    int SaveSettings(string name);

    /* Change user settings function
       ARGUMENTS:
         -int SetID: setting type;
       RETURNS:
         (int) 1 - if settings changed, 0 - if settings not changed
    */
    int ChangeSettings(int SetID);

    /* Take words with mistakes function
       ARGUMENTS:
         (int) count of requested words;
       RETURNS:
         (vector <Word>) vector of requested words;
    */
    vector<Word> GetMistakeWords(int count);
    //Не сделано
    StringVector getWords(int count);
};

#endif /*__DATABASE_H*/
/* END OF 'Database.h' FILE */
