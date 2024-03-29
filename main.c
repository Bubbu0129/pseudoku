#include "config.h"
#include "main.h"

int main(){

    char symbols[BASE+1] = {};
    Cond cond0;
    Status status0 = { 0, 0, ~0 };
    char sequence[BASE+1];
    int ans = 0;
    
    printf("#define BASE %d\n#define LEADING_ZERO %d\n", BASE, LEADING_ZERO);
    printf("Enter the pseudoku, with the last line being the sum of the previous lines:\n");
    parse(symbols, &cond0);
    printf("%s\n", symbols);
    permute(&cond0, &status0, sequence, &ans);
    switch (ans){
        case 0: 
            printf("No solution found.");
            break;
        case 1:
            printf("Found 1 solution.");
            break;
        default:
            printf("Found %d solutions.", ans);
    }
    putchar('\n');

    return 0;
}

void parse( char* sym, Cond* cptr ){

    char ch;
    int i;
    int delta[BASE];
    cptr->ld = 0;

    while ((ch = getchar()) != '\n'){
        for (i=0; i<BASE && sym[i] && sym[i]!=ch; i++)
            continue;
        cptr->ld += 1<<i;
        for (int j=0; j<BASE; j++)
            delta[j] = 0;
        do{
            for (int j=0; j<BASE; j++)
                delta[j] *= BASE;
            for (i=0; i<BASE && sym[i] && sym[i]!=ch; i++)
                continue;
            if (i == BASE){
                fprintf(stdout, "Exceeded maximum number of sym: %d\n", BASE);
                exit(EXIT_FAILURE);
            }
            sym[i] = ch;
            delta[i] ++;
        } while ((ch = getchar()) != '\n');
        for (int j=0; j<BASE; j++){
            cptr->co[j] += delta[j];
        }
    }
    for (i=0; sym[i]; i++)
        cptr->co[i] -= 2*delta[i];
    cptr->num = i;

    return;
}

void permute( Cond* cptr, Status* sptr, char* seq, int* ans ){

    if ( sptr->pos == cptr->num ){
        if ( sptr->sum == 0 ){
            printf("%s\n", seq);
            (*ans) ++;
        }
        return;
    }

    uint i = 0;
    if ( !LEADING_ZERO && (cptr->ld >> sptr->pos & 1) )
        i = 1;

    Status prev = *sptr;
    for (; i<BASE; i++)
        if ( sptr->bitmap >> i & 1 ){
            seq[sptr->pos] = num2char(i);
            sptr->bitmap -= 1<<i;
            sptr->sum += cptr->co[sptr->pos] * i;
            sptr->pos ++;
            permute( cptr, sptr, seq, ans );
            *sptr = prev;
        }

    return;
}

char num2char( int n ){
    if (n < 10)
        return n+48;
    else if (n < 36)
        return n+55;
    else
        return 32;
}
