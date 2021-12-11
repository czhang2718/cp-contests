#include "bits/stdc++.h"
using namespace std;

const int N=100001;
int n, K;
vector<int> adj[N];
bool bad;
int cnt[N];

int dfs(int x, int par){
  vector<int> rem;
  for(int k:adj[x]){
    if(k==par) continue;
    int res=dfs(k, x);
    if(res==-1){
      bad=1; return res;
    }
    res++;
    if(res==K) continue;
    rem.push_back(res);
  }

  for(int v:rem){
    cnt[v]++;
    if(K-v==v?cnt[K-v]>=2:cnt[K-v]>=1){
      cnt[v]--;
      cnt[K-v]--;
    }
  }
  
  int out=0;
  for(int v:rem){
    if(cnt[v]){
      if((out && out!=v) || cnt[v]>1){
        // cout << "bad " << v << " " << out << "\n";
        out=-1; break;
      }
      out=v;
    }
  }
  for(int v:rem) cnt[v]=0;
  // cout << x << " " << out << '\n';
  if(out==-1 || (out!=0 && x==1)) bad=1;
  return out;
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("deleg.in", "r", stdin);
  freopen("deleg.out", "w", stdout);

  cin >> n;
  for(int i=1; i<=n-1; i++){
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for(int i=1; i<=n-1; i++){
    if((n-1)%i){
      cout << "0"; 
      continue;
    }
    K=i;
    bad=0;
    // cout << "K=" << i << '\n';
    dfs(1, 0);
    cout << (bad?"0":"1");
  }
}