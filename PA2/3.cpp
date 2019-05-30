#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;



// your code will be compiled in a separate namespace
namespace MysteriousNamespace {
#endif /* __PROGTEST__ */

    int defineMonth(string & x)
    {
        if( x == "Jan") return 1;
        if( x == "Feb") return 2;
        if( x == "Mar") return 3;
        if( x == "Apr") return 4;
        if( x == "May") return 5;
        if( x == "Jun") return 6;
        if( x == "Jul") return 7;
        if( x == "Aug") return 8;
        if( x == "Sep") return 9;
        if( x == "Oct") return 10;
        if( x == "Nov") return 11;
        if( x == "Dec") return 12;
        return 0;
    }



//----------------------------------------------------------------------------------------
//
//
//
//
    class cmp{
    public:
        bool operator ()(CMail const& a, CMail const& b) {
            return b.TimeStamp().Compare(a.TimeStamp()) > 0;
        }
    };



    class CMailLog
    {
    public:
        int            ParseLog                                ( istream          & in );

        list<CMail>    ListMail                                ( const CTimeStamp & from,
                                                                 const CTimeStamp & to ) const;

        set<string>    ActiveUsers                             ( const CTimeStamp & from,
                                                                 const CTimeStamp & to ) const;
    private:
        multiset<CMail,cmp> main;
        map<string,string> notRdyObj;
        map<string,string> notRdyFrom;
    };





//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------
// string.substr()
    int CMailLog::ParseLog(istream &in)
    {
        int cnt = 0;
        int y,m,d,h,min;
        double sec;


        while(in.good())
        {
            string word[7];

            in >> word[0];

            m = defineMonth( word[0]);
            in >> d;
            in >> y;
            in >> h;
            in.ignore(1);
            in >> min;
            in.ignore(1);
            in >> setprecision(3) >> sec;
            in >> word[4];
            in >> word[5];

            string tmp;
            while (in.peek() != '\n' && in >> tmp)
            {
                word[6] += tmp + " ";
            }
            if(word[6] != "")word[6].pop_back();

            if(word[6] == "")break;
/*
            for (int i = 0; i < 7; i++)
                cout << word[i] << " - ";
            cout << " nom nom" << endl;
*/

            CTimeStamp tmpTime ( y, m, d, h, min, sec );
            //main.emplace_back(tmpTime , tmpword, "", "");


            if ( word[6].substr(0,3) == "to=" )
            {


                string TO = word[6].substr(3);

                CMail z(tmpTime, notRdyFrom[word[5]],TO,notRdyObj[word[5]]);
                main.insert(z);
                cnt++;
            }
            else if ( word[6].substr(0,5) == "from=" )
            {
                notRdyFrom.insert(make_pair(word[5], word[6].substr(5)));
            }
            else if ( word[6].substr(0,8) == "subject=" )
            {
                notRdyObj.insert(make_pair(word[5], word[6].substr(8)));
            }
            else continue;
        }
        return cnt;
    }

    set<string> CMailLog::ActiveUsers(const CTimeStamp &from, const CTimeStamp &to) const {
        set  <string> U;
        CMail a(from, "","",""), b(to  , "", "","");

        auto iter1 = lower_bound(main.begin(), main.end(), a, cmp());
        auto iter2 = upper_bound(main.begin(), main.end(), b, cmp());

        for( auto iter = iter1 ;  iter != iter2 ;  iter++) {
            U.emplace(iter->To());
            U.emplace(iter->From());
        }
        return U;
    }

    list<CMail> CMailLog::ListMail(const CTimeStamp &from, const CTimeStamp &to) const
    {

        CMail  a( from,"","","");CMail b( to  ,"","","");
        list < CMail> newlist;
        auto iter1 = lower_bound( main.begin(), main.end(),a,cmp());
        auto iter2 = upper_bound( main.begin(), main.end(),b,cmp());



        newlist.insert(newlist.begin(),iter1,iter2);

        return newlist;
    }



//----------------------------------------------------------------------------------------
#ifndef __PROGTEST__
} // namespace
string             printMail                               ( const list<CMail> & all )
{
    ostringstream oss;
    for ( const auto & mail : all )
        oss << mail << endl;
    return oss . str ();
}
string             printUsers                              ( const set<string> & all )
{
    ostringstream oss;
    bool first = true;
    for ( const auto & name : all )
    {
        if ( ! first )
            oss << ", ";
        else
            first = false;
        oss << name;
    }
    return oss . str ();
}
int                main                                    ( void )
{
    MysteriousNamespace::CMailLog m;
    list<CMail> mailList;
    set<string> users;
    istringstream iss;

    iss . clear ();
    iss . str (
            "Mar 29 2019 12:35:32.233 relay.fit.cvut.cz ADFger72343D: from=user1@fit.cvut.cz\n"
                    "Mar 29 2019 12:37:16.234 relay.fit.cvut.cz JlMSRW4232Df: from=person3@fit.cvut.cz\n"
                    "Mar 29 2019 12:55:13.023 relay.fit.cvut.cz JlMSRW4232Df: subject=New progtest homework!\n"
                    "Mar 29 2019 13:38:45.043 relay.fit.cvut.cz Kbced342sdgA: from=office13@fit.cvut.cz\n"
                    "Mar 29 2019 13:36:13.023 relay.fit.cvut.cz JlMSRW4232Df: to=user76@fit.cvut.cz\n"
                    "Mar 29 2019 13:55:31.456 relay.fit.cvut.cz KhdfEjkl247D: from=PR-department@fit.cvut.cz\n"
                    "Mar 29 2019 14:18:12.654 relay.fit.cvut.cz Kbced342sdgA: to=boss13@fit.cvut.cz\n"
                    "Mar 29 2019 14:48:32.563 relay.fit.cvut.cz KhdfEjkl247D: subject=Business partner\n"
                    "Mar 29 2019 14:58:32.000 relay.fit.cvut.cz KhdfEjkl247D: to=HR-department@fit.cvut.cz\n"
                    "Mar 29 2019 14:25:23.233 relay.fit.cvut.cz ADFger72343D: mail undeliverable\n"
                    "Mar 29 2019 15:02:34.231 relay.fit.cvut.cz KhdfEjkl247D: to=CIO@fit.cvut.cz\n"
                    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=CEO@fit.cvut.cz\n"
                    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=dean@fit.cvut.cz\n"
                    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=vice-dean@fit.cvut.cz\n"
                    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=archive@fit.cvut.cz\n" );
    assert ( m . ParseLog ( iss ) == 8 );

    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 23, 59, 59 ) );


    cout << printMail(mailList);
    assert ( printMail ( mailList ) ==
             "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
                     "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
                     "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n"
                     "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> CEO@fit.cvut.cz, subject: Business partner\n"
                     "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> dean@fit.cvut.cz, subject: Business partner\n"
                     "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> vice-dean@fit.cvut.cz, subject: Business partner\n"
                     "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> archive@fit.cvut.cz, subject: Business partner\n"
                     "2019-03-29 15:02:34.231 PR-department@fit.cvut.cz -> CIO@fit.cvut.cz, subject: Business partner\n" );

    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 14, 58, 32 ) );
    assert ( printMail ( mailList ) ==
             "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
                     "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
                     "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n" );
    mailList = m . ListMail ( CTimeStamp ( 2019, 3, 30, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 30, 23, 59, 59 ) );
    assert ( printMail ( mailList ) == "" );
    users = m . ActiveUsers ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 23, 59, 59 ) );
    cout<< printUsers(users);
    assert ( printUsers ( users ) == "CEO@fit.cvut.cz, CIO@fit.cvut.cz, HR-department@fit.cvut.cz, PR-department@fit.cvut.cz, archive@fit.cvut.cz, boss13@fit.cvut.cz, dean@fit.cvut.cz, office13@fit.cvut.cz, person3@fit.cvut.cz, user76@fit.cvut.cz, vice-dean@fit.cvut.cz" );
    users = m . ActiveUsers ( CTimeStamp ( 2019, 3, 28, 0, 0, 0 ),
                              CTimeStamp ( 2019, 3, 29, 13, 59, 59 ) );
    assert ( printUsers ( users ) == "person3@fit.cvut.cz, user76@fit.cvut.cz" );

    cout << "done" << endl;

    MysteriousNamespace::CMailLog z;


    iss . str (
            "Mar 29 2019 12:35:32.233 relay.fit.cvut.cz ADFger72343D: from=user1@fit.cvut.cz111\n"
                    "Mar 29 2019 12:37:16.234 relay.fit.cvut.cz JlMSRW4232Df: from=person3@fit.cvut.cz\n"
                    "Mar 29 2019 12:55:13.023 relay.fit.cvut.cz JlMSRW4232Df: subject=New progtest homework!\n"
                    "Mar 29 2019 13:38:45.043 relay.fit.cvut.cz Kbced342sdgA: from=office13@fit.cvut.cz\n"
                    "Mar 29 2019 13:36:13.023 relay.fit.cvut.cz JlMSRW4232Df: to=user76@fit.cvut.cz\n"
                    "Mar 29 2019 13:55:31.456 relay.fit.cvut.cz KhdfEjkl247D: from=PR-department@fit.cvut.cz\n"
                    "Mar 29 2019 14:18:12.654 relay.fit.cvut.cz Kbced342sdgA: to=boss13@fit.cvut.cz\n"
                    "Mar 29 2019 14:48:32.563 relay.fit.cvut.cz KhdfEjkl247D: subject=Business partner\n"
                    "Mar 29 2019 14:58:32.000 relay.fit.cvut.cz KhdfEjkl247D: to=HR-department@fit.cvut.cz\n"
                    "Mar 29 2019 14:25:23.233 relay.fit.cvut.cz ADFger72343D: mail undeliverable\n"
                    "Mar 29 2019 15:02:34.231 relay.fit.cvut.cz KhdfEjkl247D: to=CIO@fit.cvut.cz\n"
                    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=CEO@fit.cvut.cz\n"
                    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=dean@fit.cvut.cz\n"
                    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=vice-dean@fit.cvut.cz\n"
                    "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=archive@fit.cvut.cz\n" );

    return 0;
}
#endif /* __PROGTEST__ */