#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#endif /* __PROGTEST__ */



unsigned long long int checkTrue( unsigned long long int length,
                                  unsigned int        s1,
                                  unsigned int        s2)
{
    if(( s1 + s2 )!= 0)
    {
        if( length % ( s1 + s2 )  == 0 )
        {
            return 1;
        }
    }
    return 0;
}

unsigned long long int checkTrue3( unsigned long long int length,
                                   unsigned int        s1,
                                   unsigned int        s2,
                                   unsigned int        s3)
{
    if(( s1 + s2 +s3 )!= 0)
    {
        if( length % ( s1 + s2 + s3 )  == 0 )
        {
            return 1;
        }
    }
    return 0;
}

unsigned long long int nod(unsigned long long int  s1 ,
                           unsigned long long int  s2)
{
    unsigned long long int div;
    if (s1 == s2)  return s1;
    long long int d = s1 - s2;
    if (d < 0) {
        d = -d;  div = nod(s1, d);
    } else
        div = nod(s2, d);
    return div;
}

unsigned long long int lcm(int s1, int s2)
{
    return s1*s2 / nod(s1, s2);
}


unsigned long long int par                           ( unsigned long long int length,
                                                       unsigned int        s1,
                                                       unsigned int        s2,
                                                       unsigned int        bulkhead,
                                                       unsigned int      * c1,
                                                       unsigned int      * c2 )
{


    if((length==s1*3||length==s2*3)&&(s1==s2*2||s1*2==s2)&&(bulkhead==s1||bulkhead==s2))
    {
        if(s1==s2*2)
        {
            *c2=0;
            *c1=1;
            return 1;
        }
        else if(s1*2==s2)
        {
            *c1=0;
            *c2=1;
            return 1;
        }
    }




    if(s1==s2*2&&length==s2*3)
    {
        *c1=1;
        *c2=1;
        return 2;
    }


    if(s2==s1*2&&length==s1*3)
    {
        *c1=1;
        *c2=1;
        return 2;
    }


    if(bulkhead==length)
    {
        return 1;
    }


    if((s1==0&&s2==0)||length==0)
    {
        return 0;
    }



    if(s1==0)
    {
        if((length-bulkhead)%(s2+bulkhead)==0)
        {
            *c1=0;
            *c2=(length-bulkhead)/(s2+bulkhead);
            return 1;
        }
        else
            return 0;
    }

    if(s2==0)
    {
        if((length-bulkhead)%(s1+bulkhead)==0)
        {
            *c2=0;
            *c1=(length-bulkhead)/(s1+bulkhead);
            return 1;
        }
        else
            return 0;
    }


    if(s1==s2)
    {
        if((length-bulkhead)%(s1+bulkhead)==0)
        {
            *c1=(length-bulkhead)/(s1+bulkhead);
            *c2=0;
            return 1;
        }
        else
            return 0;
    }

    if(bulkhead>=length)
    {
        if(bulkhead==length)
        {
            *c1=0;
            *c2=0;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    unsigned long long int nok = lcm(s1 + bulkhead,s2 + bulkhead) , ss1 = s1 + bulkhead , ss2 = 0 , res = 0;
    length-=bulkhead;
    s1+=bulkhead;
    s2+=bulkhead;

    unsigned int tmpc1 , tmpc2 , crab = 0;
    tmpc1 = *c1 , tmpc2 = * c2;

    while(ss1 + ss2 <= length)
    {

        for(; ss1 + ss2 <= length; ss2 +=s2)
        {
            if(checkTrue(length,ss1,ss2))
            {
                crab = length / ( ss1 + ss2);
                tmpc1 = ss1 / s1;
                tmpc2 = ss2 / s2;
            }
            if(tmpc1 != *c1 || tmpc2 != *c2)
            {
                break;
            }
        }
        if(tmpc1 != *c1 || tmpc2 != *c2)
        {
            break;
        }
        ss2=0;
        ss1 +=s1;

    }

    ss2=0;
    ss1=s1;

    if(tmpc1==*c1 || tmpc2==*c2) {
        for (; ss1 + ss2 <= length; ss2 += s2) {

            for (; ss1 + ss2 <= length; ss1 += s1) {
                if (checkTrue(length, ss1, ss2)) {

                    crab = length / ( ss1 + ss2);
                    tmpc1 = ss1 / s1;
                    tmpc2 = ss2 / s2;
                }
                if(tmpc1 != *c1 || tmpc2 != *c2)
                {
                    break;
                }
            }
            if(tmpc1 != *c1 || tmpc2 != *c2)
            {
                break;
            }
            ss1 = 0;
            ss2 += s2;
        }
    }




    if(tmpc1!=*c1||tmpc2!=*c2)
    {
        res+= 1 + ( length - tmpc1 * s1 * crab ) / nok + ( length - crab * tmpc2 * s2  ) / nok;
    }

    if(res!=0) {
        *c1 = (tmpc1 * crab);
        *c2 = tmpc2 * crab;
    }
    return res;



}








unsigned long long int hyperloop                           ( unsigned long long int length,
                                                             unsigned int        s1,
                                                             unsigned int        s2,
                                                             unsigned int        s3,
                                                             unsigned int        bulkhead,
                                                             unsigned int      * c1,
                                                             unsigned int      * c2,
                                                             unsigned int      * c3 )
{


    if(length==0)
    {
        return 0;
    }


    if(s1==0&&s2==0&&s3==0)
    {
        if(bulkhead==length)
        {
            *c1=0;
            *c3=0;
            *c2=0;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if(s1==0&&s2==0)
    {
        if((length-bulkhead)%(s3+bulkhead)==0)
        {
            *c1=0;
            *c2=0;
            *c3=(length-bulkhead)/(s3+bulkhead);
            return 1;
        }
        else return 0;
    }


    if(s1==0&&s3==0)
    {
        if((length-bulkhead)%(s2+bulkhead)==0)
        {
            *c1=0;
            *c2=(length-bulkhead)/(s2+bulkhead);
            *c3=0;
            return 1;
        }
        else return 0;
    }


    if(s3==0&&s2==0)
    {
        if((length-bulkhead)%(s1+bulkhead)==0)
        {
            *c1=(length-bulkhead)/(s1+bulkhead);
            *c2=0;
            *c3=0;
            return 1;
        }
        else return 0;
    }



    if(s1==0||s1>length)
    {
        if(par(length,s2,s3,bulkhead,c2,c3)>=1)
        {
        *c1=0;
        return par(length,s2,s3,bulkhead,c2,c3);
        }
        else
            return 0;
    }
    else if(s2==0||s2>length)
    {
        if(par(length,s1,s3,bulkhead,c1,c3)>=1)
        {
            *c1=0;
            return par(length,s1,s3,bulkhead,c1,c3);
        }
        else
            return 0;
    }
    else if(s3==0||s3>length)
    {

        if(par(length,s1,s2,bulkhead,c1,c2)>=1)
        {
            *c3=0;
            return par(length,s1,s2,bulkhead,c1,c2);
        }
        else
            return 0;
    }

    if(s1==s2&&s1==s3)
    {
        if((length-bulkhead)%(s1+bulkhead)==0)
        {
            *c2=0;
            *c3=0;
            *c1=(length-bulkhead)/(s1+bulkhead);
            return 1;
        }
        else
        {
            return 0;
        }
    }


    if(s1==s2)
    {
        if(par(length,s1,s3,bulkhead,c1,c3)>=1)
        {
            *c3=0;
            return par(length,s1,s3,bulkhead,c1,c3);
        }
        else return 0;
    }


    if(s1==s3)
    {
        if(par(length,s1,s2,bulkhead,c1,c2)>=1)
        {
            *c3=0;
            return par(length,s1,s2,bulkhead,c1,c2);
        }
        else return 0;
    }


    if(s3==s2)
    {

        if(par(length,s1,s2,bulkhead,c1,c2)>=1)
        {
            *c3=0;
            return par(length,s1,s2,bulkhead,c1,c2);
        }
        else return 0;
    }



    unsigned long long int res = 0;
    length-=bulkhead;
    s1+=bulkhead;
    s2+=bulkhead;
    s3+=bulkhead;
    unsigned int  ss2 = 0 , ss3 =s1;
    ss2=0,ss3=0;

    for(int i = (length/s1)*s1 ; i >= 0 ; i-=s1 )
    {
        ss2=((length-i)/s2)*s2 ;

        ss3=0;
        while(ss2>0)
        {
            while(length>i+ss2+ss3)
            {
                ss3+=s3;
            }

            if(checkTrue3(length,i,ss2,ss3)==1)
            {
                *c1=i/s1;
                *c2=ss2/s2;
                *c3=ss3/s3;
                res++;
            }
            //printf("%d %d %d\n",i,ss2,ss3);
            //printf("%d\n",i+ss2+ss3);
            ss2-=s2;
        }
        if(ss2==0)
        {
            while(length>=i+ss3)
            {
                if(checkTrue3(length,i,ss2,ss3)==1)
                {
                    *c1=i/s1;
                    *c2=0;
                    *c3=ss3/s3;
                    res++;
                }
                ss3+=s3;
            }
            //printf("%d %d %d\n",i,ss2,ss3);
            //printf("%d\n",i+ss2+ss3);
        }
    }



    //-------------------------------------------




    //-------------------------------------------

    return res;


}




#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    assert(lcm(8,12)==24);
    assert(checkTrue(100,12,8)==1);

    unsigned int c1, c2 ,c3;
    /*
    assert ( par ( 100, 4, 7, 0, &c1, &c2 ) == 4
             && 4 * c1 + 7 * c2 + 0 * (c1 + c2 + 1) == 100 );

    assert ( par ( 123456, 8, 3, 3, &c1, &c2 ) == 1871
             && 8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1) == 123456 );

    assert ( par ( 127, 12, 8, 0, &c1, &c2 ) == 0 );


    assert ( par ( 127, 12, 4, 3, &c1, &c2 ) == 1
             && 12 * c1 + 4 * c2 + 3 * (c1 + c2 + 1) == 127 );

    assert ( par ( 100, 35, 0, 10, &c1, &c2 ) == 1
             && c2 == 0
             && 35 * c1 + 10 * (c1 + 1) == 100 );

    assert ( par ( 110, 30, 30, 5, &c1, &c2 ) == 1
             && 30 * c1 + 30 * c2 + 5 * (c1 + c2 + 1) == 110 );
    c1 = 2;
    c2 = 7;

    assert ( par ( 110, 30, 30, 0, &c1, &c2 ) == 0 && c1 == 2 && c2 == 7 );
    c1 = 4;
    assert ( par ( 9, 1, 2, 10, &c1, &c2 ) == 0 && c1 == 4 && c2 == 8 );

    c2 = 8;

    assert ( par ( 993000, 1, 2, 0, &c1, &c2) == 496501 && 1 * c1 + 2 * c2 + 0 * (c1 + c2 + 1) == 993000 );
    c1 = 4; c2 = 8;
    assert ( par ( 87791, 141, 81, 24, &c1, &c2 ) == 0 && c1 == 4 && c2 == 8 );
    c1 = 4; c2 = 8;
    assert ( par (780, 0, 0, 390, &c1, &c2) == 0 && c1 == 4 && c2 == 8 );
    assert ( par (742, 0, 742, 0, &c1, &c2) == 1 && 0 * c1 + 742 * c2 + 0 * (c1 + c2 + 1) == 742 );
    assert ( par (2406, 802, 1604, 0, &c1, &c2) == 2 && 802 * c1 + 1604 * c2 + 0 * (c1 + c2 + 1) == 2406 );
    assert ( par (81644, 40, 163, 14, &c1, &c2) == 26 && 40 * c1 + 163 * c2 + 14 * (c1 + c2 + 1) == 81644 );
    c1 = 4; c2 = 8;
    assert ( par (1760, 0, 0, 880, &c1, &c2) == 0 && c1 == 4 && c2 == 8 );
    assert ( par (263000, 1, 2, 1, &c1, &c2) == 43833 && 1 * c1 + 2 * c2 + 1 * (c1 + c2 + 1) == 263000 );
    assert( par ( 993000, 1, 2, 0, &c1, &c2 ) ==496501);
    assert ( par (285, 285, 285, 0, &c1, &c2) == 1 && 285 * c1 + 285 * c2 + 0 * (c1 + c2 + 1) == 285 );
    assert( par( 16911, 161, 165, 33, &c1, &c2 )==1);

*/
/*
    printf(" %d %d %d\n",par(100,4,7,0,&c1,&c2),par(100,4,5,0,&c1,&c2),par(100,5,7,0,&c1,&c2));
    printf("%d %d %d \n",lcm(4,7),lcm(4,5),lcm(7,5));
    printf(" %d \n",hyperloop ( 100, 4, 7, 5, 0, &c1, &c2, &c3 ));
    printf(" %d \n",hyperloop ( 12345, 8, 3, 11, 3, &c1, &c2, &c3 ));
    printf(" %d \n",hyperloop(100,25,1,100000,0,&c1,&c2,&c3));
    printf(" %d \n", hyperloop ( 127, 12, 8, 10, 0, &c1, &c2, &c3 ));
    printf(" %d \n",hyperloop ( 127, 12, 8, 10, 3, &c1, &c2, &c3 ));

    assert ( hyperloop(100,25,1,10000,0,&c1,&c2,&c3)==5);
*/
    assert ( hyperloop ( 127, 12, 8, 10, 3, &c1, &c2, &c3 ) == 4
             && 12 * c1 + 8 * c2 + 10 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 127 );



    assert ( hyperloop ( 100, 4, 7, 5, 0, &c1, &c2, &c3 ) == 42
             && 4 * c1 + 7 * c2 + 5 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 100 );
    assert ( hyperloop ( 12345, 8, 3, 11, 3, &c1, &c2, &c3 ) == 82708
             && 8 * c1 + 3 * c2 + 11 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 12345 );
    c1 = 8;
    c2 = 9;
    c3 = 10;
    assert ( hyperloop ( 127, 12, 8, 10, 0, &c1, &c2, &c3 ) == 0
             && c1 == 8
             && c2 == 9
             && c3 == 10 );
    assert ( hyperloop ( 100, 35, 0, 0, 10, &c1, &c2, &c3 ) == 1
             && c2 == 0
             && c3 == 0
             && 35 * c1 + 10 * ( c1 + 1 ) == 100 );
    assert ( hyperloop ( 100, 35, 0, 35, 10, &c1, &c2, &c3 ) == 1
             && c2 == 0
             && 35 * c1 + 35 * c3 + 10 * ( c1 + c3 + 1 ) == 100 );
    assert ( hyperloop ( 100, 35, 35, 35, 10, &c1, &c2, &c3 ) == 1
             && 35 * c1 + 35 * c2 + 35 * c3 + 10 * ( c1 + c2 + c3 + 1 ) == 100 );
    c1 = 42;
    c2 = 43;
    c3 = 44;
    assert ( hyperloop ( 9, 1, 2, 3, 10, &c1, &c2, &c3 ) == 0
             && c1 == 42
             && c2 == 43
             && c3 == 44 );


    assert(hyperloop ( 2094, 1396, 698, 698, 0, &c1, &c2, &c3 )==2);




}
#endif /* __PROGTEST__ */