#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct seznam {
    char number[21];
    char *name=NULL;
    char *nameT9=NULL;
    long long lonf;
} tel_seznam;
/*------------------------------------------------------------------*/
int one_space () {
    char sym;

    if ( fgetc(stdin) == ' ' )
        if ( sym=fgetc(stdin) !=' ' ) {
            ungetc(sym, stdin);
            return 0;
        }
    return 1;
}
/*------------------------------------------------------------------*/
int numbers_only(const char *s)
{
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }

    return 1;
}
/*------------------------------------------------------------------*/
int alpha_only(const char *s)
{
    while (*s) {
        if ( !isalpha(*s) && *s!=' ' ) return 0;
        s++;
    }

    return 1;
}
/*------------------------------------------------------------------*/
int charToInt(char chrctr) {
    int number;
    chrctr=tolower(chrctr);
    if (chrctr == 'a' || chrctr == 'b' || chrctr == 'c') {
        number = 2;
    } else if (chrctr == 'd' || chrctr == 'e' || chrctr == 'f') {
        number = 3;
    } else if (chrctr == 'g' || chrctr == 'h' || chrctr == 'i') {
        number = 4;
    } else if (chrctr == 'j' || chrctr == 'k' || chrctr == 'l') {
        number = 5;
    } else if (chrctr == 'm' || chrctr == 'n' || chrctr == 'o') {
        number = 6;
    } else if (chrctr == 'p' || chrctr == 'q' || chrctr == 'r' || chrctr == 's') {
        number = 7;
    } else if (chrctr == 't' || chrctr == 'u' || chrctr == 'v') {
        number = 8;
    } else if (chrctr == 'w' || chrctr == 'x' || chrctr == 'y' || chrctr == 'z') {
        number = 9;
    } else
        number=1;

    return number;
}
/*------------------------------------------------------------------*/
int alreadyexist ( tel_seznam **people , int *cnt ) {
    int lenght_name=0, lenght_nr=0;

    for (int i=0;i<*cnt-1;i++) {
        if ( (*people)[i].lonf == (*people)[*cnt-1].lonf ) {
            for (int j=0;i<(*people)[i].lonf;i++) {
                if ( (*people)[i].name[j] != (*people)[*cnt-1].name[j] )
                    break;
                else
                    lenght_name++;
            }

            if ( lenght_name != (*people)[i].lonf )
                lenght_name=0;
            else {
                for (int j=0;j<20;j++) {
                    if ( (*people)[i].number[j] != (*people)[*cnt-1].number[j] ) {
                        lenght_name=0;
                        break;
                    }
                    else
                        lenght_nr++;
                }
            }

            if ( lenght_nr != 20 )
                lenght_nr=0;
            else
                return 1;
        }
    }

    return 0;
}
/*------------------------------------------------------------------*/
int readLine ( tel_seznam **people , int *cnt ){

    size_t size;
    long long lonf1;

    if ( one_space() ) {
        return 1;
    }
    *people=(tel_seznam*)realloc(*people, (++(*cnt))*sizeof(tel_seznam));
    scanf ("%s", (*people)[*cnt-1].number);
    if ( !numbers_only((*people)[*cnt-1].number) || (*people)[*cnt-1].number[21]!='\0' || one_space() ) {
        free((*people)[*cnt-1].number);
        (*cnt)--;
        return 1;
    }

    (*people)[*cnt-1].name=NULL;
    lonf1=getline( &(*people)[*cnt-1].name, &size,stdin);
    if( !lonf1 || !alpha_only( (*people)[*cnt-1].name ) || (*people)[*cnt-1].name[lonf1-1]!='\n') {
        free((*people)[*cnt-1].number);
        free((*people)[*cnt-1].name);
        (*cnt)--;
        return 1;
    }

    if ( alreadyexist(people, cnt) ) {
        free((*people)[*cnt-1].number);
        free((*people)[*cnt-1].name);
        (*cnt)--;
        return 2;
    }

    (*people)[*cnt-1].lonf=lonf1-1;

    (*people)[*cnt-1].nameT9=NULL;
    (*people)[*cnt-1].nameT9=(char*) realloc( (*people)[*cnt-1].nameT9, (lonf1-1) * sizeof(char) );
    for (long long i=0;i<lonf1-1;i++) {
        (*people)[*cnt-1].nameT9[i]=charToInt((*people)[*cnt-1].name[i]);
    }

    return 0;
}
/*------------------------------------------------------------------*/
int freeseznam ( tel_seznam * * people , int cnt ){

    for (int i=0;i<cnt;i++){
        free ( (*people)[i].name );
        free ( (*people)[i].nameT9 );
    }
    free(*people);
    return 0;
}
/*------------------------------------------------------------------*/
int main() {

    tel_seznam *people=NULL;
    int cnt=0,n=0,m;
    char query;

   for (m=0;m<3;m++) {
       if ( (scanf("%c", &query))!=1 || ( query!='+' && query!='?' ) ) {
           printf("Nespravny vstup.\n");
       }

       if (query == '+') {
           n = readLine(&people, &cnt);
           if (n == 0) {
               printf("OK\n");
           } else if (n == 1) {
         //      printf("Nespravny vstup.\n");
           } else if (n == 2) {
               printf("Kontakt jiz existuje.\n");
           }
       }

   }



  //  freeseznam(&people,cnt);
    return 0;
}
