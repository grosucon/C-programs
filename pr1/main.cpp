#include <stdio.h>
#include <math.h>

/*---------------------------------------------------------------*/
int calc (double ls, double lv, double ps, double pv, double prek)
{
    int count, ai,bi ;
    double a,b;

    if (ls>=ps)
        ai=1;
    else {
        a = (ps - ls) / fabs(ls - prek) + 1;
        ai=a;
        if (a-0.00001<ai && a+0.00001>ai)
            ai=a;
        else
            ai++;
    }

    if (lv>=pv)
        bi=1;
    else {
        b = (pv - lv) / fabs(lv - prek) + 1;
        bi=b;
        if (b-0.00001<bi && b+0.00001>bi)
            bi=b;
        else
            bi++;
    }

    count=bi*ai;

    return count;
}
/*---------------------------------------------------------------*/
int main() {
    double l_s, l_v, p_s, p_v, pre;
    int rovne, otocene;

    printf("Velikost latky:\n");
    if ( scanf("%lf %lf", &l_s, &l_v)!=2 || l_s<=0 || l_v<=0)
    {
        printf ("Nespravny vstup.\n");
        return 0;
    }

    printf("Velikost plachty:\n");
    if ( scanf("%lf %lf", &p_s, &p_v)!=2 || p_s<=0 || p_v<=0)
    {
        printf ("Nespravny vstup.\n");
        return 0;
    }

    if ( (l_s>=p_s && p_s>=p_v) || (l_s>=p_v && l_v>=p_s) )
    {
        printf ("Pocet kusu latky: 1\n");
        return 0;
    }
    else
    {
        printf("Prekryv:\n");
        if ( scanf("%lf", &pre)!=1 || pre<0 )
        {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if (pre>l_s && pre>l_v)
        {
            printf("Nelze vyrobit.\n");
            return 0;
        }
    }

    if ( (l_s>=p_s && p_s>=p_v) || (l_s>=p_v && l_v>=p_s) )
    {
        printf ("Pocet kusu latky: 1\n");
        return 0;
    }

    rovne=calc(l_s,l_v,p_s,p_v,pre);
    otocene=calc(l_v,l_s,p_s,p_v,pre);

    if (rovne<otocene)
        printf("Pocet kusu latky: %d\n", rovne);
    else
        printf("Pocet kusu latky: %d\n", otocene);

    return 0;
}