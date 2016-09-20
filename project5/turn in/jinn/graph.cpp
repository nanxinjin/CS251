#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "graph.h"
#include <algorithm>

using namespace std;

/*
	Graph class for use in Project 5.
	
	This provided code does not include any specific data structure
	for storing a graph, only a list of methods that will be called 
	from main. Based on the project handout and the lecture slides,
	select a method for storing the graph and implement it here.

*/

// Constructor for Graph. Read in data from the input
// and set up your data structures here.
Graph::Graph()
{
	int k = 0;

	cin >> airport >> route;
	
	graph = new float * [airport];
	for(k;k<airport;k++){
		graph[k] = new float [airport];
	}
	//initialize graph
	int i = 0;
	int j = 0;
	for(i ; i < airport; i++){
		for(j ; j < airport; j++){
			graph[i][j] = 0;		
		}
	}
	
	//read
	airport_index = new string [airport];
	string input1;
	int input1_index;
	string input2;
	int input2_index;
	ifstream in;
	float price;
	for(i = 0; i < route; i++){
//		cout << "inside of for" << endl;
		cin >> input1 >> input2 >> price;
		//store the airport name in the *airport_index
		for(j = 0; j < airport; j++){
//			cout << "inside of second for" << endl;
			if(input1 == airport_index[j]){
				input1_index = j;
//				cout << "input1 == airport_index[j], j = " << j << endl;
				break;
			}else if(airport_index[j].empty()){
//				cout << "airport_index[j].empty(), j = " << j << endl;
				airport_index[j] = input1;
				input1_index = j;
				break;
			}
		}
		
		for(j = 0; j < airport; j++){
			if(input2 == airport_index[j]){
				input2_index = j;
				break;
			}else if(airport_index[j].empty()){
				airport_index[j] = input2;
				input2_index = j;
				break;
			}
		}
	
//		cout << "before set price" << endl;
//		cout << "input1_index: " << input1_index << "input2_index: " << input2_index << endl;
		graph[input1_index][input2_index] = price;
		graph[input2_index][input1_index] = price;
		
	}
	
	//TEST
	/*for(i = 0;i<airport;i++){
		for(j = 0;j<airport;j++){
			cout << graph[i][j] << endl;
		}
	}
	*/

}

// Code for part 1. Print out the sequence of airports and price
// of the trip.
void Graph::find_ticket( string source,string destination)
{
//	cout << "Inside of find_ticket" << endl;
//	cout << "source: " << source << "\ndestination: " << destination << endl;
	if(source == destination){
		cout << source << " "<< destination << " "<< 0 << endl;	
	}else{
	int i,j;
	int source_index;
	int flag = 1;
	//Store the smallest value using Dijkstra's Algorithm
	//we assume that ticket array has the same index as airport_index
	//airport_index : index: 0    1    2    3    4    5    6    7    8    9  
	//			 A    B    C    D    E    F    G    H    I    J
	//ticket        :	INF  INF  INF  INF  INF  INF  INF  INF  INF  INF		 
	ticket = new float[airport]; 
	
	//Set every airport to infinite before we have a original airport
	for(i = 0;i<airport;i++){
		ticket[i] = FLT_MAX;
	}

	//Find the original airport index in  the airport_index
	//Can not handle input error, if want can add flag
	for(j = 0; j < airport ; j++){
		if(source == airport_index[j]){
			source_index = j;
			break;
		}	
	}

	//set original airport weight to 0.
	//airport_index : index: 0    1    2    3    4    5    6    7    8    9  
	//			 A    B    C    D    E    F    G    H    I    J
	//ticket        :	INF  INF   0   INF  INF  INF  INF  INF  INF  INF		 
	ticket[source_index] = 0;
		
	float small = FLT_MAX;
	int small_index = -1;
	float temp;
	int temp2 = 0;

	//Initialize visited
	visited = new int[airport];
	for(i = 0;i<airport;i++){
		visited[i] = 0;
	}
	int counter = 0;
	
	pre = new string[airport];
//	cout << "pre[0]: " << pre[0] << endl;

	string small_airport;
	
	//Break while when we find the destination or no other place we can go
	while(flag){
		//Find the smallest value first
		//cout << "Inside of while" << endl;
		for(i = 0; i < airport ; i++){
			if((small > ticket[i]) && (visited[i] != 1)){
				small = ticket[i];
				small_index = i;
			}

		//	cout << "Inside of for" << endl;
		}
				
		if(small_index == -1){
			break;
		}
//		cout << "before small_airport=" << endl;
		small_airport = airport_index[small_index];
//		cout << "airport_index[small_index]: " << airport_index[small_index] << endl;
		//check if destination is already the smallest price for ticket
		if(small_airport == destination){
			
//			cout << "Inside of if" << endl;
			flag = 0;
			break;
		}else{
//			cout << "Inside of else" << endl;
			for(i = 0; i<airport; i++){
				if(visited[i] == 0){
					if(graph[small_index][i] != 0){
						temp = ticket[small_index] + graph[small_index][i];
						if(temp < ticket[i]){
							ticket[i] = temp;
							pre[i] = small_airport;
						}
					}
				}
			}

			//set the airport to already visited
		//	ticket[small_index] = -1;
		//	counter++;
		}


		visited[small_index] = 1;	
		small = FLT_MAX;
		small_index = -1;

	}
	

	if(small_index == -1){
		cout << "not possible" << endl;
	}else{
		output = new string[airport];
		while(pre[small_index] != source){
			output[counter]	= pre[small_index];
			for(i = 0; i< airport;i++){
				if(pre[small_index] == airport_index[i]){
					small_index = i;
					counter++;
					break;
				}
			}
		}

		cout << source << " ";

		for(i = counter - 1;i>=0;i--){
			cout << output[i] << " ";
		}

		cout << destination << " "; 
		cout<< setprecision(2) << fixed << small << endl;
	}
}

}

// Code for part 2. Print out the tour sequence or "not possible"
// if not all cities can be visited.
void Graph::eulerian_tour(const string &source)
{

//	cout << "source: " << source << "\ndestination: " << destination << endl;
	int i,j;
	int k = 0;
	int source_index;
	int flag = 1;
	int flag2 = 0;
	int count_num = 0;
	ticket = new float[airport]; 
	
	for(i = 0;i<airport;i++){
		ticket[i] = FLT_MAX;
	}

	for(j = 0; j < airport ; j++){
		if(source == airport_index[j]){
			source_index = j;
			break;
		}	
	}

	ticket[source_index] = 0;
		
	float small = FLT_MAX;
	int small_index = -1;
	float temp;
	int temp2 = 0;

	//Initialize visited
	visited = new int[airport];
	for(i = 0;i<airport;i++){
		visited[i] = 0;
	}
	int counter = 0;
	
	pre = new string[airport];
//	cout << "pre[0]: " << pre[0] << endl;

	string small_airport;
	//Break while when we find the destination or no other place we can go
	while(flag){
		for(i = 0; i < airport ; i++){
			if((small > ticket[i]) && (visited[i] != 1)){
				small = ticket[i];
				small_index = i;
				flag2 = 1;
			}

		}
				
		if(small_index == -1){
			break;
		}
		small_airport = airport_index[small_index];
		for(i = 0; i<airport; i++){
			if(visited[i] == 0){
				if(graph[small_index][i] != 0){
					temp = graph[small_index][i];
					if(temp < ticket[i]){
						ticket[i] = temp;
						pre[i] = small_airport;
					}
				}
			}
		}

			//set the airport to already visited
		//	ticket[small_index] = -1;
		count_num++;
		


		visited[small_index] = 1;
		k++;
		small = FLT_MAX;
		temp2 = small_index;
		small_index = -1;

	}

//OUTPUT PART-------------------------------------------------------------
	
		
/*	cout << "count_num: " << count_num << endl;
	cout << "source_index: " << source_index << endl;
	cout << "temp2: " << temp2 << endl;
	cout << "aiport which is the last vertice: " << airport_index[temp2] << endl;
	cout << "-------TEST-------" << endl;
	for(i = 0;i<airport;i++){
		cout << "airport_index[" << i << "]: " << airport_index[i]<<endl;
		cout << "Ticket[" << i <<"]: " << ticket[i]<<endl;
		cout << "pre[" << i <<"]: " << pre[i] << endl;
		cout << "visited[" << i <<"]: " << visited[i] << endl;
	}
*/
	counter = 0;
	int index_temp = source_index;
	int s1 = 0;
	int s2 = 0;
	flag = 1;
	int a;
	string swap;
//	cout << "k: " << k << " airport: " << airport << endl;
//	if(k != airport){
//		flag = 0;
//	}


//	for(i;i<airport;i++){
	
//	}
	for(i = 0; i<airport;i++){
//		cout << "visited[" << i << "]: " << visited[i] << endl;

//		cout << "pre[" << i << "]: " << pre[i] << endl;
		if(visited[i] == 0){
			flag = 0;
			break;
		}
	}

	for(i = 0; i<airport;i++){
		if(pre[i] == airport_index[i]){
			flag = 0;
			break;
		}
	}

/*
	cout << "count_num: " << count_num << endl;
	cout << "source_index: " << source_index << endl;
	cout << "temp2: " << temp2 << endl;
	cout << "aiport which is the last vertice: " << airport_index[temp2] << endl;
	cout << "-------TEST-------" << endl;
	for(i = 0;i<airport;i++){
		cout << "airport_index[" << i << "]: " << airport_index[i]<<endl;
		cout << "Ticket[" << i <<"]: " << ticket[i]<<endl;
		cout << "pre[" << i <<"]: " << pre[i] << endl;
		cout << "visited[" << i <<"]: " << visited[i] << endl;
	}

*/

//	cout << "flag: " << flag<<endl;
	if(flag == 0){
		cout << "not possible" << endl;
	}else{
		output = new string[airport];
		stack1 = new string[airport];
		stack2 = new string[airport];
		
		cout << airport_index[source_index] << endl;
		while(1){
			for(i = 0; i < airport;i++){
				if(pre[i] == airport_index[index_temp]){
					stack1[s1] = airport_index[i];
					s1 ++;
				}
			}
			
		//	if(s1 > 0){
				sort(stack1,stack1 + s1);
				/////////////////TEST
		//		cout << "TEST sort and stack1"<<endl;
		//		for(j = s1 - 1;j>=0;j--){
		//			cout <<"Stack1: "<< stack1[j]<<endl;
		//		}
				/////////////////////

				for(j = s1-1; j >= 0 ;j--){
					
					stack2[s2] = stack1[j];
					stack1[j] = "";
					s2 ++;
				}
				s1 = 0;
				////////////////TEST
		//		a = s2;
			
		//		for(j = 0; j < a ; j++){
					
		//			cout << "Stack2:" << stack2[j] << endl;
		//		}
				/////////////////////
			
		//	}
			s2--;
			if(s2 < 0){
				break;
			}
			cout << stack2[s2] << endl;
			for(i = 0;i < airport;i++){
				if(airport_index[i] == stack2[s2]){
					index_temp = i;
					break;
				}
			}
			stack2[s2] = "";
			
			s1 = 0;

		}


		//	for(i = 0; i < airport;i++){
		//		if((graph[index_temp][i] != 0) && (pre[i] == airport_index[index_temp])){
		//			s[counter] = airport_index[i];
		//			counter++;
		//		}
		//	}
		//	cout << airport_index[index_temp] << endl;
		//	sort(s,s+counter);
		//	for(){}
	}
//
//		/////TEST
		//	for(j = 0;j<counter;j++){
		//		cout << "s["<< j <<"]: " << s[j] << endl;
		//	}

//	}


}
