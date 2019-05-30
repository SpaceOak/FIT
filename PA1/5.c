#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*  letter possition defined by the ASCII code
 *  it means char A-Z - 65
 *  for A it is 0 (coz according to ascii A=65)
 *  for Z it is 25 (coz acc ... Z=90)
 *  why am i so good?
 */
typedef struct let {
    double pay[26];
    int place;
}let;

/* I had an idea to name this function
 * letTheUserKnowThatHeIsRetard
 * but it really too long
 * btw i wanna to use this prog for a code reviev
 */
 int err ()
{
    printf("Nespravny vstup.\n");
    return 1;
}


// binary search is my favourite
// https://en.wikipedia.org/wiki/Binary_search_algorithm for more info
int findZePlace ( let * pnt , int first , int last , int key )
{
    int mid = ( first + last ) / 2;

    if( pnt[first].place == pnt[last].place)
    {
        return first;
    }
    else if ( key > pnt[mid].place)
    {
        return findZePlace(pnt,mid + 1,last,key);
    }
    else if ( key < pnt[mid].place)
    {
        return findZePlace(pnt,first,mid,key);
    }
    else
    {
        return mid;
    }
}

// Make an ordered copy of pointers of the first arr
// 1   60 A B )        20 A
// 2   20 A    } ===>  30 B
// 3   30 B   )        60 A B
/*
let ** copy( let * pnt, int sizeOfArr )
{
    let ** arr = (let**) malloc ( sizeof ( arr[0] ) * sizeOfArr );
    int place;

    for( int i = 0 ; i < sizeOfArr ; i++ )
    {
        place = findZePlace( pnt , 0 , i , pnt[i].place);
        for( int z = i ; place <= z ; z-- )
        {
            arr[z+1]=arr[z];
        }
        arr[place]=&pnt[i];
    }


    return arr;
}
*/

int solveProblem( let * arr , int cnt )
{
    int from , to;
    int fromLocation , toLocation;
    int scanCheck;
    let answer;
    int diff;
    int tmp;

    while(1)
    {
        // clear
        for(int i = 0 ; i < 26 ; i++ )
        {
            answer.pay[i]=0;
        }

        tmp=0;

        // input
        scanCheck=scanf(" %d %d", &from , &to );

        // check input
        if( scanCheck != 2 || from < 0 || to < 0 || from == to
                || to > arr[cnt-1].place)
        {
            if(scanCheck==EOF)
            {
                return 0;
            }
            else
            {
                return err();
            }
        }

        // first part of output
        printf("%d - %d: ",from,to);

        // rotation if it is needed
        if( from > to )
        {
            int tmp;
            tmp = from;
            from = to;
            to = tmp;
        }


        toLocation = findZePlace(arr, 0 , cnt -1 , to );
        fromLocation = findZePlace(arr , 0 , cnt - 1 , from );

        for( int i = from;
                 i < to;)
        {
            diff = arr[fromLocation].place - i;
            for( int z = 0 ; z < 26 ; z ++)
            {
                answer.pay[z] += diff * arr[fromLocation].pay[z];
            }
            i= arr[fromLocation].place;
            fromLocation++;
        }


        diff = to - arr[fromLocation-1].place;
        for( int z = 0 ; z < 26 ; z ++)
        {
            answer.pay[z] += diff * arr[toLocation].pay[z];
        }


        for( int z = 0 ; z < 26 ; z ++)
        {
            if(answer.pay[z] > 0)
            {
                printf("%c=%f",z+65,answer.pay[z]);
                tmp = z + 1;
                break;
            }
        }

        for( int z = tmp ; z < 26 ; z ++)
        {
            if(answer.pay[z]>0)
            printf(", %c=%f",z+65,answer.pay[z]);
        }
        printf("\n");
    }
}


int main() {

    int cnt = 0 ;       // count of sections
    char test ,test1;   // chars to check input
    int struSize = 5;   // size of structure
    let * pnt = (let*)malloc ( sizeof ( pnt[0] ) * struSize );

    printf("Myto:\n");

    if(scanf(" %c",&test)!=1||test!='{')
    {
        free(pnt);
        return err();
    }

    while(true)
        {
            //resize if ammount of ellements = sizeOfArr
            if(cnt+1==struSize)
            {
                pnt = (let*)realloc ( pnt, sizeof ( pnt[0] ) * ( struSize * 2 ));
                struSize=struSize*2;
            }

            //first symbol        standart=='[ %d : %c = %f ]'
            if(scanf(" %c",&test)!=1||test!='[')
            {
                free(pnt);
                return err();
            }

            //location and ':'
            if(scanf(" %d %c",&pnt[cnt].place,&test)!=2||pnt[cnt].place<=0||test!=':')
            {
                free(pnt);
                return err();
            }

            if(cnt>0)
            {
                pnt[cnt].place+=pnt[cnt-1].place;
            }

            if(cnt>0)
            {
                for (int i = 0; i < 26; i++) {
                    pnt[cnt].pay[i] = pnt[cnt - 1].pay[i];
                }
            }


            //take A-Z '=' and dbl
            while(scanf(" %c",&test)==1&&test!='}')
            {
                //A-Z
                if(test<65||test>90)
                {
                    free(pnt);
                    return err();
                }

                //'=' and dbl
                if(scanf(" %c %lf",&test1,&pnt[cnt].pay[test-65])!=2||
                        pnt[cnt].pay[test-65]<0||test1!='=')
                {
                    free(pnt);
                    return err();
                }
                //continue or break (depending on the meaning of char in scan)
                if(scanf(" %c",&test)!=1||test!=',')
                {
                    if(test==']')
                    {
                        cnt++;
                        break;
                    }
                    else
                    {
                        free(pnt);
                        return err();
                    }
                }
            }
            // ',' between the blocks
            if(scanf(" %c",&test)!=1||test!=',')
            {
                //how long can this go on? untill the '}'
                if(test=='}')
                    break;
                else
                {
                    free(pnt);
                    return err();
                }
            }
        }

    //let ** arr = copy(pnt,cnt);

    printf("Hledani:\n");

    solveProblem(pnt,cnt);
    free(pnt);
    return 0;

}