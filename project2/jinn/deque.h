#include <iostream>

using namespace std;

class Deque
{
	public:
		Deque();
		void enqueue_front(int);
		void enqueue_back(int);
		int dequeue_front();
		int dequeue_back();
		int get_array_size();
		int return_size();
		
	private:
		int * deq;
		int head ;
		int tail ;
		int size;
		int count ;
		void reallocate();
		bool is_full();
};
