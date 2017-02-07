#include <stdio.h>
#include <stdlib.h>

typedef struct plane {
    int *data=NULL;
    int cnt_data;
    int id;
    int hash;
    int printed;
}PLANE;
/*----------------------------------------------------------------*/
typedef struct news {
    int id;
    int cnt_data;
    int *data=NULL;
    int hash;
}NEWS;
/*----------------------------------------------------------------*/
int comp(const void * i , const void * j) {
    return *(int *)i - *(int *)j;
}
/*----------------------------------------------------------------*/
int cmp(const void *a, const void *b){
    const PLANE *arg1 = (const PLANE *)a;
    const PLANE *arg2 = (const PLANE *)b;

    if(arg1->cnt_data > arg2->cnt_data) return 1;
    if(arg1->cnt_data < arg2->cnt_data) return -1;
    else{
        if(arg1->hash > arg2->hash) return 1;
        if(arg1->hash < arg2->hash) return -1;
        else{
            if(arg1->id > arg2->id) return 1;
            if(arg1->id < arg2->id) return -1;
            return 0;
        }
    }
}
/*----------------------------------------------------------------*/
int CompArrays (int *array1, int *array2, int lenght) {d
    int boole=1,m;

    for (int i=0;i<lenght;i++) {
        if ( array1[0]==array2[i] ) {
            for (int j = i; j < lenght+i; j++) {
                if ( j>=lenght )
                    m=j-lenght;
                else
                    m=j;
                if ( array1[j-i]!=array2[m] ) boole=0;
            }
            if ( boole )
                return 1;
            else
                boole=1;
        }
    }

    return 0;
}
/*----------------------------------------------------------------*/
int main() {

    char sym,end,sym1,sym2;
    int cnt_id=0,cnt_d=0,cnt=0,n=0,hash=0,p=0;
    int id,data,i,j;
    NEWS *parts=NULL;
    PLANE *letadla=NULL;

    printf("Zpravy:\n");
    while (1) {
        sym=fgetc(stdin);
        if ( (end=fgetc(stdin)) == EOF )
            break;
        ungetc(end,stdin);
        ungetc(sym,stdin);

        if ( (scanf("%d", &id))!=1 || id < 0 ) {
            printf("Nespravny vstup.\n");
            return 0;
        }
        parts=(NEWS*) realloc(parts, (cnt_id+1) * sizeof(NEWS));
        parts[cnt_id].id=id;

        parts[cnt_id].data=NULL;

        if ( (scanf(" %c %c", &sym1, &sym2))!=2  || sym1!=':' || sym2!='[' ) {
            printf("Nespravny vstup.\n");
            for (i=0;i<cnt_id+1;i++) {
                free(parts[i].data);
            }
            free(parts);
            return 0;
        }

        sym=',';
        while ( sym==',' ) {
            if ( (scanf("%d %c", &data, &sym))!=2 || ( sym!=',' && sym!=']' ) ) {
                printf("Nespravny vstup.\n");
                for (i=0;i<cnt_id+1;i++) {
                    free(parts[i].data);
                }
                free(parts);
                return 0;
            }

            hash+=data;
            parts[cnt_id].data=(int*) realloc(parts[cnt_id].data, (cnt_d+1) * sizeof(int));
            parts[cnt_id].data[cnt_d]=data;
            cnt_d++;
        }

        parts[cnt_id].cnt_data=cnt_d;
        parts[cnt_id].hash=hash;
        cnt_id++;
        cnt_d=0;
        hash=0;
    }

    if ( cnt_id==0 ) {
        printf("Nespravny vstup.\n");
        for (i=0;i<cnt_id;i++) {
            free(parts[i].data);
        }
        free(parts);
        return 0;
    }

    if ( cnt_id==1 ) {
        printf("Unikatni zpravy:\n");
        printf("%d\n", parts[0].id);
        for (i=0;i<cnt_id;i++) {
            free(parts[i].data);
        }
        free(parts);
        return 0;
    }

    qsort(parts, cnt_id, sizeof(NEWS), comp);

    for (i = 0; i < cnt_id-1; i++) {
        letadla=(PLANE*) realloc(letadla, (cnt+1) * sizeof(PLANE));
        if ( n==0 )letadla[cnt].data=NULL;
        letadla[cnt].printed=0;
        letadla[cnt].id=parts[i].id;
        hash+=parts[i].hash;
        letadla[cnt].hash=hash;
        n+=parts[i].cnt_data;
        letadla[cnt].cnt_data=n;
        letadla[cnt].data=(int*) realloc(letadla[cnt].data, (letadla[cnt].cnt_data) * sizeof(int));
        for (j=letadla[cnt].cnt_data-parts[i].cnt_data;j<letadla[cnt].cnt_data;j++) {
            letadla[cnt].data[j]=parts[i].data[j-(letadla[cnt].cnt_data-parts[i].cnt_data)];
        }

        if ( parts[i].id!=parts[i+1].id ) {
            cnt++;
            n=0;
            hash=0;
        }

        if ( i==(cnt_id-2) ) {
            if ( parts[i].id!=parts[i+1].id ) {
                letadla=(PLANE*) realloc(letadla, (cnt+1) * sizeof(PLANE));
                letadla[cnt].data=NULL;
                letadla[cnt].printed=0;
                letadla[cnt].id=parts[i+1].id;
                letadla[cnt].hash=parts[i+1].hash;
                letadla[cnt].cnt_data=parts[i+1].cnt_data;
                letadla[cnt].data=(int*) realloc(letadla[cnt].data, (letadla[cnt].cnt_data) * sizeof(int));
                for (j=letadla[cnt].cnt_data-parts[i+1].cnt_data;j<letadla[cnt].cnt_data;j++) {
                    letadla[cnt].data[j]=parts[i+1].data[j-(letadla[cnt].cnt_data-parts[i+1].cnt_data)];
                }
            } else {
                letadla[cnt].printed=0;
                n+=parts[i+1].cnt_data;
                letadla[cnt].cnt_data=n;
                hash+=parts[i+1].hash;
                letadla[cnt].hash=hash;
                letadla[cnt].data=(int*) realloc(letadla[cnt].data, (letadla[cnt].cnt_data) * sizeof(int));
                for (j=letadla[cnt].cnt_data-parts[i+1].cnt_data;j<letadla[cnt].cnt_data;j++) {
                    letadla[cnt].data[j]=parts[i+1].data[j-(letadla[cnt].cnt_data-parts[i+1].cnt_data)];
                }
            }
        }
    }

    cnt++;
    qsort(letadla, cnt, sizeof(PLANE), cmp);

    printf("Unikatni zpravy:\n");
    for (i=0;i<cnt;i++) {
        if ( !letadla[i].printed ) {
            printf("%d", letadla[i].id);
            letadla[i].printed=1;
            p=1;
        }
        for (j=i;j<cnt;j++) {
            if ( letadla[i].cnt_data==letadla[j].cnt_data && letadla[i].hash==letadla[j].hash && i!=j ) {
                if ( CompArrays(letadla[i].data, letadla[j].data, letadla[i].cnt_data) ) {
                    if ( !letadla[j].printed ) {
                        printf(", %d", letadla[j].id);
                        letadla[j].printed=1;
                    }
                }
            }
        }
        if (p) {
            printf("\n");
            p=0;
        }
    }

    for (i=0;i<cnt_id;i++) {
        free(parts[i].data);
    }
    free(parts);

    for (i=0;i<cnt;i++) {
        free(letadla[i].data);
    }
    free(letadla);


    return 0;
}