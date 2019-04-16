#include <iostream>
#include <vector>

using namespace std;

struct Node{
	struct Node *parent;
	int size;
};


void print_(vector<vector<int> > data){
	int n = data.size()-1;
	cout << endl << "Input mesh" << endl;
	for(int i=1;i<n+1;i++){
		for(int j=0;j<n;j++){
			if(data[i][j]==0){
				cout << " x ";
			}
			else{
				cout << "   ";
			}
		}cout << endl;
	}cout << endl<< endl;
}

void read(vector<vector<int> > &data, int n){
	for(int i=0;i<n;i++){
		vector<int> temp;
		if(data.size()==0){
			for(int j=0;j<n;j++) temp.push_back(1);
			data.push_back(temp);
			temp.clear();
		}

		for(int j=0;j<n;j++){
			int k;
			cin >> k;
			temp.push_back(k);
		}
		data.push_back(temp);
	}
}

vector<vector<Node> > initisets(int n){
	vector<vector<Node> > res(n+1, vector<Node> (n));
	for(int i=0;i<n+1;i++){
		for(int j=0;j<n;j++){
			res[i][j].parent = NULL;
			res[i][j].size = 1;
		}
	}
	return res;
}

Node* findset(vector<vector<Node> > &F, int i, int j){
	Node *temp;
	temp = &F[i][j];
	while(temp->parent!=NULL){
		temp = temp->parent;
	}
	return temp;
}

void mergesets(Node* p, Node* q){
	if(p==q) return;

	Node* temp;
	if(p->size < q->size){
		temp = p;
		p = q;
		q = temp;
	}

	q->parent = p;
	p->size += q->size;
}

void print_1(vector<vector<Node> > F){
	Node *p = findset(F,0,0); 
	cout << p->size << " ";
}

bool mergeregions(vector<vector<int> > data, int n){
	vector<vector<Node> > F = initisets(n);

	for(int i=0;i<n+1;i++){
		for(int j=0;j<n;j++){
			if(data[i][j]){
				//print_1(F);
				if(j-1>=0){
					if(data[i][j-1]) mergesets(findset(F,i,j-1), findset(F,i,j));
					//print_1(F);
					//cout << findset(F,i,j-1) << " "<< findset(F,i,j) << endl;
				}
				if(i-1>=0){
					if(data[i-1][j]) mergesets(findset(F,i-1,j), findset(F,i,j));
				}
			}
		}
	}

	Node* t1,t2;
	t1 = findset(F,0,0);
	for(int i=0;i<n;i++){
		if(data[n][i]){
			if(findset(F,n,i)==t1) return true;
		}
	}
	return false;
}

void findreach(vector<vector<int> > data, int n){
	vector<vector<Node> > F = initisets(n);

	for(int i=0;i<n+1;i++){
		for(int j=0;j<n;j++){
			if(data[i][j]){
				if(j-1>=0){
					if(data[i][j-1]) mergesets(findset(F,i,j-1), findset(F,i,j));
				}
				if(i-1>=0){
					if(data[i-1][j]) mergesets(findset(F,i-1,j), findset(F,i,j));
				}
			}
		}
	}

	cout << "Reachable cells in the mesh" <<endl<<endl;
	for(int i=0;i<n+1;i++){
		for(int j=0;j<n;j++){
			if(data[i][j]==0){
				cout << " x ";
			}
			else if(findset(F,0,0)==findset(F,i,j)){
				cout << " - ";
			}
			else{
				cout << "   ";
			}
		}cout << endl;
	}cout << endl << endl;

}

int main(){
	int n;
	cin >> n;

	vector<vector<int> > data;
	read(data, n);
	print_(data);

	bool a = mergeregions(data, n);

	if(a) cout << "Liquid can seep through the mesh\n\n";
	else cout << "Liquid cannot seep through the mesh\n\n";

	findreach(data,n);
	
	return 0;
}
