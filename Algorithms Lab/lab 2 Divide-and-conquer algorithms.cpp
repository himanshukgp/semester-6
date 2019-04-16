#include<iostream>
#include<math.h>

extern void registerme ( int );
extern void startpart ( int );
extern void endpart ( int );
extern void makemove ( int , int , int );
extern void showpegs ( );

using namespace std;

void ToH3(int i, int j, int p, int q, int r){
  if (i == j) 
    { 
      makemove(i,p,q);
      return; 
    } 
  ToH3(i, j-1, p, r, q); 
  makemove(j,p,q);
  ToH3(i, j-1, r, q, p); 
}

void ToH41(int a, int b, int p, int q, int r, int s){
  int k = (b-a+1)/2;
  if(b-a<3){
    ToH3(a,b,p,q,r);
    return;
  }
  ToH41(a,b-k,p,s,q,r);
  ToH3(b-k+1,b,p,q,r);
  ToH41(a,b-k,s,q,r,p);
}

void ToH42(int a, int b, int p, int q, int r, int s, int k){
  if(b-a<k){
    ToH3(a,b,p,q,r);
    return;
  }
  else{
    ToH42(a,b-k,p,s,q,r,k);
    ToH3(b-k+1,b,p,q,r);
    ToH42(a,b-k,s,q,r,p,k);
  }
}

void ToH43(int a, int b, int p, int q, int r, int s){
  int k = round(sqrt((b-a+1)*2));
  if(b-a<k){
    ToH3(a,b,p,q,r);
    return;
  }
  ToH43(a,b-k,p,s,q,r);
  ToH3(b-k+1,b,p,q,r);
  ToH43(a,b-k,s,q,r,p);
}


int main(){
  int n;
  cout << "Enter n:   ";
  cin >> n;
  registerme(n);

  int k = sqrt(n);

  startpart(1); ToH41(1,n,0,1,2,3); endpart(1);
  startpart(2); ToH42(1,n,0,1,2,3,k); endpart(2);
  startpart(3); ToH43(1,n,0,1,2,3); endpart(3);

}
