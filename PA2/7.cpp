#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidRangeException
{
public:
    InvalidRangeException(){};
};
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX
class CRange;
class CRangeList;




class CRange
{
public:
    CRange ( long long int f , long long int t)
    {
        if ( f > t ) throw InvalidRangeException();
        from = f ,to = t;
    }

    long long getFrom () const                { return from; }
    long long getTo   () const                { return   to; }
    void      setFrom (  const long long& q ) { from    = q; }
    void      setTo   (  const long long& q ) { to      = q; }





    CRangeList operator + ( const CRange& y );
    CRangeList operator - ( const CRange &x );


private:
    long long from;
    long long to;
};

///=================================================================================///

class CRangeList
{
  public:
    // constructor
    // Includes long long / range
    // += range / range list
    // -= range / range list
    // = range / range list
    // operator ==
    // operator !=
    // operator <<

    CRangeList ()= default;
    CRangeList ( CRange x );
    //friend CRangeList operator  +  ( CRangeList x , const CRangeList &y);
    //friend CRangeList operator  -  ( CRangeList x , const CRangeList &y);
    //friend CRangeList operator  =  ( CRangeList x , const CRange     &y);
    friend ostream   &operator  << ( ostream &os  , const CRangeList &x);
    CRangeList       &operator  += ( const CRangeList & x);
    CRangeList       &operator  +  ( const CRangeList & x);
    CRangeList       &operator  -  ( const CRangeList & x);
    CRangeList       &operator  -= ( const CRangeList & x);
    CRangeList       &operator  += ( const CRange &x );
    CRangeList       &operator  -= ( const CRange &x );
    bool Includes    ( const CRange     &x) const;
    bool Includes    ( const ulong      &x) const;
    bool operator == ( const CRangeList &x) const;
    bool operator != ( const CRangeList &x) const;
    void Add ( const CRange& x);
    void Del ( const CRange& x);
    CRange getRange ( ulong i)const { return arr[i];}

private:
    vector <CRange> arr;
};

///=================================================================================///

bool CRangeList::Includes(const ulong  &x) const {
    return Includes ( CRange ( x , x )); /// call foo for CRange
}

///=================================================================================///


bool CRangeList::Includes(const CRange &x) const {

    /// check if is empty

    if ( arr.empty())
        return false;

    /// find inters by cycles

    auto iterFrom = arr.begin();
    while((*(iterFrom)).getTo() < x.getFrom() && iterFrom != arr.end())
        iterFrom++;


    auto iterTo = iterFrom;
    while((*(iterTo)).getTo() + 1 < x.getTo() && iterTo != arr.end())
        iterTo++;


    /// nothing to check at end

    if( iterTo == arr.end())
        iterTo--;

    /// the only possible correct case means iters must be same

    if(iterFrom == iterTo)
    {
        if (x.getFrom() >= (*iterFrom).getFrom() && x.getTo() <= (*iterFrom).getTo())
            return true;
    }

    /// else return false

    return false;


}

///=================================================================================///

CRangeList::CRangeList(CRange x) {

    /// Basic conctructor

    this->arr.clear();
    this->arr.push_back(x);
}

///=================================================================================///

CRangeList CRange::operator+(const CRange &y)
{
    /// Create CRangeList and return it

    CRangeList tmp;
    tmp = ( CRange (y.getFrom() , y.getTo()));
    tmp.Add(CRange(this->getFrom(),this->getTo()));
    return tmp;

}

///=================================================================================///

CRangeList CRange::operator-(const CRange &y)
{
    /// Create CRangeList and return it

    CRangeList tmp;
    tmp = ( CRange (this->getFrom(), this->getTo()));
    tmp.Del(CRange(y.getFrom(),y.getTo()));
    return tmp;

}

///=================================================================================///

void CRangeList :: Add ( const CRange& x )
{
    ///check if arr is empty

    if ( arr.empty()) {
        arr.push_back(x);
        return;
    }

    /// find matchable inters

    auto iterFrom = arr.begin();

    auto iterTo = iterFrom;
    while(iterFrom <= arr.end() - 1)
    {
        if(  (*(iterFrom)).getTo() <= x.getFrom() )
        iterFrom++;
        else
            break;
    }

    iterTo = iterFrom;
    while(iterTo <= arr.end() - 1)
    {
        if((*(iterTo)).getTo() <= x.getTo())
            iterTo++;
        else
            break;
    }
    /// create tmp CRange

    CRange tmp ( x.getFrom() , x.getTo() );

    /// move lower vound of inter if is needed

    if(iterFrom != arr.end() ) /// only for valgrind
    if ( (*iterFrom).getTo() + 1 >= tmp.getFrom()
         && (*iterFrom).getFrom() < x.getFrom()
         && iterFrom <= arr.end() - 1 )
    {
        tmp.setFrom((*iterFrom).getFrom());
    }


    /// move upper bonud of inter if is needed
    if(iterTo !=arr.end() )
    if ( (*iterTo).getFrom() <= tmp.getTo() + 1
         && (*iterTo).getTo() >= tmp.getTo() + 1
         && iterTo <= arr.end() - 1 )
    {
        tmp.setTo((*iterTo).getTo());
        if(iterTo != arr.end())
        iterTo++;
    }

    /// if upper and low are located in the same inter

    if(iterTo != arr.begin())
    if ( iterFrom == iterTo && iterFrom != arr.end() )
    {
            /// this case means that new inter is located in alrady existing inter
        if( (*iterFrom).getFrom() < tmp.getFrom() + 1
            && (*iterTo).getTo() + 1 > x.getTo()
            && iterFrom != arr.end() )
        {
            return;
        }
            /// this case means new inter has bigger upper bound
        else if ( (*iterFrom).getFrom() > tmp.getFrom()
                  && (*iterFrom).getTo() > x.getTo()
                  && (*iterFrom).getFrom() < x.getTo()
                  && iterFrom != arr.end() )
        {
            tmp.setFrom((*iterFrom).getFrom());
            arr.erase(iterFrom);
            arr.insert(iterFrom,tmp);
            return;
        }
            /// this case means new inter is inside the selected inter
        else if ( (*iterFrom).getFrom() <= tmp.getFrom() && (*iterFrom).getTo() >= tmp.getTo() && iterFrom != arr.end())
            return;
            /// this case means new inter has lower lower bound
        else if( (*iterFrom).getTo() < tmp.getTo()
                 && iterFrom != arr.end())
        {
            if((*iterFrom).getFrom() > tmp.getFrom() )
            {
                tmp.setFrom((*iterFrom).getFrom());
                arr.erase(iterFrom);
                arr.insert(iterFrom,tmp);
                return;
            }
            else
            {
                arr.erase(iterFrom);
                arr.insert(iterFrom,tmp);
                return;
            }
        }

    }

    /// this case means inter touchs previous inter like 100-105 and 106-120
    if(iterFrom!=arr.begin())
    {
        if ((*(iterFrom - 1)).getTo() >= tmp.getFrom() - 1
            && iterFrom != arr.begin()) {
            iterFrom--;
            tmp.setFrom((*iterFrom).getFrom());
        }
    }    /// this case means we are in the end of arr
    else if( iterFrom == arr.end())
    {

        arr.push_back(tmp);
        return;
    }


    /// this case meants new inter touchs previous inter
    if(iterFrom != arr.begin()) /// only for valgrind
    if( (*(iterFrom - 1)).getTo() + 1 >= x.getFrom())
    {
        iterFrom--;
        tmp.setFrom((*iterFrom).getFrom());
    }



    /// delete old inters
    arr.erase(iterFrom,iterTo);
    /// add a new one
    arr.insert(iterFrom,tmp);

}
///=================================================================================///

void CRangeList::Del(const CRange &x) {

    /// if is empty
    if ( arr.empty()) {
        arr.push_back(x);
        return;
    }

    /// find matchable places for new inter in arr
    auto iterFrom = arr.begin();

    while(iterFrom != arr.end()) {
        if((*(iterFrom)).getTo() < x.getFrom() )
            iterFrom++;
        else
            break;
    }
    auto iterTo = iterFrom;

    while(iterTo != arr.end())
    {
        if((*(iterTo)).getTo() + 1 < x.getTo() )
            iterTo++;
        else
            break;
    }
    /// tmp CRanges if inters ll be cuted partially
    CRange FromInter(0,0) , ToInter(0,0);
    /// and bools to know if inters must be added to arr
    bool   blFrom = false , blTo = false ;



    /// if nothing to delete
    if(iterFrom == arr.end())
        return;



    if((*iterFrom).getTo() < x.getFrom())
        iterFrom++;

    if(iterTo == arr.end())
        iterTo--;


    /// if lower bound of new inter is gonna cut the old one
    if ( (*iterFrom).getTo() >= x.getFrom() && (*iterFrom).getFrom() < x.getFrom() )
    {
        blFrom = true;
        FromInter.setFrom((*iterFrom).getFrom());
        FromInter.setTo  (x.getFrom() - 1);
    }



    /// if upper bound of new inter is gonna cut the old one
    if(iterTo != arr.end())
    if ( (*iterTo).getFrom() <= x.getTo() && (*iterTo).getTo() > x.getTo() )
    {
        blTo   = true;
        ToInter.setFrom(x.getTo() + 1);
        ToInter.setTo  ((*iterTo).getTo());
    }

    if( (*iterFrom).getFrom() > x.getTo() )
        return;


    /// delete all between inters
    arr.erase(iterFrom,iterTo + 1);


    /// add lower cutted inter
    if(blTo)
        arr.insert(iterFrom,ToInter);

    /// add upper cutted inter
    if(blFrom)
        arr.insert(iterFrom,FromInter);


}

///=================================================================================///

ostream &operator << (ostream &os, const CRangeList &x) {

    ///Simple foo to make output according to task
    unsigned long size = x.arr.size();

    os << "{";
    for( unsigned int i = 0 ; i < size ; i++ )
    {
        if ( x.arr[i].getFrom() == x.arr[i].getTo())
            os << x.arr[i].getFrom();
        else
            os << "<" << x.arr[i].getFrom() << ".." << x.arr[i].getTo() << ">";

        if( i + 1 != size ) os << ",";
    }

    os << "}";
    return os;

}

///=================================================================================///

CRangeList &CRangeList::operator += (const CRangeList &x) {

    /// Cyclically adds CRanges to left list

    ulong size = x.arr.size();

    for( ulong i = 0 ; i < size ; i++)
        this->Add( CRange ( x.arr[i].getFrom() , x.arr[i].getTo()));

    return (*this);

}

///=================================================================================///

CRangeList &CRangeList::operator += ( const CRange &x ) {

    ///Nothing special here

    this->Add(x);
    return (*this);
}

///=================================================================================///

CRangeList &CRangeList::operator +  (const CRangeList &x) {

    /// Completly same like +=

    if ( x.arr.empty() )
        return (*this);

    ulong size = x.arr.size();

    for( ulong i = 0 ; i < size ; i++)
        this->Add(x.getRange(i));

    return (*this);

}

///=================================================================================///

CRangeList &CRangeList::operator -= (const CRangeList &x) {

    /// Same like -

    if( this->arr.empty())
    {
        return (*this);
    }
    else if ( x.arr.empty() )
        return (*this);

    ulong index = x.arr.size();

    for( ulong i = 0 ; i < index ; i++ )
        this->Del(x.getRange(i));

    return (*this);
}

///=================================================================================///

bool CRangeList::operator==(const CRangeList &x) const {

    /// Firstly check lists by size
    /// Then cyclically compare each CRange

    if( this->arr.size() != x.arr.size()) return false;

    for( ulong i = 0 ; i < arr.size() ; i++ )
    {
        CRange first = getRange(i) , second = x.getRange(i);
        if ( first.getFrom() != second.getFrom() || first.getTo() != second.getTo() )
            return false;
    }

    return true;
}

///=================================================================================///

bool CRangeList::operator!=(const CRangeList &x) const {

    /// Same like ==

    if( this->arr.size() != x.arr.size()) return true;

    for( ulong i = 0 ; i < arr.size() ; i++ )
    {
        CRange first = getRange(i) , second = x.getRange(i);
        if ( first.getFrom() != second.getFrom() || first.getTo() != second.getTo() )
            return true;
    }

    return false;
}

///=================================================================================///

CRangeList &CRangeList::operator-(const CRangeList &x) {

    /// Same like -=

    if( this->arr.empty())
    {
        return (*this);
    }
    else if ( x.arr.empty() )
        return (*this);


    ulong index = x.arr.size();

    for( ulong i = 0 ; i < index ; i++ )
        this->Del(x.getRange(i));

    return (*this);


}

///=================================================================================///

CRangeList &CRangeList::operator-=(const CRange &x) {

    /// Same like -

    if(this->arr.empty())
        return (*this);

    this->Del(x);
    return (*this);
}

///=================================================================================///

#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
    ostringstream oss;
    oss << x;
    cout<< x << endl;
    return oss . str ();
}


int                main                                    ( void )
{


  return 0;
}
#endif /* __PROGTEST__ */
