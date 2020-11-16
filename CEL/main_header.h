/* FILE NAME: main_header.h
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 16.11.2020
 * PERPOSE: main header project file
 */

#ifndef __MAIN_HEADER_H
#define __MAIN_HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#define ConsoleResetTime 7000   /* in ms*/
#define MaxOutputWordSize 20    /* used in OutputArray */

#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

#include "console.h"

using namespace std;


typedef struct Word {
	string Name;
	string Translate;
	int NumOfUses = 0;
	int NumOfWrongAnswers = 0;
	double ErrorKoef = 0;
};

#endif /*__MAIN_HEADER_H*/
/* END OF 'main_header.h' FILE */