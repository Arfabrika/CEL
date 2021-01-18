/* FILE NAME: Database.h
 * PROGRAMMER: Novikov Gordey
 * DATE: 15.01.2021
 * PERPOSE: database header file
 */

#ifndef __DATABASE_H
#define __DATABASE_H

#include "main_header.h"

/* Word array defenition */
struct Word;

/* Word array defenition */
typedef std::vector <Word> StringVector;

/* Database class */
class Database
{
	
  std::string installdir;
	
public:
    StringVector storage;     /* Word array */
    std::string wordfiledir;  /* File name with words */
	  std::string marksfiledir; /* File name with statistic */

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
       RETURNS:
          None.
     */
    Database(std::string word_file,std::string stat_file);
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

    /* Get array of words function
       ARGUMENTS:
         None;
       RETURNS:
         (StringVector) array of words
    */
    StringVector getStorage();

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

    //Не сделано
    StringVector getWords(int count);
};

#endif /*__DATABASE_H*/
/* END OF 'Database.h' FILE */
