#include "ExternalSort.h"


/*
	External Sorting algorithm.
	Step 1: Reads the input file one chunk at a time
	Step 2: Sorts each chunk
	Step 3: Writes each chunk to a temporary file
	Step 4: Performs a k-wise merge on the temporary files

*/
void extern_sort(string in_fname, string out_fname,
		string chunk_location, int chunk_size)
{
	int i = 0;
	int j = 0;
	int chunk_num = 1; //was 0
	int flag = 1;
	int num_data_in_chunk = 0;
	stringstream give_chunk_num;
	ifstream input_file;
	ofstream output_file;
	input_file.open(in_fname); 

	string chunk[chunk_size];
	while(flag){
		num_data_in_chunk = 0;
		//reinitialize chunk[]
		for(i ; i < chunk_size; i++){
		//	if(!(chunk[i].empty())){
				chunk[i] = string();
		//	}else{
		//		break;
		//	}
		}
		i = 0;

		for(i; i < chunk_size;i++){
			if(!(input_file >> chunk[i])){
				flag = 0;
				num_data_in_chunk = i;
	//			cout << "Inside of for num_data_in_chunk: " << num_data_in_chunk << endl;
				break;
			}
//			cout << "num_data_in_chunk: " << num_data_in_chunk << endl;
			num_data_in_chunk ++;
	//		cout << "This is i: " << i << " This is chunk[i]"<< chunk[i] << endl;
		}

	//		cout << "num_data_in_chunk: " << num_data_in_chunk << endl;
		if(i != 0){
//			cout << "chunk" << chunk_num <<endl;
	//		cout << "This is before sort()"<<endl;
			sort(chunk,0,chunk_size - 1);
/////			sort(chunk,0,num_data_in_chunk - 1);
//			cout << "chunk_num: " << chunk_num<<endl;
			give_chunk_num << chunk_location <<"chunk" << setfill('0') << setw(5) << chunk_num;
//TEST			cout << give_chunk_num.str() << endl;
		
			output_file.open(give_chunk_num.str()); 
			for(j; j < chunk_size ; j++){
				output_file << chunk[j] << "\n";
			}
			output_file.close();
			i = 0;
			j = 0;
//TEST			cout << chunk_num << endl;
			chunk_num ++;
			give_chunk_num.str("");
		}else{
			break;
		}
	}
	//cout << "This is before K_MERGE()" << endl;
	//cout << "Check parameter for k_merge:\nchunk_location: " << chunk_location << "\nout_fname: " << out_fname << "\nchunk_num: "<< chunk_num << endl;
	if(chunk_num > 99999){
		cerr<<"Out of bound" << endl;
		exit(1);
	}
	k_merge(chunk_location, out_fname,chunk_num-1);
//	k_merge(chunk_location, out_fname,chunk_num);
	input_file.close();
	
} 
				

/*
	Your favorite n*log(n) sorting algorithm.
	Be sure that you use an in-place version of the algorithm.
	i.e. It does not generate a new array to return, but rather
	works by swapping elements in the input array.
	
	Possible options:
		-Quicksort
		-Mergesort
		-Heapsort
		
*/

void sort(string * chunk, int start, int end) {
//	cout << "start: " << start << " end: " << end << endl;
	if(start < end){
		int mid = (start + end + 1)/2;
//TEST		cout << " mid: " << mid << endl;
		sort(chunk,start, mid - 1);
		sort(chunk, mid , end);
		mergeSort(chunk,start,mid,end);
	}
}

void mergeSort(string * chunk, int start, int mid, int end){
	string temp;
	int shift;
	while((start <  mid) && (mid <= end)){
		if(chunk[start].compare(chunk[mid]) <= 0){
			start ++;
		}else if(chunk[start].compare(chunk[mid]) > 0){
			temp = chunk[mid];
			shift = mid - 1;
			while(shift >= start){
				chunk[shift + 1] = chunk[shift];
				shift --;
			}
			chunk[shift + 1] = temp;
			start ++;
			mid++;
		}
	}
}

// Merges the k temporary files
void k_merge(string chunk_location, string out_fname, int num_chunks)
{
	int count_line = 0;
	int i = 0; 
	int j;
	int flag = 1;
	ifstream input_chunk[num_chunks];
	ofstream output_chunk;
	stringstream open_chunk_num;
	string chunk_compare[num_chunks];
	string stringArray_compare;
	string temp;
	int count_empty_string = 0;
	int index_replace;
//	cout << "Inside of k_merge" << endl;

	output_chunk.open(out_fname);

	for(i ; i < num_chunks; i++){
		j = i + 1;
		open_chunk_num << chunk_location <<"chunk" << setfill('0') << setw(5) << j;

//		cout << "open chunk[" << i << "]" << endl;

		input_chunk[i].open(open_chunk_num.str());
		open_chunk_num.str("");
	}
	//i = 0;
	//Store first line for each chunk in to string array
	for(i =0; i < num_chunks; i++){
		input_chunk[i] >> chunk_compare[i];
	}
	
	//i = 0;
	//cout << "BEFORE output_chunk.open()" << endl;
//TESTcout << "chunk_compare[0]" << chunk_compare[0] << " chunk_compare[1]" << chunk_compare[1]<< endl;
//	output_chunk.open(out_fname);
	//cout << "After output_chunk.open()" << endl;
	//cout << output_chunk.is_open() << endl;
	//cout << out_fname << endl;
	while(flag){
//TEST		cout << "inside of while loop" << endl;
		//Find the smallest string in the string array
		index_replace = 0;
		stringArray_compare = chunk_compare[0];
		for(i = 0; i < num_chunks;i++){
/////		cout << "inside of for. this is the string want to comapre: " << chunk_compare[i] << endl;
/////		cout << "This is temp string that take smallest string: " << stringArray_compare << endl;
			if(!chunk_compare[i].empty()){
				if((stringArray_compare.compare(chunk_compare[i]) > 0) || (stringArray_compare.empty())){
			//		temp = stringArray_compare;
					stringArray_compare = chunk_compare[i];
			//		chunk_compare[i] = temp;
					index_replace = i;
//					cout<< "this is inside for that need swap. index_replace: " << index_replace << " i = " << i << endl;
				}
			}else{
				count_empty_string++;
			}

		}
		//i = 0;
		
//		cout << "num_chunks & count_empty_string: " << num_chunks << " & " << count_empty_string  << endl;
		if(count_empty_string == num_chunks){
		//	flag = 0;
			break;
		}

		output_chunk << stringArray_compare << endl; /////////////////"\n"
/////		cout << "index_replace: " << index_replace<<endl;
/////		cout << "This is string stored into the output file: " << stringArray_compare<<endl;	
		//Replace the string we took
		if(!(input_chunk[index_replace] >> chunk_compare[index_replace])){
			chunk_compare[index_replace] = string();
			input_chunk[index_replace].close();			
		}

/////		cout << "index_replace: " << index_replace << " count_empty_string :" << count_empty_string<<endl;
//		cout << "num_chunks: " << num_chunks << endl;
		count_empty_string = 0;
		

	}
	output_chunk.close();
//	cout << "total line: " << count_line<<endl;
//	cout << "END"<<endl;
}
