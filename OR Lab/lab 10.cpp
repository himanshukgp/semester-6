#include<bits/stdc++.h>

using namespace std;

double value1,value2,value3;

vector<int> find_next_NW(vector<vector<double> > &A, int i, int j, int m, int n){
	vector<int> res(2);

	if(A[i][n]==0){
		res[1]=j;
		res[0]=i+1;
	}
	else if(A[m][j]==0){
		res[0] = i;
		res[1]=j+1;
	}
	return res;
}

int min_(int a, int b){
	if(a<b) return a;
	return b;
}

void iterate(vector<vector<double> > &A, vector<vector<double> > &res, int i, int j, int m, int n){
	int to_sub = min_(A[i][n], A[m][j]);
	res[i][j] = to_sub;
	A[i][n] = A[i][n] - to_sub;
	A[m][j] = A[m][j] - to_sub;
	A[m][n] = A[m][n] - to_sub;
}

int not_end(vector<vector<double> > &A, int m, int n){
	int flag = 0;

	for(int i=0;i<m;i++){
		if(A[i][n]!=0) flag = 1;
	}
	for(int i=0;i<n;i++){
		if(A[m][i]!=0) flag = 1;
	}
	return flag;
}

void find_value(vector<vector<double> > &res, vector<vector<double> > &A, int m, int n, int val1){
	int val = 0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			val+=res[i][j]*A[i][j];
		}
	}
	if(val1==1) value1 = val;
	if(val1==2) value2 = val;
	if(val1==3) value3 = val;
}

vector<vector<double> > North_West(vector<vector<double> > A, int m, int n){
	vector<vector<double> > res(m+1, vector<double>(n+1));

	int i=0,j=0;
	while(not_end(A,m,n)){
		iterate(A,res,i,j,m,n);
		vector<int> temp = find_next_NW(A,i,j,m,n);
		i = temp[0];
		j = temp[1];
	}
	find_value(res, A, m, n, 1);
	return res;
}

vector<vector<int> > find_indx_utility(vector<vector<double> > &A, int m, int n){
	vector<vector<int> > temp;
	vector<int> temp1;

	int min=A[0][0];

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(A[i][j]<min) min = A[i][j];
		}
	}

	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(A[i][j]==min) {
				temp1.clear();
				temp1.push_back(i);
				temp1.push_back(j);
				temp.push_back(temp1);
			}
		}
	}

	return temp;
}

int find_best(vector<vector<double> > &A, vector<vector<int> > &temp, vector<int> &temp1, int m, int n){
	int k = temp.size();
	vector<double> min_val(k);

	for(int i=0;i<k;i++) min_val[i] = min_(A[m][temp[i][1]], A[temp[i][0]][n]);

	int max = min_val[0];
	for(int i=0;i<k;i++) if(min_val[i]>max) max = min_val[i];
	if(max==0) return -1;
	for(int i=0;i<k;i++){
		if(min_val[i]==max){
			temp1[0] = temp[i][0];
			temp1[1] = temp[i][1];
			A[temp1[0]][temp1[1]] = INT_MAX;
			return 0;
		}
	}
}

vector<int> find_min_indexes(vector<vector<double> > &A, int m, int n){
	vector<int> temp1(2);

	int flag = 1;
	while(flag==1){
		vector<vector<int> > temp = find_indx_utility(A,m,n);
		int k = temp.size();
		cout << "y1\n";
		int flag1 = 1;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(A[i][j]!=INT_MAX) flag1=0;
			}
		}
		if(flag1==0) break;

		flag = 0;
		flag = find_best(A,temp,temp1,m,n);
		if(flag==-1){
			for(int i=0;i<k;i++){
				A[temp[i][0]][temp[i][1]] = INT_MAX;
			}
			flag = 1;
		}
		else{
			flag=0;
		}
	}
	return temp1;
}

vector<int> find_next_MMin(vector<vector<double> > &A, int i, int j, int m, int n){
	vector<int> res;
	res = find_min_indexes(A, m, n);
	return res;
}

void print_matrix(vector<vector<double> > &A, int m, int n){
	cout << endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout << A[i][j] << "\t";
		}cout << endl;
	}
	cout << endl;
}

vector<int> find_next_MMin1(vector<vector<double> > &A, int i, int j, int m, int n){
	vector<int> res(2);

	while(1){
		int flag2 = 0;

		vector<vector<int> > temp = find_indx_utility(A,m,n);
		int k = temp.size();
		for(int i=0;i<k;i++){

			int temp3 = min_(A[temp[i][0]][n], A[m][temp[i][1]]);

			if( temp3 != 0){
				res[0] = temp[i][0];
				res[1] = temp[i][1];
				A[temp[i][0]][temp[i][1]]  = INT_MAX;
				flag2 = 1;
				break;
			}

			A[temp[i][0]][temp[i][1]]  = INT_MAX;
		}
		if(flag2) break;
	}
	return res;
}

vector<vector<double> > Matrix_Min(vector<vector<double> > A, int m, int n){
	vector<vector<double> > res(m+1, vector<double>(n+1));
	vector<vector<double> > A1(m+1, vector<double>(n+1));
	for(int i=0;i<m+1;i++){
		for(int j=0;j<n+1;j++){
			A1[i][j] = A[i][j];
		}
	}

	int i=0,j=0;

	int k1=0;
	while(not_end(A,m,n)){
		/*k1++;
		if(k1>7) break;*/

		//print_matrix(A,m+1,n+1);
		vector<int> temp = find_next_MMin1(A,i,j,m,n);
		i = temp[0];
		j = temp[1];
		iterate(A,res,i,j,m,n);
	}
	find_value(res, A1, m, n, 2);
	return res;
}






#define TRUE 1
#define FALSE 0

#define MAX 100
 
int supply[MAX];
int demand[MAX];
int N_ROWS, N_COLS;
int costs[MAX][MAX];
 
bool row_done[MAX] = { FALSE };
bool col_done[MAX] = { FALSE };
 
void diff(int j, int len, bool is_row, int res[3]) {
    int i, c, min1 = INT_MAX, min2 = min1, min_p = -1;
    for (i = 0; i < len; ++i) {
        if((is_row) ? col_done[i] : row_done[i]) continue;
        c = (is_row) ? costs[j][i] : costs[i][j];
        if (c < min1) {
            min2 = min1;
            min1 = c;
            min_p = i;
        }
        else if (c < min2) min2 = c;
    }
    res[0] = min2 - min1; res[1] = min1; res[2] = min_p;
}
 
void max_penalty(int len1, int len2, bool is_row, int res[4]) {
    int i, pc = -1, pm = -1, mc = -1, md = INT_MIN;
    int res2[3];
 
    for (i = 0; i < len1; ++i) {
        if((is_row) ? row_done[i] : col_done[i]) continue;
        diff(i, len2, is_row, res2);
        if (res2[0] > md) {
            md = res2[0];  /* max diff */
            pm = i;        /* pos of max diff */
            mc = res2[1];  /* min cost */
            pc = res2[2];  /* pos of min cost */
        }
    }
 
    if (is_row) {
        res[0] = pm; res[1] = pc;
    }
    else {
        res[0] = pc; res[1] = pm;
    }
    res[2] = mc; res[3] = md;
}
 
void next_cell(int res[4]) {
    int i, res1[4], res2[4];
    max_penalty(N_ROWS, N_COLS, TRUE, res1);
    max_penalty(N_COLS, N_ROWS, FALSE, res2);
 
    if (res1[3] == res2[3]) {
        if (res1[2] < res2[2])
            for (i = 0; i < 4; ++i) res[i] = res1[i];
        else
            for (i = 0; i < 4; ++i) res[i] = res2[i];
        return;
    }
    if (res1[3] > res2[3])
        for (i = 0; i < 4; ++i) res[i] = res2[i];
    else
        for (i = 0; i < 4; ++i) res[i] = res1[i];
}
 
void VAM() {
    	cout<<"Enter the number of Sources:"<<endl;
	cin>>N_ROWS;
	cout<<"Enter the number of Destinations:"<<endl;
	cin>>N_COLS;
	cout<<"Enter the supply matrix:"<<endl;
	for(int i = 0; i < N_ROWS; ++i){
		for(int j = 0; j < N_COLS; ++j){
			cin>>costs[i][j];
		}
	}

	cout<<"Enter the value of availibilities:"<<endl;
	for(int i = 0; i < N_ROWS; ++i){
		cin>>supply[i];
	}

	cout<<"Enter the value of demands:"<<endl;

	for(int i = 0; i < N_COLS; ++i){
		cin>>demand[i];
	}	


    int i, j, r, c, q, supply_left = 0, total_cost = 0, cell[4];
    int results[MAX][MAX] = { 0 };
 
    for (i = 0; i < N_ROWS; ++i) supply_left += supply[i];
    while (supply_left > 0) {
        next_cell(cell);
        r = cell[0];
        c = cell[1];
        q = (demand[c] <= supply[r]) ? demand[c] : supply[r];
        demand[c] -= q;
        if (!demand[c]) col_done[c] = TRUE;
        supply[r] -= q;
        if (!supply[r]) row_done[r] = TRUE;
        results[r][c] = q;
        supply_left -= q;
        total_cost += q * costs[r][c];
    }
 
    printf("    A   B   C   D   E\n");
    for (i = 0; i < N_ROWS; ++i) {
        printf("%c", 'W' + i);
        for (j = 0; j < N_COLS; ++j) printf("  %2d", results[i][j]);
        printf("\n");
    }
    printf("\nTotal cost = %d\n", total_cost);
    
}






void input(vector<vector<double> > &A, int m, int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin >> A[i][j];
		}
	}
}



int main(){
	int n,m;
	// m is no of rows
	// n is no of columns
	cout << "Enter number of stocks and demands res\n";
	cin >> m >> n;
	vector<vector<double> > A(m+1, vector<double>(n+1));

	input(A, m+1, n+1);

	while(1){
		cout << "\n\nEnter 1 for North West\n";
		cout << "Enter 2 for Matrix Min\n";
		cout << "Enter 3 for VAM\n";

		cout << endl << "Enter key  :   ";
		int key;
		cin >> key;

		if(key==1){
			vector<vector<double> > res1 = North_West(A, m, n);
			print_matrix(res1, m+1, n+1);
			cout << "Value =  " << value1 << endl << endl;
		}
		else if(key==2){
			vector<vector<double> > res1 = Matrix_Min(A, m, n);
			print_matrix(res1, m+1, n+1);
			cout << "Value =  " << value2 << endl << endl;
		}
		else if(key==3){
			VAM();
		}
		else{
			break;
		}
	}
	

	return 0;
}

