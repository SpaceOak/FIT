#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TEmployee
{
    struct TEmployee         * m_Next;
    struct TEmployee         * m_Bak;
    char                     * m_Name;
} TEMPLOYEE;

#endif /* __PROGTEST__ */

//it works
TEMPLOYEE        * newEmployee  ( const char      * name,
                                  TEMPLOYEE       * next )
{
    if(name==NULL)
    {
        TEMPLOYEE *a = (TEMPLOYEE *) malloc(sizeof(TEMPLOYEE));
        a->m_Next = next;
        a->m_Bak = NULL;
        a->m_Name = NULL;
        return a;
    }

        TEMPLOYEE *a = (TEMPLOYEE *) malloc(sizeof(TEMPLOYEE));
        size_t q = strlen(name);

        a->m_Name = (char *) malloc( (q + 1) * sizeof(char));
        for (size_t i = 0; i < q; i++)
            a->m_Name[i] = name[i];
        a->m_Name[q] = 0;
        a->m_Next = next;
        a->m_Bak = NULL;
        return a;

}

//it doesnt
TEMPLOYEE        * cloneList    ( TEMPLOYEE       * src ) {
    TEMPLOYEE * pNew = NULL;
    TEMPLOYEE * tmp = src;
    TEMPLOYEE * head = NULL;
    TEMPLOYEE * search = NULL;

    while (tmp != NULL)
    {
        TEMPLOYEE * newList = (TEMPLOYEE *) malloc (sizeof(TEMPLOYEE));
        newList -> m_Next = NULL;
        newList -> m_Name = NULL;
        newList -> m_Bak = NULL;

        if(tmp ->m_Name!= NULL) {
            size_t q = strlen(tmp->m_Name);
            newList->m_Name = (char *) malloc((q + 1) * sizeof(char));

            for(size_t i = 0 ; i < q ; i++ )
                newList -> m_Name[i] = tmp->m_Name[i];
            newList ->m_Name[q] = 0;
        }

        if(head == NULL) {
            head = newList;
            pNew = head;
        } else {
            pNew->m_Next = newList;
            pNew = pNew->m_Next;
        }
        tmp = tmp-> m_Next;
    }
    pNew = head;
    search = src;

    while ( search != NULL )
    {
        if( search -> m_Bak != NULL )
        {
            tmp = src;
            TEMPLOYEE * tmpNew = head;
            while (tmp && tmpNew && search -> m_Bak != tmp ) {
                tmpNew = tmpNew->m_Next;
                tmp = tmp->m_Next;
            }
            pNew -> m_Bak = tmpNew;
        }
        search = search -> m_Next;
        pNew = pNew -> m_Next;
    }

    return head;
}

/*
 * tmp = &(*src);
            place = 0;
            for (int a = 0 ; search -> m_Bak != tmp -> m_Bak ; a++ ) {
                tmp = tmp->m_Next;
                place++;
            }
            tmp = head;
            while (place>=0 )
            {
                place--;
                tmp = tmp ->m_Next;
            }

            newList -> m_Bak = tmp;
 */


void               freeList     ( TEMPLOYEE       * src )
{


    if( src != NULL )
    {
        freeList(src->m_Next);
        free ( src -> m_Name );
    }
    free ( src );



    /*TEMPLOYEE * tmp;

    while(src != NULL)
    {
        free ( src -> m_Name );
        tmp = src -> m_Next;
        free ( src );
        src = tmp;
    }*/
}

/*
void printer ( TEMPLOYEE       * src )
{
    while (src != NULL && src ->m_Name != NULL)
    {
        for( int i = 0 ; i < strlen(src ->m_Name ); i++)
        {
            printf("%c",src ->m_Name[i]);
        }
        printf(" -> ");
        src = src -> m_Next;
    }
    printf("\n");
}

*/
#ifndef __PROGTEST__
int                main         ( int               argc,
                                  char            * argv [] )
{
    TEMPLOYEE * a, *b;
    char tmp[100];

    assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
    a = NULL;
    a = newEmployee ( "Peter", a );
    a = newEmployee ( "John", a );
    a = newEmployee ( "Joe", a );
    a = newEmployee ( "Maria", a );
    a -> m_Bak = a -> m_Next;
    a -> m_Next -> m_Next -> m_Bak = a -> m_Next -> m_Next -> m_Next;
    a -> m_Next -> m_Next -> m_Next -> m_Bak = a -> m_Next;
    assert ( a
             && ! strcmp ( a -> m_Name, "Maria" )
             && a -> m_Bak == a -> m_Next );
    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

    b = cloneList ( a );
    strncpy ( tmp, "Moe", sizeof ( tmp ) );

    a = newEmployee ( tmp, a );


    strncpy ( tmp, "Victoria", sizeof ( tmp ) );
    a = newEmployee ( tmp, a );


    strncpy ( tmp, "Peter", sizeof ( tmp ) );
    a = newEmployee ( tmp, a );


    b -> m_Next -> m_Next -> m_Next -> m_Bak = b -> m_Next -> m_Next;

    assert ( a
             && ! strcmp ( a -> m_Name, "Peter" )
             && a -> m_Bak == NULL );

    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
             && a -> m_Next -> m_Bak == NULL );

    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
             && a -> m_Next -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

    assert ( b
             && ! strcmp ( b -> m_Name, "Maria" )
             && b -> m_Bak == b -> m_Next );
    assert ( b -> m_Next
             && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
             && b -> m_Next -> m_Bak == NULL );
    assert ( b -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
             && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    freeList ( a );
    b -> m_Next -> m_Bak = b -> m_Next;
    a = cloneList ( b );

    assert ( a
             && ! strcmp ( a -> m_Name, "Maria" )
             && a -> m_Bak == a -> m_Next );
    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Bak == a -> m_Next );
    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b
             && ! strcmp ( b -> m_Name, "Maria" )
             && b -> m_Bak == b -> m_Next );
    assert ( b -> m_Next
             && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
             && b -> m_Next -> m_Bak == b -> m_Next );
    assert ( b -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
             && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

    TEMPLOYEE * z = NULL;
    freeList ( b );
    freeList ( a );
    freeList ( NULL );
    z = newEmployee(" adsad",z);
    z ->m_Bak = z;
    freeList ( z );

    a = newEmployee(NULL,NULL);
    b = cloneList(a);
    freeList(a);
    a = cloneList(NULL);
    assert(a==NULL && b&& b->m_Name == NULL);
    freeList(a);
    freeList(b);



    return 0;
}
#endif /* __PROGTEST__ */