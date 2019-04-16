#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//generates combinations to choose r of n elements
vector< vector<bool> > getCombos(int n, int r) {
    vector<bool> v(n);
    fill(v.end() - r, v.end(), true);
    vector< vector<bool> > combos;
    do {
       vector<bool> cpy(n);
       cpy = v;
       combos.push_back(cpy);
    } while (next_permutation(v.begin(), v.end()));
    return combos;
}


//Code from internet for gaussian elimination (slight modifications)
vector<double> gaussianElimination(vector< vector<double> > A, int& isSingular) {
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
        	if(A[i][i] == 0) isSingular = 1;
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
    	if(A[i][i] == 0) isSingular = 1;
        x[i] = A[i][n]/A[i][i];
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

int main() {
	int np = 0, cont;
	ofstream out("out.txt");
	streambuf *coutbuf = cout.rdbuf();

	do {
		int i, j, ptr, M, N, l, p, ptr2, flag, m, n, count = 0, isSingular;
		double sol;

		cout << "===============INPUT===============" << endl;
		cout << endl << "Enter Number of Equations m : " << endl;
		cin >> m;
		cout << endl << "Enter Number of Variables n including Slack Variables" << endl;
		cin >> n; 

		M = n;
		N = m;
		cout << endl << "Enter matrix A|b, ie. A augmented with vector b as last column: [dim- N x (M + 1)]" << endl;
		double mat[N][M+1];
		vector< vector<double> > A(N);
		for(i = 0; i < N; i++)
			A[i].resize(N + 1);
		for(i = 0; i < N; i++) 
			for(j = 0; j < M + 1; j++)
				cin >> mat[i][j];

		cout.rdbuf(out.rdbuf());

		cout << endl << "===============PROBLEM NO. " << (++np) << "===============" << endl;
		cout << endl << "Number of Equations : " << m << endl; 
		cout << endl << "Number of Variables (including Slack Variables) : " << n << endl;
		cout << endl << "Entered Matrix A|b :" << endl;

		for(i = 0; i < N; i++) {
			for(j = 0; j < M + 1; j++)
				cout << mat[i][j] << " ";
			cout << endl;
		}

		vector< vector<bool> > combos = getCombos(M, N);
		l = combos.size();
		vector< pair< vector<double>, int> > solutions;

		for(p = 0; p < l; p++) {
			flag = isSingular = 0;
			vector<double> x;

			for(i = 0; i < N; i++) {
				ptr=0;
				for(j = 0; j < M; j++) {
					if(combos[p][j])
						A[i][ptr++] = mat[i][j];
				}
			} 

			for(i = 0; i < N; i++){
				A[i][N] = mat[i][M];
			}

			x = gaussianElimination(A, isSingular); 
			solutions.push_back(make_pair(x, isSingular));			
		} 

		cout << endl << "All Basic Solutions" << endl;
		count = 0;
		for(p = 0; p < l; p++) {
			flag = 0;
			vector<double> x = solutions[p].first;
			isSingular = solutions[p].second;
			for(i = 0; i < N; i++)
				if(x[i] < 0) // check if feasible
					flag = 1;

			cout << endl << "Solution no. " << (++count) << endl;
			if(isSingular) 
				cout << "Warn : Singular Matrix" << endl;
			
			ptr2 = 0;
			for(i = 0; i < M; i++) {
				cout << "X" << (i+1) << " = ";
				if(combos[p][i] == 0)
					cout << 0 << endl;
				else {
					sol = x[ptr2++];
					cout << sol << endl;
				}
			}
			if(flag == 0) 
				cout << "(Feasible)" << endl; 
			else 
				cout << "(Infeasible Solution)" << endl;
			cout << endl;
		}

		cout << "Only Basic Feasible Solutions : " << endl;
		count = 0;
		for(p = 0; p < l; p++) {
			flag = 0;
			vector<double> x = solutions[p].first;
			isSingular = solutions[p].second;
			if(isSingular) 
				continue;
			for(i = 0; i < N; i++)
				if(x[i] < 0) // check if infeasible
					flag = 1;
			if(flag == 1)
				continue;
			cout << endl << "Solution no. " << (++count) << endl;
			if(isSingular) 
				cout << "Warn : Singular Matrix" << endl;
			
			ptr2 = 0;
			for(i = 0; i < M; i++) {
				cout << "X" << (i+1) << " = ";
				if(combos[p][i] == 0)
					cout << 0 << endl;
				else {
					sol = x[ptr2++];
					cout << sol << endl;
				}
			}
			cout << endl;
		}

		cout.rdbuf(coutbuf);
		cout << endl << "Enter 1 for another problem, 0 to exit : " << endl;
		cin >> cont;
	} while(cont);
	return 0;
} 
