#include<bits/stdc++.h>

using namespace std;

struct glass{
	int a;
	int b;
	int c;
};

vector<glass> create_vertices(vector<int> &capacities, vector<int> &init_content, int sum){
	vector<glass> res;
	for(int i=0;i<=capacities[0];i++){
		for(int j=0;j<=capacities[1];j++){
			for(int k=0;k<=capacities[2];k++){
				if((i+j+k==sum) && (i==0 || j==0 || k==0 || i==capacities[0] || j==capacities[1] || k==capacities[2])){
					glass temp;
					temp.a=i; temp.b=j; temp.c=k;
					res.push_back(temp);
				}
			}
		}
	}
	return res;
}

void generate_graph(vector<glass> &possible, vector<int> &capacities, vector<vector<int> > &graph){
	for(int i=0;i<possible.size();i++){
		for(int j=0;j<possible.size();j++){
			glass temp;
			temp.a = possible[i].a - possible[j].a;
			temp.b = possible[i].b - possible[j].b;
			temp.c = possible[i].c - possible[j].c;

			int check_1=0, check_2=0, check_3=0;
			if(temp.a * temp.b * temp.c == 0) check_1 = 1;
			if((temp.a!=0 && possible[j].a==capacities[0]) || 
				(temp.b!=0 && possible[j].b==capacities[1]) ||
				(temp.c!=0 && possible[j].c==capacities[2])) check_2 = 1;
			if((temp.a!=0 && possible[j].a==0) || 
				(temp.b!=0 && possible[j].b==0) ||
				(temp.c!=0 && possible[j].c==0)) check_3 = 1;

			if(check_1 && (check_3 || check_2)) graph[i][j]=1;
		}
	}
}

vector<int> BFS(int n, 
		vector<glass> &possible, 
		int first, 
		int last, 
		vector<vector<int> > &graph, 
		vector<glass> &res, 
		vector<int> &visited){

	vector<int> parent(n);
	queue <int> q1;
	q1.push(first);
	while(q1.size()!=0){
		int k = q1.front();
		if(k==last) break;
		q1.pop();
		visited[k] = 1;
		for(int i=0;i<n;i++){
			if(graph[k][i]==1 && visited[i]!=1){
				visited[i]=1;
				q1.push(i);
				parent[i] = k;
			}
		}
	}
	return parent;
}

void print(vector<glass> &possible){
	int flag=0;
	for(int i=0;i<possible.size();i++){
		flag++;
		cout << "(" << possible[i].a << "," << possible[i].b << "," << possible[i].c << ")  ";
		if(flag==7){
			cout << endl<<"\t";
			flag=0;
		}
	}
	cout << endl;
}

void print_graph(vector<vector<int> > &graph, vector<glass> possible){
	for(int i=0;i<graph.size();i++){
		cout << "\t(" << possible[i].a << "," << possible[i].b << "," << possible[i].c << ")  ->  ";
		for(int j=0;j<graph.size();j++){
			if(graph[i][j]==1){
				cout << "(" << possible[j].a << "," << possible[j].b << "," << possible[j].c << ")  ";
			}
		} cout << endl;
	}
}

int main(){
	vector<int> capacities(3), init_content(3), final_content(3);
	for(int i=0;i<3;i++) cin >> capacities[i];
	for(int i=0;i<3;i++) cin >> init_content[i];
	for(int i=0;i<3;i++) cin >> final_content[i];

	int sum = init_content[0]+init_content[1]+init_content[2];
	if(final_content[0]+final_content[1]+final_content[2]!=sum) cout << "Invalid Input";

	// Part 1
	vector<glass> possible = create_vertices(capacities, init_content, sum);
	glass temp;
	temp.a = init_content[0]; temp.b = init_content[1]; temp.c = init_content[2];
	possible.push_back(temp);
	cout << "+++ The vertices are\n\t";
	print(possible);

	// Part 2
	int n = possible.size();
	vector<vector<int> > graph(n, vector<int> (n));
	generate_graph(possible, capacities, graph);
	cout << "+++ Graph generated\n";
	print_graph(graph, possible);
	cout << endl;


	// Part 3
	int first = possible.size()-1;
	int last = -1;
	for(int i=0;i<n;i++){
		if(final_content[0]==possible[i].a && 
			final_content[1]==possible[i].b && 
			final_content[2]==possible[i].c) last=i;
	}
	vector<int> visited(n);
	vector<glass> res;
	vector<int> result = BFS(n, possible, first, last, graph, res, visited);
	vector<int> final_res;
	int temp1=last;
	while(temp1!=first){
		final_res.push_back(temp1);
		temp1  = result[temp1];
	}
	final_res.push_back(first);
	cout << "\n+++ Make the following moves\n";
	for(int i=final_res.size()-1;i>0;i--){
		cout << "\t(" << possible[final_res[i]].a << "," << possible[final_res[i]].b << "," << possible[final_res[i]].c << ")  ==>  Transfer ";
		int x,y,qt;
		if(possible[final_res[i]].a > possible[final_res[i-1]].a) x = 1;
		if(possible[final_res[i]].b > possible[final_res[i-1]].b) x = 2;
		if(possible[final_res[i]].c > possible[final_res[i-1]].c) x = 3;
		if(possible[final_res[i]].a < possible[final_res[i-1]].a) y = 1;
		if(possible[final_res[i]].b < possible[final_res[i-1]].b) y = 2;
		if(possible[final_res[i]].c < possible[final_res[i-1]].c) y = 3;
		if(x==1) qt=possible[final_res[i]].a - possible[final_res[i-1]].a;
		if(x==2) qt=possible[final_res[i]].b - possible[final_res[i-1]].b;
		if(x==3) qt=possible[final_res[i]].c - possible[final_res[i-1]].c;

		cout << qt << " ml from Glass " << x <<" to Glass " << y <<"  ==>\n";
	}

	cout << "\t(" << possible[last].a << "," << possible[last].b << "," << possible[last].c << ")\n";

	/*cout << "\n+++ Make the following moves\n\t";
	print(res);*/

	return 0;
}


/*
27 28 20
15 13 7
5 10 20
*/