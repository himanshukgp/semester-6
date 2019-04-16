#include <iostream>
#include <vector>
#include <cmath>
#include "BB5.h"
#include <stdio.h>  
#include <stdlib.h> 

using namespace std;

typedef struct {
STACK F, B;
} QUEUE;

QUEUE QINIT(){
	QUEUE temp;
	temp.F = SINIT();
	temp.B = SINIT();
	return temp;
}

QUEUE ENQUEUE(QUEUE Q, int s){
	Q.B = PUSH(Q.B, s);
	return Q;
}

QUEUE DEQUEUE(QUEUE Q){
	if(ISEMPTY(Q.F)==0){
		Q.F = POP(Q.F);
		return Q;
	}
	else{
		while(ISEMPTY(Q.B)==0){
			Q.F = PUSH(Q.F, TOP(Q.B));
			Q.B = POP(Q.B);
		}
		Q.F = POP(Q.F);
	}
	return Q;
}

void QPRN(QUEUE Q){
	SPRNT2B(Q.F);
	SPRNB2T(Q.B);
	cout << "  ]" <<endl;
}

void SETN(TREE &T){
	TREE p, e;

	e = T;
	p = T;

	while(p!=NULL){
		if(p->L!=NULL) {
			e->N = p->L;
			e = e->N;
		}

		if(p->R!=NULL){
			e->N = p->R;
			e = e->N;
		}
		p = p->N;
	}
}

void TPRNL(TREE T){
	cout << "\t";
	for(int i=0;T!=NULL;i++) {
		cout << T->key << " ";
		T = T->N;
	}
	cout << endl;
}



int main(){
	int n;
	cin >> n;
	QUEUE Q = QINIT();

	cout << "\n\n++ Part 1"<<endl<<endl;

	int count_enq=n,count_deq=n;
	while(count_deq || count_enq){
		int random_num = rand() % 100;
		if(random_num>50 && count_enq>0){
			cout << "\tENQUEUE("<< random_num <<") : \t : Q = \t[";
			Q = ENQUEUE(Q,random_num);
			count_enq--;
		} 
		else if( (ISEMPTY(Q.F)==0 || ISEMPTY(Q.B)==0) & count_deq>0 ){
			cout << "\tDEQUEUE() : \t : Q = \t[" ;
			Q = DEQUEUE(Q);
			count_deq--;
		}
		QPRN(Q);
	}
	cout << endl<<endl;



	cout << "++ Part 2" << endl<<endl;

	TREE T = TGEN(n);
	SETN(T);

	TPRN(T);
	cout << endl;

	TPRNL(T);
	cout << endl;

	return 0;
}