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
	double temp[NN][NN+1];
	vector<int> sign;

	//take input the equations
	inp(mat,n,m,sign);

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

	while(1){
	  cout << "Input 1 for basic solutions"<< endl;
	  cout << "Input 2 for basic feasible solution" << endl;
	  cout << "Input 3 for optimal solution" << endl;
	  cout << "Input 4 for optimal value" << endl;
	  cout << "Input -1 to exit" << endl;

	  int switch1;
	  cin >> switch1;
	  
	  if(switch1==1){
	    cout << endl<<"Basic solution"<< endl;
	    cout << endl<<endl;
	for(int i=0;i<new1.size();i++){
	  for(int j=0;j<new1[i].size();j++){
	    cout << new1[i][j]<<" ";
	  }
	  cout << endl;
	}
	cout << endl<<endl;
	  }
	  else if(switch1==2){
	    cout << endl<<endl<<"Basic Feasible Solution"<< endl;

	for(int i=0;i<new3.size();i++){
	  for(int j=0;j<new3[i].size();j++){
	    cout << new3[i][j]<<" ";
	  }
	  cout << endl;
	}
	cout << endl<<endl;
	  }
	  else if(switch1==3){
	    cout << endl<< "Optimal Solutions are"<< endl;
	    for(int i=0;i<n;i++){
	      cout << new3[temp7][i]<< " ";
	    }
	    cout << endl;
	    cout << endl<<endl;
	  }
	  else if(switch1==4){
	    cout <<endl<<"Optimal value is" << endl << final1[temp7] << endl;
	    cout << endl<<endl;
	  }
	  else{
	    break;
	  }

	}

  	return 0; 
} 
