 #include <iostream>
 #include <utility>
 
 using namespace std;



 struct ListNode{
 	pair<int,int>data;
	ListNode * next;
 };
 
 class Stack
 {
 	
// 	LinkedList * list;
	int stackSize;
	int top;

	public:
		
		Stack();
		void push(pair<int,int>);
		pair<int,int> pop();
		ListNode *head;
		int pos;
 };

