#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */



class home
{
public:
    unsigned int id;
    string owner;
    string city;
    string adr;
    string reg;
    unsigned int nmb;

    /// Two kinds of constructor
    /// Second constructor is used to create object with owner
    /// For example NewOwner function

    home     ( unsigned int id, string region, string city, string addr , string owner, unsigned int nmb)
    {
        this->id=id;
        this->reg=region;
        this->city=city;
        this->adr=addr;
        this->owner=owner;
        this->nmb=nmb;
    }

};
/*
======================================================================================================
*/
/// Comparators for lower and upper bound

class ComparatorAdr{
public:
    bool operator() (const home& p, const string& adr ) const {
        return (p.adr < adr);
    }
    bool operator() (const string& adr, const home& p ) const {
        return (adr < p.adr);
    }
};

/// According to task ownerList had to ignore difference between upper and lower reddit

class ComparatorOwn{
public:
    bool operator() (const home& p, const string& owner ) const {


        int len = (int)(strlen(p.owner.c_str()));

        string newstrX;

        for(int i = 0 ; i < len ; i++ )
            if( p.owner[i] <= 122 && p.owner[i] >= 97 )
                newstrX = p.owner[i]-32;
            else
                newstrX = p.owner[i];

        len = (int)(strlen(owner.c_str()));

        string newstrY;

        for(int i = 0 ; i < len ; i++ )
            if( owner[i] <= 122 && owner[i] >= 97 )
                newstrY = owner[i]-32;
            else
                newstrY = owner[i];

        return (newstrX < newstrY );
    }
    bool operator() (const string& owner ,const home& p ) const {
        int len = (int)(strlen(p.owner.c_str()));

        string newstrX;

        for(int i = 0 ; i < len ; i++ )
            if( p.owner[i] <= 122 && p.owner[i] >= 97 )
                newstrX = p.owner[i]-32;
            else
                newstrX = p.owner[i];

        len = (int)(strlen(owner.c_str()));

        string newstrY;

        for(int i = 0 ; i < len ; i++ )
            if( owner[i] <= 122 && owner[i] >= 97 )
                newstrY = owner[i]-32;
            else
                newstrY = owner[i];

        return (newstrY < newstrX );
    }
};

class ComparatorId{
public:
    bool operator() (const home& p, const unsigned int& id ) const {
        return (p.id < id);
    }
    bool operator() (const unsigned int& id, const home& p ) const {
        return (id < p.id);
    }
};


class ComparatorReg{
public:
    bool operator() (const home& p, const string& reg ) const {
        return (p.reg < reg);
    }
    bool operator() (const string& reg, const home& p ) const {
        return (reg < p.reg);
    }
};


class ComparatorCity{
public:
    bool operator() (const home& p, const string& city ) const {
        return (p.city < city);
    }
    bool operator() (const string& city, const home& p ) const {
        return (city < p.city);
    }
};

class ComparatorOwnVec{
public:
    bool operator() (const home& p, const home& owner ) const {


        int len = (int)(strlen(p.owner.c_str()));

        string newstrX;

        for(int i = 0 ; i < len ; i++ )
            if( p.owner[i] <= 122 && p.owner[i] >= 97 )
                newstrX = p.owner[i]-32;
            else
                newstrX = p.owner[i];

        len = (int)(strlen(owner.owner.c_str()));

        string newstrY;

        for(int i = 0 ; i < len ; i++ )
            if( owner.owner[i] <= 122 && owner.owner[i] >= 97 )
                newstrY = owner.owner[i]-32;
            else
                newstrY = owner.owner[i];

        if (newstrX != newstrY )return (newstrY > newstrX );
        else return owner.nmb > p.nmb;
    }
};

class ComparatorRegId{
public:
    bool operator() (const home& p, const home& q ) const {
        if (p.reg != q.reg) return p.reg < q.reg;
        else return p.id < q.id;
    }
};


class ComparatorCityAdr{
public:
    bool operator() (const home& p, const home& q ) const {
        if (p.city != q.city) return p.city < q.city;
        else return p.adr < q.adr;
    }

};
/*
======================================================================================================
*/

class CIterator
{

public:
    bool                     AtEnd                         ( void ) const;
    void                     Next                          ( void );
    string                   City                          ( void ) const;
    string                   Addr                          ( void ) const;
    string                   Region                        ( void ) const;
    unsigned                 ID                            ( void ) const;
    string                   Owner                         ( void ) const;
    CIterator                                              ( vector <home> q , string s )
    {
        for(auto iter = q.begin();iter != q.end() ; iter++ )
            tmp.push_back(*iter);
        sort(tmp.begin(),tmp.end(),ComparatorOwnVec());
        vector<home>::const_iterator iter = lower_bound(tmp.begin(),tmp.end(),s,ComparatorOwn());
        vector<home>::const_iterator iter2 = upper_bound(tmp.begin(),tmp.end(),s,ComparatorOwn());
        pos = static_cast<int>(iter - tmp.begin());
        totalSize = static_cast<int>(iter2 - iter) + pos;
    }

    CIterator                                              ( vector <home> q)
    {
        for(auto iter = q.begin();iter != q.end() ; iter++ )
            tmp.push_back(*iter);
        pos = 0;
        totalSize =(int) tmp.size();
    }


private:
    vector<home> tmp;
    int pos;                           /// Position in arr
    int totalSize;                     /// Total size of arr
};

/*
======================================================================================================
*/

/// Getters and basic methods for work with iter
/// Nothing to explain imao
string       CIterator::City                               ( void ) const
{
    return tmp[pos].city;
}

string       CIterator::Addr                               ( void ) const
{
    return tmp[pos].adr;
}

string       CIterator::Region                             ( void ) const
{
    return tmp[pos].reg;
}

unsigned int CIterator::ID                                 ( void ) const
{
    return tmp[pos].id;
}

string       CIterator::Owner                              ( void ) const
{
    return tmp[pos].owner;
}

bool         CIterator::AtEnd                              ( void ) const
{
    return pos >= totalSize;
}

void         CIterator::Next                               ( void )
{
    pos++;
}


/*
======================================================================================================
*/

class CLandRegister
{

public:

    bool                     Add                           ( const string    & city,
                                                             const string    & addr,
                                                             const string    & region,
                                                             unsigned int      id );
    bool                     Del                           ( const string    & city,
                                                             const string    & addr );
    bool                     Del                           ( const string    & region,
                                                             unsigned int      id );
    bool                     GetOwner                      ( const string    & city,
                                                             const string    & addr,
                                                             string          & owner ) const;
    bool                     GetOwner                      ( const string    & region,
                                                             unsigned int      id,
                                                             string          & owner ) const;
    bool                     NewOwner                      ( const string    & city,
                                                             const string    & addr,
                                                             const string    & owner );
    bool                     NewOwner                      ( const string    & region,
                                                             unsigned int      id,
                                                             const string    & owner );
    unsigned                 Count                         ( const string    & owner ) const;
    CIterator                ListByAddr                    ( void ) const;
    CIterator                ListByOwner                   ( const string    & owner ) const;
    void                     show                          ( void                    ) const;
    void                     showByAdr                     ( void                    ) const;
private:
    vector <home> byAdr; /// Vector sorted by Addres
    vector <home> byReg; /// Vector sorted by Region
    unsigned int cnt;    /// Count of elements
    unsigned int nmb;
};

/*
======================================================================================================
*/

bool CLandRegister:: Add                                   ( const string    & city,
                                                             const string    & addr,
                                                             const string    & region,
                                                             unsigned int      id)
{
    size_t index = byAdr.size();
    vector<home>::iterator iterAdrBot, iterAdrTop, iterOwner, iterRegionTop, iterRegionBot;


    string owner;
    if (index == 0){    /// If first land
        nmb = 0;
        home tmp (id, region, city, addr, owner, nmb);
        byAdr.       push_back ( tmp );
        byReg.       push_back ( tmp );
        nmb++;
        cnt=1;
        return true;
    } else {            /// Find place for next land
                        /// Combinations like you can see there lower_bound(lower,upper) used to sort them by two arguments
        home tmp (id, region, city, addr, owner, nmb);
        //------------------------------------------------------------------------------------
        iterAdrBot     = lower_bound(  byAdr.begin(),  byAdr.end()  , tmp  ,  ComparatorCityAdr ());
        //------------------------------------------------------------------------------------
        iterRegionBot  = lower_bound(  byReg.begin(),  byReg.end()  , tmp  ,  ComparatorRegId ());
        //------------------------------------------------------------------------------------

                        /// Check if land does not exist
        if((*iterAdrBot).adr == addr && (*iterAdrBot).city == city )
            return false;

        if((*iterRegionBot).reg == region && (*iterRegionBot).id == id )
            return false;


                        /// Add new land
        byAdr.insert( iterAdrBot   , {id, region, city, addr, owner, nmb} );
        byReg.insert( iterRegionBot, {id, region, city, addr, owner, nmb} );
        cnt++;
        nmb++;
    }
    return true;
}

bool CLandRegister:: Del                                   ( const string     & city,
                                                             const string     & addr )
{
    if ( cnt == 0 ) return false; /// If empty arr

    auto iterBot  = lower_bound(byAdr.begin(),byAdr.end(),addr  ,ComparatorAdr ());
    auto iterTop  = upper_bound(byAdr.begin(),byAdr.end(),addr  ,ComparatorAdr ());
    iterBot       = lower_bound(iterBot      ,iterTop    ,city  ,ComparatorCity());

    /// If there is no such land
    if ( (*iterBot).city != city || (*iterBot).adr != addr ) return false;

    /// Save other attributes
    string tmpReg = (*iterBot).reg;
    string tmpOwn = (*iterBot).owner;
    int    tmpId  = (*iterBot).id;

    byAdr.erase(iterBot);
//------------------------------------------------------------------------------------
    home tmp (tmpId,tmpReg,city,addr,tmpOwn,0);

    iterBot       = lower_bound(byReg.begin(),byReg.end(),tmp ,ComparatorRegId ());

    byReg.erase(iterBot);
    cnt--;/// size -= 1

    return true;
}


bool CLandRegister:: Del                                   ( const string    & region,
                                                             unsigned int      id   )
{
    if ( cnt == 0 ) return false;

    auto iterBot    = lower_bound(byReg.begin(),byReg.end(),region  ,ComparatorReg ());
    auto iterTop    = upper_bound(byReg.begin(),byReg.end(),region  ,ComparatorReg ());
    iterBot         = lower_bound(iterBot      ,iterTop    ,id      ,ComparatorId  ());

    if ( (*iterBot).reg != region || (*iterBot).id != id ) return false;

    string tmpAdr   = (*iterBot).adr;
    string tmpOwn   = (*iterBot).owner;
    string tmpCity  = (*iterBot).city;


    byReg.erase(iterBot);
//------------------------------------------------------------------------------------
    home tmp (id,region,tmpCity,tmpAdr,tmpOwn,0);

    iterBot         = lower_bound(byAdr.begin(),byAdr.end(),tmp  ,ComparatorCityAdr ());

    byAdr.erase(iterBot);
    cnt--;

    return true;
}


unsigned CLandRegister:: Count                             ( const string    & owner ) const
{
    vector<home>crab;
    for(auto iter = byAdr.begin();iter != byAdr.end() ; iter++ )
        crab.push_back(*iter);
    sort(crab.begin(),crab.end(),ComparatorOwnVec());
    auto iterBot    = lower_bound(crab.begin(),crab.end(),owner  ,ComparatorOwn ());
    auto iterTop    = upper_bound(crab.begin(),crab.end(),owner  ,ComparatorOwn ());
    unsigned z = (unsigned)distance(iterBot,iterTop);
    return z;
}


bool CLandRegister:: NewOwner                              ( const string    & region,
                                                             unsigned int      id,
                                                             const string    & owner )
{
    vector<home>::iterator iterTop , iterBot;

    if ( cnt == 0 ) return  false;

    home tmp (id,region,"","","",0);
    iterBot          = lower_bound( byReg .begin(), byReg .end(), tmp,   ComparatorRegId  ());

    /// If no such land here
    if      ((*iterBot).owner  == owner
          || (*iterBot).reg    != region
          || (*iterBot).id     != id) return false;


    (*iterBot).owner=owner;
    (*iterBot).nmb=nmb;

    /// Save other attributes
    string tmpAdr  = (*iterBot).adr;
    string tmpCity = (*iterBot).city;
    (*iterBot).owner=owner;

    home q (id,region,tmpCity,tmpAdr,"",nmb);

    iterBot        = lower_bound( byAdr .begin(), byAdr .end(), q,   ComparatorCityAdr  ());
    (*iterBot).owner=owner;
    (*iterBot).nmb=nmb;
    nmb++;
    return true;


}

/// Same but with other arguments
bool CLandRegister:: NewOwner                              ( const string    & city,
                                                             const string    & addr,
                                                             const string    & owner )
{
    vector<home>::iterator iterTop , iterBot;

    if ( cnt == 0 ) return  false;

    home tmp (0,"",city,addr,"",0);
    iterBot       = lower_bound(  byAdr.begin(),  byAdr.end()  , tmp  ,  ComparatorCityAdr());

    if   ((*iterBot).owner == owner
       || (*iterBot).adr   != addr
       || (*iterBot).city  != city) return false;


    (*iterBot).owner=owner;
    (*iterBot).nmb=nmb;

    string tmpReg       = (*iterBot).reg;
    unsigned int tmpId  = (*iterBot).id;

    home q (tmpId,tmpReg,city,addr,"",nmb);


    iterBot        = lower_bound( byReg .begin(), byReg .end(), q,   ComparatorRegId  ());
    (*iterBot).owner=owner;
    (*iterBot).nmb=nmb;
    nmb++;
    return true;
}


bool CLandRegister:: GetOwner                              ( const string    & region,
                                                             unsigned int      id,
                                                             string          & owner ) const
{
    home tmp (id,region,"","","",0);
    auto iterBot    = lower_bound(byReg.begin(),byReg.end(),tmp  ,ComparatorRegId ());

    /// If no such land here
    if((*iterBot).reg != region || (*iterBot).id != id )
    {
        return false;
    }

    owner = (*iterBot).owner;
    return true;
}

bool CLandRegister:: GetOwner                              ( const string    & city,
                                                             const string    & addr,
                                                             string          & owner  ) const
{
    home tmp (0,"",city,addr,"",0);
    auto iterBot  = lower_bound(  byAdr.begin(),  byAdr.end()  , tmp  ,  ComparatorCityAdr());

    if((*iterBot).city != city || (*iterBot).adr != addr )
    {
        return false;
    }

    owner = (*iterBot).owner;
    return true;
}

/// byArr is alredy created vector so no reason to do something
CIterator CLandRegister::ListByAddr              ( void                    ) const
{
    CIterator x (byAdr);
    return x;
}
/// Same with owner but we have to find lower upper iters to walk between them
CIterator CLandRegister::ListByOwner             ( const string    & owner ) const
{
    CIterator x (byAdr,owner);
    return x;
}


/// Function for tests
void CLandRegister::show                         ( void                    ) const
{
    cout << "By adress" << endl << "-----------------------" << endl;
    for(unsigned int i = 0 ; i < byAdr.size() ; i++)
    {
        cout <<// byAdr[i].owner << setw(10 - (int)strlen(byAdr[i].owner.c_str()))
             byAdr[i].owner << setw((int)strlen(byAdr[i].owner.c_str()) + 5) <<
             byAdr[i].city << setw((int)strlen(byAdr[i].city.c_str()) + 5) <<
             byAdr[i].reg << setw((int)strlen(byAdr[i].reg.c_str()) + 5) <<
             byAdr[i].adr << setw((int)strlen(byAdr[i].adr.c_str()) + 5) << endl;
    }
}

void CLandRegister::showByAdr                         ( void                    ) const
{
    cout << "By adress" << endl << "-----------------------" << endl;
    for(unsigned int i = 0 ; i < byAdr.size() ; i++)
    {
        cout <<             byAdr[i].city << setw((int)strlen(byAdr[i].city.c_str()) + 5) <<
                            byAdr[i].adr << setw((int)strlen(byAdr[i].adr.c_str()) + 5) << endl;
    }
}

/*
======================================================================================================
*/

#ifndef __PROGTEST__

static void test0 ( void )
{
    CLandRegister tester;
    assert ( tester . Add ( "aaa", "aaa", "aaa", 1 ) );
    assert ( tester . Add ( "aab", "aaa", "aaa", 2 ) );
    assert ( tester . Add ( "aac", "aaa", "aaa", 3 ) );
    assert ( tester . Add ( "aad", "aaa", "aaa", 4 ) );
    assert ( tester . Add ( "aad", "aab", "aaa", 5 ) );
    assert ( tester . Add ( "aad", "aac", "aaa", 6 ) );
    assert ( tester . Add ( "aad", "aad", "aaa", 7 ) );
    assert ( tester . Add ( "aad", "aaq", "aax", 8 ) );
    assert ( tester . Add ( "aad", "aaw", "aae", 9 ) );
    assert ( tester . Add ( "aag", "aag", "aag", 456 ) );
    assert ( tester . Add ( "aaa", "aah", "aah", 456 ) );
    assert ( tester . Add ( "aaa", "aai", "aai", 456 ) );
    assert ( tester . Add ( "aad", "aaz", "aar", 10 ) );
    assert ( tester . Add ( "aad", "aax", "aah", 11 ) );
    assert ( tester . Add ( "aad", "aaj", "aag", 12 ) );
    assert ( tester . Add ( "aad", "aav", "aat", 13 ) );


    assert ( tester . Add ( "qqq", "qqq", "qqq", 42 ) );
    assert ( ! tester . Add ( "aaa", "aaa", "aaa", 53 ) );
    assert ( tester . Add ( "aaa", "aab", "aab", 64 ) );
    assert ( tester . Add ( "aaq", "aaq", "aaq", 75 ) );
    assert ( tester . Add ( "aaa", "aae", "aae", 456 ) );
    assert ( tester . Add ( "aaf", "aaf", "aaf", 123 ) );


    tester.showByAdr();

    CLandRegister x;
    string owner;
    cout << "1" << endl;
    assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
    assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
    assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );
    assert ( x . Add ( "Plzen", "Evropska", "Plzen mesto", 78901 ) );
    assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );
    assert (! x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );
    cout << 2 << endl;
    //x.show();

    CIterator i0 = x . ListByAddr ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Liberec"
             && i0 . Addr () == "Evropska"
             && i0 . Region () == "Librec"
             && i0 . ID () == 4552
             && i0 . Owner () == "" );
    i0 . Next ();
    cout << "3" << endl;


    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Plzen"
             && i0 . Addr () == "Evropska"
             && i0 . Region () == "Plzen mesto"
             && i0 . ID () == 78901
             && i0 . Owner () == "" );

    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Evropska"
             && i0 . Region () == "Vokovice"
             && i0 . ID () == 12345
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Technicka"
             && i0 . Region () == "Dejvice"
             && i0 . ID () == 9873
             && i0 . Owner () == "" );
    cout << "5" << endl;
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Thakurova"
             && i0 . Region () == "Dejvice"
             && i0 . ID () == 12345
             && i0 . Owner () == "" );
    i0 . Next ();
    cout << "6" << endl;
    assert ( i0 . AtEnd () );

    cout << x.Count( "" );
    assert ( x . Count ( "" ) == 5 );

    CIterator i1 = x . ListByOwner ( "" );
    cout << "gonna works" << endl;
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Prague"
             && i1 . Addr () == "Thakurova"
             && i1 . Region () == "Dejvice"
             && i1 . ID () == 12345
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Prague"
             && i1 . Addr () == "Evropska"
             && i1 . Region () == "Vokovice"
             && i1 . ID () == 12345
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Prague"
             && i1 . Addr () == "Technicka"
             && i1 . Region () == "Dejvice"
             && i1 . ID () == 9873
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Plzen"
             && i1 . Addr () == "Evropska"
             && i1 . Region () == "Plzen mesto"
             && i1 . ID () == 78901
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Liberec"
             && i1 . Addr () == "Evropska"
             && i1 . Region () == "Librec"
             && i1 . ID () == 4552
             && i1 . Owner () == "" );
    i1 . Next ();
    assert ( i1 . AtEnd () );


    assert ( x . Count ( "CVUT" ) == 0 );
    CIterator i2 = x . ListByOwner ( "CVUT" );
    assert ( i2 . AtEnd () );

    assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
    assert ( x . NewOwner ( "Dejvice", 9873, "CVUT" ) );
    assert ( x . NewOwner ( "Plzen", "Evropska", "Anton Hrabis" ) );
    assert ( x . NewOwner ( "Librec", 4552, "Cvut" ) );

    assert ( x . GetOwner ( "Prague", "Thakurova", owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Dejvice", 12345, owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Prague", "Evropska", owner ) && owner == "" );
    assert ( x . GetOwner ( "Vokovice", 12345, owner ) && owner == "" );
    assert ( x . GetOwner ( "Prague", "Technicka", owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Dejvice", 9873, owner ) && owner == "CVUT" );
    assert ( x . GetOwner ( "Plzen", "Evropska", owner ) && owner == "Anton Hrabis" );
    assert ( x . GetOwner ( "Plzen mesto", 78901, owner ) && owner == "Anton Hrabis" );
    assert ( x . GetOwner ( "Liberec", "Evropska", owner ) && owner == "Cvut" );
    assert ( x . GetOwner ( "Librec", 4552, owner ) && owner == "Cvut" );

    CIterator i3 = x . ListByAddr ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Liberec"
             && i3 . Addr () == "Evropska"
             && i3 . Region () == "Librec"
             && i3 . ID () == 4552
             && i3 . Owner () == "Cvut" );
    i3 . Next ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Plzen"
             && i3 . Addr () == "Evropska"
             && i3 . Region () == "Plzen mesto"
             && i3 . ID () == 78901
             && i3 . Owner () == "Anton Hrabis" );
    i3 . Next ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Prague"
             && i3 . Addr () == "Evropska"
             && i3 . Region () == "Vokovice"
             && i3 . ID () == 12345
             && i3 . Owner () == "" );
    i3 . Next ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Prague"
             && i3 . Addr () == "Technicka"
             && i3 . Region () == "Dejvice"
             && i3 . ID () == 9873
             && i3 . Owner () == "CVUT" );
    i3 . Next ();
    assert ( ! i3 . AtEnd ()
             && i3 . City () == "Prague"
             && i3 . Addr () == "Thakurova"
             && i3 . Region () == "Dejvice"
             && i3 . ID () == 12345
             && i3 . Owner () == "CVUT" );
    i3 . Next ();
    assert ( i3 . AtEnd () );

    assert ( x . Count ( "cvut" ) == 3 );

    CIterator i4 = x . ListByOwner ( "cVuT" );
    assert ( ! i4 . AtEnd ()
             && i4 . City () == "Prague"
             && i4 . Addr () == "Thakurova"
             && i4 . Region () == "Dejvice"
             && i4 . ID () == 12345
             && i4 . Owner () == "CVUT" );
    i4 . Next ();
    assert ( ! i4 . AtEnd ()
             && i4 . City () == "Prague"
             && i4 . Addr () == "Technicka"
             && i4 . Region () == "Dejvice"
             && i4 . ID () == 9873
             && i4 . Owner () == "CVUT" );
    i4 . Next ();
    assert ( ! i4 . AtEnd ()
             && i4 . City () == "Liberec"
             && i4 . Addr () == "Evropska"
             && i4 . Region () == "Librec"
             && i4 . ID () == 4552
             && i4 . Owner () == "Cvut" );
    i4 . Next ();
    assert ( i4 . AtEnd () );

    assert ( x . NewOwner ( "Plzen mesto", 78901, "CVut" ) );
    assert ( x . Count ( "CVUT" ) == 4 );
    CIterator i5 = x . ListByOwner ( "CVUT" );
    assert ( ! i5 . AtEnd ()
             && i5 . City () == "Prague"
             && i5 . Addr () == "Thakurova"
             && i5 . Region () == "Dejvice"
             && i5 . ID () == 12345
             && i5 . Owner () == "CVUT" );
    i5 . Next ();
    assert ( ! i5 . AtEnd ()
             && i5 . City () == "Prague"
             && i5 . Addr () == "Technicka"
             && i5 . Region () == "Dejvice"
             && i5 . ID () == 9873
             && i5 . Owner () == "CVUT" );
    i5 . Next ();
    assert ( ! i5 . AtEnd ()
             && i5 . City () == "Liberec"
             && i5 . Addr () == "Evropska"
             && i5 . Region () == "Librec"
             && i5 . ID () == 4552
             && i5 . Owner () == "Cvut" );
    i5 . Next ();
    assert ( ! i5 . AtEnd ()
             && i5 . City () == "Plzen"
             && i5 . Addr () == "Evropska"
             && i5 . Region () == "Plzen mesto"
             && i5 . ID () == 78901
             && i5 . Owner () == "CVut" );
    i5 . Next ();
    assert ( i5 . AtEnd () );

    assert ( x . Del ( "Liberec", "Evropska" ) );
    assert ( x . Del ( "Plzen mesto", 78901 ) );

    assert ( x . Count ( "cvut" ) == 2 );

    CIterator i6 = x . ListByOwner ( "cVuT" );
    assert ( ! i6 . AtEnd ()
             && i6 . City () == "Prague"
             && i6 . Addr () == "Thakurova"
             && i6 . Region () == "Dejvice"
             && i6 . ID () == 12345
             && i6 . Owner () == "CVUT" );
    i6 . Next ();
    assert ( ! i6 . AtEnd ()
             && i6 . City () == "Prague"
             && i6 . Addr () == "Technicka"
             && i6 . Region () == "Dejvice"
             && i6 . ID () == 9873
             && i6 . Owner () == "CVUT" );
    i6 . Next ();
    assert ( i6 . AtEnd () );

    assert ( x . Add ( "Liberec", "Evropska", "Librec", 4552 ) );

}

static void test1 ( void )
{
    CLandRegister x;
    string owner;

    assert ( x . Add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
    assert ( x . Add ( "Prague", "Evropska", "Vokovice", 12345 ) );
    assert ( x . Add ( "Prague", "Technicka", "Dejvice", 9873 ) );
    assert ( ! x . Add ( "Prague", "Technicka", "Hradcany", 7344 ) );
    assert ( ! x . Add ( "Brno", "Bozetechova", "Dejvice", 9873 ) );
    assert ( !x . GetOwner ( "Prague", "THAKUROVA", owner ) );
    assert ( !x . GetOwner ( "Hradcany", 7343, owner ) );
    CIterator i0 = x . ListByAddr ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Evropska"
             && i0 . Region () == "Vokovice"
             && i0 . ID () == 12345
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Technicka"
             && i0 . Region () == "Dejvice"
             && i0 . ID () == 9873
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( ! i0 . AtEnd ()
             && i0 . City () == "Prague"
             && i0 . Addr () == "Thakurova"
             && i0 . Region () == "Dejvice"
             && i0 . ID () == 12345
             && i0 . Owner () == "" );
    i0 . Next ();
    assert ( i0 . AtEnd () );

    assert ( x . NewOwner ( "Prague", "Thakurova", "CVUT" ) );
    assert ( ! x . NewOwner ( "Prague", "technicka", "CVUT" ) );
    assert ( ! x . NewOwner ( "prague", "Technicka", "CVUT" ) );
    assert ( ! x . NewOwner ( "dejvice", 9873, "CVUT" ) );
    assert ( ! x . NewOwner ( "Dejvice", 9973, "CVUT" ) );
    assert ( ! x . NewOwner ( "Dejvice", 12345, "CVUT" ) );
    assert ( x . Count ( "CVUT" ) == 1 );
    CIterator i1 = x . ListByOwner ( "CVUT" );
    assert ( ! i1 . AtEnd ()
             && i1 . City () == "Prague"
             && i1 . Addr () == "Thakurova"
             && i1 . Region () == "Dejvice"
             && i1 . ID () == 12345
             && i1 . Owner () == "CVUT" );
    i1 . Next ();
    assert ( i1 . AtEnd () );

    assert ( ! x . Del ( "Brno", "Technicka" ) );
    assert ( ! x . Del ( "Karlin", 9873 ) );
    assert ( x . Del ( "Prague", "Technicka" ) );
    assert ( ! x . Del ( "Prague", "Technicka" ) );
    assert ( ! x . Del ( "Dejvice", 9873 ) );
}

int main ( void )
{
    test0();
    test1();
    return 0;
}
#endif /* __PROGTEST__ */
