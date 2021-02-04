/* FILE NAME: main_header.h
 * PROGRAMMER: Fabrika Artem
 * DATE: 03.02.2021
 * PERPOSE: main header project file
 */

#ifndef __MAIN_HEADER_H
#define __MAIN_HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#define MaxOutputWordSize 20    /* used in OutputArray */
#define NumOfTasks 6				    /* number of tasks for one word */

#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <map>
#include <functional>

#include "console.h"
#include "Database.h"

using namespace std;

/* Word struct defenition */
typedef struct Word
{
	string Name;
	string Translate;
	int NumOfUses = 0;
	int NumOfWrongAnswers = 0;
	double ErrorKoef = 0;
} Word;
/* End of 'Word' struct */

/* User settings struct defenition */
typedef struct Settings
{
	bool ExitSave = false;						 /* Need to do exit save */
	bool StartLoad = false;						 /* Need to do start load */
	string LastFileName = "exit_save"; /* Name of last opened file */
	int ExitSort = 0;									 /* Type of sort in file when exit */
	bool ResaveMenu = false;					 /* Need to output resave menu */
	int NumOfWords = 0;								 /* Number of loading words */
} Settings;
/* End of 'Settings' struct */

extern console *cons; /* console object */
extern Database *db;  /* database object */

#endif /*__MAIN_HEADER_H*/

/* END OF 'main_header.h' FILE */
