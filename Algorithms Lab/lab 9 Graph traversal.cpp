#include<bits/stdc++.h>

using namespace std;

struct bhulbhulaiya{
	int m;
	int n;
	vector<vector<int> > H;
	vector<vector<int> > V;
	vector<vector<pair<int,int> > > P;
};

bhulbhulaiya* initbhul(int m1, int n1){
	bhulbhulaiya *res;
	res = new bhulbhulaiya();
	res->m = m1;
	res->n = n1;
	vector<vector<int> > temp1(m1-1, vector<int> (n1,1));
	res->H = temp1;
	vector<vector<int> > temp2(m1, vector<int> (n1-1,1));
	res->V = temp2;
	vector<vector<pair<int,int> > > temp3(m1, vector<pair<int,int> > 
												(n1,make_pair(-1,-1)));
	res->P = temp3;
	return res;
}

vector<vector<int> > get_unvisited(vector<vector<int> > &d, int i, int j){
	vector<vector<int> > res;
	vector<int> temp(2);
	int m,n;
	m = i-1; n = j;
	if(m>=0 && d[m][n]==0){
		temp[0]=m; temp[1]=n;
		res.push_back(temp);
	}
	m = i; n = j-1;
	if(n>=0 && d[m][n]==0){
		temp[0]=m; temp[1]=n;
		res.push_back(temp);
	}
	m = i+1; n = j;
	if(m<d.size() && d[m][n]==0){
		temp[0]=m; temp[1]=n;
		res.push_back(temp);
	}
	m = i; n = j+1;
	if(n<d[0].size() && d[m][n]==0){
		temp[0]=m; temp[1]=n;
		res.push_back(temp);
	}
	return res;
}

void DFS(bhulbhulaiya* M, vector<vector<int> > &d, int i, int j){
	/*cout << i << " " << j << endl;
	prnbhul(M);*/
	d[i][j]=1;
	vector<vector<int> > unvist = get_unvisited(d,i,j);
	if(unvist.size()==0) return;

	while(unvist.size()!=0){
		int random = rand() % unvist.size();
		int k = unvist[random][0], l = unvist[random][1];
		int x = min(i,k),y=min(j,l);

		//Parent of (k,l) is (i,j)
		M->P[k][l].first = i;
		M->P[k][l].second = j;

		if(i==k){
			M->V[x][y] = 0;
		}
		if(j==l){
			M->H[x][y] = 0;
		}

		DFS(M,d,k,l);
		unvist = get_unvisited(d,i,j);
	}

}

int check_present(vector<pair<int,int> > res, int i, int j){
	for(int k=0;k<res.size();k++){
		if(res[k].first==i && res[k].second==j) return 1;
	}
	return 0;
}

void prnbhul(bhulbhulaiya* M, vector<pair<int,int> > res){
	int m = M->m;
	int n = M->n;
	vector<vector<int> > H = M->H;
	vector<vector<int> > V = M->V;

	for(int j=0;j<n;j++){
		cout << "+---";
	} cout << "+\n";

	for(int i=0;i<m-1;i++){

		if(check_present(res, i, 0)) cout << "| x ";
		else cout << "|   ";

		for(int j=0;j<n-1;j++){
			string str1 = "   ";
			if(check_present(res,i,j+1)) str1 = " x ";

			if(V[i][j]==1)cout << "|"<<str1;
			else cout << " "<<str1;
		}cout << "|\n";

		for(int j=0;j<n;j++){
			if(H[i][j]==1) cout << "+---";
			else cout << "+   ";
		}cout << "+\n";
	}

	if(check_present(res, m-1, 0)) cout << "| x ";
	else cout << "|   ";
	//cout << "|   ";
	for(int j=0;j<n-1;j++){
		string str1 = "   ";
		if(check_present(res,m-1,j+1)) str1 = " x ";

		if(V[m-1][j]==1) cout << "|"<<str1;
		else cout << " "<<str1;
	}cout << "|\n";

	for(int j=0;j<n;j++){
		cout << "+---";
	} cout << "+\n";
	cout << endl;

}

vector<pair<int,int> > findrani(bhulbhulaiya* M, int a, int b, int c, int d, int m, int n){
	vector<vector<pair<int,int> > > temp3 = M->P;
	vector<pair<int,int> > temp1,temp2,res;
	vector< vector<int> > se1(m, vector<int>(n,0));
	pair<int,int> p;

	p = temp3[a][b];
	while(p.first>=0 && p.second>=0){
		se1[p.first][p.second]=1;
		temp1.push_back(p);
		a = p.first; b = p.second;
		p = temp3[a][b];
	}

	p = temp3[c][d];
	while(p.first>=0 && p.second>=0){
		if(se1[p.first][p.second]==1) break;
		res.push_back(p);
		c = p.first; d = p.second;
		p = temp3[c][d];
	}

	int z = 0;
	while(!(temp1[z].first==p.first && temp1[z].second==p.second)){
		res.push_back(temp1[z]);
		z++;
	}
	res.push_back(p);

	//prnbhul1(M, res);
	return res;
}

int main(){
	srand((unsigned int)time(NULL));

	int m,n;
	vector<pair<int,int> > pair_array;

	cin >> m >> n;

	// Part 1
	bhulbhulaiya* M = initbhul(m,n);

	// Part 2
	cout << "Initial bhul bhulaiya\n";
	prnbhul(M,pair_array);

	// Part 3
	vector<vector<int> > d(m,vector<int>(n,0));
	DFS(M,d,0,0);
	cout << "Created a random bhulbhulaiya\n";
	prnbhul(M, pair_array);

	// Part 4
	int a = rand()%m, b = rand()%n;
	int c = rand()%m, e = rand()%n;

	pair_array = findrani(M,a,b,c,e,m,n);
	cout << "Taking (" << a << "," << b << ") to (" << c  << "," << e << ") a random bhulbhulaiya\n";
	prnbhul(M, pair_array);

	return 0;
}