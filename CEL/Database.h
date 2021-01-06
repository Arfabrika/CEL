/* FILE NAME: Database.h
 * PROGRAMMER: Novikov Gordey
 * DATE: 23.11.2020
 * PERPOSE: database header file
 */

#ifndef __DATABASE_H
#define __DATABASE_H

//#include <string>
//#include <vector>

#include "main_header.h"

/* Word array defenition */
struct Word;

typedef std::vector <Word> StringVector;

class Database
{
	StringVector storage;
    std::string installdir;
	std::string wordfiledir;
	std::string marksfiledir;
public:
    /* Database class default constructor
       ARGUMENTS:
         None;
       RETURNS:
         None. */
    Database();

    /* Database class constructor
       ARGUMENTS:
         - Name of file with words:
            std::string word_file;
         - Name of file with statistic:
            std::string stat_file;
       RETURNS:
          None. */
    Database(std::string word_file,std::string stat_file);
    // Не важно как это работает,важно что это рабоает
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
         None. */
    void loadWords();

    /* Load statistic function
       ARGUMENTS:
         None;
       RETURNS:
         None. */
    void loadMarks();
	
	void save();
    /* Get array of words function
       ARGUMENTS:
         None;
       RETURNS:
         (StringVector) array of words */
    StringVector getStorage();

    //Не сделано
    StringVector getWords(int count);

};

#endif /*__DATABASE_H*/
/* END OF 'Database.h' FILE */
