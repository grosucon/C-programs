#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct seznam {
    char *number=NULL;
    char *name=NULL;
    char *nameT9=NULL;
    long long len;
    int len_nr;
} tel_seznam;
/*------------------------------------------------------------------*/
int one_space () {
    char sym;

    if ( (sym = fgetc(stdin) )== ' ' )
        if ( (sym=fgetc(stdin))!=' '&&sym!='\n' ) {
            ungetc(sym, stdin);
            return 0;
        }
    ungetc(sym, stdin);
    return 1;
}
/*------------------------------------------------------------------*/
void removeLF ( char *x ) { //Vagner kod
    int l = strlen ( x );
    if ( l > 0 && x[l-1] == '\n' )
        x[l-1] = 0;
}
/*------------------------------------------------------------------*/
int numbers_only(const char *s) {
    while (*s) {
        if ( isdigit(*s++) == 0 ) return 0;
    }

    return 1;
}
/*------------------------------------------------------------------*/
int alpha_only(const char *s) {
    while (*s) {
        if ( !isalpha(*s) && *s!=' ' ) return 0;
        s++;
    }

    return 1;
}
/*------------------------------------------------------------------*/
char charToInt(char chrctr) {
    char number;
    chrctr=tolower(chrctr);
    if (chrctr == 'a' || chrctr == 'b' || chrctr == 'c') {
        number = '2';
    } else if (chrctr == 'd' || chrctr == 'e' || chrctr == 'f') {
        number = '3';
    } else if (chrctr == 'g' || chrctr == 'h' || chrctr == 'i') {
        number = '4';
    } else if (chrctr == 'j' || chrctr == 'k' || chrctr == 'l') {
        number = '5';
    } else if (chrctr == 'm' || chrctr == 'n' || chrctr == 'o') {
        number = '6';
    } else if (chrctr == 'p' || chrctr == 'q' || chrctr == 'r' || chrctr == 's') {
        number = '7';
    } else if (chrctr == 't' || chrctr == 'u' || chrctr == 'v') {
        number = '8';
    } else if (chrctr == 'w' || chrctr == 'x' || chrctr == 'y' || chrctr == 'z') {
        number = '9';
    } else
        number = '1';

    return number;
}
/*------------------------------------------------------------------*/
int alreadyexist ( tel_seznam **people , int *cnt ) {

    for (int i=0;i<*cnt-1;i++) {
        if ( (*people)[i].len == (*people)[*cnt-1].len && (*people)[i].len_nr == (*people)[*cnt-1].len_nr )
                if ( memcmp( (*people)[i].name, (*people)[*cnt-1].name, (*people)[*cnt-1].len ) == 0 )
                        if ( memcmp( (*people)[i].number, (*people)[*cnt-1].number, (*people)[*cnt-1].len_nr ) == 0 )
                            return 1;

            }

    return 0;
}
/*------------------------------------------------------------------*/
int readNesVys ( tel_seznam **people , int *cnt ) {
    size_t size;

    (*people)[*cnt-1].name=NULL;
    getline( &(*people)[*cnt-1].name, &size,stdin);
    free((*people)[*cnt-1].name);

    return 0;
}
/*------------------------------------------------------------------*/
int readLine ( tel_seznam **people , int *cnt ){

    size_t size;
    long long len1;
    char numeric='\0';
    int n=0;

    *people=(tel_seznam*)realloc(*people, (++(*cnt))*sizeof(tel_seznam));

    if ( one_space() ) {
        readNesVys(&(*people),&(*cnt));
        (*cnt)--;
        return 1;
    }

    (*people)[*cnt-1].number=NULL;
    (*people)[*cnt-1].number=(char*) malloc( 20 * sizeof (char) );

    while ( n!=20 ) {
        numeric=fgetc(stdin);
        if ( numeric==' ' || numeric=='\n' ) break;
        if ( !isdigit(numeric) ) {
            readNesVys(&(*people),&(*cnt));
            free((*people)[*cnt-1].number);
            (*cnt)--;
            return 1;
        }
        (*people)[*cnt-1].number[n]=numeric;
        n++;
    }
     if ( n!=20 ) ungetc(numeric,stdin);

    if ( n<1 || one_space() ) {
        free((*people)[*cnt-1].number);
        readNesVys(&(*people),&(*cnt));
        (*cnt)--;
        return 1;
    }

    (*people)[*cnt-1].number=(char*) realloc((*people)[*cnt-1].number, n * sizeof (char) );
    (*people)[*cnt-1].len_nr=n;


    (*people)[*cnt-1].name=NULL;
    len1=getline( &(*people)[*cnt-1].name, &size,stdin);
    removeLF( (*people)[*cnt-1].name );
    len1--;
    if ( !len1 || !alpha_only( (*people)[*cnt-1].name ) || (*people)[*cnt-1].name[len1-1]==' ' ) {
        free((*people)[*cnt-1].number);
        free((*people)[*cnt-1].name);
        (*cnt)--;
        return 1;
    }

    (*people)[*cnt-1].len=len1;

    if ( alreadyexist(&(*people),&(*cnt)) ) {
        free((*people)[*cnt-1].number);
        free((*people)[*cnt-1].name);
        (*cnt)--;
        return 2;
    }

    (*people)[*cnt-1].nameT9=NULL;
    (*people)[*cnt-1].nameT9=(char*) realloc( (*people)[*cnt-1].nameT9, len1 * sizeof(char) );
    for (long long i=0;i<len1;i++) {
        (*people)[*cnt-1].nameT9[i]=charToInt((*people)[*cnt-1].name[i]);
    }

    return 0;
}
/*------------------------------------------------------------------*/
int cauta(char *x, int m, char *y, long long n) {

    if ( m<=n ) {
        for (int i=m-1;i>=0;i--) {
            if ( x[i]!=y[i] ) return 0;
        }
        return 1;
    }

    return 0;
}
/*------------------------------------------------------------------*/
int hled ( tel_seznam people[] , int cnt ){
    char *nfrase=NULL;
    int *naid=NULL;
    int  na=0, o=0,a,m=0;
    long long lonf2;
    size_t size;

    if ( one_space() ) {
        printf("Nespravny vstup.\n");
        getline( &nfrase, &size,stdin);
        free(nfrase);
        return 1;
    }

    lonf2=getline( &nfrase, &size,stdin);
    removeLF(nfrase);
    lonf2--;
    if ( !lonf2 || !numbers_only(nfrase) ){
        printf("Nespravny vstup.\n");
        free(nfrase);
        return 1;
    }
    a=(int)lonf2;
    for(m=0;m<cnt;m++){
        if( cauta(nfrase,a,people[m].number, people[m].len_nr) || cauta(nfrase,a,people[m].nameT9, people[m].len) ){
            naid=(int*)realloc(naid, ++na*sizeof(int));
            naid[na-1]=m;
        }
    }
    if ( na<=10 )
    for (o=0;o<na;o++){
        for (int i=0;i<(people)[naid[o]].len_nr;i++)
            printf("%c", (people)[naid[o]].number[i]);
        printf (" %s\n", (people)[naid[o]].name );
    }

    printf("Celkem: %d\n", na);

    free(naid);
    free(nfrase);
    return 0;

}
/*------------------------------------------------------------------*/
int freeseznam ( tel_seznam * * people , int cnt ){

    for (int i=0;i<cnt;i++){
        free ( (*people)[i].number );
        free ( (*people)[i].name );
        free ( (*people)[i].nameT9 );
    }
    free(*people);

    return 0;
}
/*------------------------------------------------------------------*/
int main() {

    tel_seznam *people=NULL;
    int cnt=0,n=0;
    char query,symbol;

    while (1) {
        if ( (symbol=fgetc(stdin)) == EOF )
            break;
        ungetc(symbol,stdin);

        if ( scanf("%c", &query) != 1 || (query != '+' && query != '?') ) {
            printf("Nespravny vstup.\n");
            people=(tel_seznam*)realloc(people, (++(cnt))*sizeof(tel_seznam));
            readNesVys(&people, &cnt);
            cnt--;
            continue;
        }

        if (query == '+') {
            n = readLine(&people, &cnt);
            switch (n) {
                case 0:
                    printf("OK\n");
                    break;
                case 1:
                    printf("Nespravny vstup.\n");
                    break;
                case 2:
                    printf("Kontakt jiz existuje.\n");
                    break;
            }
            if ( n ) continue;
        }

        if (query == '?') {
            if ( hled(people,cnt) ) continue;
        }
    }

    freeseznam(&people,cnt);
    return 0;
}
