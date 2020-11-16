#include "Database.h"
#include <fstream>
const char SEPORATOR = ',';

Database::Database()
{
    wordfiledir = std::string("C:/Users/User/Documents/CEL/word");
    marksfiledir = std::string("C:/Users/User/Documents/CEL/stat");
}

Database::Database(std::string word_file, std::string stat_file)
{
    wordfiledir = word_file;
    marksfiledir = stat_file;
}

void Database::loadWords()
{
	std::ifstream in(wordfiledir);;
	std::string line;
	if (in.is_open()) {
		while (getline(in, line))
		{
			Word w;
			std::string buf;
			for (size_t i = 0; i < line.length(); i++)
			{
				if (line.at(i) == SEPORATOR) {
					w.ru_word = buf;
                    buf.clear();
				}
				else
					buf+=(line.at(i));
			}
			w.en_translate = buf;
			storage.push_back(w);
		}
	}
	in.close();
}

void Database::loadMarks()
{
    std::ifstream in(marksfiledir);
	StringVector localStore;

    //Загрузка слов из файла в локальное хранилище

	std::string line;
	if (in.is_open()) {
		while (getline(in, line))
		{
			Word w;
			std::string buf;
            int counter = 0;
			for (size_t i = 0; i < line.length(); i++)
			{
				if (line.at(i) == SEPORATOR) {
                    switch (counter) {
                    case 0:
                        w.ru_word = buf;
                        counter++;
                        break;
                    case 1:
                        w.uses = std::stoi(buf);
                        counter++;
                        break;
                    }
                    buf.clear();
				}
				else
                    buf += (line.at(i));
			}
            w.wrong = std::stoi(buf);
            counter = 0;
            localStore.push_back(w);
		}  
	}
	in.close();
    //TODO Организовать НОРМАЛЬНЫЙ Поиск
    for(size_t i = 0; i < storage.size();i++){
        bool flag = 0;
        for(size_t j = 0; j < localStore.size();j++){
            if(storage[i].ru_word == localStore[j].ru_word){
                storage[i].uses = localStore[j].uses;
                storage[i].wrong = localStore[j].wrong;
                storage[i].errork = localStore[j].wrong/localStore[j].uses;
                flag = 1;
            }
        }
        if(!flag){
            storage[i].uses = 0;
            storage[i].wrong = 0;
            storage[i].errork = 1;
        }
    }
}

StringVector Database::getStorage()
{
    return storage;
}
