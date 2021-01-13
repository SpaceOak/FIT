#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <iterator>

using namespace std;




class Path {
public:
    int planet, time, pathLenght;
    Path* previous;
};



int main() {

    int p_cnt, r_cnt;
    set < int > visited;

    cin >> p_cnt;
    cin >> r_cnt;

    int start, end, length;

    cin >> start;
    cin >> end;
    cin >> length;

    int ill_cnt, tmp;
    map <int,bool> ill;

    vector < vector<int>> routes(p_cnt);


    //------------------------------------------

    cin >> ill_cnt;

    for ( int i = ill_cnt; i > 0 ; i-- ) {
        cin >> tmp;
        ill[tmp] = true;
    }

    //------------------------------------------

    int heal_cnt;
    map<int,bool> heal;

    cin >> heal_cnt;

    for ( int i = heal_cnt; i > 0 ; i-- ) {
        cin >> tmp;
        heal[tmp] = true;
    }

    heal[end] = true;

    //------------------------------------------


    int from, to;

    for (int i = r_cnt ; i > 0 ; i-- )
    {
        cin >> from;
        cin >> to;
        routes[from].push_back(to);
        routes[to].push_back(from);
    }

    //------------------------------------------


    list <Path> que;
    Path first;
    first.planet = end;
    first.time = length;
    first.pathLenght = 0;
    que.push_back(first);
    auto pos = que.begin();
    int limit = max(p_cnt, p_cnt * heal_cnt);
    visited.insert(end);


    //------------------------------------------









    //------------------------------------------



    for(auto iter1 = que.begin() ; (*iter1).time != 0 ; iter1++)
    {
        for( auto iterLast = routes[(*iter1).planet].begin(); iterLast != routes[(*iter1).planet].end() ; iterLast++ )
        {
            if ( (*iterLast) == start )
            {
                first.previous = &(*iter1); // pos in que
                first.planet   = (*iterLast); // planet id in routes
                que.push_back(first);
                break;
            }
            else if( ( heal.find(*iterLast) == heal.end() || visited.find(*iterLast) == visited.end() ) )
            {
                if (heal.find(*iterLast) != heal.end())
                    first.time = length;
                else
                    first.time     = (*iter1).time - 1; // max heal
                first.previous = &(*iter1); // pos in que
                first.planet   = (*iterLast); // planet id in routes
                first.pathLenght = (*iter1).pathLenght + 1;
                que.push_back(first);
                visited.insert(first.planet);
            }
        }
    }




    //------------------------------------------






    for ( ; (*pos).planet != start &&  pos != que.end() ; pos++ )
    {
        if ( (*pos).pathLenght > limit )
            continue;


        for ( auto iter = routes[(*pos).planet].begin(); iter != routes[(*pos).planet].end() ; iter++ )
        {



                if( heal.find(*iter) != heal.end() && visited.find(*iter) == visited.end())
                {

                    //------------------------------------------

                    list <Path> small;

                    first.time     = length; // max heal
                    first.previous = &(*pos); // pos in que
                    first.planet   = (*iter); // planet id in routes
                    first.pathLenght = (*pos).pathLenght + 1;
                    small.push_back(first);
                    visited.insert(first.planet);


                    for(auto iterSmall = small.begin() ; (*iterSmall).time != 0 ; iterSmall++)
                    {
                        if ( (*iterSmall).planet == start )
                        {
                            pos = iterSmall;
                            break;
                        }

                        for( auto iterLast = routes[(*iterSmall).planet].begin(); iterLast != routes[(*iterSmall).planet].end() ; iterLast++ )
                        {
                            if ( (*iterLast) == start )
                            {
                                first.previous = &(*iterSmall); // pos in que
                                first.planet   = (*iterLast); // planet id in routes
                                small.push_back(first);
                                break;
                            }
                            else if( ( heal.find(*iterLast) == heal.end() || visited.find(*iterLast) == visited.end() ) )
                            {
                                if(heal.find(*iterLast) != heal.end())
                                    first.time = length;
                                else
                                    first.time     = (*iterSmall).time - 1; // max heal
                                first.previous = &(*iterSmall); // pos in que
                                first.planet   = (*iterLast); // planet id in routes
                                first.pathLenght = (*iterSmall).pathLenght + 1;
                                small.push_back(first);
                                visited.insert(first.planet);
                            }
                        }
                    }

                    if ( (*pos).planet == start )
                    {
                        break;
                    }

                    que.splice(que.end(),small);
                    //------------------------------------------
                }
                else
                {
                    if ( ill.find(*iter) != ill.end() || visited.find(*iter) != visited.end()) continue;
                    first.previous = &(*pos); // pos in que
                    first.planet   = (*iter); // planet id in routes
                    first.pathLenght = (*pos).pathLenght + 1;
                    que.push_back(first);
                    visited.insert(first.planet);
                }

        }
    }


    // trouble test
    if ( (*pos).planet != start ||  pos == que.end() )
    {
        cout << "-1";
        return 0;
    }

    // output
    bool trigger = true;
    for( Path* d = &(*pos); d != &(*que.begin()) ; d = ((*d).previous) )
    {
        if( trigger )
        {trigger = false;}
        else
        { cout << " ";}

        cout << (*d).planet;
    }

    cout << " " << end;

    return 0;
}