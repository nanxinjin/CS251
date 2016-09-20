#include <iostream>
#include <string>
#include "ExternalSort.h"
#include "ExternalSearch.h"

using namespace std;

int main(int argc, const char* argv[])
{	
	if(argv[1] == string("1")) // Run P4 Part 1
	{
		string in_fname = argv[2];
		string out_fname = argv[3];
		int chunk_size = stoi(argv[4]);
		string chunk_location = argv[5];
		extern_sort(in_fname, out_fname, chunk_location,chunk_size);
	}
	else if(argv[1] == string("2"))
	{
		int word_num = argc - 3;
		int i = 0;
		string fileName = argv[2];

		for(i;i<word_num;i++){
			string toFind = argv[i + 3];
			if(extern_search(fileName,toFind)){
				cout << "found" << endl;	
			}else{
				cout << "missing" << endl;
			}
		}
	}
	return 0;
}
