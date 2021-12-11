#include "bits/stdc++.h"
using namespace std;

#define f first
#define s second
#define nl '\n'

const int N=100001;
int q;
int par[N][17];
const int B=190;
vector<int> adj[N];
pair<int, int> mx;
int a, b;
int dist[N];
int comp[N];
int n=0;
pair<int, int> diam[N];
bool done[N];
int h[N];
int logv[N];

void dfs(int x, int prv){
  mx=max(mx, {dist[x], x});
  for(int u:adj[x]){
    if(u==prv) continue;
    dist[u]=dist[x]+1;
    dfs(u, x);
  }
}

void build(){
  for(int i=1; i<=n; i++){
    int c=comp[i];
    if(done[c]) continue;
    mx={0, -1};
    dist[c]=0;
    dfs(c, 0);
    a=mx.s;
    mx={0, -1};
    dist[a]=0;
    dfs(a, 0);
    b=mx.s;
    diam[c]={a, b};
    done[c]=1;
  }
  for(int i=1; i<=n; i++) done[i]=dist[i]=0;
}

int lca(int a, int b){
  if(a==b) return a;
  if(h[a]<h[b]) swap(a, b);
  for(int i=logv[a]; i>=0; i--){
    if(par[a][i] && h[par[a][i]]>h[b]) a=par[a][i];
  }
  if(h[a]!=h[b]) a=par[a][0];
  if(a==b) return a;
  for(int i=logv[a]; i>=0; i--){
    if(par[a][i] && par[a][i]!=par[b][i]) a=par[a][i], b=par[b][i];
  }
  return par[a][0];
}

int dis(int a, int b){
  int l=lca(a, b);
  return h[a]+h[b]-2*h[l];
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("newbarn.in", "r", stdin);
  freopen("newbarn.out", "w", stdout);
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  cin >> q;
  while(q--) {
    char op; cin >> op;
    if(op=='B'){
      n++;
      int p; cin >> p;
      if(p==-1){
        comp[n]=n; 
        if(n%B==0) build();
        continue;
      }
      comp[n]=comp[p];
      par[n][0]=p;
      h[n]=h[p]+1;
      adj[n].push_back(p);
      adj[p].push_back(n);
      for(int i=1; ; i++){
        par[n][i]=par[par[n][i-1]][i-1];
        logv[n]++;
        if(par[n][i]==0) break;
      }
      if(n%B==0) build();
    }
    else{
      int x; cin >> x;
      int ans=0;
      if(diam[comp[x]].first) ans=dis(x, diam[comp[x]].first);
      if(diam[comp[x]].second) ans=max(ans, dis(x, diam[comp[x]].second));
      for(int j=n; j%B; j--) if(comp[j]==comp[x]) ans=max(ans, dis(x, j));
      cout << ans << nl;
    }
    
  }
}
// n*sqrt(n)*log(n)

// N^2/B + NBlog(N)
// B=100
// or 150ish

// speed up: log = current log(n)
//           increase B?
//           
// bugs: old value of L not big enough- use lg[n] instead
//       for(int j=n; (j==n || j%B); j--) j==n for j multiple of B
//       reset when # nodes mult of B, NOT i