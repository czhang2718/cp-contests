#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "bits/stdc++.h"

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
typedef long long ll;

const int N=200001;
int n, k;
int ind[N];
ord_set seg[4*N];

void upd(int i, int v, int x, int lx, int rx){
  seg[x].insert(v);
  // cout << lx << " " << rx << " insert " << v << '\n';
  if(rx-lx==1) return;
  int m=(lx+rx)/2;
  if(i<m) upd(i, v, 2*x+1, lx, m);
  else upd(i, v, 2*x+2, m, rx);
}

void upd(int i, int v){
  upd(i, v, 0, 0, n+1);
}

int calc(int l, int r, int v, int x, int lx, int rx){
  if(lx>=l && rx<=r){
    if(seg[x].size()==0) return 0;
    return seg[x].size()-(seg[x].order_of_key(v+k+1)-seg[x].order_of_key(v-k));
  }
  if(lx>=r || rx<=l) return 0;
  int m=(lx+rx)/2;
  return calc(l, r, v, 2*x+1, lx, m)+calc(l, r, v, 2*x+2, m, rx);
}

int calc(int l, int r, int v){
  return calc(l, r, v, 0, 0, n+1);
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("friendcross.in", "r", stdin);
  freopen("friendcross.out", "w", stdout);

  cin >> n >> k;
  for(int i=1; i<=n; i++){
    int x; cin >> x;
    ind[x]=i;
  }

  ll ans=0;
  for(int i=1; i<=n; i++){
    int x; cin >> x;
    ans+=calc(ind[x]+1, n+1, x);
    upd(ind[x], x);
  }
  cout << ans;
}