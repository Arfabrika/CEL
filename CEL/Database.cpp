/* FILE NAME: Database.cpp
 * PROGRAMMER: Novikov Gordey
 * DATE: 04.02.2021
 * PERPOSE: database functions file
 */

#include "main_header.h"

const char SEPORATOR = '`';
const double ERROR_AFFECT = 3.0;
const double RANDOM_AFFECT = 0.01;

/* Database class default constructor
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
Database::Database()
{
  wordfiledir = std::string("Data\\words.cel");
  marksfiledir = std::string("Data\\marks.cel");
  Set = new Settings();
} /* End of default 'Datadase' constructor */

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
Database::Database(std::string word_file, std::string stat_file, Settings *Sets)
{
    wordfiledir = word_file;
    marksfiledir = stat_file;
    Set = new Settings();
    Set = Sets;
} /* End of 'Datadase' constructor */

/* Load words function
   ARGUMENTS:
     None;
   RETURNS:
     None.
*/
void Database::loadWords()
{
	std::ifstream in(wordfiledir);
    if (!in)
    {
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
     None.
*/
void Database::loadMarks()
{
    std::ifstream in(marksfiledir);
	StringVector localStore;
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

    for(size_t i = 0; i < storage.size();i++){
        bool flag = 0;
        for(size_t j = 0; j < localStore.size();j++){
            if(storage[i].Translate == localStore[j].Translate){
                storage[i].NumOfUses = localStore[j].NumOfUses;
                storage[i].NumOfWrongAnswers = localStore[j].NumOfWrongAnswers;
                storage[i].ErrorKoef = storage[i].NumOfUses != 0? (double)localStore[j].NumOfWrongAnswers / localStore[j].NumOfUses : 1;
                flag = 1;
            }
        }
        if(!flag){
            storage[i].NumOfUses = 0;
            storage[i].NumOfWrongAnswers = 0;
            storage[i].ErrorKoef = 1;
        }
    }
} /* End of 'loadWords' function */

/* Take random words function
   ARGUMENTS:
     (int) count of requested words;
   RETURNS:
     (vector <Word>) vector of requested words;
*/
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

} /* End of 'getWords' function */

/* Take words with mistakes function
   ARGUMENTS:
     (int) count of requested words;
   RETURNS:
     (vector <Word>) vector of requested words;
*/
vector<Word> Database::GetMistakeWords( int count )
{
  int ArraySize = storage.size();
  vector <Word> ans = storage;

  for (int i = 0; i < ArraySize; i++)
    for (int j = i; j < ArraySize; j++)
    {
      if (ans.at(i).ErrorKoef < ans.at(j).ErrorKoef)
      {
        Word tmp = ans.at(i);
    
        ans.at(i) = ans.at(j);
        ans.at(j) = tmp;
      }
    }
  ans.resize(count);
  return ans;
} /* End of GetMistakeWords' function */

/*Saving statistic and wordlist to files
  ARGUMENTS:
    None;
  RETURNS:
    None;
*/
void Database::save(){
	std::ofstream out(marksfiledir);
  
  if (!out.is_open())
  {
    cons->MyError("Ошибка при сохранении. Не удалось открыть файл сохранения.");
    return;
  }
	for(size_t i = 0; i < storage.size();i++){
        out << storage[i].Translate << SEPORATOR;
        out << storage[i].NumOfUses << SEPORATOR;
        out << storage[i].NumOfWrongAnswers;
        out << std::endl;
    };
    out.close();
    out.open(wordfiledir);
    if (!out.is_open())
    {
      cons->MyError("Ошибка при сохранении. Не удалось открыть файл сохранения.");
      return;
    }
    for(size_t i = 0; i < storage.size();i++){
        out << storage[i].Name << SEPORATOR;
        out << storage[i].Translate;
        out << std::endl;
    };
    out.close();
}/* End of 'save' function */

/* Save data in files with user's name function
   ARGUMENTS:
     None;
   RETURNS:
     (int) 1 - if completed successfully, 0 - if error
*/
int Database::GeneralSave( void )
{
  string UserName;

  cons->HeadText();
  printf("Введите название файла для сохранения данных: ");
  cin >> UserName;
  wordfiledir = "Data\\" + UserName + ".txt";
  marksfiledir = "Data\\" + UserName + ".cel";
  if (cons->mas.size() == 0)
    return 0;
  ifstream in(wordfiledir);
  ifstream in2(wordfiledir);
  if ((in.is_open() || in2.is_open()) && Set->ResaveMenu)
  {
    printf("Файл с таким именем уже существует. Вы действительно хотите перезаписать его?\n"
           "Нажмите кнопку 'Y' чтобы продолжить или любую другую, чтобы выйти в главное меню\n");

    char param = _getch();
    switch(param)
    {
      case 'Y':
      case 'y':
      case 'Н':
      case 'н':
        break;
      default:
        return 1;
    }
  }
  switch (Set->ExitSort)
  {
  case 1:
    cons->SortAlpha();
    break;
  case 2:
    cons->SortAlphaBack();
    break;
  case 3:
    cons->SortErrorKoef();
    break;
  case 4:
    cons->SortErrorKoefBack();
    break;
  }
  storage.clear();
  storage = cons->mas;
  save();
  storage.clear();
  return 1;
} /* End of 'GeneralLoad' function */

/* Load data from files with user's name function
   ARGUMENTS:
     None;
   RETURNS:
     (int) 1 - if completed successfully, 0 - if error
*/
int Database::GeneralLoad( void )
{
  string UserName;

  cons->HeadText();
  
  printf("Введите название файла для загрузки данных: ");
  cin >> UserName;
  wordfiledir = "Data\\" + UserName + ".txt";
  marksfiledir = "Data\\" + UserName + ".cel";

  ifstream in(wordfiledir);
  ifstream in2(wordfiledir);
  if (!in.is_open() || !in2.is_open())
  {
    printf("Указанный файл не найден\n\n");
    return 0;
  }

  cons->mas.clear();
  storage.clear();
  loadWords();
  loadMarks();
  if (storage.size() == 0)
    return 0;
  if (Set->NumOfWords != 0)
    storage = GetMistakeWords(Set->NumOfWords);
  cons->mas = storage;
  storage.clear();
  return 1;
} /* End of 'GeneralSave' function */

/* Save data in files when exit function
   ARGUMENTS:
     None;
   RETURNS:
     (int) 1 - if completed successfully, 0 - if error
*/
int Database::ExitSave( void )
{
  if (wordfiledir == "Data\\words.txt" && marksfiledir == "Data\\marks.txt")
  {
    wordfiledir = "Data\\exit_save.txt";
    marksfiledir = "Data\\exit_save.cel";
  }
  switch (Set->ExitSort)
  {
  case 1:
    cons->SortAlpha();
    break;
  case 2:
    cons->SortAlphaBack();
    break;
  case 3:
    cons->SortErrorKoef();
    break;
  case 4:
    cons->SortErrorKoefBack();
    break;
  }
  storage = cons->mas;
  save();
  db->SaveSettings("Sys\\sets.cel");
  return 1;
} /* End of 'ExitSave' function */

/* Load user settings from file function
   ARGUMENTS:
     -string name: settings file name;
   RETURNS:
     (int) 1 - if completed successfully, 0 - if error
*/
int Database::LoadSettings( string name )
{
  ifstream in(name);
  string buf;
  int SettingsID = 0, i = 0;

  if (!in.is_open())
    return 0;
  while (getline(in, buf))
  {
    bool val = 0;

    if (isdigit(buf[0]) && buf.size() == 1)
      val = buf[0] - '0';

    switch(SettingsID)
    {
    case 0:
      Set->ExitSave = val;
      break;
    case 1:
      Set->StartLoad = val;
      break;
    case 2:
      Set->LastFileName = buf;
      break;
    case 3:
      Set->ExitSort = val;
      break;
    case 4:
      Set->ResaveMenu = val;
      break;
    case 5:
      while (isdigit(buf[i]))
      {
        Set->NumOfWords = Set->NumOfWords * 10 + buf[i] - '0';
        i++;
      }
      break;
    default:
      break;
    }
    SettingsID++;
    buf.clear();
  }
  return 1;
} /* End of 'LoadSettings' function */

/* Save user settings in file function
   ARGUMENTS:
     -string name: settings file name;
   RETURNS:
     (int) 1 - if completed successfully, 0 - if error
*/
int Database::SaveSettings( string name )
{
  ofstream out(name);
 
  if (!out.is_open())
    return 0;
  out << (int)Set->ExitSave << '\n';
  out << (int)Set->StartLoad << '\n';
  out << Set->LastFileName  << '\n';
  out << Set->ExitSort << '\n';
  out << (int)Set->ResaveMenu << '\n';
  out << Set->NumOfWords << '\n';
  return 1;
} /* End of 'SaveSettings' function */

/* Change user settings function
   ARGUMENTS:
     -int SetID: setting type;
   RETURNS:
     (int) 1 - if settings changed, 0 - if settings not changed
*/
int Database::ChangeSettings( int SetID )
{
  if (Set == 0)
    return 0;

  string name;
  ifstream in;
  char param;
  int NumOfWords = 0, i = 1;

  switch(SetID)
  {
  case 1:
    printf("Для того, чтобы включить/выключить сохранение слов в файл перед закрытием, нажмите 'Y'\n"
           "Для выхода в главное меню нажмите любую другую кнопку\n");
    cout << "Данный параметр сейчас " << ((int)db->Set->ExitSave == 1 ? "включен" : "выключен") << "\n";
    param = _getch();
    switch(param)
    {
      case 'Y':
      case 'y':
      case 'Н':
      case 'н':
        db->Set->ExitSave = !db->Set->ExitSave;
        break;
      default:
        return 0;
      }
      break;
   case 2:
    printf("Для того, чтобы включить/выключить загрузку слов из файла при начале работы программы, нажмите 'Y'\n"
           "Для выхода в главное меню нажмите любую другую кнопку\n");
    cout << "Данный параметр сейчас " << ((int)db->Set->StartLoad == 1 ? "включен" : "выключен") << "\n";
    param = _getch();
    switch(param)
    {
    case 'Y':
    case 'y':
    case 'Н':
    case 'н':
      db->Set->StartLoad = !db->Set->StartLoad;
      break;
    default:
      return 0;
    }
    break;
    case 3:
      printf("Для того, чтобы изменить имя файла, из которого идет загрузка при начале работы программы, нажмите 'Y'\n"
             "Для выхода в главное меню нажмите любую другую кнопку\n");
      cout << "Сейчас загрузка идет из файла: " << Set->LastFileName << "\n";

      param = _getch();
      switch(param)
      {
      case 'Y':
      case 'y':
      case 'Н':
      case 'н':
        printf("Введите новое имя файла: ");
        cin >> name;

       in.open("Data\\" + name + ".txt");
        if (!in.is_open())
        {
          cons->MyError("Такого файла не существует.");
          cons->ConsoleResetWithMessage("Для возвращения в главное меню нажмите любую кнопку");
          return 0;
        }
        Set->LastFileName = name;
        break;
      default:
        return 0;
      }
      break;
    case 4:
      printf("Нажмите '0' для выхода в главное меню\nСейчас сортировка ");
      switch(Set->ExitSort)
      {
      case 1:
        printf("по алфавиту по возрастанию (A-Z)\n");
        break;
      case 2:
        printf("по алфавиту по убыванию (Z-A)\n");
        break;
      case 3:
        printf("по частоте ошибок по убыванию\n");
        break;
      case 4:
        printf("по частоте ошибок по возрастанию\n");
        break;
      default:
        printf("отключена\n");
      }
      printf("Нажмите нужную клавишу для изменения настройки:\n"
             "1 - отключить сортировку\n"
             "2 - включить сортировку по алфавиту по возрастанию (A-Z)\n"
             "3 - включить сортировку по алфавиту по убыванию (Z-A)\n"
             "4 - включить сортировку по по частоте ошибок по убыванию\n"
             "5 - включить сортировку по по частоте ошибок по возрастанию\n");
      int param;

      scanf("%i", &param);
      if (param == 0)
        return 0;
      Set->ExitSort = param - 1;
      break;
    case 5:
    printf("Для того, чтобы включить/выключить подтверждение при сохранении в существующий файл, нажмите 'Y'\n"
           "Для выхода в главное меню нажмите любую другую кнопку\n");
    cout << "Данный параметр сейчас " << ((int)db->Set->ResaveMenu == 1 ? "включен" : "выключен") << "\n";
    param = _getch();
    switch(param)
    {
      case 'Y':
      case 'y':
      case 'Н':
      case 'н':
        db->Set->ResaveMenu = !db->Set->ResaveMenu;
        break;
      default:
        return 0;
      }
      break;
    case 6:
      printf("Нажмите '0' для выхода в главное меню\n");
      if (Set->NumOfWords == 0)
        printf("В данный момент загружаются все слова из файла\n");
      else
        printf("В данный момент загружаются %i слов из файла\n", Set->NumOfWords);
      printf("Введите количество слов, которое хотите загружать из файла, или слово all, если хотите загружать все слова из файла\n");
      cin >> name;
      if (name[0] == '0')
        return 0;
      if (isdigit(name[0]))
      {
        NumOfWords = name[0] - '0';
        while (isdigit(name[i]))
        {
          NumOfWords = NumOfWords * 10 + name[i] - '0';
          i++;
        }
      }
      Set->NumOfWords = NumOfWords;
      break;
  default:
    return 0;
  }
  SaveSettings("Sys\\sets.cel");
  printf("Настройки успешно изменены!\n");
  return 1;
} /* End of 'ChangeSettings' function */

/* END OF 'Database.cpp' FILE */
