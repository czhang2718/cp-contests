#include "grader.h"
#include<bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
typedef pair<int, int> pii;

const int N=100001;
const int K=17;
int n, q;
vector<int> adj[N];
int ss[N];
pii loc[N];
int par[N][K];
int tin[N], tout[N];
int t;

bool anc(int a, int b){
  return tin[a]<=tin[b] && tout[a]>=tout[b];
}

int lca(int a, int b){
  if(anc(a, b)) return a;
  int x=a;
  for(int i=K-1; i>=0; i--){
    if(par[x][i] && !anc(par[x][i], b)) x=par[x][i];
  }
  return par[x][0];
}

void dfs(int x){
  tin[x]=++t;
  ss[x]=1;
  for(int i=1; i<K; i++){
    par[x][i]=par[par[x][i-1]][i-1];
  }
  for(int u:adj[x]){
    if(par[x][0]==u) continue;
    par[u][0]=x;
    dfs(u);
    ss[x]+=ss[u];
  }
  tout[x]=++t;
}

void solve(int x){
  int sy=ss[x];
  int sx=0;
  for(int i=0; i<adj[x].size(); i++){
    int k=adj[x][i];
    if(par[x][0]==k) continue;
    sy-=ss[k];
    loc[k]={loc[x].f+sx+1, loc[x].s+sy+1};
    sx+=ss[k];
    solve(k);
  }
}

void addRoad(int a, int b){
  adj[a+1].pb(b+1);
  adj[b+1].pb(a+1);
}

void buildFarms(){
  n=getN();
  dfs(1);
  loc[1]={1, 1};
  solve(1);
  for(int i=1; i<=n; i++){
    setFarmLocation(i, loc[i].f, loc[i].s);
  }
}

void notifyFJ(int a, int b){
  a++; b++;
  vector<int> x, y;
  int l=lca(a, b);
  addBox(loc[l].f, loc[l].s, loc[a].f, loc[a].s);
  if(!anc(a, b) && !anc(b, a)) addBox(loc[l].f, loc[l].s, loc[b].f, loc[b].s);
}
// I had a dream I could fly my way to heaven
// When I awoke I spent it on a necklace