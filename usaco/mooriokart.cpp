#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define sz(x) (int) x.size()
const int MOD=1e9+7;
#define f first
#define s second

int n, m;

ll add(ll a, ll b){
  return (a+b)%MOD;
}

ll mult(ll a, ll b){
  return (a*b)%MOD;
}

const int N=1501;
pair<int, ll> dp[2*N];
pair<int, ll> dp2[2*N];
vector<int> vec[N];
vector<int> adj[N];
int x, y;
int w[N][N];
int par[N];
vector<int> lens;

void dfs(int x){
  for(int k:adj[x]){
    if(par[x]!=k) par[k]=x, dfs(k);
  }
  for(int i=0; i<sz(adj[x]); i++){
    int a=adj[x][i];
    if(a==par[x]) continue;
    for(int k:vec[a]) vec[x].push_back(k+w[x][a]), lens.push_back(k+w[x][a]);
    for(int j=i+1; j<sz(adj[x]); j++){
      int b=adj[x][j];
      if(b==par[x]) continue;
      for(int l1:vec[a]){
        for(int l2:vec[b]){
          lens.push_back(l1+l2+w[x][a]+w[x][b]);
        }
      }
    }
  }
  vec[x].push_back(0);
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("mooriokart.in", "r", stdin);
  freopen("mooriokart.out", "w", stdout);

  cin >> n >> m >> x >> y;
  for(int i=1; i<=m; i++){
    int u, v, d; cin >> u >> v >> d;
    adj[u].push_back(v);
    adj[v].push_back(u);
    w[u][v]=w[v][u]=d;
  }

  int k=0;
  dp[0]={1, 0};
  for(int i=1; i<=n; i++){
    if(par[i]) continue;
    lens.clear();
    dfs(i);

    map<int, pair<int, int>> mp;
    for(int l:lens){
      mp[min(y, l)].f++;
      mp[min(y, l)].s=add(mp[min(y, l)].s, l);
    }

    for(int j=0; j<=y; j++){
      for(pair<int, pair<int, int>> pa:mp){
        pair<int, int> p=pa.s;
        dp2[min(y, j+pa.f+x)].f=add(dp2[min(y, j+pa.f+x)].f, mult(dp[j].f, p.f));
        dp2[min(y, j+pa.f+x)].s=add(dp2[min(y, j+pa.f+x)].s, add(mult(p.f, dp[j].s), mult(dp[j].f, p.s)));
      }
    }

    for(int i=0; i<=y; i++){
      dp[i]=dp2[i];
      // cout << dp[i].f << "," << dp[i].s  << " ";
      dp2[i]={0, 0};
    }
    k++;
  }
  ll ans=0;
  ll fac=1;
  ll pw=1;
  for(int i=1; i<=k-1; i++) fac=mult(fac, i), pw=mult(pw, 2);
  ans=add(dp[y].s, mult(dp[y].f, k*x));
  cout << mult(ans, mult(pw, fac));
}