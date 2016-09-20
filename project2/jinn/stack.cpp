 #include "stack.h"
 #include <utility>
 
 using namespace std;

void llist_insert_first(Stack *s,pair<int,int>p) {
	
	ListNode * e1;
	ListNode * e;
	e1 = NULL;
	e = s->head;
	if(e == NULL){
		e = new ListNode();
		s->head = e;
		e->data = p;
		s->pos++;

	}else{
		e1 = new ListNode();
		e1->data = p;
		s->head = e1;
		e1->next = e;
		s->pos++;
	}


}

int llist_remove_first(Stack *s,pair<int,int>*p) {
	ListNode * e;
	e = s->head;
	if(e == NULL){
		return 0;
	}else{
		*p = e->data;
		s->pos--;
	}
	s->head = e->next;
	free(e);
	return 1;
	
}

 Stack::Stack()
 {
	 //TODO: Write the constructor
	head = NULL;
	pos = -1;
 }
 
 void Stack::push(pair<int,int>p)
 {
	 //TODO: Write the push method
	llist_insert_first(this,p);	
 }
 
 pair<int,int> Stack::pop()
 {
	 //TODO: Write the pop method
	pair<int,int>p;
	if( llist_remove_first(this,&p) == 0){
		return pair<int,int>(-1,-1);
	}else {
	 	return p;
	 }
 }
