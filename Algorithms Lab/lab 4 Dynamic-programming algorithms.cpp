#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int to_index(int N, int S){
	if(N>S || N<S*-1) return 0;
	return N+S;
}

void realizable(vector<int> arr, int N, int T){
	int S=0;
	for(int i=0;i<N;i++) S+=arr[i];
	if(T>S || T<S*-1 || T%2!=S%2) { cout << "Not realizable" << endl; return; }

	vector<vector<int> > table(N+1, vector<int> (2*S+1));
	table[0][S] = 1;

	for(int i=1;i<=N;i++){
		for(int j=0;j<2*S+1;j++){
			if(table[i-1][to_index(j-S-arr[i-1], S)]==1 || table[i-1][to_index(j-S+arr[i-1], S)]==1) table[i][j]=1;
		}
	}

	/*for(int i=0;i<=N;i++){
		for(int j=0;j<2*S+1;j++){
			cout << table[i][j] << "\t";
		}
		cout << endl;
	}*/

	if(table[N][to_index(T, S)]==1) {
		cout << "The value " << T << " is realizable." << endl;
	}
	else{
		cout << "The value " << T << " is not realizable." << endl;
	}
}

void showone(vector<int> arr, int N, int T){
	int S=0;
	for(int i=0;i<N;i++) S+=arr[i];
	if(T>S || T<S*-1 || T%2!=S%2) { cout << "Not realizable" << endl; return; }

	vector<vector<int> > table(N+1, vector<int> (2*S+1));
	table[0][S] = 1;

	for(int i=1;i<=N;i++){
		for(int j=0;j<2*S+1;j++){
			if(table[i-1][to_index(j-S-arr[i-1], S)]==1 || table[i-1][to_index(j-S+arr[i-1], S)]==1) table[i][j]=1;
		}
	}


	if(table[N][to_index(T, S)]==1) {
		int temp_count = N+1;
		vector<int> temp;

		int temp1 = T;

		while(temp_count--) {
			temp1 = temp1-arr[temp_count-1];
			if(table[temp_count][to_index(temp1, S)]==1) temp.push_back(-1*arr[temp_count-1]);
			else {
				temp.push_back(arr[temp_count-1]);
				temp1 = temp1+2*arr[temp_count-1];
			}
		}

		for(int i=0;i<N;i++) {
			if(temp[N-i-1]>0) cout<<"+";
			cout << temp[N-i-1];
		}
		cout << " = " << T << endl;
	}

	else{
		cout << "The value " << T << " is not realizable." << endl;
	}

}

void print_all(vector<int> &arr, vector<vector<int> > &table, int N, vector<int> temp, int T, int S){

	if(N==0) {
		int a=0;

		for(int i=temp.size()-1;i>=0;i--){
			a+=temp[i];
			if(temp[i]>0) cout << "+";
			cout << temp[i];
		}
		cout <<" = " << a << endl;
		return;
	}

	int temp1 = T-arr[N-1];
	if(table[N-1][to_index(temp1, S)]==1) {
		temp.push_back(arr[N-1]);
		print_all(arr, table, N-1, temp, T-arr[N-1], S);
	}


	temp1 = T+arr[N-1];
	if(table[N-1][to_index(temp1, S)]==1) {
		temp.pop_back();
		temp.push_back(-1*arr[N-1]);
		print_all(arr, table, N-1, temp, T+arr[N-1], S);
		temp.pop_back();
	}

}

void showall(vector<int> arr, int N, int T){
	int S=0;
	for(int i=0;i<N;i++) S+=arr[i];
	if(T>S || T<S*-1 || T%2!=S%2) { cout << "Not realizable" << endl; return; }

	vector<vector<int> > table(N+1, vector<int> (2*S+1));
	table[0][S] = 1;

	for(int i=1;i<=N;i++){
		for(int j=0;j<2*S+1;j++){
			if(table[i-1][to_index(j-S-arr[i-1], S)]==1 || table[i-1][to_index(j-S+arr[i-1], S)]==1) table[i][j]=1;
		}
	}


	if(table[N][to_index(T, S)]==1) {
		vector<int> temp; 
		print_all(arr, table, N, temp, T, S);
	}

	else{
		cout << "The value " << T << " is not realizable." << endl;
	}

}


int main(){
	// Input
	int N;
	cin >> N;
	vector<int> arr(N);
	for(int i=0;i<N;i++) cin >> arr[i];
	int T;
	cin >> T;

	cout << "+++ Part 1 : Realizability check \n";
	realizable(arr, N, T);
	cout << "\n+++ Part 2 : One Solution \n";
	showone(arr, N, T);
	cout << "\n+++ Part 3 : All Solution \n";
	showall(arr, N, T);
	cout << endl;

	return 0;
}