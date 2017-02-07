#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sums {
    int sum;
}SUMS;
/*-----------------------------------------------------------------------*/
typedef struct counts {
    int sum,cnt;
}COUNTS;
/*-----------------------------------------------------------------------*/
int comp(const void * i , const void * j) {
    return *(int *)i - *(int *)j;
}
/*----------------------------------------------------------------------*/
int **create_pole() {
    int **pole;

    pole= (int **) malloc(2001 * sizeof (int *));
    for (int i=0; i<2001; i++)
        pole[i]=(int *) malloc(2001 * sizeof(int));

    return pole;
}
/*----------------------------------------------------------------------*/
void free_pole(int **pole, int line) {
    for (int i=0; i<line; i++)
        free((void *) pole[i]);

    free((void *) pole);
}
/*----------------------------------------------------------------------*/
int sum_pole ( int **pole, int s_h, int s_w, int f_h, int f_w ) {

    int sum=0,i,j;

    for (j=s_h;j<=f_h;j++) {
        for (i=s_w;i<=f_w;i++) {
            sum+=pole[i][j];
        }
    }

    return sum;
}
/*----------------------------------------------------------------------*/
int main() {

    int **grid=NULL;
    int width,height,i,j,m,n,sum,cnt=0,lenght=0,end=0;
    char word[10],symbol,symbol1;
    SUMS *results=NULL;
    COUNTS *final=NULL;

    printf("Velikost mapy:\n");
    if ( (scanf("%d %d", &width, &height))!=2 || width<=0 || height<=0 || width>2000 || height>2000 ) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    grid=create_pole();
    printf("Cenova mapa:\n");
    for (j=0;j<height;j++) {
        for (i=0;i<width;i++) {
            if ( (scanf("%d", &grid[i][j]))!=1 ) {
                printf("Nespravny vstup.\n");
                return 0;
            }
        }
    }

    results=(SUMS*) malloc( height*height*width*width * sizeof(SUMS) );
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            for (n = j; n < height; n++) {
                for (m = i; m < width; m++) {
                    results[lenght].sum=sum_pole(grid, j, i, n, m);
                    lenght++;
                }
            }
        }
    }
    results=(SUMS*) realloc(results, lenght * sizeof(SUMS) );
    qsort(results, lenght, sizeof(SUMS), comp);

    for (i = 0; i < lenght-1; i++) {
        if ( results[i].sum==results[i+1].sum )
            cnt++;
        else {
            final=(COUNTS*) realloc(final, (end+1) * sizeof(COUNTS) );
            final[end].sum=results[i].sum;
            final[end].cnt=cnt+1;
            end++;
            cnt=0;
        }
    }
    cnt=0;

    printf("Dotazy:\n");

    while (1) {

        symbol1=fgetc(stdin);
        if ( (symbol=fgetc(stdin)) == EOF )
            break;
        ungetc(symbol,stdin);
        ungetc(symbol1,stdin);

        if ( scanf("%8s %d", word, &sum)!=2 || ( strcmp(word, "count") != 0 && strcmp(word, "list") != 0 ) ) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if ( strcmp(word, "list") == 0 ) {
            for (j = 0; j < height; j++) {
                for (i = 0; i < width; i++) {
                    for (n = j; n < height; n++) {
                        for (m = i; m < width; m++) {
                            if ((sum_pole(grid, j, i, n, m)) == sum) {
                                cnt++;
                                printf("%d @ (%d,%d) - (%d,%d)\n", sum,i,j,m,n);
                            }
                        }
                    }
                }
            }
        }

        if ( strcmp(word, "count") == 0 ) {
            for (i = 0; i < end; i++) {
                if ( final[i].sum == sum ) {
                    cnt = final[i].cnt;
                    break;
                }
            }
        }

        printf("Celkem: %d\n", cnt);
        cnt=0;
    }

    free(final);
    free(results);
    free_pole(grid,2001);
    return 0;
}