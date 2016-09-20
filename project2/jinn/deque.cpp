#include <iostream>
#include "deque.h"

using namespace std;

Deque::Deque()
{
	//TODO: Write the Deque constructor
	//NOTE: Start with an array of size 10!
	size = 10;
	deq = new int[size];
	head = 0;
	tail = 0;
	count = 0;
}

void Deque::enqueue_front(int n)
{
	//TODO: Front enqueue method
       if (is_full() == true){
       	 reallocate();
       }
       head--;
       if(head < 0){
           head = size - 1;
       }
       deq[head] = n;
       count ++;
}

void Deque::enqueue_back(int n)
{
	//TODO: Back enqueue
	if(is_full() == true){
		reallocate();
	}
	is_full();
	deq[tail] = n;
	tail++;
	if(tail >= size){
		tail = 0;
	}
	count++;
}

int Deque::dequeue_front()
{
	//TODO: front dequeue
	if(count <= 0){
		return -1;
	}
	int pop = deq[head];
	head ++;
	if(head >= size){
		head = 0;
	}
	count--;
	return pop;
}

int Deque::dequeue_back()
{
	//TODO: back dequeue
	if(count <= 0){
		return -1;
	}
	tail--;
	if(tail < 0){
	    	tail = size-1;
	}
	int pop = deq[tail];
	count--;
	return pop;
}

bool Deque::is_full()
{
	//TODO: Determine if you need to double the array
	if(count == size){
		return true;
	}else{	
		return false;
	}
}

void Deque::reallocate()
{
	//TODO: Correctly reallocate memory for the deque. Use the doubling strategy.
	int i = head;
	int j = tail;
	int k = size;
	size = size * 2;
	int * temp = deq;
	deq = new int[size];
	int copy = 0;
	for(i; i < k; i++){
		deq[copy] = temp[i];
		copy++;
	}
	i = 0;
	for(i;i<j;i++){
		deq[copy] = temp[i];
		copy++;
	}
	head = 0;
	tail = k;

}

int Deque::return_size(){
	int a = size;
	return a;
}
