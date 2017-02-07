#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int Prestupny (int year ) {

    if (((year % 4 == 0) && (year % 100 != 0) && (year % 4000 != 0))
        || ((year % 400 == 0) && (year % 4000 != 0)))
        year=1;
    else
        year=2;

    return year;
}
/*--------------------------------------------------------------------*/
int NespVstupIs ( int y1, int m1, int d1 ) {

    if ( y1<2000 || m1<1 || m1>12 || d1<1 || d1>31 ) return 0;

    if ( (m1==4 || m1==6 || m1==9 || m1==11) && (d1>30) ) return 0;

    if ( (Prestupny(y1)==1) && m1==2 && d1>29 ) return 0;
    if ( (Prestupny(y1)==2) && m1==2 && d1>28 ) return 0;

    return 1;
}
/*--------------------------------------------------------------------*/
int NespVstupCount ( int y1, int m1, int d1,
                     int y2, int m2, int d2 ) {

    if ( y1==y2 && m2<m1 ) return 0;
    if ( y1==y2 && m1==m2 && d2<d1 ) return 0;
    if ( y2<y1 || y2<2000 || y1<2000 || m1<1 || m2<1 || m1>12 || m2>12 || d1<1 || d2<1 || d1>31 || d2>31 ) return 0;

    if ( (m1==4 || m1==6 || m1==9 || m1==11) && (d1>30) ) return 0;
    if ( (m2==4 || m2==6 || m2==9 || m2==11) && (d2>30) ) return 0;

    if ( (Prestupny(y1)==1) && m1==2 && d1>29 ) return 0;
    if ( (Prestupny(y1)==2) && m1==2 && d1>28 ) return 0;
    if ( (Prestupny(y2)==1) && m2==2 && d2>29 ) return 0;
    if ( (Prestupny(y2)==2) && m2==2 && d2>28 ) return 0;

    return 1;
}
/*--------------------------------------------------------------------*/
int CountJD1 ( int y1, int m1, int d1 )
{
    int a, y, m, jdn, d;
    a = (14 - m1) / 12;
    y = (y1 + 4800 - a);
    m = m1 + 12 * a - 3;
    jdn = d1 + (153 * m + 2)/5 + 365 * y + y/4 - y/100 + y/400 - 32045;

    if (y>=4000){
        jdn-=y1/4000-(y1%4000==0&&m1<=2);
    }

    d = (jdn % 7) + 1;

    return d;

}
/*--------------------------------------------------------------------*/
int IsWorkDay ( int y, int m, int d ) {

    if ( !(NespVstupIs( y, m, d )) ) {
        return 0; }

    if ( (m==1 && d==1) || (m==5 && d==1) || (m==7 && d==5) ||
         (m==7 && d==6) || (m==9 && d==28) || (m==10 && d==28) ||
         (m==11 && d==17) || (m==12 && d==24) || (m==12 && d==25) ||
         (m==12 && d==26) || (m==5 && d==8) ) return 0;

    int a, y1, m1, jdn, d1;
    a = (14 - m) / 12;
    y1 = (y + 4800 - a);
    m1 = m + 12 * a - 3;
    jdn = d + (153 * m1 + 2)/5 + 365 * y1 + y1/4 - y1/100 + y1/400 - 32045;

    if (y>=4000){
        jdn-=y/4000-(y%4000==0&&m<=2);
    }

    d1 = (jdn % 7) + 1;

    if ( d1>=1 && d1<=5 )
        return 1;

    return 0;
}
/*--------------------------------------------------------------------*/
int Days_in_M ( int y, int m ) {

    int days=0;
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        days = 31;
    if (m == 4 || m == 6 || m == 9 || m == 11)
        days = 30;
    if (m == 2) {
        if ((Prestupny(y)) == 1)
            days = 29;
        else
            days=28;
    }

    return days;
}
/*--------------------------------------------------------------------*/
int FirstY ( int y1, int m1, int d1 ) {

    int m,d,cnt1=0;

    for (d=d1;d<=Days_in_M(y1,m1);d++) {
        if ( IsWorkDay(y1,m1,d) )
            cnt1++;
    }

    for ( m=m1+1; m<=12; m++ ) {
        for (d=1;d<=Days_in_M(y1,m);d++) {
            if ( IsWorkDay(y1,m,d) )
                cnt1++;
        }
    }
    return cnt1;
}
/*--------------------------------------------------------------------*/
int AllY ( int y1, int m1, int d1,
           int y2, int m2, int d2 ) {

    int y,cnt2=0,p,day;
    y1+=1;
    y2-=1;

    for (y=y1;y<=y2;y++) {
        p=Prestupny(y);
        day=CountJD1(y,1,1);
        if ( (p==1 && day==6) || (p==2 && day==1) || (p==2 && day==4) || (p==2 && day==7) )
            cnt2+=252;
        if ( (p==1 && day==3) || (p==1 && day==7) || (p==2 && day==2) || (p==2 && day==3) )
            cnt2+=253;
        if ( (p==1 && day==1) || (p==1 && day==2) || (p==1 && day==5) || (p==2 && day==5) || (p==2 && day==6) )
            cnt2+=254;
        if ( (p==1 && day==4) )
            cnt2+=255;
    }

    return cnt2;
}
/*--------------------------------------------------------------------*/
int LastY ( int y2, int m2, int d2 ) {

    int m,d,cnt3=0;

    for (d=1;d<=d2;d++) {
        if ( IsWorkDay(y2,m2,d) )
            cnt3++;
    }

    for ( m=1; m<=m2-1; m++ ) {
        for (d=1;d<=Days_in_M(y2,m);d++) {
            if ( IsWorkDay(y2,m,d) )
                cnt3++;
        }
    }
    return cnt3;
}
/*--------------------------------------------------------------------*/
int CountWorkDays ( int y1, int m1, int d1,
                    int y2, int m2, int d2,
                    int * cnt ) {

    int i,cnt4=0;

    if ( !(NespVstupCount( y1, m1, d1, y2, m2, d2 )) )
        return 0;

    if ( y2-y1>28001 ) {
        int after,n;

        n=(y2-y1-1)/28000;

        after=AllY( n*28000+y1, 1, 1, y2, 12, 31);

        *cnt = FirstY( y1, m1, d1 ) + LastY( y2, m2, d2 ) + after + n*7084845;
        
        return 1;
    }

    if ( y2>y1+1 ) {
        *cnt = FirstY( y1, m1, d1 ) + LastY( y2, m2, d2 ) + AllY( y1, m1, d1, y2, m2, d2 );
    }
    if ( y2==y1+1 ) {
        *cnt = FirstY( y1, m1, d1 ) + LastY( y2, m2, d2 );
    }
    if ( y2==y1 ) {
        *cnt =  FirstY( y1, m1, d1 ) - FirstY( y2, m2, d2 ) + IsWorkDay(y2,m2,d2);
    }
    if ( y2==y1 && m1==m2 ) {
        for (i=d1;i<=d2;i++){
            if (IsWorkDay(y1, m1, i))
                cnt4++;
        }
        *cnt = cnt4;
    }

    return 1;
}
/*--------------------------------------------------------------------*/
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    int cnt;

    assert ( IsWorkDay ( 2016, 11, 11 ) );
    assert ( ! IsWorkDay ( 2016, 11, 12 ) );
    assert ( ! IsWorkDay ( 2016, 11, 17 ) );
    assert ( ! IsWorkDay ( 2016, 11, 31 ) );
    assert ( IsWorkDay ( 2016,  2, 29 ) );
    assert ( ! IsWorkDay ( 2004,  2, 29 ) );
    assert ( ! IsWorkDay ( 2001,  2, 29 ) );
    assert ( ! IsWorkDay ( 1996,  1,  1 ) );
    assert ( CountWorkDays ( 2016, 11,  1,
                             2016, 11, 30, &cnt ) == 1
             && cnt == 21 );
    assert ( CountWorkDays ( 2016, 11,  1,
                             2016, 11, 17, &cnt ) == 1
             && cnt == 12 );
    assert ( CountWorkDays ( 2016, 11,  1,
                             2016, 11,  1, &cnt ) == 1
             && cnt == 1 );
    assert ( CountWorkDays ( 2016, 11, 17,
                             2016, 11, 17, &cnt ) == 1
             && cnt == 0 );
    assert ( CountWorkDays ( 2016,  1,  1,
                             2016, 12, 31, &cnt ) == 1
             && cnt == 254 );
    assert ( CountWorkDays ( 2015,  1,  1,
                             2015, 12, 31, &cnt ) == 1
             && cnt == 252 );
    assert ( CountWorkDays ( 2000,  1,  1,
                             2016, 12, 31, &cnt ) == 1
             && cnt == 4302 );
    assert ( CountWorkDays ( 2001,  2,  3,
                             2016,  7, 18, &cnt ) == 1
             && cnt == 3911 );
    assert ( CountWorkDays ( 2014,  3, 27,
                             2016, 11, 12, &cnt ) == 1
             && cnt == 666 );
    assert ( CountWorkDays ( 2001,  1,  1,
                             2000,  1,  1, &cnt ) == 0 );
    assert ( CountWorkDays ( 2001,  1,  1,
                             2015,  2, 29, &cnt ) == 0 );
    return 0;
}
#endif /* __PROGTEST__ */