#include <iostream>
#include <vector>
#include <stdlib.h>
#include<bits/stdc++.h>
#include "BB7.h"

using namespace std;

void preorder(BST a){
	cout << a->key << " ";
	if(a->L != NULL) preorder(a->L);
	if(a->R != NULL) preorder(a->R);
}

BST rrotate(BST u){
	BST v=NULL,M=NULL;
	v = u->L;
	if(v->R != NULL) M=v->R;
	v->R = u;
	u->L = M;
	return v;
}

BST lrotate(BST v){
	BST u=NULL, M=NULL;
	u = v->R;
	M = u->L;
	u->L = v;
	v->R = M;
	return u;
}

BST rightskew(BST S, vector<BST> &history){
	BST dummy2, dummy1;
	dummy2 = new BSTnode();

	dummy2->key = INT_MIN;
	dummy2->R = S;
	dummy1 = dummy2;

	while(dummy2->R!=NULL || dummy2->L!=NULL){
		while(dummy2->R->L!=NULL){
			dummy2->R = rrotate(dummy2->R);
			history.push_back(dummy2);
		}
		dummy2 = dummy2->R;
	}
	
	return dummy1;
}

vector<BST> findcorr(BST S, BST T, vector<BST> HT){
	vector<BST> HS_;
	for(int i=0;i<HT.size();i++){
		while(T!=HT[i]) {
			T = T->R;
			S = S->R;
		}
		HS_.push_back(S);
	}
	return HS_;
}

void unskew(vector<BST> &HS_){
	for(int i=HS_.size()-1;i>=0;i--){
		HS_[i]->R = lrotate(HS_[i]->R);
	}
}

int main(){

	int n;
	cin >> n;

	BST S, T;
	registerme(n);
	S = getsourcetree();
	T = gettargettree();

	cout << "+++  Initial tree \n\n";
	cout << "Source : \t";
	preorder(S);
	cout << endl;
	cout << "Target : \t";
	preorder(T);
	cout << endl<<endl;

	vector<BST> HS_,HT, HS;

	S = rightskew(S, HS);
	T = rightskew(T, HT);

	cout << "+++  Right-skewing the trees \n\n";
	cout << "Source : \t";
	preorder(S->R);
	cout << endl;
	cout << "Number of rotations = "<< HS.size() <<"\n";
	cout << "Target : \t";
	preorder(T->R);
	cout << endl;
	cout << "Number of rotations = "<< HT.size() <<"\n";
	cout << endl;

	HS_ = findcorr(S, T, HT);

	cout << "+++ Finding node correspondence\n\n";

	unskew(HT);
	unskew(HS_);

	cout << "+++  Reversing the skewing process \n\n";
	cout << "Source : \t";
	preorder(S->R);
	cout << endl;
	cout << "Target : \t";
	preorder(T->R);
	cout << endl<<endl;

	return 0;
}