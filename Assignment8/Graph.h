//********************************************************************
// ASU CSE310 Assignment #8 Spring 2022
// Name of Author: Stephen Austria
// ASU ID: 1220159551
// Description: This is the header file that defines an undirected graph
//              with an array of vertices and edges
//********************************************************************

//include necessary header file here
#include "Edge.h"

using namespace std;

class Graph
{
private:
    int V, E;         //number of vertices and edges in the graph
    City* cityArr;    //an array of City objects
    Edge* edgeArr;    //an array of Edge objects

public:
    Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
    void destructor();
    void make_set(City* aCity);
    City* find_set(City* aCity);
    void link(City* aCity, City* bCity);
    void Union(City* aCity, City* bCity);
    void SortEdges();

    void MST_Kruskal();

};

Graph::Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray) {

    //new variables
    V = numOfCities;
    E = numOfEdges;
    cityArr = cityArray;
    edgeArr = edgeArray;
}
//destructor
void Graph::destructor() {

    delete[] cityArr, edgeArr;

}
//make a new set
void Graph::make_set(City* aCity) {

    //parent set to itself
    aCity->parent = aCity;
    //rank set to 0
    aCity->rank = 0;
}
//find the root of the set
City* Graph::find_set(City* aCity) {

    //return city, if city is root
    City* city = aCity->parent;

    if (city == aCity) {
        return aCity;
    }
    //recursive call 
    else {
        return find_set(aCity->parent);
    }
}

void Graph::link(City* aCity, City* bCity) {

    double distance = 0.0;
    Edge* myLink = new Edge(aCity, bCity, distance);
}

//function unites sets
void Graph::Union(City* aCity, City* bCity) {

    //root of the city
    City* x = find_set(aCity);
    City* y = find_set(bCity);
    
    if (x == y) {
        return;
    }

    //if x has a higher rank then y parent is the root of x
    if (x->rank > y->rank) {
        y->parent = x;
    }
    //if y has a higher rank then x parent is the root of y
    else if (x->rank < y->rank) {
        x->parent = y;
    }
    //if rank is equal
    else {
        y->parent = x;
        x->rank = x->rank + 1;
    }
}

void Graph::SortEdges() {

    Edge* t;
    int a = 0;

    //sorting edges
    while (a < E) {
        for (int b = a + 1; b < E; b++) {
            if (edgeArr[b].getDistance() < edgeArr[a].getDistance()) {
                t = new Edge(edgeArr[a].getCity1(), edgeArr[a].getCity2(), edgeArr[a].getDistance());
                edgeArr[a] = edgeArr[b];
                edgeArr[b] = *t;
            }
        }
        a++;
    }
}

//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal()
{
    Edge* set = new Edge[E];
 
    int c = 0;
    int a = 0;

    cout << "MST Kruskal Algorithm Result\n" << endl;
    double totalDistance = 0.0;

    //will make a new set 
    while (a < V) {
        make_set(&cityArr[a]);
        a++;
    }

    //edges sorted by weight
    SortEdges();
    
    //assign new sets to itself
    for (int a = 0; a < V; a++) {

        for (int b = 0; b < E; b++) {

            //if names match then city1 is set as parent
            if (cityArr[a].cityName.compare(edgeArr[b].getCity1()->cityName) == 0) {
                edgeArr[b].getCity1()->parent = find_set(&cityArr[a]);
            }
            //if names match then city2 is set as parent
            if (cityArr[a].cityName.compare(edgeArr[b].getCity2()->cityName) == 0) {
                edgeArr[b].getCity2()->parent = find_set(&cityArr[a]);
            }
        }
    }

    //edges to use in MST
    int d = 0;
    while (d < E) {
        //if cities have the same parent
        if (find_set(edgeArr[d].getCity1()) != find_set(edgeArr[d].getCity2())) {
            set[c] = edgeArr[d];
            c++;
            Union(edgeArr[d].getCity1(), edgeArr[d].getCity2());
        } 
        d++;
    }

    //print out the set
    int e = 0;
    while (e < c) {
        set[e].printEdge();
        totalDistance = totalDistance + set[e].getDistance();
        e++;
    } 
    cout << "=================================================" << endl;
    cout << "Total Distance: " << totalDistance << endl;
}
