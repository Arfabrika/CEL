/* Fabrika Artem, 10-5, 30.10.2018 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "h.h"

void GetStr( char *s, int maxlen )
{
  int i = 0;
  char ch;

  while ((ch = getchar()) != '\n')
    if (s != NULL && i < maxlen - 1)
      s[i++] = ch;
  if ( s != NULL && i < maxlen)
    s[i] = 0;
}

void Menu( void )
{
  printf("0 - exit\n"
         "1 - create new worker\n"
         "2 - view a base\n"
         "3 - delete worker with certain number\n"
         "4 - sort a base: a)surname + name b) date of birth\n"
         "5 - reverse base\n"
         "6 - save base into file\n"
         "7 - load base from file\n"
         "8 - edit information with certain number\n"
         "9 - create base of salaries\n");
}

void ReadWorker( WORKER *W )
{
  printf("Name: ");
  GetStr(W->Name, sizeof W->Name);
  printf("Surname: ");
  GetStr(W->Surname, sizeof W->Surname);
  printf("Birthday:\n  Day: ");
  scanf("%d", &W->Birthday.Day);
  GetStr(NULL, 0);
  printf("Birthday:\n  Month: ");
  scanf("%d", &W->Birthday.Month);
  GetStr(NULL, 0);
  printf("Birthday:\n  Year: ");
  scanf("%d", &W->Birthday.Year);
  GetStr(NULL, 0);
  printf("Sex: ");
  /*GetStr(W->Sex, sizeof W->Sex);*/
  scanf("%c", &W->Sex);
  printf("Work hours on Monday: ");
  scanf("%d", &W->Hours[0]);
  GetStr(NULL, 0);
  printf("Work hours on Tuesday: ");
  scanf("%d", &W->Hours[1]);
  GetStr(NULL, 0);
  printf("Work hours on Wednesday: ");
  scanf("%d", &W->Hours[2]);
  GetStr(NULL, 0);
  printf("Work hours on Thursday: ");
  scanf("%d", &W->Hours[3]);
  GetStr(NULL, 0);
  printf("Work hours on Friday: ");
  scanf("%d", &W->Hours[4]);
  GetStr(NULL, 0);
  printf("Work hours on Saturday: ");
  scanf("%d", &W->Hours[5]);
  GetStr(NULL, 0);
  printf("Work hours on Sunday: ");
  scanf("%d", &W->Hours[6]);
  GetStr(NULL, 0);
  printf("Ok!\n");
}

int SaveDB( char *FName, WORKER *Base, int n )
{
  FILE *F;

  if ((F = fopen(FName, "wb")) == NULL)
    return 0;
  fwrite(Base, sizeof(WORKER), n, F);
  fclose(F);
  return 1;
}

int LoadDB( char *FName, WORKER *Base, int size )
{
  int n;
  FILE *F;

  if ((F = fopen(FName, "rb")) == NULL)
    return 0;
  n = fread(Base, sizeof(WORKER), size, F);
  fclose(F);
  return n;
}

int IsNameLess( WORKER A, WORKER B )
{
  int n = strcmp(A.Surname, B.Surname);
  if (n == 0)
    return strcmp(A.Name, B.Name);
  return n;
}

int IsDateLess( WORKER A, WORKER B )
{
  if (A.Birthday.Year == B.Birthday.Year)
    if (A.Birthday.Month == B.Birthday.Month)
      return A.Birthday.Day < B.Birthday.Day;
    else
      return A.Birthday.Month < B.Birthday.Month;
  else
    return A.Birthday.Year < B.Birthday.Year;
}

void Sort( WORKER *A, int n, int (*IsLess)( WORKER A, WORKER B ) )
{
   int i, k;
   WORKER tmp;
   
   for (k = 0; k < n - 1; k++)
     for (i = 0; i < n - 1 - k; i++)
     {
       if (IsLess(A[i], A[i + 1]))
       {
         tmp = A[i];
         A[i] = A[i + 1];
         A[i + 1] = tmp;
       }
     }
}

void Reverse( WORKER *A, int n )
{
  int i, j;

  for (i = 0, j = n - 1; i < j; i++, j--)
  {
    WORKER tmp = A[i];

    A[i] = A[j];
    A[j] = tmp;
  }
}

void Report( FILE *F, WORKER *A, int n )
{
  int h[7], cost, i, j, s;

  printf("Hour cost: ");
  scanf("%d", &cost);
  for (i = 0; i < 7; i++)

  for (i = 0; i < n; i++)
  {
    for (s = 0, j = 0; j < 7; j++)
      s += h[j] * A[i].Hours[j];
    fprintf(F, "%i) %s %s =>$%d\n", i, A[i].Surname, A[i].Name, s * cost);
  }
}