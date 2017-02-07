#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zpravy {
    long long int fi,se;
}ZPRAVY;
/*-----------------------------------------------------------------------*/
int comp(const void * i , const void * j)
{
    return *(int *)i - *(int *)j;
}
/*-----------------------------------------------------------------------*/
int myPow(int base, int exponent) {
    int n = 1;
    for (int i = 0; i < exponent; i++) {
        n *= base;
    }
    return n;
}
/*-----------------------------------------------------------------------*/
long long int delka_z ( int *alph ){
    int i;
    long long int delka=0, a;
    for (i=0;i<26;i++){
        a=myPow(2, i);
        delka+=(a * alph[i]);
    }
    return delka;
}
/*-----------------------------------------------------------------------*/
int main() {

    int alphabet[26];
    char sym;
    int cod_a, m=0, n=0, i, j;
    ZPRAVY *news=NULL;

    memset(alphabet, 0, 26*sizeof(int));
    printf("Zpravy:\n");

    while (1){
        if ( (sym=fgetc(stdin)) == EOF )
            break;
        ungetc(sym,stdin);
        news=(ZPRAVY*) realloc(news, (n+1) * sizeof(ZPRAVY) );

        while (1) {
            if ( (sym=fgetc(stdin)) == '\n' )
                break;

            cod_a = sym;
            if (cod_a >= 97 && cod_a <= 122) {
                alphabet[cod_a - 97]++;
            } else {
                if ( sym != '|') {
                    printf("Nespravny vstup.\n");
                    return 0;
                } else {
                    news[n].fi = delka_z(alphabet);
                    memset(alphabet, 0, 26*sizeof(int));
                    m++;
                }
            }
        }

        news[n].se=delka_z(alphabet);
        n++;
        memset(alphabet, 0, 26*sizeof(int));
        if ( m != n ){
            printf("Nespravny vstup.\n");
            return 0;
        }
    }

    m=0;
    for (i=0;i<n-1;i++) {
        if (news[i].fi == news[i+1].fi || news[i].se == news[i+1].se)
            if (news[i].fi == 0 || news[i].se == 0) {
                m++;
            }
    }
    if ( m == n-1 ){
        printf("Synchronizace za: 0\n");
        return 0;
    }

    for (i=0;i<n;i++){
        news[i].se+=news[i].fi;
    }

    for (i=0;i<n;i++){
        for (j=1;j<n;j++){
            if ( (news[i].fi % 2 == 0 && news[j].fi % 2 == 1) || (news[i].fi % 2 == 1 && news[j].fi % 2 == 0) )
                if ( news[i].se % 2 == 0 && news[j].se ){
                    printf("Nelze dosahnout.\n");
                    return 0;
                }
        }
    }

    while ( news[n-1].fi != news[0].fi ){
        qsort(news, n, sizeof(ZPRAVY), comp);
        for (i=0;i<n-1;i++){
            if ( news[n-1].fi > news[i].fi )
                news[i].fi+=news[i].se;
            }
    }

    printf("Synchronizace za: %lld\n", news[0].fi);

    free(news);
    return 0;
}