#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef struct permute_condition{
    int co[BASE]; // coefficient
    int num; // number of symbols
    uint ld; // leading_digits
} Cond;
typedef struct permute_status{
    int pos;
    int sum;
    uint bitmap;
} Status;

void parse( char* , Cond* );
void permute( Cond*, Status*, char*, int* );
char num2char( int );
