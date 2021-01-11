/* FILE NAME: main_header.h
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 10.01.2020
 * PERPOSE: main header project file
 */

#ifndef __MAIN_HEADER_H
#define __MAIN_HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#define ConsoleResetWithMessageTime 7000   /* in ms*/
#define MaxOutputWordSize 20               /* used in OutputArray */

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

#include "console.h"
#include "Database.h"

using namespace std;

extern console *cons; /* console object */
extern Database *db;  /* database object */

/* Word struct defenition */
typedef struct Word {
	string Name;
	string Translate;
	int NumOfUses = 0;
	int NumOfWrongAnswers = 0;
	double ErrorKoef = 0;
} Word; /* End of 'Word' struct */

#endif /*__MAIN_HEADER_H*/

/* END OF 'main_header.h' FILE */