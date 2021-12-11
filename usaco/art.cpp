#include "bits/stdc++.h"
using namespace std;

const int N=1001;
int n;
int a[N][N];
int l[N*N], r[N*N], u[N*N], d[N*N];
int ps[N+1][N+1];
bool bad[N*N];

#define nl '\n'

int main(){
  freopen("art.in", "r", stdin);
  freopen("art.out", "w", stdout);
  
  set<int> s;
  cin >> n;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      int x; cin >> x;
      a[i][j]=x;
      if(x) s.insert(x);
      l[x]=(!l[x]?j:min(l[x], j));
      r[x]=max(r[x], j);
      u[x]=(!u[x]?i:min(u[x], i));
      d[x]=max(d[x], i);
    }
  }
  if(s.size()==1){
    cout << max(1, n*n-1); return 0;
  }

  auto add=[&](int x1, int y1, int x0, int y0){
    // cout << "add " << x1 << " " << y1 << " " << x0 << " " << y0 << '\n';
    ps[x0][y0]++;
    ps[x1+1][y0]--;
    ps[x0][y1+1]--;
    ps[x1+1][y1+1]++;
  };

  for(int i=1; i<=n*n; i++){
    if(!d[i]) continue;
    add(d[i], r[i], u[i], l[i]);
  }

  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      ps[i][j]+=ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
      // cout << ps[i][j] << " ";
      if(ps[i][j]>1) bad[a[i][j]]=1;
    }
    // cout << '\n';
  }

  int ans=0;
  for(int i=1; i<=n*n; i++) if(!bad[i]) ans++;
  cout << ans;
}