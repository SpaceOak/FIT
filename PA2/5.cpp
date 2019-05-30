#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */


/// I decided to use flags to solve the problem with output
/// We keep those flags in state false always and if required change
/// to true and then change back to false
/// Check method CDisc::showContent and CComputer::allOut for more info

bool lastHost;
bool lastComponent;
bool shortPrint;

/// I use shortPrint for correct output of CComputer

///==============================================================================///
///==============================================================================///

/// Header abstract class

struct CComponent
{
    CComponent(){}
    ~CComponent(){}
    virtual string showContent() const = 0;
};

///==============================================================================///
///==============================================================================///

class CCPU : public CComponent
{
    string content;
public:
    CCPU ( ulong core , ulong pow )
    {
        ostringstream z;
        z << "CPU, " << core << " cores @ " << pow << "MHz" << endl;
        content = z.str();
    }
    CCPU ( string bite ) { content = bite;}
    virtual string showContent() const
    { return content; }
};

///==============================================================================///
///==============================================================================///

class CMemory : public CComponent
{
    string content;
public:
    CMemory (ulong a ) {
        string tmp = "Memory, " + to_string(a) + " MiB" + "\n";
        content = tmp;
    }
    virtual string showContent () const
    { return content; }
};

///==============================================================================///
///==============================================================================///

class CDisk : public CComponent
{
public:
    enum diskType { SSD, MAGNETIC };

    CDisk ( const CDisk& z)
    {
        ulong arrSize = z.parts.size();
        dSize = z.dSize;
        type  = z.type;

        for ( ulong i = 0 ; i < arrSize ; i++)
            this->parts.emplace_back( make_pair(z.parts[i].first,z.parts[i].second));
    }

///==============================================================================///

    CDisk  (CDisk::diskType currType, unsigned int currSize)
            : type(currType), dSize (currSize) {}

///==============================================================================///

    string getComp ( const ulong i ) const
    {
        ostringstream out;
        out << "-[" << i << "]: " << parts[i].first << " GiB, " << parts[i].second << "\n";
        return out.str();
    }

///==============================================================================///

    CDisk& AddPartition ( ulong pow, string n)
    {
        parts.emplace_back(make_pair(pow,n));
        return (*this);
    }

///==============================================================================///

    virtual string showContent () const
    {

        ulong arrSize = parts.size();
        ostringstream out;
        out << ((type == diskType::MAGNETIC) ? "HDD, " : "SSD, ") << dSize << " GiB\n";
        for ( ulong i = 0 ; i < arrSize ; i++) {

            /// case it is last host
            if ( !shortPrint ) {
                if (!lastHost) {
                    out << "| ";
                } else /// other case
                {
                    out << "  ";
                }
            }

            /// case it is last component
            if( !lastComponent ) {

                if (i + 1 == arrSize)/// if it is the time to put last slash
                    out << "| \\";
                else                 /// if it is any other component
                    out << "| +";

            } else
            {
                if (i + 1 == arrSize)/// if it is the time to put last slash
                    out << "  \\";
                else                 /// if it is any other component
                    out << "  +";
            }

            /// get string
            out << getComp(i);
        }
        return out.str();
    }

///==============================================================================///

private:
    diskType type;
    vector<pair<unsigned int, string>> parts;
    ulong dSize;
};

///==============================================================================///
///==============================================================================///

class CComputer
{
public:
    CComputer ( string n ) { name = n; }

///==============================================================================///

    CComputer& AddComponent (const CCPU z )
    {
        cout << "CPU added to Comp " << name << endl;
        arr.push_back(make_shared<CCPU>(CCPU(z)));
        return (*this);
    }
///==============================================================================///

    CComputer& AddComponent (const CMemory z )
    {
        cout << "Memory added to Comp " << name << endl;
        arr.push_back(make_shared<CMemory>(CMemory(z)));
        return (*this);
    }
///==============================================================================///

    CComputer& AddComponent (const CDisk &z )
    {
        cout << "Disk added to Comp " << name << endl;
        arr.push_back(make_shared<CDisk>(CDisk(z)));
        return (*this);
    }
///==============================================================================///


    CComputer& AddAddress (const string n )
    {
        cout << "new Address added to Comp " << name << endl;
        string tmp = n + "\n";
        adr.push_back(tmp);
        return (*this);
    }

///==============================================================================///

    string showName() const { return name; }

///==============================================================================///

    /// this foo implements basic logic of tree to make it according to Ladia's task
    string allOut () const
    {

        ostringstream out;

        for ( ulong i = 0 ; i < adr.size() ; i++ ) /// first 'for' for adresses
        {

            if( arr.size() == 0 )
            {
                if ( lastHost )
                    out << "  \\-" ;
                else
                    out << "| \\-" ;

                out << adr[i];
                continue;
            }


            if ( lastHost )
                out << "  +-" ;
            else
                out << "| +-" ;

            out << adr[i];
        }


        for ( ulong i = 0 ; i < arr.size() ; i++ ) /// second 'for' for components
        {
            if ( i + 1 == arr.size() )
                lastComponent = true;


            if(!lastHost)
            {
                if (i + 1 != arr.size())
                    out << "| +-";
                else
                    out << "| \\-" ;
            } else
            {

                if (i + 1 != arr.size())
                    out << "  +-" ;
                else
                    out << "  \\-";
            }
            out << arr[i]->showContent();
            lastComponent = false;
        }
        return out.str();
    }
///==============================================================================///

    /// this foo is needed to dead with output of toString(CComputer)
    string showSingleComp () const
    {
        ostringstream out;
        shortPrint = true;

        for ( ulong i = 0 ; i < adr.size() ; i++ )
            out << "+-" << adr[i];

        for ( ulong i = 0 ; i < arr.size() ; i++ )
        {
            if ( i + 1 == arr.size() ){ lastComponent = true; }

                if (i + 1 != arr.size())
                    out << "+-" ;
                else
                    out << "\\-";

            out << arr[i]->showContent();
            lastComponent = false;
        }
        lastComponent = false;
        lastHost      = false;
        shortPrint    = false;
        return out.str();
    }

///==============================================================================///


private:
    string name;                          /// name of comp
    vector<shared_ptr<CComponent>> arr;   /// shared ptr coz i hate memory leaks and etc
    vector<string> adr;                   /// extra vector to print adresses first according to task
};

///==============================================================================///
///==============================================================================///

class CNetwork
{
public:
    CNetwork ( string n ) { name = n; cnt = 0; }
    ~CNetwork () = default;
///==============================================================================///

    CNetwork ( const CNetwork & src )
    {
        name = src.name;
        cnt = src.cnt;
        for ( auto & iter : src.arr )
        {
            arr.push_back( make_shared<CComputer>(*iter) );
        }
    }


///==============================================================================///

    CNetwork & AddComputer(const CComputer& x)
    {
        arr.emplace_back(make_shared<CComputer>(x));
        cnt++;
        return (*this);
    }

///==============================================================================///

    CComputer * FindComputer (const string& current ) {

        auto iter = arr.begin();

        for ( int i = 0 ; i < cnt ; i++, iter++)
        {
            if ( current == (*iter).get()->showName() )
                return (*iter).get();
        }
        return nullptr;
    }

///==============================================================================///

    string showContent () const
    {
        auto iter = arr.begin();
        ostringstream out;
        shortPrint = false;
        out << "Network: " << name << endl;
        for ( int i = 0 ; i < cnt; i++, iter++) {
            if( i >= cnt - 1 )
                lastHost = true;

            if ( lastHost)
                out << "\\-Host: " + (*iter)->showName() + "\n";
            else
                out << "+-Host: " + (*iter)->showName() + "\n";

            out << (*iter)->allOut();
            lastHost = false;
        }
        return out.str();
    }

///==============================================================================///


private:
    string name;                      /// name of network
    list<shared_ptr<CComputer>> arr;  /// use shared ptr coz dont want to worry about memory
    int cnt;                          /// count of comps in this network
};

///==============================================================================///
///==============================================================================///

ostringstream& operator << ( ostringstream& os, const CNetwork& zis )
{
    os << zis.showContent().c_str();
    return os;
}

///==============================================================================///

ostringstream& operator << ( ostringstream& os, const CComputer& zis )
{
    os << "Host: " << zis.showName().c_str() << endl;
    os << zis.showSingleComp().c_str();
    return os;
}

///==============================================================================///

ostringstream& operator << ( ostringstream& os, const CComputer* zis )
{
    os << "Host: " << zis->showName().c_str() << endl;
    os << zis->showSingleComp().c_str();
    return os;
}


///============================ THATS ALL FOLKS !!! =============================///







#ifndef __PROGTEST__
template<typename _T>
string toString ( const _T & x )
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}



int main ( void )
{


    CNetwork n ( "FIT network" );
    n . AddComputer (
            CComputer ( "progtest.fit.cvut.cz" ) .
                    AddAddress ( "147.32.232.142" ) .
                    AddComponent ( CCPU ( 8, 2400 ) ) .
                    AddComponent ( CCPU ( 8, 1200 ) ) .
                    AddComponent ( CDisk ( CDisk::MAGNETIC, 1500 ) .
                    AddPartition ( 50, "/" ) .
                    AddPartition ( 5, "/boot" ).
                    AddPartition ( 1000, "/var" ) ) .
                    AddComponent ( CDisk ( CDisk::SSD, 60 ) .
                    AddPartition ( 60, "/data" )  ) .
                    AddComponent ( CMemory ( 2000 ) ).
                    AddComponent ( CMemory ( 2000 ) ) ) .
            AddComputer (
            CComputer ( "edux.fit.cvut.cz" ) .
                    AddAddress ( "147.32.232.158" ) .
                    AddComponent ( CCPU ( 4, 1600 ) ) .
                    AddComponent ( CMemory ( 4000 ) ).
                    AddComponent ( CDisk ( CDisk::MAGNETIC, 2000 ) .
                    AddPartition ( 100, "/" )   .
                    AddPartition ( 1900, "/data" ) ) ) .
            AddComputer (
            CComputer ( "imap.fit.cvut.cz" ) .
                    AddAddress ( "147.32.232.238" ) .
                    AddComponent ( CCPU ( 4, 2500 ) ) .
                    AddAddress ( "2001:718:2:2901::238" ) .
                    AddComponent ( CMemory ( 8000 ) ));


            cout << "============================!!==========================" << endl;
            cout << toString(n);


                    assert ( toString ( n ) ==
             "Network: FIT network\n"
                     "+-Host: progtest.fit.cvut.cz\n"
                     "| +-147.32.232.142\n"
                     "| +-CPU, 8 cores @ 2400MHz\n"
                     "| +-CPU, 8 cores @ 1200MHz\n"
                     "| +-HDD, 1500 GiB\n"
                     "| | +-[0]: 50 GiB, /\n"
                     "| | +-[1]: 5 GiB, /boot\n"
                     "| | \\-[2]: 1000 GiB, /var\n"
                     "| +-SSD, 60 GiB\n"
                     "| | \\-[0]: 60 GiB, /data\n"
                     "| +-Memory, 2000 MiB\n"
                     "| \\-Memory, 2000 MiB\n"
                     "+-Host: edux.fit.cvut.cz\n"
                     "| +-147.32.232.158\n"
                     "| +-CPU, 4 cores @ 1600MHz\n"
                     "| +-Memory, 4000 MiB\n"
                     "| \\-HDD, 2000 GiB\n"
                     "|   +-[0]: 100 GiB, /\n"
                     "|   \\-[1]: 1900 GiB, /data\n"
                     "\\-Host: imap.fit.cvut.cz\n"
                     "  +-147.32.232.238\n"
                     "  +-2001:718:2:2901::238\n"
                     "  +-CPU, 4 cores @ 2500MHz\n"
                     "  \\-Memory, 8000 MiB\n" );
    CNetwork x = n;


    cout << "==============================================" <<endl;
    cout << toString(x);
    cout << "==============================================" <<endl;



    auto c = x . FindComputer ( "imap.fit.cvut.cz" );
    cout << toString(*c);

    assert ( toString ( *c ) ==
             "Host: imap.fit.cvut.cz\n"
                     "+-147.32.232.238\n"
                     "+-2001:718:2:2901::238\n"
                     "+-CPU, 4 cores @ 2500MHz\n"
                     "\\-Memory, 8000 MiB\n" );
    c -> AddComponent ( CDisk ( CDisk::MAGNETIC, 1000 ) .
            AddPartition ( 100, "system" ) .
            AddPartition ( 200, "WWW" ) .
            AddPartition ( 700, "mail" ) );
    assert ( toString ( x ) ==
             "Network: FIT network\n"
                     "+-Host: progtest.fit.cvut.cz\n"
                     "| +-147.32.232.142\n"
                     "| +-CPU, 8 cores @ 2400MHz\n"
                     "| +-CPU, 8 cores @ 1200MHz\n"
                     "| +-HDD, 1500 GiB\n"
                     "| | +-[0]: 50 GiB, /\n"
                     "| | +-[1]: 5 GiB, /boot\n"
                     "| | \\-[2]: 1000 GiB, /var\n"
                     "| +-SSD, 60 GiB\n"
                     "| | \\-[0]: 60 GiB, /data\n"
                     "| +-Memory, 2000 MiB\n"
                     "| \\-Memory, 2000 MiB\n"
                     "+-Host: edux.fit.cvut.cz\n"
                     "| +-147.32.232.158\n"
                     "| +-CPU, 4 cores @ 1600MHz\n"
                     "| +-Memory, 4000 MiB\n"
                     "| \\-HDD, 2000 GiB\n"
                     "|   +-[0]: 100 GiB, /\n"
                     "|   \\-[1]: 1900 GiB, /data\n"
                     "\\-Host: imap.fit.cvut.cz\n"
                     "  +-147.32.232.238\n"
                     "  +-2001:718:2:2901::238\n"
                     "  +-CPU, 4 cores @ 2500MHz\n"
                     "  +-Memory, 8000 MiB\n"
                     "  \\-HDD, 1000 GiB\n"
                     "    +-[0]: 100 GiB, system\n"
                     "    +-[1]: 200 GiB, WWW\n"
                     "    \\-[2]: 700 GiB, mail\n" );
    assert ( toString ( n ) ==
             "Network: FIT network\n"
                     "+-Host: progtest.fit.cvut.cz\n"
                     "| +-147.32.232.142\n"
                     "| +-CPU, 8 cores @ 2400MHz\n"
                     "| +-CPU, 8 cores @ 1200MHz\n"
                     "| +-HDD, 1500 GiB\n"
                     "| | +-[0]: 50 GiB, /\n"
                     "| | +-[1]: 5 GiB, /boot\n"
                     "| | \\-[2]: 1000 GiB, /var\n"
                     "| +-SSD, 60 GiB\n"
                     "| | \\-[0]: 60 GiB, /data\n"
                     "| +-Memory, 2000 MiB\n"
                     "| \\-Memory, 2000 MiB\n"
                     "+-Host: edux.fit.cvut.cz\n"
                     "| +-147.32.232.158\n"
                     "| +-CPU, 4 cores @ 1600MHz\n"
                     "| +-Memory, 4000 MiB\n"
                     "| \\-HDD, 2000 GiB\n"
                     "|   +-[0]: 100 GiB, /\n"
                     "|   \\-[1]: 1900 GiB, /data\n"
                     "\\-Host: imap.fit.cvut.cz\n"
                     "  +-147.32.232.238\n"
                     "  +-2001:718:2:2901::238\n"
                     "  +-CPU, 4 cores @ 2500MHz\n"
                     "  \\-Memory, 8000 MiB\n" );




    cout << "trying to use showContent" << endl;
    //cout << n.showContent();

    //cout << "dine" << endl<< "dine" << endl<< "dine" << endl;
    return 0;
}
#endif /* __PROGTEST__ */