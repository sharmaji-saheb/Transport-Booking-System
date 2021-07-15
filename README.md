#SIMPLE TRANSPORT BOOKING SYSTEM
Books different vehicles for travelling between cities

This program can find the shortest path and distance between the cities, which is used to calculate fare and time required for travel.
Buses, cabs, trains and airplanes can be booked using this program.
Main concept used in this program is of graph implemented using adjacency list and dijiksrtra's algorithm.
Each node of graph represent a city and edge represent a dirrect road between two cities.
An overlapping graph using same nodes is created for air travel. Since air travel is ussualy done in straight line connecting both cities, no dijikstra's is needed. We can simply use the distance(via straight line) between to city from dataset.

**PLEASE DOWNLOAD THE TXT FILE WITH THE CODE AND PUT THEM IN THE SAME FOLDER WITH CODE AS TXT FILES CONTAINS DATASET**

The initial database contains:- 
119 major cities of india stored in cities.txt file, each of them connected with roads in certain fashion.
There are 1131 edges stored in route.txt file,
7 ciities with airports stored in airCities.txt file.
Distance via air between cities having airports are connected is stored in airways.txt 

**TO DELETE DATASET AND CREATE YOUR OWN, JUST DELETE THE CONTENT OF TXT FILE AND EDIT IT THROUGH PROGRAM. BUT DONT DELETE THE FILES THEMSELVES**

**THANK YOU**
