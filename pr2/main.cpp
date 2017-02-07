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
    int cod_a, m=0, n=0, s=1, i;
    long long int mult;
    __int128_t max=1;
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
        if ( news[n].se + news[n].fi == 0 ) {
            printf("Nespravny vstup.\n");
            return 0;
        }
        n++;
        memset(alphabet, 0, 26*sizeof(int));
        if ( m != n ){
            printf("Nespravny vstup.\n");
            return 0;
        }
    }

    if ( n < 2 ){
        printf("Nespravny vstup.\n");
        return 0;
    }

    for (i=0;i<n-1;i++) {
        if ((news[i].fi == 0 && news[i+1].fi == 0) || (news[i].fi == 0 && news[i+1].se == 0) ||
            (news[i].se == 0 && news[i+1].fi == 0) || (news[i].se == 0 && news[i+1].se == 0)) {
            s++;
        }
    }

    if ( n == s ){
        printf("Synchronizace za: 0\n");
        return 0;
    }

    for (i=0;i<n;i++) {
        news[i].se += news[i].fi;
        max*=news[i].se;
    }

    qsort(news, n, sizeof(ZPRAVY), comp);
    while ( news[n-1].fi != news[0].fi ){
        for (i=0;i<n-1;i++) {
            while (news[n-1].fi > news[i].fi) {
                if (max < news[i].fi) {
                    printf("Nelze dosahnout.\n");
                    return 0;
                }
                if ( (mult=(news[n-1].fi-news[i].fi)/news[i].se)>=1 )
                    news[i].fi += mult*news[i].se;
                else
                news[n-1].fi += news[n-1].se;
            }
        }
    }

    printf("Synchronizace za: %lld\n", news[0].fi);

    free(news);
    return 0;
}