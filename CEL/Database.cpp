/* FILE NAME: Database.cpp
 * PROGRAMMER: Novikov Gordey
 * DATE: 16.11.2020
 * PERPOSE: database functions file
 */

#include "main_header.h"
#include <map>

const char SEPORATOR = ',';
const double ERROR_AFFECT = 3.0;
const double RANDOM_AFFECT = 0.01;

/* Database class default constructor
   ARGUMENTS:
     None;
   RETURNS:
     None. */
Database::Database()
{
    wordfiledir = std::string("words.txt");
    marksfiledir = std::string("mark.txt");
} /* End of default 'Datadase' constructor */

/* Database class constructor
   ARGUMENTS:
     - Name of file with words:
        std::string word_file;
     - Name of file with statistic:
        std::string stat_file;
   RETURNS:
      None. */
Database::Database(std::string word_file, std::string stat_file)
{
    wordfiledir = word_file;
    marksfiledir = stat_file;
} /* End of 'Datadase' constructor */

/* Load words function
   ARGUMENTS:
     None;
   RETURNS:
     None. */
void Database::loadWords()
{
	std::ifstream in(wordfiledir);
    if (!in)
    {
        // то выводим следующее сообщение об ошибке и выполняем функцию exit()
        cons->MyError("Указанный файл не найден.");
        return;
    }
	std::string line;
	if (in.is_open()) {
		while (getline(in, line))
		{
			Word w;
			std::string buf;
			for (size_t i = 0; i < line.length(); i++)
			{
				if (line.at(i) == SEPORATOR) {
					w.Name = buf;
                    buf.clear();
				}
				else
					buf+=(line.at(i));
			}
			w.Translate = buf;
			storage.push_back(w);
		}
	}
	in.close();
} /* End of 'loadWords' function */

/* Load statistic function
   ARGUMENTS:
     None;
   RETURNS:
     None. */
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
                        w.Translate = buf;
                        counter++;
                        break;
                    case 1:
                        w.NumOfUses = std::stoi(buf);
                        counter++;
                        break;
                    }
                    buf.clear();
				}
				else
                    buf += (line.at(i));
			}
            w.NumOfWrongAnswers = std::stoi(buf);
            counter = 0;
            localStore.push_back(w);
		}  
	}
	in.close();
    //TODO Организовать НОРМАЛЬНЫЙ Поиск
    for(size_t i = 0; i < storage.size();i++){
        bool flag = 0;
        for(size_t j = 0; j < localStore.size();j++){
            if(storage[i].Translate == localStore[j].Translate){
                storage[i].NumOfUses = localStore[j].NumOfUses;
                storage[i].NumOfWrongAnswers = localStore[j].NumOfWrongAnswers;
                storage[i].ErrorKoef = storage[i].NumOfUses != 0? localStore[j].NumOfWrongAnswers / localStore[j].NumOfUses : 1;
                flag = 1;
            }
        }
        if(!flag){
            storage[i].NumOfUses = 0;
            storage[i].NumOfWrongAnswers = 0;
            storage[i].ErrorKoef = 1;
        }
    } /* End of 'loadWords' function */
}
/* Get array of words function
   ARGUMENTS:
     None;
   RETURNS:
     (StringVector) array of words */
StringVector Database::getStorage()
{
    return storage;
}
/*Take Word
  ARGUMENTS:
    (int) count of reqested words;
  RETURNS:
    (vector <Word>) vector of reqwested words;
 * */
vector<Word> Database::getWords(int count)
{
    map <int, Word> ans;
    for(size_t t = 0;t < storage.size();t++){
        const auto c = storage[t].ErrorKoef*ERROR_AFFECT + (rand() % 100)*RANDOM_AFFECT;
        ans.insert(pair<int,Word>(c,storage[t]));
    }
    vector <Word> _ans;
    for (auto i = 0; i < count; i++){
        _ans.push_back(ans[i]);
    }
    return _ans;

} /* End of 'loadWords' function */


/*Saving statistic and wordlist to files
  ARGUMENTS:
    None;
  RETURNS:
    None;
 * */
void Database::save(){
	std::ofstream out(marksfiledir);
	for(size_t i = 0; i < storage.size();i++){
        out << storage[i].Translate << SEPORATOR;
        out << storage[i].NumOfUses << SEPORATOR;
        out << storage[i].NumOfWrongAnswers;
        out << std::endl;
    };
    out.close();
    out.open(wordfiledir);
    for(size_t i = 0; i < storage.size();i++){
        out << storage[i].Name << SEPORATOR;
        out << storage[i].Translate;
        out << std::endl;
    };
    out.close();
}/* End of 'save' function */

/* END OF 'Database.cpp' FILE */
