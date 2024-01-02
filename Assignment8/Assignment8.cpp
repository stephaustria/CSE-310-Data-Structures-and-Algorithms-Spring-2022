//************************************************************************
// ASU CSE310 Assignment #8 Spring 2022
// ASU ID: 1220159551
// Name: Stephen Austria 
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
// //---- is where you need to add your own codes
//**************************************************************************

#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance);
int searchCity(City* oneCityArray, int size, string oneCityName);

int main()
{
    int V, E;        //number of vertices and edges

    //cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;
    cin.ignore(20, '\n');

    //a City array used to store all vertices (Cities) of the graph
    City* cityArray = new City[V];

    //an array used to store all edges of the graph
    Edge* edgeArray = new Edge[E];

    int i = 0, j = 0; //index for cityArray and edgeArray

    //local variables
    City* city1;
    City* city2;
    Edge* aNewEdge;
    int c = 0;      //counts elements in cityArray
    int c2 = 0;     //counts elements in edgeArray

    string oneLine;
    //cout << "Enter one departure and its arrival city info." << endl;
    getline(cin, oneLine);

    while (oneLine.compare("End") != 0)
    {
        //get one line of the input, extract the first token
        //create a City if it doesn't exist in cityArray,
        //insert it inside the cityArray. This will be first point of the 'aNewEdge'

        string departureCity;
        string arrivalCity;
        double distance;
        string delimiter = ",";
        
        //get departure city name
        departureCity = oneLine.substr(0, oneLine.find(delimiter));
        oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());
       
        //new city
        city1 = new City(departureCity);

        //if city does not exist 
        if (searchCity(cityArray, V, departureCity) == -1) {
            cityArray[c] = City(departureCity);
            c++;
        }

        //extract the arrival city info. check whether it exists in
        //cityArray or not, if not, create a new City, add it inside.
        //This city will be the second point of the 'aNewEdge'

        string token = oneLine.substr(0, oneLine.find(delimiter));

        //get all of the arrival cities
        while (token.length() > 1) {
            getArrCityInfo(token, arrivalCity, distance);
            
            //new city
            city2 = new City(arrivalCity);

            //add new city to array 
            if (searchCity(cityArray, V, arrivalCity) == -1) {
                cityArray[c] = City(arrivalCity);
                c++;
            }
            //by using the two cities we got above, create a new edge, add
             //it inside edgeArray
            aNewEdge = new Edge(city1, city2, distance);
            edgeArray[c2] = *aNewEdge;
            c2++;
            oneLine.erase(0, oneLine.find(delimiter) + delimiter.length());
            token = oneLine.substr(0, oneLine.find(delimiter));
        }

        //get next line
        getline(cin, oneLine);
    } //repeat until the 'End'

    //Create a Graph object by using cityArray and edgeArray
    Graph* myGraph = new Graph(V, E, cityArray, edgeArray);

    //Run Kruskal MST algorithm on above graph
    myGraph->MST_Kruskal();

}

//****************************************************************
//By giving a string, for example 'Dallas(1456.5)', this function
//extract the arrival city name 'Dallas' and distance '1456.5'
//Note: the delimeter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance)
{

    string delimiter = "(";
    //get city name
    arrCityName = oneArrCityInfo.substr(0, oneArrCityInfo.find(delimiter));
    oneArrCityInfo.erase(0, oneArrCityInfo.find(delimiter) + delimiter.length());

    delimiter = ")";
    //get city name
    distance = stod(oneArrCityInfo.substr(0, oneArrCityInfo.find(delimiter)));
    oneArrCityInfo.erase(0, oneArrCityInfo.find(delimiter) + delimiter.length());
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCity(City* oneCityArray, int arraySize, string oneCityName)
{
    int a = 0;
    //check to see if the index of the city exists
    while (a < arraySize) {
        if (oneCityArray[a].cityName.compare(oneCityName) == 0) {
            return 1;
        }
        a++;
    }
    //return -1
    return -1;
}
