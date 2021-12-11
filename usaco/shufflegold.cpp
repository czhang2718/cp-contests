#include "bits/stdc++.h"
using namespace std;

const int M=100001;
int ip[M];
int p[M];
int n, m, q, cc;
int v[M];
int cyc[M];
vector<int> cycle[M];
bool vis[M];
vector<int> nodes;
int ind[M];
int j;

void dfs(int x){
  cyc[x]=cc;
  ind[x]=j;
  j++;
  nodes.push_back(x);
  vis[x]=1;
  if(vis[ip[x]+1]) return;
  dfs(ip[x]+1);
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("shufflegold.in", "r", stdin);
  freopen("shufflegold.out", "w", stdout);

  cin >> n >> m >> q;
  for(int i=1; i<=m; i++){
    cin >> p[i];
    ip[p[i]]=i;
  }
  int cnt=1;
  int cur=0;
  while(true){
    v[cnt]=cur;
    vis[cur]=1;
    ind[cur]=cnt;
    if(ip[cur]==m) break;
    cnt++;
    cur=ip[cur]+1;
  }
  cnt++;

  cc=1;
  for(int i=2; i<=m; i++){
    if(vis[i]) continue;
    nodes.clear();
    j=0;
    dfs(i);
    cycle[cc]=nodes;
    cc++;
  }

  auto solve=[&](int i, int k)->int{
    // cout << "solve " << i << " " << k << "\n";
    if(!cyc[k]){
      if(i<cnt-ind[k]){
        int x=v[ind[k]+i-1];
        return ip[x];
      }
      else{
        i-=(cnt-1-ind[k]);
        return i+m-1;
      }
    }
    k=cycle[cyc[k]][(ind[k]+i-1)%(cycle[cyc[k]].size())];
    return ip[k];
  };

  while(q--){
    int x; cin >> x;
    x=n-x+1;
    if(x>n-m+1) cout << solve(n-m+1, x-(n-m)) << '\n';
    else cout << solve(x, 1) << '\n';
  }
}
// q_i -> n-q_i+1
// p_x = PY^-1[i]=x
// let f(x) = p_x + 1 if p_x!=n
//            deadend otherwise
// (1, Q) -> (f(1), Q-1) -> ... -> (smth, deadend) or (smth, 1)
// path is line
// if 1st ans = smth+n-1
// if 2nd ans = ip[smth]