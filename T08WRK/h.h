/* Fabrika Artem, 10-5, 30.10.2018 */

#define max 10

typedef struct
{
  int Day, Month, Year;
} DATE;

typedef struct
{
  char Name[30], Surname[47];
  DATE Birthday;
  char Sex;
  int Hours[7];
} WORKER;

void Menu( void );
void GetStr( char *s, int maxlen );
void ReadWorker( WORKER *W );
int SaveDB( char *FName, WORKER *Base, int n );
int LoadDB( char *FName, WORKER *Base, int size );
int IsNameLess( WORKER A, WORKER B );
int IsDateLess( WORKER A, WORKER B );
void Reverse( WORKER *A, int n );
void Report( FILE *F, WORKER *A, int n );
void Sort( WORKER *A, int n, int (*IsLess)( WORKER A, WORKER B ) );