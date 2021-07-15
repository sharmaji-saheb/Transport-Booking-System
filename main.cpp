#include <iostream>
#include<vector>
#include<ctime>
#include<queue>
#include<fstream>
#include<unordered_map>
#include<map>
#include<bits/stdc++.h>

using namespace std;

//defining value of infinite
# define inf 0x3f3f3f3f
string months[13]={" ","january","Feburary","March","April","May","June","July","August","September","October","November","December"};



//node for graph
class node
{
public:
    vector<int> next;           //vector for nodes connected to this node
    vector<int> weight;         //vector for storing distance(weight) between two nodes
    vector<int> airCity;        //vector for nodes connected to this node for air route
    vector<int> airDist;        //vector for storing air distance between two nodes
    int haveAirport = 0;        //tells whether this city has airport or not
    string city;                //name of city this node represents

    //establishes two way connection between two nodes
    void add(int i, int w)
    {
        next.push_back(i);
        weight.push_back(w);
    }

    //establishes two way connection between two nodes via air
    void airAdd(int i, int w)
    {
        airCity.push_back(i);
        airDist.push_back(w);
        haveAirport = 1;
    }
};



//to establish two way connection between nodes
void undirectedAdd(node a[],int i, int j, int w)
{
    a[i].add(j,w);
    a[j].add(i,w);
}



void undirectedAirAdd(node a[],int i, int j, int w)
{
    a[i].airAdd(j,w);
    a[j].airAdd(i,w);
}



//dijkstra's algorithm, returns a record of shortest distance of each node from starting node
vector < pair <int, int> > graphSsspDijkstra(node a[], int start, int to,  int n)
{
    int i;
    vector < pair <int, int> > record;              //record of shortest distance of each node from starting node to be returned
    priority_queue < pair <int, int> ,vector <pair <int, int> >, greater <pair <int, int> > > pq;       //priority queue returning lowest value


    //initializing vector record by setting distance of each node from starting node as infinity, and 0 for starting node
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
        if(i==to)
        {
            break;
        }

        auto k = a[i].weight.begin();
        for(auto j = a[i].next.begin(); j!=a[i].next.end(); j++, k++)
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



vector < pair <int, int> > graphSsspDijkstraForSearch(node a[], int start,  int n)
{
    int i;
    vector < pair <int, int> > record;              //record of shortest distance of each node from starting node to be returned
    priority_queue < pair <int, int> ,vector <pair <int, int> >, greater <pair <int, int> > > pq;       //priority queue returning lowest value


    //initializing vector record by setting distance of each node from starting node as infinity, and 0 for starting node
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

        auto k = a[i].weight.begin();
        for(auto j = a[i].next.begin(); j!=a[i].next.end(); j++, k++)
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



void cityStats(node a[], int i)
{

        cout << a[i].city << " is connected with following cities with following distances\n";
        auto k=a[i].weight.begin();
        for(auto j=a[i].next.begin(); j!=a[i].next.end(); j++, k++)
        {
            cout << a[*j].city << " with distance of " << *k << "\n";
        }

        cout << "\n";

    cout << "\n";
}



void airCityStats(node a[], int i)
{

        cout << a[i].city << " is connected with following cities with following distances\n";
        auto k=a[i].airDist.begin();
        for(auto j=a[i].airCity.begin(); j!=a[i].next.end(); j++, k++)
        {
            cout << a[*j].city << " with distance of " << *k << "\n";
        }

        cout << "\n";

    cout << "\n";
}



int findDistance(string from, string to, node a[], map<string, int> city, int no_nodes)
{
    vector < pair <int, int> > record = graphSsspDijkstra(a, city[from], city[to], no_nodes);
    stack<string> res;
    stack<int> distp;

    int i = city[to];
    int temp = record[city[to]].first, temp2;
    if(record[i].first != inf)
    {
        cout << "DISTANCE = " << record[i].first << "Km" << endl;
        cout << "ROUTE::-\n";
        while(i!=city[from])
        {
            res.push(a[record[i].second].city);
            i = record[i].second;
            temp2 = record[i].first;
            distp.push(temp - temp2);
            temp = temp2;
        }

        while(!res.empty())
        {
            cout << res.top() << " ---" << distp.top() << "km-> ";
            res.pop(); distp.pop();
        }
            cout << to << "\n";
    }
    else{cout << "No Way Possible" << endl;}
    return record[city[to]].first;
}



int findDistance_withStops(string from, string to, node a[], map<string, int> city, int no_nodes, vector<string> stops)
{
    int dist = 0;
    string jj = from;
    for(auto ii = stops.begin(); ii != stops.end(); ii++)
    {
        dist = dist + findDistance(jj, *ii, a, city, no_nodes); cout << endl;
        jj = *ii;
    }
    dist = dist + findDistance(jj, to, a, city, no_nodes);
    return dist;
}



void inputCities(string *from, string *to, map<string, int> city)
{
    while(1)
    {
        cout << "FROM:: ";
        cin >> *from;
        if(city.find(*from) != city.end())
        {
            break;
        }
        else
        {
            cout << "\nWe do not provide service in " << *from << endl;
            cout << "enter another city\n";
        }
    }

    while(1)
    {
        cout << "TO:: ";
        cin >> *to;
        if(city.find(*to) != city.end())
        {
            break;
        }
        else
        {
            cout << "\nWe do not provide service in " << *to << endl;
            cout << "enter another city\n";
        }
    }
}



string findNearestAirport(string from, node a[], map<string, int> city, vector<string> airports, int no_nodes, int *distReturn)
{
    vector < pair <int, int> > record = graphSsspDijkstraForSearch(a, city[from], no_nodes);
    int dist = inf;
    string resCity;
    for(auto i = airports.begin(); i != airports.end(); i++)
    {
        if(dist > record[city[*i]].first)
        {
            dist = record[city[*i]].first;
            resCity = *i;
        }
    }
    *distReturn = dist;

    return resCity ;
}



int distBetweenAirports(string from, string to, node a[], map<string, int> city, vector<string> airports, int no_nodes)
{
    auto j = a[city[from]].airDist.begin();
    for(auto i = a[city[from]].airCity.begin(); i!=a[city[from]].airCity.end(); i++, j++)
    {
        if(*i == city[to])
        {
            return *j;
        }
    }
}



vector<string> inputStops(map<string, int> city)
{
    vector<string> res;
    string s = "" ;
    cout << "Enter Stops or To Exit Enter -1\n";
    while(1)
    {
        cout << ">> ";
        cin >> s;
        if(s == "-1")
        {
            break;
        }
        if(city.find(s) == city.end())
        {
            cout << "we dont provide service in " << s << endl;
            continue;
        }
        res.push_back(s);
    }

    return res;
}



class vehicle
{
    int speed;
    int fare_Km;
    int no_Of_Seats;

public:
    int get_speed()
    {
        return speed;
    }

    int get_fare_Km()
    {
        return fare_Km;
    }

    int get_no_of_seats()
    {
        return no_Of_Seats;
    }

    vehicle(int speed,int fare_km,int no_Of_Seats)
    {
        this->speed=speed;
        this->fare_Km=fare_km;
        this->no_Of_Seats=no_Of_Seats;
    }

};



class cab_type:public vehicle
{
    string company;
    string car_type;
    string car_name;
    bool is_ac;

public:
    string get_company()
    {
        return company;
    }

    string get_car_type()
    {
        return car_type;
    }

    string get_car_name()
    {
        return car_name;
    }

    bool get_is_ac()
    {
        return is_ac;
    }

    cab_type(string car_type,string car_name,bool is_ac,int speed,int fare_km,int no_Of_Seats,string company): vehicle(speed,fare_km,no_Of_Seats)
    {
          this->car_type=car_type;
          this->car_name=car_name;
          this->is_ac=is_ac;
          this->company=company;
    }

};



class bus:public vehicle
{

    string company;
    string bus_type;
    bool is_ac;

public:
    string get_company()
    {
        return company;
    }

    string get_bus_type()
    {
        return bus_type;
    }

    bool get_is_ac()
    {
        return is_ac;
    }

    bus(string bus_type,bool is_ac,int speed,int fare_km,int no_Of_Seats,string company): vehicle(speed,fare_km,no_Of_Seats)
    {
          this->bus_type=bus_type;
           this->is_ac=is_ac;
          this->company=company;
    }

};



class Railways:public vehicle
{
    string railway_Name;
    int  lay_Over_time;
    bool is_ac;

public:
    string get_railway_name()
    {
        return railway_Name;
    }

    int get_lay_Over_time()
    {
        return lay_Over_time;
    }

    bool get_is_ac()
    {
        return is_ac;
    }

    Railways(string railway_Name,int lay_Over_time,bool is_ac,int speed,int fare_km,int no_Of_Seats):vehicle(speed,fare_km,no_Of_Seats)
    {
        this->railway_Name=railway_Name;
        this->lay_Over_time=lay_Over_time;
        this->is_ac=is_ac;
    }

};



class Airlines:public vehicle
{
    string name_Airlines;
    int lay_Over_time;
    string type_class;

public:
    string get_name_Airlines()
    {
        return name_Airlines;
    }

    int get_lay_Over_time()
    {
        return lay_Over_time;
    }

    string get_type_class()
    {
        return type_class;
    }

    Airlines(string type_class,string name_Airlines,int lay_Over_time,int speed,int no_Of_Seats,int fare_km):vehicle(speed,fare_km,no_Of_Seats)
    {
        this->name_Airlines=name_Airlines;
        this->lay_Over_time=lay_Over_time;
        this->type_class=type_class;
    }
};



void init_cab_system(vector<cab_type>cabs,string from,string to, node a[], map<string, int> city, int no_nodes)
{
    string stop_option;
    vector<string> stops;
    int distance;
    int areStops = 0;
    cout << "DO YOU WANT TO ADD STOPS??\nY/N>> ";
    cin >> stop_option;
    if(stop_option == "Y")
    {
        stops = inputStops(city);
        areStops = 1;
    }
    cout<<"**** FOLLOWING ARE CABS WE OFFER ****"<<endl;

    for (int i = 0; i < cabs.size(); ++i)
    {
        cout<<i+1<<". "<<cabs[i].get_company()<<"\n   Car Name: "<<cabs[i].get_car_name()<<" \n   Fare/km: "<<cabs[i].get_fare_Km()<<" \n   seats: "<<cabs[i].get_no_of_seats()<<" \n   speed of cab: "<<cabs[i].get_speed()<<endl;

        if(cabs[i].get_is_ac())
        {
            cout<<"   Ac Cab"<<endl;
        }
        else
        {
            cout<<"   Non Ac Cab"<<endl;
        }

        cout<<endl;
    }

    cout<<"\nENTER YOUR CHOICE>> ";
    int i;
    cin>>i;

    cout << "\n\n";

    if(areStops == 1)
    {
        distance = findDistance_withStops(from, to, a, city, no_nodes, stops);
        cout << "\nDISTANCE:: " << distance << endl;
    }
    else
    {
        distance=findDistance(from, to, a, city, no_nodes);
    }
    cout << "\n";
    int time_to_reach=distance/cabs[i-1].get_speed();
     if(time_to_reach==0){
        time_to_reach=1;
    }
    cout<<"FARE WILL BE:: "<<(cabs[i-1].get_fare_Km()*distance)<<endl<<endl;
    cout<<"TOTAL TIME REQUIRED FOR JOURNEY WILL BE "<<time_to_reach<<" hrs "<<endl;
    cout<<endl;

    time_t my_time = time(NULL);
    printf("CURRENT TIME IS %s ", ctime(&my_time));
    cout<<endl;
    tm *local_time = localtime(&my_time);
    cout<<"YOU WILL REACH BY:: ";
    time_t now = time(0);

    tm *ltm = localtime(&now);

    if((time_to_reach+ltm->tm_hour)>24)
    {
        cout<<months[1+ltm->tm_mon]<<" "<<1+ltm->tm_mday<<" "<<(time_to_reach+ltm->tm_hour)%24<< ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<" "<<1900+ltm->tm_year;

    }
    else
    {
        cout<<months[1+ltm->tm_mon]<<" "<<ltm->tm_mday<<" "<<(time_to_reach+ltm->tm_hour)%24<< ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<" "<<1900+ltm->tm_year;
    }
    cout<<endl;
}



void init_bus_system(vector<bus>buses,string from,string to, node a[], map<string, int> city, int no_nodes)
{
    cout<<"**** FOLLOWING ARE BUSES WE OFFER ****"<<endl;

    for (int i = 0; i < buses.size(); ++i)
    {
        cout<<i+1<<". "<<buses[i].get_company()<<": \n   Car Name: "<<buses[i].get_bus_type()<<" \n   Fare/km: "<<buses[i].get_fare_Km()<<" \n   seats: "<<buses[i].get_no_of_seats()<<" \n   speed of bus: "<<buses[i].get_speed()<<endl;

        if(buses[i].get_is_ac())
        {
            cout<<"   Ac Bus"<<endl;
        }
        else
        {
            cout<<"   Non Ac bus"<<endl;
        }

        cout<<endl;
    }

    cout<<"\nENTER YOUR CHOICE>> ";
    int i;
    cin>>i;

    cout << "\n\n";

    int distance=findDistance(from, to, a, city, no_nodes);
    cout << "\n";
    int time_to_reach=distance/buses[i-1].get_speed();
     if(time_to_reach==0){
        time_to_reach=1;
    }
    cout<<"FARE WILL BE:: "<<buses[i-1].get_fare_Km()*distance<<endl<<endl;

    cout<<"TOTAL TIME REQUIRED FOR JOURNEY WILL BE "<<time_to_reach<<" hrs "<<endl;
    cout<<endl;

    time_t my_time = time(NULL);
    printf("CURRENT TIME IS %s ", ctime(&my_time));
    cout<<endl;
    tm *local_time = localtime(&my_time);
    cout<<"YOU WILL REACH BY:: ";
    time_t now = time(0);

    tm *ltm = localtime(&now);

    if((time_to_reach+ltm->tm_hour)>24)
    {
        cout<<months[1+ltm->tm_mon]<<" "<<1+ltm->tm_mday<<" "<<(time_to_reach+ltm->tm_hour)%24<< ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<" "<<1900+ltm->tm_year;
    }
    else
    {
        cout<<months[1+ltm->tm_mon]<<" "<<ltm->tm_mday<<" "<<(time_to_reach+ltm->tm_hour)%24<< ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<" "<<1900+ltm->tm_year;
    }
    cout<<endl;
}



void init_railway_sytem(vector<Railways> Train,string from,string to, node a[], map<string, int> city, int no_nodes)
{
    cout<<"**** FOLLOWING ARE TRAINS WE OFFER ****"<<endl;

    for (int i = 0; i < Train.size(); ++i)
    {
        cout<<i+1<<". "<<Train[i].get_railway_name()<<": \n   Fare/km: "<<Train[i].get_fare_Km()<<" \n   speed: "<<Train[i].get_speed()<<" \n   Lay Over Time: "<<Train[i].get_lay_Over_time()<<endl;
        if(Train[i].get_is_ac())
        {
            cout<<"   Ac Train"<<endl;
         }
        else
        {
            cout<<"   Non Ac Train"<<endl;
        }

        cout<<endl;
     }

    cout<<"\nENTER YOUR CHOICE>> "<<endl;
    int i;
    cin>>i;

    cout << "\n\n";

    int distance=findDistance(from, to, a, city, no_nodes);
    cout << "\n";

    int time_to_reach=distance/Train[i-1].get_speed();
     if(time_to_reach==0){
        time_to_reach=1;
    }
    cout<<"FARE WILL BE:: "<<Train[i].get_fare_Km()*distance<<endl<<endl;

    cout<<"TOTAL TIME REQUIRED FOR JOURNEY WILL BE "<<time_to_reach<<" hrs "<<endl;
    cout<<endl;

    time_t my_time = time(NULL);
    printf("CURRENT TIME IS %s ", ctime(&my_time));
    cout<<endl;
    tm *local_time = localtime(&my_time);
    cout<<"YOU WILL REACH BY:: ";
    time_t now = time(0);

    tm *ltm = localtime(&now);

    if((time_to_reach+ltm->tm_hour)>24)
    {
        cout<<months[1+ltm->tm_mon]<<" "<<1+ltm->tm_mday<<" "<<(time_to_reach+ltm->tm_hour)%24<< ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<" "<<1900+ltm->tm_year;

    }
    else
    {
        cout<<months[1+ltm->tm_mon]<<" "<<ltm->tm_mday<<" "<<(time_to_reach+ltm->tm_hour)%24<< ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<" "<<1900+ltm->tm_year;
    }
    cout<<endl;
}




void  init_Airlines_system(vector<Airlines>planes,string from,string to, node a[], map<string, int> city, vector<string> airports, int no_nodes)
{
    int distReturn = 0;
    string no_airport_option;
    string newFrom = from;
    string newTo = to;

    if(a[city[from]].haveAirport == 0)
    {
        newFrom = findNearestAirport(from, a, city, airports, no_nodes, &distReturn);
        cout << "Sorry airport is not available at " << from <<endl;
        cout << "nearest airport is " << newFrom << " " << distReturn << "km away" << endl;
        cout << "you will need to book vehicle till " << newFrom << ". You can use our services for that" << endl;
        cout << "do you want to continue Y/N>> ";
        cin >> no_airport_option;

        if(no_airport_option == "N")
        {
            return ;
        }
        cout << "\n";
    }

    if(a[city[to]].haveAirport == 0)
    {
        newTo =  findNearestAirport(to, a, city, airports, no_nodes, &distReturn);
        cout << "sorry airport is not available at " << to <<endl;
        cout << "nearest airport is " << newTo << " " << distReturn << "km away" << endl;
        cout << "you will need to book vehicle till " << newTo << ". You can use our services for that" << endl;
        cout << "do you want to continue Y/N>> ";
        cin >> no_airport_option;
        if(no_airport_option == "N")
        {
            return ;
        }
        cout << "\n";
    }

    cout << "\n";

    cout << "**** FOLLOWING ARE AIRPLANES WE OFFER ****" << endl;

    for (int i = 0; i < planes.size(); ++i)
    {
        cout<<i+1<<". "<<planes[i].get_name_Airlines()<<": \n   "<<planes[i].get_type_class()<<"class : \n   Fare/km: "<<planes[i].get_fare_Km()<<" \n   speed: "<<planes[i].get_speed()<<" \n   Lay Over Time: "<<planes[i].get_lay_Over_time()<<endl;

        cout<<endl;
     }

    cout<<"\nENTER YOUR CHOICE>> ";
    int i;
    cin>>i;

    cout << "\n\n";

    int distance=distBetweenAirports(newFrom, newTo, a, city, airports, no_nodes);
    cout << "DISTANCE BETWEEN " << newFrom << " AND " << newTo << " IS:: " << distance << endl;
    cout << "\n";
    int time_to_reach=distance/planes[i-1].get_speed();
    if(time_to_reach==0){
        time_to_reach=1;
    }
    cout<<"FARE WILL BE:: "<<planes[i-1].get_fare_Km()*distance<<endl<<endl;

    cout<<"TOTAL TIME REQUIRED FOR JOURNEY WILL BE "<<time_to_reach<<" hrs "<<endl;
    cout<<endl;

    time_t my_time = time(NULL);
    printf("CURRENT TIME IS %s ", ctime(&my_time));
    cout<<endl;
    tm *local_time = localtime(&my_time);
    cout<<"YOU WILL REACH BY:: ";
    time_t now = time(0);

    tm *ltm = localtime(&now);

    if((time_to_reach+ltm->tm_hour)>24){
    cout<<months[1+ltm->tm_mon]<<" "<<1+ltm->tm_mday<<" "<<(time_to_reach+ltm->tm_hour)%24<< ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<" "<<1900+ltm->tm_year;

    }
    else
    {
        cout<<months[1+ltm->tm_mon]<<" "<<ltm->tm_mday<<" "<<(time_to_reach+ltm->tm_hour)%24<< ":"<<ltm->tm_min << ":"<<ltm->tm_sec<<" "<<1900+ltm->tm_year;
    }
    cout<<endl;
}




void databas_manager(node a[],map<string, int> city,int no_nodes){
    fstream file;
    cout << "*************WELCOME ADMIN*************\n\n";
    int c;
    string from,to;
    string out="-1";
    while(c!=7)
    {
        cout << "CHOOSE:\n1. FIND DISTANCE\n2. ADD A CITY AND IT'S CONNECTIONS WITH OTHER\n3. LIST OF CITIES\n4. DISPLAY ALL THE DIRECTLY CONNECTED CITIES IN DATABASE\n5. AIR CONNECTION\n6. AIR CONNECTION DISPLAY\n7. EXIT\n" << endl;
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

                findDistance(from, to, a, city, no_nodes);

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
                        if(t == out)
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

                        if(t == out)
                        {
                            break;
                        }

                        if(city.find(t) == city.end())
                        {
                            cout << "\n\n" << t << " city doesnt exist, enter another one\n";
                        }
                        else
                        {
                            std::vector<int>::iterator it;
                            it = std::find(a[city[c]].next.begin(), a[city[c]].next.end(), city[t]);

                            if(it != a[city[c]].next.end())
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
                int z=1;
                cout << "List of the cities::\n";
                file.open("cities.txt", ios::in);
                if(file.is_open())
                {
                    string s;
                    while(getline(file, s))
                    {
                        cout << z << ". " << s << endl;
                        z++;
                    }
                }
                file.close();
                break;
            }

        case 4:
            {
                string cccc;
                cin >> cccc;
                cityStats(a, city[cccc]);
                break;
            }
        case 5:
            {
                string c, t;
                int dist;
                cout << "Enter new city you want to add OR Enter city with which you want to connect other cities\n>>";
                cin >> c;

                if(city.find(c) == city.end())
                {
                    file.open("airways.txt", std::ios_base::app);
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
                        if(t == out)
                        {
                            break;
                        }
                        else if(city.find(t) == city.end())
                        {
                            cout << t << " city doesnt exist in database\ntry another city to connect with " << c << "\n";
                        }
                        else
                        {
                            file.open("airways.txt", std::ios_base::app);
                            file << "\n" << city[c] << "\n" << city[t];
                            cout << "please enter distance in Km between " << c << " and " << t << ":: ";
                            cin >> dist;
                            file << "\n" << dist;

                            undirectedAirAdd(a, city[c], city[t], dist);
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

                        if(t == out)
                        {
                            break;
                        }

                        if(city.find(t) == city.end())
                        {
                            cout << "\n\n" << t << " city doesnt exist, enter another one\n";
                        }
                        else
                        {
                            std::vector<int>::iterator it;
                            it = std::find(a[city[c]].airCity.begin(), a[city[c]].airCity.end(), city[t]);

                            if(it != a[city[c]].airCity.end())
                            {
                                cout << "Connection between " << c << " and " << t << " already exist\n";
                            }
                            else
                            {
                                file.open("airways.txt", std::ios_base::app);
                                file << "\n" << city[c] << "\n" << city[t];
                                cout << "\nplease enter distance in Km between " << c << " and " << t << ":: ";
                                cin >> dist;
                                file << "\n" << dist;

                                undirectedAirAdd(a, city[c], city[t], dist);
                                file.close();
                            }
                        }
                    }
                }
                break;
            }

        case 6:
            {
                string cccc;
                cin >> cccc;
                airCityStats(a, city[cccc]);
                break;
            }

        case 7:
            break ;
        }

        cout << "**************\n****************\n";
    }

}




int main()
{
    //------------- READING DATASET ----------------------------------------------------------------------------------------------------

    int no_nodes = 0;
    int count;
    node a[1000];                                           //graph initialization
    map<string, int> city;                                  //map for relation between cities and there numbers
    string ssss, op;
    vector < pair <int, int> > record;
    vector<string> airports;

    fstream file;

    //reading file with all cities names
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

    //reading file with all cities names having airports
    file.open("airCities.txt", ios::in);
    if(file.is_open())
    {
        string s;
        while(getline(file, s))
        {
            a[city[s]].haveAirport = 1;
            airports.push_back(s);
        }
    }
    file.close();

    int rcount = 1, fr, t;
    int r;
    int we;

    //reading file with routes, ie edges for graph
    file.open("route.txt", ios:: in);
    if(file.is_open())
    {
        while(file >> r)
        {
            if(rcount%3 == 1)
            {
                fr = (int)r;
            }
            else if(rcount%3 == 2)
            {
                t = (int)r;
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

    //reading file with air routes, ie edges for graph
    file.open("airways.txt", ios:: in);
    rcount = 1;
    if(file.is_open())
    {
        while(file >> r)
        {
            if(rcount%3 == 1)
            {
                fr = (int)r;
            }
            else if(rcount%3 == 2)
            {
                t = (int)r;
            }
            else
            {
                we = r;
                undirectedAirAdd(a, fr, t, we);
            }
            rcount++;
        }
    }
    file.close();
    //-----------------DATASET READING COMPLETE------------------------------------------------------------------------------------------

    stack<string> res;
    stack<int> distp;
    no_nodes = count-1;
    vector<cab_type> cabs;

    cab_type car1("suv","innova",true,100,20,7,"Tuber_Cabs");//AC innova

    cab_type car2("sedan","swift",true,90,15,4,"Tuber_Cabs");//AC swift
    cab_type car3("hatchback","Wagon-R",false,70,10,4,"Tola_Cabs");//non-AC Wagon-R;

    cabs.push_back(car1);
    cabs.push_back(car2);
    cabs.push_back(car3);

    vector<bus> buses;

    bus bus1("volvo",false,100,2,30,"Indo-Canadian");//non-Ac-bus;
    bus bus2("Mercedes",true,100,3,35,"Indo-Canadian-Mercedes");//Ac-bus;

    buses.push_back(bus1);
    buses.push_back(bus2);

    vector<Airlines> planes;

    Airlines plane1("economy","Indigo",30,400,30,100);
    Airlines plane2("Business","Indigo",30,400,40,200);//business class planes;
    planes.push_back(plane1);
    planes.push_back(plane2);

    vector<Railways>Train;

    Railways train1("shatabdi",20,true,100,1,200);
    Railways train2("JanRath",40,false,80,1,250);//janrath

    Train.push_back(train1);
    Train.push_back(train2);



    cout << "*********************************************************\n**********WELCOME TO TRANSPORT BOOKING SERVICES**********\n*********************************************************\n\n";
    string name,password;
    cout<<"1. ADMIN\n2. USER"<<endl;
    int ch;
    cin>>ch;

    cout << endl;
    if(ch==1)
    {
        cout<<"enter username"<<endl;
        cin>>name;
        cout<<"enter Password"<<endl;
        cin>>password;

        if(password=="1234")
        {
            databas_manager(a,city,no_nodes);
            return 0;
        }
        else
        {
            cout<<"No Access"<<endl;
            return 0;
        }
    }
    cout << "CHOOSE CITY\n";
    cout << "ENTER CITIES\n";
    string from;
    string to;
    // string from,string to;

    inputCities(&from, &to, city);
    //string from,string to=100;
    cout<<endl;
    cout<<endl;
    cout<<endl;


    cout<<"*** PLEASE SELECT MODE OF TRANSPORT ***"<<endl;

    cout<<"1. CABS "<<endl;

    cout<<"2. BUS "<<endl;

    cout<<"3. TRAINS "<<endl;

    cout<<"4. AIRPLANES "<<endl;


    cout<<"\n\nPLEASE SELECT>> ";

    int x;
    cin>>x;
    cout << "\n\n";

    switch(x)
    {
        case 1:
            {
                init_cab_system(cabs,from,to, a, city, no_nodes);
                break;
            }

        case 2:
            {
                init_bus_system(buses,from,to, a, city, no_nodes);
                break;
            }

        case 3:
            {
                init_railway_sytem(Train,from,to, a, city, no_nodes);
                break;
            }

        case 4:
            {
                init_Airlines_system(planes,from,to, a, city, airports, no_nodes);
            }
    }
}

