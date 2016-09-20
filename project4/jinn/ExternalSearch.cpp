#include "ExternalSearch.h"

bool extern_search(string fileName, string toFind)
{
	ifstream fd;
	fd.open(fileName);
	fd.seekg(0,fd.end);
	int total_data = fd.tellg();
	double size = (total_data + 1)/2;
	int get_mid = (total_data + 1)/2;
	fd.seekg((-1)*get_mid,fd.cur);
	string temp;
	char findword;
	int last_n;
	int next_n;
	int word_len;
	int flag = 0;
//	cout << "toFind: " << toFind << endl;
	while(1){
		while((fd.peek() != '\n') && (fd.tellg() != 0)){
			fd.seekg(-1,fd.cur);
		}
		last_n = fd.tellg();
		fd >> temp;
//		cout << "this is temp string: " << temp << endl;
		next_n = fd.tellg();
		word_len = next_n - last_n;
		size = size /2;
//		cout << "size: " << size << " Total_data: " << total_data << endl;
		if(size < 1){
			return false;
		}
		
//		cout << "get_mid before: " << get_mid << endl;
		if(temp.compare(toFind) < 0){
			get_mid =  get_mid + size;
//			cout << "get_mid in >0: " << get_mid << endl;
			fd.seekg(get_mid);
		}else if(temp.compare(toFind) > 0){
			get_mid = get_mid - size;
//			cout << "get_mid in <0: " << get_mid << endl;
			fd.seekg(get_mid);
		}else{
			break;
		}
	}	
	

	return true;
}
