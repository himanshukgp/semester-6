#include<bits/stdc++.h>

using namespace std;

struct bhulbhulaiya{
   int m;
   int n;
   vector<vector<int> > H;
   vector<vector<int> > V;
   vector<vector<pair<int,int> > > P;
};

struct Node{
   struct Node *parent;
   int size;
};

void prnbhul(bhulbhulaiya*, vector<pair<int,int> >);

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

vector<vector<Node> > initisets(int m, int n){
   vector<vector<Node> > res(n+1, vector<Node> (n));
   for(int i=0;i<n+1;i++){
      for(int j=0;j<n;j++){
         res[i][j].parent = NULL;
         res[i][j].size = 1;
      }
   }
   return res;
}

Node* findset(vector<vector<Node> > &F, int i, int j){
   Node *temp;
   temp = &F[i][j];
   while(temp->parent!=NULL){
      temp = temp->parent;
   }
   return temp;
}

void mergesets(Node* p, Node* q){
   if(p==q) return;

   Node* temp;
   if(p->size < q->size){
      temp = p;
      p = q;
      q = temp;
   }

   q->parent = p;
   p->size += q->size;
}


int union_find(vector<int> temp2, bhulbhulaiya* M, vector<vector<int> > &d, int m, int n){

   vector<vector<Node> > F = initisets(m,n);

   for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
         if(d[i][j]){
            //print_1(F);
            if(j-1>=0){
               if(M->V[i][j-1]==0) mergesets(findset(F,i,j-1), findset(F,i,j));
               //print_1(F);
               //cout << findset(F,i,j-1) << " "<< findset(F,i,j) << endl;
            }
            if(i-1>=0){
               if(M->H[i-1][j]==0) mergesets(findset(F,i-1,j), findset(F,i,j));
            }
         }
      }
   }

   Node *t1=NULL,*t2=NULL;
   int i=temp2[1], j=temp2[2];
   if(temp2[0]==0){
      t1 = findset(F,i,j);
      t2 = findset(F,i+1,j);
   }
   if(temp2[0]==1){
      t1 = findset(F,i,j);
      t2 = findset(F,i,j+1);
   }
   if(t1==t2) return 0;
   return 1;

}

void MSTbhul(bhulbhulaiya* M, vector<vector<int> > &d){
   vector<pair<int,int> > pair_array;
   map<int, vector<int> > Mp;
   vector<int>  temp(3);

   int r = rand();
   int m = M->m;
   int n = M->n;

   for(int i=0;i<m-1;i++){
      for(int j=0;j<n;j++){
         int random1=rand()%100000;
         while(Mp.find(random1)!=Mp.end()) random1 = rand();
         temp[0]=0; temp[1]=i; temp[2]=j;
         Mp[random1] = temp;
      }
   }

   for(int i=0;i<m;i++){
      for(int j=0;j<n-1;j++){
         int random1=rand()%100000;
         while(Mp.find(random1)!=Mp.end()) random1 = rand();
         temp[0]=1; temp[1]=i; temp[2]=j;
         Mp[random1] = temp;
      }
   }

   //cout << Mp.size();


   int count=0;
   map<int, vector<int> >::iterator itr;
   for(itr=Mp.begin();itr!=Mp.end();itr++){
      //prnbhul(M,pair_array);
      vector<int> temp2 = itr->second;
      int i=temp2[1], j=temp2[2];
      if(union_find(temp2,M,d,m,n)){
         count++;
         if(temp2[0]==0){
            M->H[i][j] = 0;
            d[i][j] = 1;
            d[i+1][j] = 1;
         }
         else{
            M->V[i][j] = 0;
            d[i][j] = 1;
            d[i][j+1] = 1;
         }
         if(count==m*n-1) break;
      }
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

void DFS(bhulbhulaiya* M, vector<vector<int> > &d1, int i, int j){
   d1[i][j]=1;
   if(i-1>=0 && M->H[i-1][j]==0 && d1[i-1][j]==0) {
      M->P[i-1][j]=make_pair(i,j);
      DFS(M,d1,i-1,j);
   }

   if(j-1>=0 && M->V[i][j-1]==0 && d1[i][j-1]==0) {
      M->P[i][j-1]=make_pair(i,j);
      DFS(M,d1,i,j-1);
   }

   if(i+1<d1.size() && M->H[i][j]==0 && d1[i+1][j]==0) {
      M->P[i+1][j]=make_pair(i,j);
      DFS(M,d1,i+1,j);
   }
   if(j+1<d1[0].size() && M->V[i][j]==0 && d1[i][j+1]==0) {
      M->P[i][j+1]=make_pair(i,j);
      DFS(M,d1,i,j+1);
   }

}

int main(){
   srand((unsigned int)time(NULL));

   int m,n;
   vector<pair<int,int> > pair_array;

   cin >> m >> n;
   m = min(m,n);
   n = max(m,n);

   // Part 1
   bhulbhulaiya* M = initbhul(m,n);

   // Part 2
   cout << "Initial bhul bhulaiya\n";
   prnbhul(M,pair_array);

   // Part 3
   vector<vector<int> > d(m,vector<int>(n,0));
   MSTbhul(M,d);
   cout << "Created a random bhulbhulaiya\n";
   prnbhul(M, pair_array);
   
   // Part 4
   vector<vector<int> > d1(m,vector<int>(n,0));
   DFS(M,d1,0,0);
   int a = rand()%m, b = rand()%n;
   int c = rand()%m, e = rand()%n;

   pair_array = findrani(M,a,b,c,e,m,n);
   cout << "Taking (" << a << "," << b << ") to (" << c  << "," << e << ") a random bhulbhulaiya\n";
   prnbhul(M, pair_array);

   return 0;
}

