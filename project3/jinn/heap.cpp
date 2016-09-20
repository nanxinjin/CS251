#include <iostream>
#include <cstdlib>

#include "heap.h"

using namespace std;

    bool TreeNode::operator < (const TreeNode& anotherNode) {
        // TODO : add your logic here.
        return false;
    }
    
    bool TreeNode::operator > (const TreeNode& anotherNode) {
        // TODO : add your logic here.
        return false;
    }
    
    /*
    * If isMaxHeap == true, initialize as a MaxHeap.
    * Else, initialize as a MinHeap.
    */
    BinaryHeap::BinaryHeap(bool isMaxHeap) {
        // TODO : add your logic here.
	root = NULL;
	heap_size = 0;
	this->isMaxHeap = isMaxHeap;
    }
    
    /*
    * Given an array of TreeNode elements, create the heap.
    * Assume the heap is empty, when this is called.
    */
    void BinaryHeap::heapify(int size, TreeNode * nodes) {
        // TODO : add your logic here.
	int i = 0;
	for(i;i<size;i++){
		insert(nodes);
		nodes++;
	}
    }
    
    /*
    * insert the node into the heap.
    * return false, in case of failure.
    * return true for success.
    */

    bool BinaryHeap::insert(TreeNode * node) {
        // TODO : add your logic here.
	if(root == NULL){
		root = node;
		heap_size ++;
		return true;
	}

	TreeNode * n = root;
	int find_last_node[32];
	int a;
	int i = 0;
	int count = 0;
	heap_size = heap_size + 1;
	int temp_size = heap_size;
	while(temp_size != 0){
		a = temp_size%2;
		temp_size = temp_size/2;
		find_last_node[count] = a;
		count++;
	}
	i = count-2;
	for(i ; i >= 1; i--){
		if(find_last_node[i] == 0){
			n = n->leftChild;
		}else{
			n = n->rightChild;
		}
	}
	node->parent = n;
	if(find_last_node[i] == 0){
		n->leftChild = node;
	}else{
		n->rightChild = node;
	}
	int temp_key;
	int temp_value;
	int flag = 0;
	while(n != NULL){
		if(isMaxHeap == 1){
			if(node->key > n->key){
				temp_key = node->key;
				temp_value = node->value;
				node->key = n->key;
				node->value = n->value;
				n->key = temp_key;
				n->value = temp_value;
				node = node->parent;
				n = n->parent;
			}else{
				flag = 1;
				break;
			}		
		}else{
			if(node->key < n->key){
				temp_key = node->key;
				temp_value = node->value;
				node->key = n->key;
				node->value = n->value;
				n->key = temp_key;
				n->value = temp_value;
				node = node->parent;
				n = n->parent;
			}else{
				flag = 1;
				break;
			}
		}
	}

		return true;
    }
    
    /*
     * Return the minimum element of the min-heap [max element of max-heap]
     */
    TreeNode * BinaryHeap::extract() {
        // TODO : add your logic here
	
	if(root == NULL){
//		cout << "empty"<<endl;
		return NULL;
	}
	TreeNode * just_root = root;
	if(heap_size == 1){
		root = NULL;
		heap_size--;
		return just_root;
	}

	TreeNode * n = root;
	int find_last_node[32];
	int a;
	int i = 0;
	int count = 0;
	int temp_size = heap_size;
	int temp_key;
	int temp_value;
	//convert heap_size to binary
	while(temp_size != 0){
		a = temp_size%2;
		temp_size = temp_size/2;
		find_last_node[count] = a;
		count++;
	}
	i = count-2;
	int is_left_or_right;
	//find last node
	for(i ; i >= 0; i--){
		if(find_last_node[i] == 0){
			n = n->leftChild;
			is_left_or_right = 0;
		}else{
			n = n->rightChild;
			is_left_or_right = 1;
		}
	}
	//swap last node and root

	temp_key = root->key;
	temp_value = root->value;
	root->key = n->key;
	root->value = n->value;
	n->key = temp_key;
	n->value = temp_value;

	if(is_left_or_right == 0){
		n->parent->leftChild = NULL;
		n->parent = NULL;
	}else{
		n->parent->rightChild = NULL;
		n->parent = NULL;
	}

	heap_size --;

	TreeNode * m = root;
	while(1){
		if(isMaxHeap == 1){
			if(m->leftChild == NULL && m->rightChild == NULL){
				break;
			}else if(m->leftChild != NULL && m->rightChild == NULL){
				if(m->leftChild->key > m->key){				
					temp_key = m->key;
					temp_value = m->value;
					m->key = m->leftChild->key;
					m->value = m->leftChild->value;
					m->leftChild->key = temp_key;
					m->leftChild->value = temp_value;
					m = m->leftChild;
				}else{
					break;
				}
			}else{
				if((m->leftChild->key > m->key) || (m->rightChild->key > m->key)){
					if(m->leftChild->key > m->rightChild->key){
						temp_key = m->key;
						temp_value = m->value;
						m->key = m->leftChild->key;
						m->value = m->leftChild->value;
						m->leftChild->key = temp_key;
						m->leftChild->value = temp_value;
						m = m->leftChild;
					}else{
					
						temp_key = m->key;
						temp_value = m->value;
						m->key = m->rightChild->key;
						m->value = m->rightChild->value;
						m->rightChild->key = temp_key;
						m->rightChild->value = temp_value;
						m = m->rightChild;
					}
				}else{
					break;
				}
				
			}						
		}else{
		
			if(m->leftChild == NULL && m->rightChild == NULL){
				break;
			}else if(m->leftChild != NULL && m->rightChild == NULL){
				if(m->leftChild->key < m->key){				
					temp_key = m->key;
					temp_value = m->value;
					m->key = m->leftChild->key;
					m->value = m->leftChild->value;
					m->leftChild->key = temp_key;
					m->leftChild->value = temp_value;
					m = m->leftChild;
				}else{
					break;
				}
			}else{
				if((m->leftChild->key < m->key) || (m->rightChild->key < m->key)){
					if(m->leftChild->key < m->rightChild->key){
						temp_key = m->key;
						temp_value = m->value;
						m->key = m->leftChild->key;
						m->value = m->leftChild->value;
						m->leftChild->key = temp_key;
						m->leftChild->value = temp_value;
						m = m->leftChild;
					}else{
					
						temp_key = m->key;
						temp_value = m->value;
						m->key = m->rightChild->key;
						m->value = m->rightChild->value;
						m->rightChild->key = temp_key;
						m->rightChild->value = temp_value;
						m = m->rightChild;
					}
				}else{
					break;
				}
				
			}						
		}
	}
        return n;
    }
    
    /*
     * Return the current size of the Heap.
     */
    int BinaryHeap::size() {
        // TODO : add your logic here.
        return heap_size;
    }
    
    void heapSort(int size, TreeNode * elements, bool isReverseOrder) {
        // TODO : add your logic here.
	BinaryHeap b(isReverseOrder);
	b.heapify(size, elements);
	int i = 0;
	TreeNode * temp;
	for(i ; i < size; i++){
		temp = b.extract();
		cout << temp->key << " " << temp->value << endl; 
	}
    }

    TreeNode*  BinaryHeap::peak(){
    	TreeNode * n = root;
    	return n;
    }
