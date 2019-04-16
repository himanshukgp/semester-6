#include <iostream>
#include <vector>
#include <stdlib.h> 

using namespace std;

void merge(vector<vector<int> > &arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    vector<vector<int> > L(n1, vector<int> (3));
    vector<vector<int> > R(n2, vector<int> (3));
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0; 
    k = l;
    while (i < n1 && j < n2){ 
        if (L[i][0] <= R[j][0]){ 
            arr[k] = L[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  

    while (i < n1){ 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2){ 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  

void mergeSort(vector<vector<int> > &arr, int l, int r) 
{ 
    if (l < r){ 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 


void printArray(vector<vector<int> > A) 
{ 
    int i; 
    int size = A.size();
    for (i=0; i < size; i++) 
        cout << A[i][0] << " "; 
    cout << endl; 
} 

int findmin(vector<vector<int> > &arr){
	int i=0;
	while(i*2+1<arr.size()){
		i = i*2+1;
	}
	return i;
}

void deleteQ(vector<vector<int> > &arr, vector<int> &idx, int i, int left, int right){
	int min = findmin(arr);

	int temp = idx[i];
	int last = arr.size()-1;
	if(temp==last){
		arr.pop_back();
		return;
	}
	arr[temp][0] = arr[last][0];
	arr[temp][1] = arr[last][1];
	arr[temp][2] = arr[last][2];

	idx[i] = idx[arr[last][0]];
	idx[arr[last][0]] = -1;

	arr.pop_back();

	int t = temp;
	int parent = (t-1)/2;
	while(parent>=0){
		if(arr[parent][2]<arr[t][2]){
			int i_,l_,r_;
			i_ = arr[t][0];
			l_ = arr[t][1];
			r_ = arr[t][2];

			arr[t][0] = arr[parent][0];
			arr[t][1] = arr[parent][1];
			arr[t][2] = arr[parent][2];

			arr[parent][0] = i_;
			arr[parent][1] = l_;
			arr[parent][2] = r_;

			int a,b;
			a = idx[arr[parent][0]];
			b = idx[arr[t][0]];
			idx[arr[parent][0]] = b;
			idx[arr[t][0]] = a;

			t = parent;
			parent = (t-1)/2;
		}
		else break;
	}

}

void insertQ(vector<vector<int> > &arr, vector<int> &idx, int i, int left, int right){
	vector<int> temp;
	temp.push_back(i);
	temp.push_back(left);
	temp.push_back(right);
	arr.push_back(temp);


	idx[i] = arr.size()-1;
	//printArray(arr);

	int t = arr.size()-1;
	int parent = (t-1)/2;
	while(parent>=0){
		if(arr[parent][2]<arr[t][2]){
			int i_,l_,r_;
			i_ = arr[t][0];
			l_ = arr[t][1];
			r_ = arr[t][2];

			arr[t][0] = arr[parent][0];
			arr[t][1] = arr[parent][1];
			arr[t][2] = arr[parent][2];

			arr[parent][0] = i_;
			arr[parent][1] = l_;
			arr[parent][2] = r_;

			int a,b;
			a = idx[arr[parent][0]];
			b = idx[arr[t][0]];
			idx[arr[parent][0]] = b;
			idx[arr[t][0]] = a;

			t = parent;
			parent = (t-1)/2;
		}
		else break;
	}
}


void mincover(vector<vector<int> > &arr){
	vector<vector<int> > E(arr.size()*2, vector<int> (3));

	int zero_idx=0;
	for(;arr[zero_idx][0]!=0;zero_idx++); 

	for(int i=0;i<arr.size();i++){
		E[2*i][0] = arr[i][0];
		E[2*i][1] = i;
		E[2*i][2] = 0;
		E[2*i+1][0] = arr[i][1];
		E[2*i+1][1] = i;
		E[2*i+1][2] = 1;
	}
	mergeSort(E, 0, E.size()-1);
	//printArray(E);

	vector<vector<int> > Q;
	vector<int> idx(arr.size(), -1);

	vector<int> temp;
	temp.push_back(zero_idx);
	temp.push_back(arr[zero_idx][0]);
	temp.push_back(arr[zero_idx][1]);
	Q.push_back(temp);
	idx[zero_idx] = 0;

	int x = arr[zero_idx][1];

	int k=0;

	//printArray(Q);
	while(x<999 && k<E.size()){
		k++;

		if(E[k][2]==0){
			//cout << E[k][1] << endl;
			insertQ(Q, idx, E[k][1], arr[E[k][1]][0], arr[E[k][1]][1]);
		}
		else{
			deleteQ(Q, idx, E[k][1], arr[E[k][1]][0], arr[E[k][1]][1]);

			if(E[k][0]==x){
				cout << Q[0][0] << " " << Q[0][1] << " " << Q[0][2] << endl;
				x = Q[0][2]; 
			}
		}
		//printArray(Q);
	}

}
  


int main() 
{ 
	int arr_size;
	cin >> arr_size;
	if(arr_size<=256){
		vector<vector<int> > arr(arr_size, vector<int> (2));

	    for(int i=0;i<arr_size;i++) {
	    	cin >> arr[i][0];
	    	cin >> arr[i][1];
	    }

	    cout << endl;

	    mincover(arr);
	}
    return 0; 
} 