#include <iostream>
#include <cstdlib>
#include <cstring>

#include "heap.h"

using namespace std;

void CuckooHashing_insert(int ** T1, int ** T2,int max_loop, int num, int & table_length){
		//lookup(num)
		int insert_T1 = num % table_length;
		int insert_T2 = num % (table_length - 1);
		int temp;
		int flag = 0;
		int i = 0;
		int print_flag = 0;
//		cout << "Inside of insert function" << endl;
//		cout << T1 << endl;
//		cout << T2 << endl;
//		cout << insert_T1 << endl;
//		cout << insert_T2 << endl;
		if((*T1)[insert_T1] == num){
			cout << num << " already in T1[" << insert_T1 << "]"<< endl;
		}else if((*T2)[insert_T2] == num){
			cout << num << " already in T2[" << insert_T2 << "]"<< endl;
		}else{
//			cout << "This is before while loop" << endl;
			while(flag == 0){
				for(i ; i < max_loop ; i++){
//					cout << "Inside of for(i;i<max_loop;i++)" << endl;
					if((*T1)[insert_T1] == -1){
						(*T1)[insert_T1] = num;
						flag = 1;
						cout << num << " in T1[" << insert_T1 << "]!" << endl;
						break;
					}else{
						cout << num << " in T1[" << insert_T1 << "]" << endl;
						temp = (*T1)[insert_T1];
						(*T1)[insert_T1] = num;
						num = temp;
						insert_T2 = num % (table_length - 1);
						flag = 0;
					}
					if((*T2)[insert_T2] == -1){
						(*T2)[insert_T2] = num;
						flag = 1;
						cout << num << " in T2[" << insert_T2 << "]!" << endl;
						break;
					}else{
						cout << num << " in T2[" << insert_T2 << "]" << endl;
						temp = (*T2)[insert_T2];
						(*T2)[insert_T2] = num;
						num = temp;
						insert_T1 = num % table_length;
						flag = 0;
					}
				}
				if(flag == 0){
					cout << "maxloop reached" << endl;
					int * T1_rehash = *T1;
					int * T2_rehash = *T2;
					int old_table_length = table_length;
					i = 0;
					table_length = 2*table_length;
					*T1 = new int[table_length];
					*T2 = new int[table_length];
					for(i;i<table_length;i++){
						(*T1)[i] = -1;
						(*T2)[i] = -1;
					}
					i = 0;
					for(i;i<old_table_length;i++){
						if(T1_rehash[i] != -1){
							CuckooHashing_insert(T1,T2,max_loop, T1_rehash[i], table_length);	
						}
						if(T2_rehash[i] != -1){
							CuckooHashing_insert(T1,T2,max_loop, T2_rehash[i], table_length);
						}
					}
					CuckooHashing_insert(T1,T2,max_loop, num, table_length);
					flag = 1;
				}
			}	
		}
	
}

void CuckooHashing() {
    // TODO : add your logic here.
	int table_length;
	int max_loop;
	cin >> table_length >> max_loop;

	int * T1 = new int[table_length];
	int * T2 = new int[table_length];
	int i = 0;
	for(i;i<table_length;i++){
		T1[i] = -1;
		T2[i] = -1;
	}

	char command;
	int num;
	i = 0;

	while (cin >> command){
		cin >> num;
		if(command == 'i'){
			CuckooHashing_insert( &T1, &T2, max_loop , num,table_length);
		}else if(command == 'r'){
			int remove;
			remove = num % table_length;
			if(T1[remove] == num){
				T1[remove] = -1;
				cout << num << " out T1[" << remove << "]"<< endl;
			}else{
				remove = num % (table_length - 1);
				if(T2[remove] == num){
					T2[remove] = -1;
					cout << num << " out T2[" << remove << "]"<< endl;
				}else{
					cout << "no out " << num << endl;
				}
			}
		}else if(command == 'l'){
			int lookup;
			lookup = num % table_length;
			if(T1[lookup] == num){
				cout << num << " at T1[" << lookup << "]"<<endl;
			}else{
				lookup = num % (table_length-1);
				if(T2[lookup] == num){
					cout << num << " at T2[" << lookup << "]"<<endl;
				}else{
					cout << "no " << num << endl;
				}
			}
		}
	}

}

void main_BinaryHeap() {
    // TODO : add your logic here.
	int lines;
	cin >> lines;
	int i = 0;
	char command;
	for(i ; i < lines ; i++){
		cin >> command;
		BinaryHeap *b;
		if(command == 'c'){
			int c_1;
			cin >> c_1;
			if(c_1 == 1){
				b = new BinaryHeap(true);	
			}else if(c_1 == 2){
				b = new BinaryHeap(false);
			}
		}else if(command == 'i'){
			int i_1;
			int i_2;
			cin >> i_1 >> i_2;
			TreeNode * t = new TreeNode(i_1,i_2);
			b->insert(t);
		}else if(command == 'p'){
			TreeNode * t;
			t = b->peak();
			if(t == NULL){
				cout << "empty" << endl;
			}else{
				int p_1;
				int p_2;
				p_1 = t->key;
				p_2 = t->value;
				cout << p_1 << " " << p_2 <<endl;
			}
		}else if(command == 'e'){
			TreeNode * t;
			t = b->extract();
			if(t == NULL){
				cout << "empty" << endl;
			}else{
				int e_1;
				int e_2;
				e_1 = t->key;
				e_2 = t->value;
				cout << e_1 << " " << e_2 << endl;
			}
		}else if(command == 'h'){
			int h_size;
			cin >> h_size;
			int i = 0;
			int h_key;
			TreeNode * node_array = new TreeNode[h_size];
			for(i ; i < h_size ; i++){
				cin >> h_key;
				node_array[i].key = h_key;
				node_array[i].value = 0;
			}
			b->heapify(h_size , node_array);
			
		}else if(command == 's'){
			int s = b->size();
			cout << s << endl;
		}
	}
	cout << endl;
}

void HeapSort() {
    // TODO : add your logic here.
    	int max_or_min;
	int isReverseOrder;
    	cin >> max_or_min;
	if(max_or_min == 1){
		isReverseOrder = 0;
	}else if(max_or_min == 2){
		isReverseOrder = 1;
	}

    	int size;
    	cin >> size;
    	int i = 0;
	int sort_key;
	int sort_value;
	TreeNode * elements = new TreeNode[size];
	for(i ; i < size ; i++){
		cin >> sort_key >> sort_value;
		elements[i].key = sort_key;
		elements[i].value = sort_value;
	}
	char command;
	cin >> command;
	if(command == 'q'){
		heapSort(size,elements,isReverseOrder);
	}
	cout << endl;
}	


/* Main function */
int main(int argc, char** argv) {

    /* Read the option */
    int option;
    std::cin >> option;

    /* Call the respective function */
    switch(option) {

        /* Cuckoo Hashing */
        case 1:
            CuckooHashing();
        break;

        /* Binary Heap */
        case 2:
            main_BinaryHeap();
        break;
        
        case 3:
            HeapSort();
        break;

        /* Wrong option */
        default:
            std::cout << "Wrong option" << std::endl;

    }

    /* Close the program */
	return 0;
}

