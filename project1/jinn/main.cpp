/**
 *  CS251 - Spring 2016: Project 1 Solution
 */

#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
    
        FILE *inputfile = stdin;
        FILE *outputfile = stdout;
    
        //number will be read
	int a;
	//see how many columns
	int col;
	//to see the last number of row
	int count = 0;
	int i = 0;
	//calculate how many dashes should use
	int dashes = 0;
	//print top dashes
	cin >> a;
	col = a;
	dashes = a*6-3;
	for(i; i<dashes;i++){
		cout<<'-';
	}
	i = 0;
	cout << '\n';
	while(cin >> a){
		cout << setw(3) << a << ' ' << "|" << ' ';
		count ++;
		if(count == col-1){
			cin >> a;
			cout<< setw(3) << a << '\n';
			count = 0;
		}
	}
	//print bottom dashes
        for(i = 0; i<dashes;i++){
    	    cout<<'-';
        }
        fclose(inputfile);
        fclose(outputfile);

    /* Exit the program */
        return 0;
}
