#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define int ll

const int N=200001;
const int K=18;
int n, m;
int t;
int par[N][K];
int tin[N], tout[N];
vector<int> adj[N];
int dp[N];
int ans[2*N];
vector<int> ed[N];
int edge[2*N][2];
vector<int> out[N];
map<pair<int, int>, int> mp;
map<pair<int, pair<int, int>>, int> mp2;
int ps[N], cnt[N];
ll SUM;

bool anc(int a, int b){
  return tin[a]<=tin[b] && tout[a]>=tout[b];
}

int lca(int u, int v){
  if(anc(u, v)) return u;
  for(int i=K-1; i>=0; i--){
    if(par[u][i] && !anc(par[u][i], v)) u=par[u][i];
  }
  return par[u][0];
}

int lca2(int u, int v){
  if(anc(u, v)) return u;
  for(int i=K-1; i>=0; i--){
    if(par[u][i] && !anc(par[u][i], v)) u=par[u][i];
  }
  return u;
}

void dfs(int x){
  tin[x]=++t;
  for(int k=1; k<K; k++){
    par[x][k]=par[par[x][k-1]][k-1];
  }
  for(int k:adj[x]){
    if(par[x][0]==k) continue;
    par[k][0]=x;
    dfs(k);
  }
  tout[x]=++t;
}


void dfs2(int x){
  for(int k:adj[x]){
    if(par[x][0]==k) continue;
    dfs2(k);
    dp[x]+=dp[k];
    mp[{x, k}]+=dp[k];
    cnt[x]+=cnt[k];
  }

  for(int e:ed[x]){
    dp[x]++;
    int a=lca2(edge[e][0], x);
    int b=lca2(edge[e][1], x);
    if(b!=x) mp[{x, b}]++;
    if(a!=x) mp[{x, a}]++;
    if(a!=x && b!=x) mp2[{x, {min(a, b), max(a, b)}}]++;
  }
}

void dfs3(int x){
  if(par[x][0]){
    SUM-=mp[{par[x][0], x}];
  }
  SUM+=dp[x];
  ps[x]=SUM;
  for(int i:out[x]) ans[i]+=SUM;
  
  for(int k:adj[x]){
    if(par[x][0]==k) continue;
    dfs3(k);
  }
  if(par[x][0]){
    SUM+=mp[{par[x][0], x}];
  }
  SUM-=dp[x];
}

signed main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("exercise.in", "r", stdin);
  freopen("exercise.out", "w", stdout);

  cin >> n >> m;
  for(int i=1; i<n; i++){
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1);

  for(int i=n; i<=m; i++){
    int u, v; cin >> u >> v;
    edge[i][0]=u;
    edge[i][1]=v;
    ed[lca(u, v)].push_back(i);
    out[u].push_back(i);
    out[v].push_back(i);
    cnt[u]++;
    cnt[v]++;
  }

  dfs2(1);
  dfs3(1);

  ll tot=0;
  assert(dp[1]==m-n+1);
  for(int i=n; i<=m; i++){
    int l=lca(edge[i][0], edge[i][1]);
    int a=lca2(edge[i][0], l);
    int b=lca2(edge[i][1], l);
    ans[i]=ans[i]-2*ps[l]+mp[{l, a}]+mp[{l, b}];
    ans[i]+=dp[1]-(a!=l)*(cnt[a]-dp[a])-(b!=l)*(cnt[b]-dp[b])+mp2[{l, {min(a, b), max(a, b)}}];
    tot+=m-(n-1)-1-ans[i];
  }
  cout << tot/2;
}

// fix one edge to get 1-cycle graph -> the other has to bridge two subtrees
// == not fully contained in one subtree

// dp[p] = sum of dp_children + # edges with lca p
// sub[c] = #cycle edges with lca par(c) & a node in c's subtree

// keep running prefix sums, store in map[node]
// walk down tree, when at p's child c, add dp[p]-(dp[c]+sub[c]) to running psum
// at each node process cycle edges that go out-- independently for the two nodes it connects
// for each, know its lca and the ans[edge] += (psum[i]-psum[lca])

// in end ans[i] = m-(n-1)-ans[i] + dp[par(lca)]-sub[lca]