#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

int main(){

	int i = 0;
	int j = 0;
	int chunk_num = 0;
	int flag = 1;
	stringstream give_chunk_num;
	ifstream input_file;
	ofstream output_file;
	input_file.open("mytest.txt"); //in_fname

	int chunk_size = 3;	//
	string chunk_location = "./"; //

	string chunk[chunk_size];
	while(flag){
		for(i; i < chunk_size;i++){
			if(!(input_file >> chunk[i])){
				flag = 0;
				break;
			};
			cout << chunk[i] << endl;
		}
		if(i != 0){
			cout << "chunk" << chunk_num <<endl;
			give_chunk_num << chunk_location <<"chunk" << setfill('0') << setw(5) << chunk_num;
			cout << give_chunk_num.str() << endl;
		
			output_file.open(give_chunk_num.str()); 
			for(j; j < chunk_size ; j++){
				output_file << chunk[j] << "\n";
			}
			output_file.close();
			i = 0;
			j = 0;
			cout << chunk_num << endl;
			chunk_num ++;
			give_chunk_num.str("");
		}else{
			break;
		}
	}
	input_file.close();
	return 1;
}

