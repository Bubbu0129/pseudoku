#include <stdio.h>
#include <stdlib.h>

typedef unsigned int bitmap;
typedef struct permute_condition{
    int co[BASE];
    int num;
    bitmap ld;
} Cond;
typedef struct permute_status{
    int pos;
    int sum;
    bitmap usage;
} Status;

void parse( char* , Cond* );
void parse_line( char*, int*, char, bitmap* );
void permute( Cond*, Status*, char*, int* );
char num2char( int );
char getchar_no_enter( void );
