#include<bits/stdc++.h>

using namespace std;

//////////////////////////////////////////////
/////////////  NAME - HIMANSHU  //////////////
/////////////  ROLL - 16MA20020 //////////////
//////////////////////////////////////////////


int N;
# define NN 500
vector<vector<int> > possible;



////////////////////////////////////////////////
////////   GAUSSIAN ELIMINATION METHOD  ////////
/////  To get solution of linear equations. ////
////////////////////////////////////////////////



vector<double> gauss(vector< vector<double> > A) {

  
    int n = A.size();

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n]/A[i][i];
	//if(A[i][i]==0) { vector<double> t; return t;}
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

////////////////////////////////////////////////
////////////////////////////////////////////////


  

// utility function for subset function to 
// save each subset in global 2D vector 'possible' 
void save( list<int> l){
	vector<int> temp;
    for(list<int>::iterator it=l.begin(); it!=l.end() ; ++it){
      temp.push_back(*it);
    }
    possible.push_back(temp);
}

// function to calculate and save all the permutation of taking 
// different combinations of all variables.
// In global 2D vector 'possible' it saves index of each variable 
// which should be taken in each row.
void subset(int arr[], int size, int left, int index, list<int> &l){
    if(left==0){
        save(l);
        return;
    }
    for(int i=index; i<size;i++){
        l.push_back(arr[i]);
        subset(arr,size,left-1,i+1,l);
        l.pop_back();
    }

}  


// To get input equations
// input each row with n+1 values here n is number of variables
//  without counting slack variables
// total values in all rows are n+1 as one additional value of 
// b should be input at end
// input sign whether less than equals (1) or greater than equals (-1).
void inp(double mat[NN][NN+1], int n, int m, vector<int> &sign){
  cout << "Input n+1 values in each row i.e. value of b at the end and with" << endl
   << "sign after that input 1 for less than equal and -1 otherwise"<<endl;
    for(int i=0;i<m;i++){
      	for(int j=0;j<n+2;j++){
			if(j!=n+1)cin >> mat[i][j];
			else{
		  		cout << "input sign"<< endl;
		  		double temp;
		  		cin >> temp;
		  		sign.push_back(temp);
		  		cout << "input row"<< endl;
			}
		}
    }
}


// Main driver program
int main() 
{ 
	int n,m;
	cout << "number of unknowns"<< endl;
	cin >> n;
	cout << "number of equations" << endl;
	cin >> m;

	double mat[NN][NN+1];
	double simp[NN][NN+1];
	double temp[NN][NN+1];
	vector<int> sign;

	//take input the equations
	inp(mat,n,m,sign);

	for(int i=0;i<m;i++){
	  for(int j=0;j<n+1;j++){
	    simp[i][j] = mat[i][j];
	  }
	}

	// introduce slack variables
	N=m;
	int tot = n+m;
	for(int i=0;i<m;i++) {mat[i][n+m] = mat[i][n]; mat[i][n]=0;}
	for(int i=0;i<m;i++) mat[i][n+i] = sign[i];


	//get all combinations
	int vec[1000];
	for(int t=0;t<tot;t++) vec[t]=t;

	list <int> lt;
	subset(vec, tot, m, 0, lt);

	vector<double> p_;
	vector<vector<double> > res, res1;


	for(int k=0;k<possible.size();k++){
        res1.clear();
	for(int i=0;i<m;i++){
	  p_.clear();
	for(int j=0;j<=m;j++){
	  if(j==m) p_.push_back(mat[i][tot]);
	  else p_.push_back(mat[i][possible[k][j]]);
	}
            res1.push_back(p_);
		}
        p_ = gauss(res1);

        
        res.push_back(p_);
	}


	vector<vector<double> > new1(res.size(), vector<double> (tot));
	
	for(int i=0;i<new1.size();i++) {
	  int temp=0;
	  for(int j=0;j<new1[i].size();j++){
	    if(possible[i][temp]==j) new1[i][j]=res[i][temp++];
	  }
	}
	  

	// DAY 2

	vector<double> temp4;
	vector<vector<double> > new2;
	int flag=0;

	for(int i=0;i<new1.size();i++){
	  flag=0;
	  temp4.clear();
	  for(int j=0;j<new1[i].size();j++){
	    temp4.push_back(new1[i][j]);
	    if(new1[i][j]<0|| isinf(new1[i][j])==1 || isnan(new1[i][j])==1) flag=1;
	  }
	  if(flag==0) new2.push_back(temp4);
	}

	vector<vector<double> > new3;

	for(int i=0;i<new2.size();i++){
	  temp4.clear();
	  for(int j=0;j<n;j++){
	    temp4.push_back(new2[i][j]);
	  }
	  new3.push_back(temp4);
	}

	

	


	cout << "input coefficient of function"<< endl;


	vector <double> opt;
	double temp5;
	for(int i=0;i<n;i++) {
	  cin >> temp5;
	  opt.push_back(temp5);
	}

	cout << "Input 1 if to maximize else -1" << endl;
	int flag3=1;
	cin >> flag3;

	vector<double> final1;

	for(int i=0;i<new3.size();i++){
	  double temp6=0;
	  for(int j=0;j<opt.size();j++){
	    temp6+=new3[i][j]*opt[j];
	  }
	  final1.push_back(temp6);
	}
	
	int temp7=0;
	for(int i=0;i<final1.size();i++){
	  cout << temp7 << endl;
	  if(final1[temp7]<final1[i] && flag3==1) temp7=i;
	  if(final1[temp7]>final1[i] && flag3==-1) temp7=i;
	}

	//cout << "final "<< temp7 << endl;

	//for(int i=0;i<final1.size();i++) cout << final1[i]<< " ";
	//cout << endl;

	// Basic soln in new1
	// Basic Feasible solution in new3
	// Optimal solution in new3[temp7][i]
	// Optimal value in final1[temp7]



	// DAY 3

	int d;
	cout << "Input d"<< endl;
	cin >> d;
	vector< vector<double> > table(m+1, vector<double>(n+1));

	for(int i=0;i<table.size()-1;i++){
	  for(int j=0;j<table[i].size();j++){
	    table[i][j] = simp[i][j];
	  }
	}

	for(int i=0;i<n;i++) table[m][i] = opt[i]*-1;
	table[m][n] = d;

	

	vector<int> basic_variable1(m+n),basic_variable2(m+n);
	for(int i=0;i<m+n;i++){ basic_variable1[i]=i+1; basic_variable2[i] = i+1;}




	int min_column=0;
	for(int i=0;i<n;i++) if(table[m][i]<table[m][min_column]) min_column = i;
	vector<double> min_ratios(m);
	for(int i=0;i<m;i++) min_ratios[i] = table[i][n]/table[i][min_column];




	int pivot_i=0,pivot_j;
	while(pivot_i<m) if(min_ratios[pivot_i]>0 && !isinf(min_ratios[pivot_i]) && !isnan(min_ratios[pivot_i]) ) break; else pivot_i++; 
	pivot_j = min_column;
	for(int i=0;i<m;i++) if(min_ratios[i]<min_ratios[pivot_i] && min_ratios[i]>0 && !isinf(min_ratios[pivot_i]) && !isnan(min_ratios[pivot_i]) ) pivot_i = i;

	cout << pivot_i << " " << pivot_j;
	int pivot_ele = table[pivot_i][pivot_j];

	vector<vector<double> > iter2(m+1, vector<double>(n+1));


	for(int i=0;i<=m;i++) if(i!=pivot_i) iter2[i][pivot_j] = -1*table[i][pivot_j]/pivot_ele;
	for(int i=0;i<=n;i++) if(i!=pivot_j) iter2[pivot_i][i] = table[pivot_i][i]/pivot_ele;

	for(int i=0;i<=m;i++){
	  for(int j=0;j<=n;j++){
	    if(i!=pivot_i && j!=pivot_j){
	      iter2[i][j] = table[i][j]*pivot_ele - table[pivot_i][j]*table[i][pivot_j];
	      iter2[i][j] = iter2[i][j]/pivot_ele;
	    }
	  }
	}

	iter2[pivot_i][pivot_j] = 1/pivot_ele;
	
	int temp000 = basic_variable2[pivot_i];
	basic_variable2[pivot_i] = basic_variable2[n+pivot_j];
	basic_variable2[n+pivot_j] = temp000;
	

	cout <<endl <<endl;
	for(int i=0;i<iter2.size();i++){
	  for(int j=0;j<iter2[i].size();j++){
	    cout << iter2[i][j] << "\t";
	  }

	  cout << endl;
	}

	

	while(1){
	  cout << "Input 1 for basic feasible solution" << endl;
	  cout << "Input 2 for initial simplex table" << endl;
	  cout << "Input 3 for non-basic variables" << endl;
	  cout << "Input 4 for basic variables and min ratio" << endl;
	  cout << "Input 5 for 2nd iteration table" << endl;
	  cout << "Input -1 to exit" << endl;

	  int switch1;
	  cin >> switch1;
	  
	  if(switch1==1){
	    cout << endl<<endl<<"Basic Feasible Solution"<< endl;

	for(int i=0;i<new3.size();i++){
	  for(int j=0;j<new3[i].size();j++){
	    cout << new3[i][j]<<" ";
	  }
	  cout << endl;
	}
	cout << endl<<endl;
	  }



	  else if(switch1==2){
	    cout << endl<< "Initial Simplex table is"<< endl;
	    
	    for(int i=0;i<n;i++) {
	  if(basic_variable1[i]<=n) cout << "-x" << basic_variable1[i]<<"\t";
	  else cout <<"-z" << basic_variable1[i]-n<< "\t";
	}
	cout << "b" << endl;

	
	for(int i=0;i<table.size();i++){
	  for(int j=0;j<table[i].size();j++){
	    cout << table[i][j] << "\t";
	  }
	  cout << endl;
	}
	    
	    cout << endl;
	    cout << endl<<endl;
	  }



	  else if(switch1==3){
	    cout << "Non Basic variables are: " << endl;

	    for(int i=0;i<n;i++) {
	  if(basic_variable1[i]<=n) cout << "x" << basic_variable1[i]<<"\t";
	  else cout <<"z" << basic_variable1[i]-n<< "\t";
	}

	    cout << endl<<endl;
	  }


	  else if(switch1==4){
	    cout << "Input 4 for basic variables and min ratio"<<endl;
	    	for(int i=n;i<n+m;i++) {
	  if(basic_variable1[i]<=n) cout << "x" << basic_variable1[i]<<"\t";
	  else cout <<"z" << basic_variable1[i]<< "\t";
	}
	cout << endl;
	for(int i=0;i<min_ratios.size();i++) cout << min_ratios[i] << "\t";
	cout << endl;
	  }

	  else if(switch1==5){
	    cout << "2nd table" << endl;
cout << endl<< "Initial Simplex table is"<< endl;
	    
	    for(int i=0;i<n;i++) {
	  if(basic_variable2[i]<=n) cout << "-x" << basic_variable2[i]<<"\t";
	  else cout <<"z" << basic_variable2[i]-n<< "\t";
	}
	cout << "b" << endl;

	
	for(int i=0;i<table.size();i++){
	  for(int j=0;j<table[i].size();j++){
	    cout << iter2[i][j] << "\t";
	  }
	  cout << endl;
	}
	    
	    cout << endl;
	    cout << endl<<endl;
	  }


	  else{
	    break;
	  }

	}

  	return 0; 
} 
