#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Greedy strategy costliest first
void grdsearch1(int N, vector<double> prices, vector<double> rates){
	vector<int> register1(N);
	vector<double> tot_price(N);

	for(int i=0;i<N;i++) tot_price[i] = prices[i];

	double result;

	int k=0;
	while(k<N){
		double temp=0,index;
		for(int i=0;i<N;i++) if(tot_price[i]>temp && register1[i]==0) { index=i; temp=tot_price[i];}
		register1[index] = 1;
		result+=temp;
		cout << k << "\t" << index << "\t" << temp << endl;
		for(int i=0;i<N;i++) tot_price[i] = tot_price[i]*rates[i];
		k++;
	}
	cout << "--- Total cost =  " << result << endl << endl;
}

// reedy strategy cheapest last
void grdsearch2(int N, vector<double> prices, vector<double> rates){
	vector<int> register1(N);
	vector<double> tot_price(N);
	vector<vector<double> > to_print(N, vector<double>(2));

	for(int i=0;i<N;i++) tot_price[i] = prices[i];

	double result;

	int k=N-1;
	while(k>=0){
		for(int i=0;i<N;i++) tot_price[i] = prices[i]*pow(rates[i],k);
		double temp=100000,index;
		for(int i=0;i<N;i++) if(tot_price[i]<temp && register1[i]==0) { index=i; temp=tot_price[i];}
		register1[index] = 1;
		result+=temp;
		to_print[k][0] = index;
		to_print[k][1] = temp;
		//cout << k << "\t" << index << "\t" << temp << endl;
		k--;
		for(int i=0;i<N;i++) tot_price[i]=0;
	}

	for(int i=0;i<to_print.size();i++){
		cout << i <<"\t" << to_print[i][0] << "\t" << to_print[i][1]<<endl;
	}

	cout << "--- Total cost =  " << result << endl << endl;
}

// Greedy strategy maximum price increase first
void grdsearch3(int N, vector<double> prices, vector<double> rates){
	vector<int> register1(N);
	vector<double> tot_price(N);

	for(int i=0;i<N;i++) tot_price[i] = prices[i];

	double result;

	int k=0;
	while(k<N){
		double temp=0,index;
		vector<double> temp_vec(N);
		for(int i=0;i<N;i++) temp_vec[i] = tot_price[i]*rates[i]-tot_price[i];
		for(int i=0;i<N;i++) if(temp_vec[i]>temp && register1[i]==0) { index=i; temp=temp_vec[i];}
		register1[index] = 1;
		result+=tot_price[index];
		cout << k << "\t" << index << "\t" << tot_price[index] << endl;
		for(int i=0;i<N;i++) tot_price[i] = tot_price[i]*rates[i];
		k++;
	}
	cout << "--- Total cost =  " << result << endl << endl;
}

// Utility to swap two numbers in array.
void Swap(int &A, int &B){
	int k=A;
	A=B; 
	B=k;
}

// Utility to look at all permutations.
void genpermutations ( vector<int> &P, int n, int k, vector<double> &prices, vector<double> &rates, vector<int> &min_seq){
	int i;

	if (k == n) {
		int min_price = 0, current_price=0;
		for(int i=0;i<rates.size();i++) min_price+=pow(rates[min_seq[i]], i)*prices[min_seq[i]];
		for(int i=0;i<rates.size();i++) current_price+=pow(rates[P[i]], i)*prices[P[i]];
		if(current_price<min_price) for(int i=0;i<P.size();i++) min_seq[i] = P[i];
	}

	for (i=k; i<n; ++i) {
		Swap(P[k], P[i]);

		// At this point in array P no change from 0 to index k.
		// If cost by getting only these k items is more than minimum
		// obtained so far don't look for more permutations. 
		int temp1=0,temp2=0;
		for(int j=0;j<=k;j++) temp1+=pow(rates[P[j]], j)*prices[P[j]];
		for(int j=0;j<rates.size();j++) temp2+=pow(rates[min_seq[j]], i)*prices[min_seq[j]];
		if(temp1>=temp2) continue;

		genpermutations(P,n,k+1,prices,rates,min_seq);
		Swap(P[k], P[i]);
	}
}

// Function to do make exhaustive search
void exhsearch(int N, vector<double> prices, vector<double> rates){
	vector<int> P(N);
	vector<int> min_seq(N);
	for(int i=0;i<N;i++) P[i]=i;
	for(int i=0;i<N;i++) min_seq[i]=i;
	int k=0;
	double min_price=0;

	genpermutations(P, N, k, prices, rates, min_seq);

	for(int i=0;i<rates.size();i++) min_price+=pow(rates[min_seq[i]], i)*prices[min_seq[i]];

	for(int i=0;i<N;i++){
		cout << i << "\t" << min_seq[i] << "\t" << pow(rates[min_seq[i]],i)*prices[min_seq[i]] << endl;
	}

	cout << "--- Total cost = " <<min_price << endl; 
}


int main(){

	int N;
	cin >> N;
	vector<double> prices(N);
	vector<double> rates(N);

	for(int i=0;i<N;i++){
		cin >> prices[i];
	}

	for(int i=0;i<N;i++){
		cin >> rates[i];
	}

	cout << "+++ Greedy search 1" << endl;
	grdsearch1(N, prices, rates);
	cout << "+++ Greedy search 2" << endl;
	grdsearch2(N, prices, rates);
	cout << "+++ Greedy search 3" << endl;
	grdsearch3(N, prices, rates);
	cout << "+++ Greedy search 4" << endl;
	exhsearch(N, prices, rates);

	return 0;
}
