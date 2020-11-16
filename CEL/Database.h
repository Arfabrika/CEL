#pragma once
#include <string>
#include <vector>
#include "Header.h"
typedef std::vector <Word> StringVector;

class Database
{
	StringVector storage;
	std::string wordfiledir;
	std::string marksfiledir;
public:
    Database();
    Database(std::string word_file,std::string stat_file);
    // Не важно как это работает,важно что это рабоает
    /*
     * Использование
     * Database* DB = new Database();
     * DB->loadWords();
     * DB->loadMarks();
    */
    void loadWords();
    void loadMarks();
    StringVector getStorage();

    //Не сделано
	void sortbyalphobet();
	void sortbyalphobet(char start,char end);
	void sortbyalphobet(char start, char end,bool reverse);
};

