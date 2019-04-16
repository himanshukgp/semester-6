#include<bits/stdc++.h>

extern void registerme ( );
extern void startgame ( int );
extern int valquery ( int );
extern int sgnquery ( int );
extern int delquery ( int );
extern int sumquery ( int );
extern void checksoln ( int, int );

using namespace std;

void playgame0(){
  startgame(0);

  int i=0,L,R;
  while(1) { 
    if(valquery(i)>i) break;
    else i++;
  }
  L = i;
  R = valquery(i);
  checksoln(L,R);
}

int rec(int l, int r){
  // Utility function for playgame1() function
  // which output value found or -1 if not exist 
  // in given range.
  if(l>r) return -1;
  int mid = (l+r)/2;
  if(valquery(mid)!=mid) return mid;
  int k =  rec(l, mid-1);
  if(k!=-1) return k;
  return rec(mid+1,r);
}

void playgame1(){
  startgame(1);

  int i,L,R;
  L = rec(0, 999999999);
  R = valquery(L);
  // if L and R maybe reversed
  if(R<L){
    i = R;
    R = L;
    L = i;
  }
  checksoln(L,R);
}

void playgame2(){
  startgame(2);

  int left=0,right=999999999,temp,flag=0,v,R,L,mid;

  // binary search for 0. If L+R is odd then it 
  // will use all the log(N) allowed queries such 
  // that at the end left = (L+R+1)/2.
  while(left<=right){
    mid = (left+right)/2;
    temp = sgnquery(mid);
    if(temp==0) {
      flag=1;
      break;
    }
    else if(temp==-1) left=mid+1;
    else right = mid-1;
  }

  v = delquery(0);

  // Simply solve equation in both cases. 
  // Flag is used to check whether 0 is found.
  // if 0 is found that means mid has value (L+R)/2
  // else it means left has value (L+R+1)/2
  if(flag){
    R = (v+2*mid)/2;
    L = (2*mid-v)/2;
  }

  else{
    R = (left*2+v-1)/2;
    L = (left*2-v-1)/2;
  }

  checksoln(L,R);
}

void playgame3(){
  startgame(3);

  int L,R,left_sum,right_sum,mid_sum,v,mid,left=0,right=999999999;

  // Calculate initial values of sum at left
  // and right
  left_sum = sumquery(left);
  right_sum = sumquery(right);

  v = left_sum;

  // Binary search 
  while(left<=right){
    mid = (left+right)/2;
    mid_sum = sumquery(mid);
    if(left_sum==right_sum && left_sum==mid_sum) break;

    if(left_sum > right_sum) { 
      left=mid; 
      left_sum=mid_sum;
    }
    else { 
      right = mid; 
      right_sum = mid_sum;
    }
  }

  // Solve equation
  R = (v+mid_sum)/2;
  L = (v-mid_sum)/2;

  checksoln(L,R);
}

int main(){
  // Driver program
  registerme();
  playgame0();
  playgame1();
  playgame2();
  playgame3();
}
