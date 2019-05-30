#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>

#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#endif /* C++ 11 */

using namespace std;
#endif /* __PROGTEST__ */

class NoRouteException { };

//=================================================================================================
//=================================================================================================
template <typename _T, typename _E> class CPoint;

template<typename _E>
    bool cmp(const _E & var){ return true; }

template <typename _T, typename _E>
class CWay
{
public:
    const      _E   km;
    CPoint<_T, _E> *firstPlace, *secondPlace;

    CWay( const _E &k, CPoint<_T, _E> *firstPnt, CPoint<_T, _E> *secPnt )
            : km( k )
    {
        firstPlace  = firstPnt;
        secondPlace =   secPnt;
    }
};

//=================================================================================================
//=================================================================================================
template <typename _T, typename _E>
class CPoint
{
public:
    _T content;
    vector<CWay<_T, _E>*> routes;
    CPoint( _T i ) : content( i ) {}
};

//=================================================================================================
//=================================================================================================
template <typename _T, typename _E>
class CRoute
{
public:
    ~CRoute()
    {
        for ( auto place =  arr.begin() ; place !=    arr.end() ; place++ )
            delete (*place).second;
        for ( auto way = routes.begin() ; way   != routes.end() ;   way++ )
            delete ( *way );
    }

//=================================================================================================
    CRoute &Add( const _T from, const _T to, const _E way )
    {

        CPoint<_T, _E> * placeTo;

        if ( arr.count( to ) > 0 )
            placeTo = arr[to];
        else
        {
            CPoint<_T, _E> *place = new CPoint<_T, _E>( to );
            arr[ to ] = place;
            placeTo   = place;
        }
        CPoint<_T, _E> * placeFrom;

        if ( arr.count( from ) > 0 )
            placeFrom = arr[from];
        else
        {
            CPoint<_T, _E> *place = new CPoint<_T, _E>( from );
            arr[ from ] = place;
            placeFrom   = place;
        }

        auto newEdge = new CWay<_T, _E>( way, placeFrom, placeTo );

        routes           .emplace_back( newEdge );
        placeTo  ->routes.insert      ( placeTo  ->routes.end(), newEdge );
        placeFrom->routes.insert      ( placeFrom->routes.end(), newEdge );

        return *this;
    }

//=================================================================================================
    list<_T> Find( const _T &from, const _T &to ) const
    {
        return Find( from, to, cmp<_E> );
    }

//=================================================================================================
    template<typename _F> list<_T> Find( const _T &from, const _T &to, const _F & condition ) const
    {
        map<CPoint   <_T, _E>*,CPoint<_T, _E>*> previous;
        queue<CPoint <_T, _E>*>              searchQueue;
        set          <_T>                        visited;
        list         <_T>                          route;

        if ( from == to )
        {
            route . push_back( from );
            return route;
        }
        else if ( arr.count( from ) > 0 ) searchQueue.push( arr.at( from ) );
        else throw NoRouteException();

        visited.insert( from );

        while ( ! searchQueue.empty() )
        {
            CPoint<_T, _E> *place = searchQueue.front();
            searchQueue.pop();

            if ( place->content == to )
            {
                CPoint<_T, _E> *pnt = place;

                while ( pnt->content != from )
                {
                    route.push_front( pnt->content );
                    pnt = previous[ pnt ];
                }
                route.push_front( pnt->content );
            }

            for ( CWay<_T, _E> *way : place->routes )
            {
                CPoint<_T, _E> *other;
                if ( way->firstPlace == place ) other = way->secondPlace;
                else other = way->firstPlace;

                if ( condition       ( way->km ) == true
                     && visited.count( other->content  ) == 0    )
                {
                    searchQueue.push( other );
                    visited.insert( other->content );
                    previous[other] = place;
                }
            }
        }

        if ( ! route.size() ) throw NoRouteException();

        return route;
    }

private:
    map<_T,CPoint <_T,_E>*>    arr;
    vector<CWay   <_T,_E>*> routes;
};
//=================================================================================================
class CTrain
{
public:
    CTrain                        ( const string    & company,
                                    int               speed )
            : m_Company ( company ),
              m_Speed ( speed )
    {
    }
    //---------------------------------------------------------------------------------------------
    string                   m_Company;
    int                      m_Speed;
};
//=================================================================================================
class TrainFilterCompany
{
public:
    TrainFilterCompany            ( const set<string> & companies )
            : m_Companies ( companies )
    {
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain & train ) const
    {
        return m_Companies . find ( train . m_Company ) != m_Companies . end ();
    }
    //---------------------------------------------------------------------------------------------
private:
    set <string>             m_Companies;
};
//=================================================================================================
class TrainFilterSpeed
{
public:
    TrainFilterSpeed              ( int               min,
                                    int               max )
            : m_Min ( min ),
              m_Max ( max )
    {
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain    & train ) const
    {
        return train . m_Speed >= m_Min && train . m_Speed <= m_Max;
    }
    //---------------------------------------------------------------------------------------------
private:
    int                      m_Min;
    int                      m_Max;
};
//=================================================================================================
bool               NurSchnellzug                           ( const CTrain    & zug )
{
    return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
static string      toText                                  ( const list<string> & l )
{
    ostringstream oss;

    auto it = l . cbegin();
    oss << *it;
    for ( ++it; it != l . cend (); ++it )
        oss << " > " << *it;
    return oss . str ();
}
//=================================================================================================
int main ( void )
{
    CRoute<string,CTrain> lines;

    lines . Add ( "Berlin", "Prague", CTrain ( "DB", 120 ) )
            . Add ( "Berlin", "Prague", CTrain ( "CD",  80 ) )
            . Add ( "Berlin", "Dresden", CTrain ( "DB", 160 ) )
            . Add ( "Dresden", "Munchen", CTrain ( "DB", 160 ) )
            . Add ( "Munchen", "Prague", CTrain ( "CD",  90 ) )
            . Add ( "Munchen", "Linz", CTrain ( "DB", 200 ) )
            . Add ( "Munchen", "Linz", CTrain ( "OBB", 90 ) )
            . Add ( "Linz", "Prague", CTrain ( "CD", 50 ) )
            . Add ( "Prague", "Wien", CTrain ( "CD", 100 ) )
            . Add ( "Linz", "Wien", CTrain ( "OBB", 160 ) )
            . Add ( "Paris", "Marseille", CTrain ( "SNCF", 300 ))
            . Add ( "Paris", "Dresden",  CTrain ( "SNCF", 250 ) );

    list<string> r1 = lines . Find ( "Berlin", "Linz" );
    assert ( toText ( r1 ) == "Berlin > Prague > Linz" );

    list<string> r2 = lines . Find ( "Linz", "Berlin" );
    assert ( toText ( r2 ) == "Linz > Prague > Berlin" );

    list<string> r3 = lines . Find ( "Wien", "Berlin" );
    assert ( toText ( r3 ) == "Wien > Prague > Berlin" );

    list<string> r4 = lines . Find ( "Wien", "Berlin", NurSchnellzug );
    assert ( toText ( r4 ) == "Wien > Linz > Munchen > Dresden > Berlin" );

    list<string> r5 = lines . Find ( "Wien", "Munchen", TrainFilterCompany ( set<string> { "CD", "DB" } ) );
    assert ( toText ( r5 ) == "Wien > Prague > Munchen" );

    list<string> r6 = lines . Find ( "Wien", "Munchen", TrainFilterSpeed ( 120, 200 ) );
    assert ( toText ( r6 ) == "Wien > Linz > Munchen" );

    list<string> r7 = lines . Find ( "Wien", "Munchen", [] ( const CTrain & x ) { return x . m_Company == "CD"; } );
    assert ( toText ( r7 ) == "Wien > Prague > Munchen" );

    list<string> r8 = lines . Find ( "Munchen", "Munchen" );
    assert ( toText ( r8 ) == "Munchen" );

    list<string> r9 = lines . Find ( "Marseille", "Prague" );
    assert ( toText ( r9 ) == "Marseille > Paris > Dresden > Berlin > Prague"
             || toText ( r9 ) == "Marseille > Paris > Dresden > Munchen > Prague" );

    try
    {
        list<string> r10 = lines . Find ( "Marseille", "Prague", NurSchnellzug );
        assert ( "Marseille > Prague connection does not exist!!" == NULL );
    }
    catch ( const NoRouteException & e )
    {
    }

    list<string> r11 = lines . Find ( "Salzburg", "Salzburg" );
    assert ( toText ( r11 ) == "Salzburg" );

    list<string> r12 = lines . Find ( "Salzburg", "Salzburg", [] ( const CTrain & x ) { return x . m_Company == "SNCF"; }  );
    assert ( toText ( r12 ) == "Salzburg" );

    try
    {
        list<string> r13 = lines . Find ( "London", "Oxford" );
        assert ( "London > Oxford connection does not exist!!" == NULL );
    }
    catch ( const NoRouteException & e )
    {
    }



    return 0;
}