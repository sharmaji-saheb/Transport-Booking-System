#include<bits/stdc++.h>
#include<iostream>
#include<map>

using namespace std;

# define inf 0x3f3f3f3f

class node
{
public:
    vector<int> next;
    vector<int> weight;
    string city;
    int n = 0;
    int ndeg = 0;

    void add(int i, int w)
    {
        next.push_back(i);
        weight.push_back(w);
        n++;
        ndeg++;
    }

    void direcToAdd()
    {
        ndeg++;
    }

    void direcFromAdd(int j, int w)
    {
        next.push_back(j);
        weight.push_back(w);
        n++;
    }


};


void undirectedAdd(node a[],int i, int j, int w)
{
    a[i].add(j,w);
    a[j].add(i,w);
}


vector < pair <int, int> > graphSsspDijkstra(node a[], int start, int n)
{
    int i;
    vector < pair <int, int> > record;
    priority_queue < pair <int, int> ,vector <pair <int, int> >, greater <pair <int, int> > > pq;


    for( i =0; i<=n; i++)
    {
        if(i == start)
        {
            record.push_back(make_pair(0, i));
        }
        else
        {
            record.push_back(make_pair(inf, i));
        }
    }

    pq.push(make_pair(0, start));

    while(!pq.empty())
    {
        i = pq.top().second;

        for(auto j = a[i].next.begin(), k = a[i].weight.begin(); j!=a[i].next.end(); j++, k++)
        {
            if(record[*j].first > *k + record[i].first)
            {
                record[*j].first = *k + record[i].first;
                record[*j].second = i;
                pq.push(make_pair(*k + record[i].first, *j));
            }
        }

        pq.pop();
    }

    return record;
}


void cityStats(node a[], int n)
{
    for(int i=1; i<=n; i++)
    {
        cout << a[i].city << " is connected with following cities with following distances\n";
        for(auto j=a[i].next.begin(), k=a[i].weight.begin(); j!=a[i].next.end(); j++, k++)
        {
            cout << a[*j].city << " with distance of " << *k << "\n";
        }
        cout << "\n\n";
    }

    cout << "\n\n";
}


int main()
{
    int no_nodes = 0;
    int count;
    node a[1000];
    vector < pair <int, int> > record;
    map<string, int> city;
    string from, to;

    fstream file;
    file.open("cities.txt", ios::in);
    if(file.is_open())
    {
        count=1;
        string s;
        while(getline(file, s))
        {
            a[count].city = s;
            city.insert(pair<string, int>(s, count));
            count++;
        }
    }

    file.close();

    file.open("route.txt", ios:: in);
    int rcount = 1, fr, t, we, r;
    if(file.is_open())
    {
        while(file >> r)
        {
            if(rcount%3 == 1)
            {
                fr = r;
            }
            else if(rcount%3 == 2)
            {
                t = r;
            }
            else
            {
                we = r;
                undirectedAdd(a, fr, t, we);
            }
            rcount++;
        }
    }

    file.close();
    no_nodes = count-1;
    stack<string> res;
    int c = 1;
    cout << "***************************************************************************\n*********************WELCOME TO ROUTE FINDING SERVICES*********************\n***************************************************************************\n\n";

    while(c!=4)
    {
        cout << "******************************************\n******************************************\n";
        cout << "CHOOSE:\n1. FIND DISTANCE\n2. ADD A CITY AND IT'S CONNECTIONS WITH OTHER\n3. LIST OF CITIES\n4. DISPLAY ALL THE DIRECTLY CONNECTED CITIES IN DATABASE\n5. EXIT\n" << endl;
        cout << ">>";
        cin >> c;
        cout << endl;

        switch(c)
        {
        case 1:
            {
                cout << "FROM:: ";
                cin >> from;
                if(city.find(from) == city.end())
                {
                    cout << "\nNo city named " << from << " found in database" << endl;
                    break;
                }

                cout << "TO:: ";
                cin >> to;
                if(city.find(to) == city.end())
                {
                    cout << "\nNo city named " << to << " found in database\n" << endl;
                    break;
                }

                record = graphSsspDijkstra(a, city[from], no_nodes);

                int i = city[to];
                if(record[i].first != inf)
                {
                    cout << "\nDistance = " << record[i].first << "Km" << endl;
                    cout << "\nRoute to be taken:-\n";
                    while(i!=city[from])
                    {
                        res.push(a[record[i].second].city);
                        i = record[i].second;
                    }

                    while(!res.empty())
                    {
                        cout << res.top() << " -> ";
                        res.pop();
                    }
                    cout << to << "\n\n";
                }
                else{cout << "No Way Possible" << endl;}
                break;
            }

        case 2:
            {
                string c, t;
                int dist;
                cout << "Enter new city you want to add OR Enter city with which you want to connect other cities\n>>";
                cin >> c;

                if(city.find(c) == city.end())
                {
                    file.open("cities.txt", std::ios_base::app);
                    file << "\n" << c;
                    no_nodes++;
                    a[no_nodes].city = c;
                    city.insert(pair<string, int>(c, no_nodes));
                    cout << "\nCity Added.....\n";
                    file.close();

                    while(1)
                    {
                        cout << "Enter the city to be connected with " << c << " OR to exit from city adding proccess enter -1:: ";
                        cin >> t;
                        if(t == "-1")
                        {
                            break;
                        }
                        else if(city.find(t) == city.end())
                        {
                            cout << t << " city doesnt exist in database\ntry another city to connect with " << c << "\n";
                        }
                        else
                        {
                            file.open("route.txt", std::ios_base::app);
                            file << "\n" << city[c] << "\n" << city[t];
                            cout << "please enter distance in Km between " << c << " and " << t << ":: ";
                            cin >> dist;
                            file << "\n" << dist;

                            undirectedAdd(a, city[c], city[t], dist);
                            file.close();
                        }
                    }
                }
                else
                {
                    cout << "\n" << c << " already exists....\n";
                    while(1)
                    {
                        cout << "\nEnter city you want to connect with " << c << " or to exit connecting process enter -1>> ";
                        cin >> t;
                        if(city.find(t) == city.end())
                        {
                            cout << "\n\n" << t << " city doesnt exist, enter another one\n";
                        }
                        else
                        {
                            std::vector<int>::iterator it;
                            it = std::find(a[city[c]].next.begin(), a[city[c]].next.end(), city[t]);
                            if(t == "-1")
                            {
                                break;
                            }
                            else if(it != a[city[c]].next.end())
                            {
                                cout << "Connection between " << c << " and " << t << " already exist\n";
                            }
                            else
                            {
                                file.open("route.txt", std::ios_base::app);
                                file << "\n" << city[c] << "\n" << city[t];
                                cout << "\nplease enter distance in Km between " << c << " and " << t << ":: ";
                                cin >> dist;
                                file << "\n" << dist;

                                undirectedAdd(a, city[c], city[t], dist);
                                file.close();
                            }
                        }
                    }
                }
                break;
            }

        case 3:
            {
                cout << "List of the cities::\n";
                file.open("cities.txt", ios::in);
                if(file.is_open())
                {
                    string s;
                    while(getline(file, s))
                    {
                        cout << s << endl;
                    }
                }
                file.close();
                break;
            }

        case 4:
            {
                cityStats(a, no_nodes);
                break;
            }
        case 5:
            break;
        }
    }
}
