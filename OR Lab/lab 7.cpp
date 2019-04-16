#include<bits/stdc++.h>

using namespace std; 

class Equation{ 
    public: 

    vector<vector<double> > equation;
    int n,m;
    vector<double> b;
    vector<double> z;
  
    void input_equation() 
    { 
    	cout << "Input all equation in <= form \n";
    	cout << "Input n \n";
		cin >> n;
		cout << "Input m \n";
		cin >> m;

   		cout << "Input A of AX = b \n";
       	for(int i=0;i<m;i++){
       		vector<double> a;
       		equation.push_back(a);
       		for(int j=0;j<n;j++){
       			double temp;
       			cin >> temp;
       			equation[i].push_back(temp);
       		}
       	}

       	cout << "Input vector b of AX = b \n";
       	for(int i=0;i<m;i++){
       		double temp;
       		cin >> temp;
       		b.push_back(temp);
       	}

       	cout << "Input vector z of max z \n";
       	for(int i=0;i<n;i++){
       		double temp;
       		cin >> temp;
       		z.push_back(temp);
       	}
    }

	void output_equation() 
    { 
   		cout << "\n Output A of AX = b \n";
       	for(int i=0;i<m;i++){
       		for(int j=0;j<n;j++){
       			cout << equation[i][j] << "\t";
       		}
       		cout << endl;
       	}

       	cout << "Output vector b of AX = b \n";
       	for(int i=0;i<m;i++) cout << b[i] << "\t";
       	cout << endl;

       	cout << "Output vector z of max z \n";
       	for(int i=0;i<n;i++) cout << z[i] << "\t";
       	cout << endl;
    }
};


class simplex_table{
	public:
		vector<int> basic_variables;
		vector<int> all_variables;
		vector<double> z;
		vector<vector<double> > values;
		vector<double> b;
		vector<double> ratio;
		vector<bool> bool_ratio;
		int i,j;

	void print_simplex_table(){

		// Decoration
		cout << "B var\t";
		cout << setprecision(2);
		for(int i=0;i<all_variables.size();i++) cout << "x" << all_variables[i]+1 << "\t";
		cout << "Solution\n";
		for(int i=0;i<all_variables.size();i++) cout << "\t----";
		cout << endl;


		for(int i=0;i<values.size();i++){
			if(i<values.size()-1) cout << "x" << basic_variables[i]+1 << "\t";
			else cout << "z\t";
			for(int j=0;j<values[i].size();j++){
				cout << values[i][j] << "\t";
			}
			cout << endl;
		}
	}

};


class Dual_simplex{
	public: 

		Equation eq;
		simplex_table current_table;
		vector<simplex_table> all_table;
		int n,m;
		

		Dual_simplex(Equation eq1){
			eq = eq1;
			n = eq1.n;
			m = eq1.m;
		}

		void form_current_table(){
			for(int i=0;i<m;i++){
	       		vector<double> a;
	       		current_table.values.push_back(a);
	       		for(int j=0;j<n;j++){
	       			current_table.values[i].push_back(eq.equation[i][j]);
	       		}
	       	}

	       	for(int i=0;i<m;i++){
	       		for(int j=0;j<m;j++){
	       			if(i==j) current_table.values[i].push_back(1);
	       			else current_table.values[i].push_back(0);
	       		}
	       	}

	       	for(int i=0;i<n+m;i++){
	       		current_table.all_variables.push_back(i);
	       	}
	       	for(int i=n;i<n+m;i++){
	       		current_table.basic_variables.push_back(i);
	       	}
	       	for(int i=0;i<=n+m;i++){
	       		if(i<n) current_table.z.push_back(eq.z[i]*-1);
	       		else current_table.z.push_back(0);
	       	}

	       	for(int i=0;i<m;i++){
	       		current_table.values[i].push_back(eq.b[i]);
	       	}

	       	// Append in values as the real simplex table
	       	current_table.values.push_back(current_table.z);

		}

		bool iterate_more(){
			int flag = 0;
			double first;
			for(int i=0;i<m;i++){
				if(current_table.values[i][m+n]<0) {
					flag = 1;
					first = current_table.values[i][m+n];
				}
			}

			for(int j=0;j<m;j++){
				if(current_table.values[j][m+n]<=first){
					first = current_table.values[j][m+n];
					current_table.i = j;
				}
			}

			if(flag==1) return true;
			return false;
		}

		void find_ratios(){
			for(int k=0;k<m+n;k++){
				double temp=current_table.values[m][k]/current_table.values[current_table.i][k];
				if(temp<0) temp = temp*-1;
				if(current_table.values[current_table.i][k]<0 && current_table.values[m][k]!=0){
					current_table.bool_ratio.push_back(true);
					current_table.ratio.push_back(temp);
				}
				else {
					current_table.bool_ratio.push_back(false);
					current_table.ratio.push_back(0);
				}
			}
		}

		void find_pivot(){
			double temp;
			for(int i=0;i<m+n;i++) if(current_table.bool_ratio[i]){temp = current_table.ratio[i]; break;}
			for(int i=0;i<m+n;i++) if(current_table.bool_ratio[i] && current_table.ratio[i]<=temp) current_table.j = i;  
		}

		void convert_pivot_row(){
			double temp = current_table.values[current_table.i][current_table.j];
			for(int k=0;k<=m+n;k++){
				current_table.values[current_table.i][k] = 
					current_table.values[current_table.i][k]/temp;
			}
		}

		void convert_rest_rows(){
			for(int k=0;k<=m;k++){
				if(k==current_table.i) continue;
				double temp = current_table.values[k][current_table.j];
				for(int l=0;l<=m+n;l++){
					current_table.values[k][l] = current_table.values[k][l] -
						temp*current_table.values[current_table.i][l];
				}
			}
			// Update basic variable
			current_table.basic_variables[current_table.i] = current_table.all_variables[current_table.j];
		}

		void perform_iteration(){
			convert_pivot_row();
			convert_rest_rows();
		}

		void gauss_jordan(){
			while(iterate_more()){
				// Clear previous values in vector
				current_table.bool_ratio.clear();
				current_table.ratio.clear();

				find_ratios();
				find_pivot();  
				perform_iteration();
				all_table.push_back(current_table);
			}
		}

		void execute(){
			form_current_table();
			all_table.push_back(current_table);
			gauss_jordan();
		}
};


int main(){
	Equation a;
	a.input_equation();

	Dual_simplex b(a);
	b.execute();

	for(int i=0;i<b.all_table.size();i++){
		cout << "\n Simplex table: " << i+1 << " \n";
		b.all_table[i].print_simplex_table();
		if(i+1<b.all_table.size()){
			cout << "\n Most Negative value = \t" 
					<< b.all_table[i].values[b.all_table[i+1].i][b.all_table[i+1].values[0].size()-1] << endl;
			cout << "Leaving Variable = \tx" << b.all_table[i].basic_variables[b.all_table[i+1].i]+1 << endl;
			cout << "\n Least value of (deltaj/Xr) = \t" 
					<< b.all_table[i+1].ratio[b.all_table[i+1].j] << endl;
			cout << "Incoming Variable = \tx" << b.all_table[i+1].all_variables[b.all_table[i+1].j]+1 << endl;
		}
	}

	int i = b.all_table.size()-1;
	int j = b.all_table[0].values.size()-1;
	int k = b.all_table[0].values[0].size()-1;
	
	cout << "\nOptimal Value = " << b.all_table[i].values[j][k] << endl << endl;

	return 0;
}

