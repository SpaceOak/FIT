#include <stdio.h>
#include <math.h>
#include <float.h>


int main() {
    double a11,a12,a21,a22,b11,b12,b21,b22,c11,c12,c21,c22;
    double ab1,bc1,ca1,ab2,bc2,ca2;
    char test, shit,scunner=1;


//scan 1


printf("Trojuhelnik #1:\n");
    if(scanf(" %c",&test)!=1||test!='{')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }	

    while(scunner!=EOF)
    {
	scunner=scanf(" %lf",&ab1);
	if(scunner==1)
	{break;}
        if(scanf(" %c",&test)==1)
        {shit=1;break;}
    }

    if(test!=91&&shit==1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }



    if(test==91)
    {//first way
       // if(scanf(" %lf ; %lf ] , [ %lf ; %lf ] , [ %lf ; %lf ] }", &a11,&a12,&b11,&b12,&c11,&c12)!=6)
  //-----------------------------------------------------------------------------------

	if(scanf(" %lf",&a11)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %c",&test)!=1||test!=';')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %lf",&a12)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!=']')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!=',')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!='[')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %lf",&b11)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %c",&test)!=1||test!=';')
        	{printf("Nespravny vstup.\n");return 1;}      
	if(scanf(" %lf",&b12)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!=']')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!=',')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!='[')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %lf",&c11)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %c",&test)!=1||test!=';')
        	{printf("Nespravny vstup.\n");return 1;}       
	if(scanf(" %lf",&c12)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %c",&test)!=1||test!=']')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!='}')
        	{printf("Nespravny vstup.\n");return 1;}





//----------------------------------------------------------------------


        ab1=sqrt((a11-b11)*(a11-b11)+(a12-b12)*(a12-b12));
        bc1=sqrt((b11-c11)*(b11-c11)+(b12-c12)*(b12-c12));
        ca1=sqrt((c11-a11)*(c11-a11)+(c12-a12)*(c12-a12));
        test=0;
}
    else //second way
    {
       // if (scanf(" , %lf , %lf %c", &bc1, &ca1, &test) != 3||test!='}') 
       

if(scanf(" %c",&test)!=1||test!=',')
        	{printf("Nespravny vstup.\n");return 3;}

if(scanf(" %lf",&bc1)!=1)
        	{printf("Nespravny vstup.\n");return 2;}

if(scanf(" %c",&test)!=1||test!=',')
        	{printf("Nespravny vstup.\n");return 5;}

if(scanf(" %lf",&ca1)!=1)
        	{printf("Nespravny vstup.\n");return 4;}

if(scanf(" %c",&test)!=1||test!='}')
        	{printf("Nespravny vstup.\n");return 6;}

    }

    if(ab1+bc1-ca1<=DBL_EPSILON*100*ab1*ab1
       ||bc1+ca1-ab1<=DBL_EPSILON*100*bc1*bc1
       ||ca1+ab1-bc1<=DBL_EPSILON*100*ca1*ca1)
    {
        printf("Neplatny trojuhelnik.\n");
        return 1;
    }


    test=0;
    shit=0;
    scunner=1;






//scan end

 


// scan 2





printf("Trojuhelnik #2:\n");

    if(scanf(" %c",&test)!=1||test!='{')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    while(scunner!=EOF)
    {
	scunner=scanf(" %lf",&ab2);
	if(scunner)
	{break;}
        if(scanf(" %c",&test)==1)
        {shit=1;break;}
	
    }

    if(test!=91&&shit==1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    if(test==91) 
    {//-------------------------------------------------------------------------------------------------
      //  if(scanf(" %lf ; %lf ] , [ %lf ; %lf ] , [ %lf ; %lf ] }", &a21,&a22,&b21,&b22,&c21,&c22)!=6)
        //	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %lf",&a21)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %c",&test)!=1||test!=';')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %lf",&a22)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!=']')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!=',')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!='[')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %lf",&b21)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %c",&test)!=1||test!=';')
        	{printf("Nespravny vstup.\n");return 1;}      
	if(scanf(" %lf",&b22)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!=']')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!=',')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!='[')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %lf",&c21)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %c",&test)!=1||test!=';')
        	{printf("Nespravny vstup.\n");return 1;}       
	if(scanf(" %lf",&c22)!=1)
        	{printf("Nespravny vstup.\n");return 1;}
	if(scanf(" %c",&test)!=1||test!=']')
        	{printf("Nespravny vstup.\n");return 1;}
        if(scanf(" %c",&test)!=1||test!='}')
        	{printf("Nespravny vstup.\n");return 1;}


        //----------------------------------------------------------
        ab2=sqrt((a21-b21)*(a21-b21)+(a22-b22)*(a22-b22));
        bc2=sqrt((b21-c21)*(b21-c21)+(b22-c22)*(b22-c22));
        ca2=sqrt((c21-a21)*(c21-a21)+(c22-a22)*(c22-a22));
    }
    else
    {
        //if(scanf(" , %lf , %lf %c}",&bc2,&ca2,&test)!=3||test!='}')
        

     

if(scanf(" %c",&test)!=1||test!=',')
        	{printf("Nespravny vstup.\n");return 3;}

if(scanf(" %lf",&bc2)!=1)
        	{printf("Nespravny vstup.\n");return 2;}

if(scanf(" %c",&test)!=1||test!=',')
        	{printf("Nespravny vstup.\n");return 5;}

if(scanf(" %lf",&ca2)!=1)
        	{printf("Nespravny vstup.\n");return 4;}

if(scanf(" %c",&test)!=1||test!='}')
        	{printf("Nespravny vstup.\n");return 6;}

    }
        

    if(ab2+bc2-ca2<=DBL_EPSILON*100*ab2*ab2
       ||bc2+ca2-ab2<=DBL_EPSILON*100*bc2*bc2
       ||ca2+ab2-bc2<=DBL_EPSILON*100*ca2*ca2)
    {
        printf("Neplatny trojuhelnik.\n");
        return 1;
    }


    double obv1 = ab1+bc1+ca1,obv2 = ab2+bc2+ca2;


    if((fabs(ab1-ab2)<=DBL_EPSILON*100*ab1*ab1
||fabs(ab1-bc2)<=DBL_EPSILON*100*ab1*ab1
||fabs(ab1-ca2)<=DBL_EPSILON*100*ab1*ab1)
       &&(fabs(bc1-ab2)<=DBL_EPSILON*100*bc1*bc1
||fabs(bc1-bc2)<=DBL_EPSILON*100*bc1*bc1 
||fabs(bc1-ca2)<=DBL_EPSILON*100*bc1*bc1)
       &&(fabs(ca1-ab2)<=DBL_EPSILON*100*ca1*ca1 
||fabs(ca1-bc2)<=DBL_EPSILON*100*ca1*ca1
||fabs(ca1-ca2)<=DBL_EPSILON*100*ca1*ca1))
    {
        printf("Trojuhelniky jsou shodne.\n");
    }
    else if(fabs(obv1-obv2)<=DBL_EPSILON*100*obv1*obv1)
    {
        printf("Trojuhelniky nejsou shodne, ale maji stejny obvod.\n");
    }
    else if(obv1>obv2)
    {
        printf("Trojuhelnik #1 ma vetsi obvod.\n");
    }
    else
    {
        printf("Trojuhelnik #2 ma vetsi obvod.\n");
    }
    return 0;

}
