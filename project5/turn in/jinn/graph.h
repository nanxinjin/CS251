#include <iostream>
#include <string>
#include <float.h>


using namespace std;

class Graph
{
	public:
		
		int airport,route;
		float **graph;
		string *airport_index;
		float *ticket;
		int * visited;
		string * pre;
		string * output;
		string * s;
		string * stack1;
		string * stack2;
		// Constructor
		Graph(); 
		
		// Part 1: Find a ticket using Dijkstra
		void find_ticket(string source,string destination); 
		
		// Part 2: Try to do a tour of all cities
		void eulerian_tour(const string &source); 
	
	// Add any needed private methods here
};
