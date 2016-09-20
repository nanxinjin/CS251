#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Main function for sorting the file
void extern_sort(string in_fname, string out_fname,
		string chunk_location, int chunk_size);

// Pick your favorite n*log(n) sorting algorithm here!		
void sort(string * chunk, int start, int end); 
void mergeSort(string * chunk, int start, int mid, int end);

// Merges the k temporary files
void k_merge(string chunk_location, string out_fname, int num_chunks);
