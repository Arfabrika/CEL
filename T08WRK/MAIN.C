/* Fabrika Artem, 10-5, 30.10.2018 */

#include <stdio.h>
#include <conio.h>

#include "h.h"

void main( void )
{
  FILE *F;
  int DBSize = 0, i;
  char *fname[100];
  static WORKER DB[max];

  while (1)
  {
    Menu();
    switch (getch())
    {
      case '0':
        return;
      case '1':
        if (DBSize < max)
          ReadWorker(&DB[DBSize++]);
        else
          printf("Not enough room\n");
        break;
      case '2':
        for (i = 0; i < DBSize; i++)
        {
          printf("%i)  %s %s ",i,  DB[i].Surname, DB[i].Name);
          printf("%d.%d.%d ", DB[i].Birthday.Day, DB[i].Birthday.Month, DB[i].Birthday.Year);
          printf("%c ", DB[i].Sex);
          printf("%d, %d, %d, %d, %d, %d, %d\n", DB[i].Hours[0], DB[i].Hours[1], DB[i].Hours[2], DB[i].Hours[3], DB[i].Hours[4], DB[i].Hours[5], DB[i].Hours[6]);
        }
        break;
      case '3':
        printf("Imput a number: ");
        scanf("%i", &i);
        break;
      case '4':
        printf("Choice a sort\n");
        switch (getch())
        {
        case 'a':
          Sort(DB, DBSize, IsNameLess);
          printf("Completed successfully!\n");
          break;
        case 'b':
          Sort(DB, DBSize, IsDateLess);
          printf("Completed successfully!\n");
          break;
        }
        break;
      case '5':
        Reverse(&DB, DBSize);
        printf("Completed successfully!\n");
        break;
      case '6':
        printf("save file name: ");
        GetStr(fname, sizeof(fname));
        if (SaveDB(fname, DB, DBSize))
          printf("Ok!\n");
        else
          printf("Error!\n");
        break;
      case '7':
        printf("load file name: ");
        GetStr(fname, sizeof(fname));
        DBSize = LoadDB(fname, DB, max);
        printf("Load %d records\n", DBSize);
        /*DBSize += LoadDB(fname, DB + DbSize, max - DBSize); */
        break;
      case '8':
        break;
      case '9':
        if (F = fopen("rep.txt", "w") != NULL)
          Report(F, DB, DBSize);
        printf("Completed successfully!\n");
        break;
      default:
        printf("Incorrect choice!\n");
     }
  }
}