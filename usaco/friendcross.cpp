#include "bits/stdc++.h"
using namespace std;

struct Fenwick{
  int n;  
  vector<int> bit;

  Fenwick(){
    // 🤡
  }

  Fenwick(int n){
    this->n=n;
    bit.resize(n+5, 0);
  }

  void upd(int i){
    i++;
    while(i<=n){
      bit[i]++;
      i+=(i&(-i));
    }
  }

  int sum(int r){
    r++;
    int ret=0;
    while(r){
      ret+=bit[r];
      r-=(r&(-r));
    }
    return ret;
  }
};

const int N=100000;
int n, k;
vector<int> vec[4*N];
int ind[N+1], a[N];
Fenwick ft[4*N];


void build(int x, int lx, int rx){
  Fenwick tree(rx-lx);
  ft[x]=tree;
  if(rx-lx==1){
    vec[x].push_back(a[lx]);
    return;
  }
  int m=(lx+rx)/2;
  build(2*x+1, lx, m);
  build(2*x+2, m, rx);
  int i=0, j=0;
  while(i+j<rx-lx){
    if(i==m-lx) vec[x].push_back(vec[2*x+2][j++]);
    else if(j==rx-m) vec[x].push_back(vec[2*x+1][i++]);
    else{
      if(vec[2*x+1][i]<vec[2*x+2][j]) vec[x].push_back(vec[2*x+1][i++]);
      else vec[x].push_back(vec[2*x+2][j++]);
    }
  }
  // cout << "Vec " << lx << " " << rx << "\n";
  // for(int k:vec[x]) cout << k << " ";
  // cout << '\n';
}

void insert(int i, int x, int lx, int rx){
  int j=lower_bound(vec[x].begin(), vec[x].end(), a[i])-vec[x].begin();
  // cout << lx << " " << rx << " ind " << a[i] << " is " << j << "\n";
  ft[x].upd(j);
  if(rx-lx==1) return;
  int m=(lx+rx)/2;
  if(i<m) insert(i, 2*x+1, lx, m);
  else insert(i, 2*x+2, m, rx);
}

void insert(int i){
  insert(i, 0, 0, n);
}

int calc(int l, int r, int v, int x, int lx, int rx){
  if(lx>=r || rx<=l) return 0;
  if(lx>=l && rx<=r){
    int ret=0;
    int i=lower_bound(vec[x].begin(), vec[x].end(), v-k)-vec[x].begin();
    ret+=ft[x].sum(i-1);
    i=upper_bound(vec[x].begin(), vec[x].end(), v+k)-vec[x].begin();
    ret+=ft[x].sum(rx-lx-1)-ft[x].sum(i-1);
    return ret;
  }
  int m=(lx+rx)/2;
  return calc(l, r, v, 2*x+1, lx, m)+calc(l, r, v, 2*x+2, m, rx);
}

int calc(int l, int r, int v){
  if(r<=l) return 0;
  return calc(l, r, v, 0, 0, n);
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("friendcross.in", "r", stdin);
  freopen("friendcross.out", "w", stdout);

  cin >> n >> k;
  for(int i=0; i<n; i++){
    cin >> a[i];
    ind[a[i]]=i;
  }

  build(0, 0, n);
  long long ans=0;
  for(int i=0; i<n; i++){
    int x; cin >> x;
    ans+=calc(ind[x]+1, n, x);
    insert(ind[x]);
  }
  cout << ans;
}