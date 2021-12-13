#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int N=200001;
int n;
int a[N];
int last[N];
ll sum[4*N];
ll on[4*N];
ll lazy[4*N];
int L[N];

void push(int x, int lx, int rx){
  if(rx-lx==1) return;
  lazy[2*x+1]+=lazy[x];
  lazy[2*x+2]+=lazy[x];
  sum[2*x+1]+=on[2*x+1]*lazy[x];
  sum[2*x+2]+=on[2*x+2]*lazy[x];
  lazy[x]=0;
}

ll get_sum(int l, int r, int x, int lx, int rx){
  push(x, lx, rx);
  if(lx>=l && rx<=r) return sum[x];
  if(lx>=r || rx<=l) return 0;
  int m=(lx+rx)/2;
  return get_sum(l, r, 2*x+1, lx, m)+get_sum(l, r, 2*x+2, m, rx);
}

ll get_sum(int l, int r){
  if(r<=l) return 0;
  return get_sum(l, r, 0, 0, n+1);
}

void deact(int i, int x, int lx, int rx){
  push(x, lx, rx);
  if(rx-lx==1){
    sum[x]=0;
    on[x]=0;
    return;
  }
  int m=(lx+rx)/2;
  if(i<m) deact(i, 2*x+1, lx, m);
  else deact(i, 2*x+2, m, rx);
  sum[x]=sum[2*x+1]+sum[2*x+2];
  on[x]=on[2*x+1]+on[2*x+2];
}

void deact(int i){
  deact(i, 0, 0, n+1);
}

void act(int i, int x, int lx, int rx){
  push(x, lx, rx);
  if(rx-lx==1){
    on[x]=1;
    return;
  }
  int m=(lx+rx)/2;
  if(i<m) act(i, 2*x+1, lx, m);
  else act(i, 2*x+2, m, rx);
  on[x]=on[2*x+1]+on[2*x+2];
}

void act(int i){
  act(i, 0, 0, n+1);
}

void add(int l, int r, int v, int x, int lx, int rx){
  push(x, lx, rx);
  if(lx>=l && rx<=r){
    sum[x]+=v*on[x];
    lazy[x]+=v;
    return;
  }
  if(lx>=r || rx<=l) return;
  int m=(lx+rx)/2;
  add(l, r, v, 2*x+1, lx, m);
  add(l, r, v, 2*x+2, m, rx);
  sum[x]=sum[2*x+1]+sum[2*x+2];
}

void add(int l, int r, int v){
  if(r<=l) return;
  add(l, r, v, 0, 0, n+1);
}

int main(){
  cin.tie(0)->sync_with_stdio(0);

  cin >> n;
  for(int i=1; i<=n; i++){
    cin >> a[i];
  }

  ll ans=0;
  for(int i=1; i<=n; i++){
    L[i]=last[a[i]];
    ans+=get_sum(last[a[i]]+1, i);
    // cout << "add " << get_sum(last[a[i]]+1, i) << "\n";
    deact(last[a[i]]);
    add(L[last[a[i]]]+1, last[a[i]], -1);
    act(i);
    add(last[a[i]]+1, i, 1);
    last[a[i]]=i;

    // for(int j=1; j<=n; j++){
    //   cout << get_sum(j, j+1) << " ";
    // }
    // cout << "\n";
  }
  cout << ans;
}







