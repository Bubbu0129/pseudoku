#include "config.h"
#include "main.h"

int main(){

    char symbols[BASE+1] = {};
    Cond cond0 = { {0}, 0, 0 };
    Status status0 = { 0, 0, 0 };
    char sequence[BASE+1] = {};
    int ans = 0;
    
    printf("#define BASE %d\n#define LEADING_ZERO %d\n", BASE, LEADING_ZERO);

    parse(symbols, &cond0);

    printf("\n%s\n", symbols);
    for (int j=0; j < cond0.num; j++)
        putchar('-');
    putchar('\n');

    permute(&cond0, &status0, sequence, &ans);

    switch (ans){
        case 0: 
            printf("No solution found.\n");
            break;
        case 1:
            printf("Total 1 solution.\n");
            break;
        default:
            printf("Total %d solutions.\n", ans);
    }

    return 0;
}

void parse( char* sym, Cond* cptr ){

    char ch;
    int i;
    int delta[BASE+1];

    printf("Enter the summands of the pseudoku:\n");
    ch = getchar_no_enter();
    do {
        parse_line(sym, delta, ch, &cptr->ld);
        for (i=0; i<BASE; i++)
            cptr->co[i] += delta[i];
    } while ((ch = getchar()) != '\n');

    printf("Enter the sum of the pseudoku:\n");
    ch = getchar_no_enter();
    parse_line(sym, delta, ch, &cptr->ld);
    for (i=0; i<BASE && sym[i]; i++)
        cptr->co[i] -= delta[i];

    if ( sym[BASE] ){
        fprintf(stderr, "Error: Maximum number of symbols exceeded (%d).\n", BASE);
        exit(EXIT_FAILURE);
    }
    cptr->num = i;

    return;
}

void parse_line( char* sym, int* co, char initial, bitmap* ld){

    char ch;
    int i;

    for (int j=0; j<BASE; j++)
        co[j] = 0;

    for (i=0; i<BASE && sym[i] && sym[i]!=initial; i++)
        continue;
    sym[i] = initial;
    co[i] ++;
    *ld |= 1<<i;

    while ((ch = getchar()) != '\n'){
        for (int j=0; j<BASE; j++)
            co[j] *= BASE;
        for (i=0; i<BASE && sym[i] && sym[i]!=ch; i++)
            continue;
        sym[i] = ch;
        co[i] ++;
    }

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

    int i = !LEADING_ZERO && (cptr->ld >> sptr->pos & 1);

    Status prev = *sptr;
    for (; i<BASE; i++){
        if ( sptr->usage >> i & 1 )
            continue;
        seq[sptr->pos] = num2char(i);
        sptr->usage |= 1<<i;
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
    return 32;

}

char getchar_no_enter( void ){

    char ch = getchar();
    if ( ch == '\n' ){
        fprintf(stderr, "Error: Empty line.\n");
        exit(EXIT_FAILURE);
    }

    return ch;
}
