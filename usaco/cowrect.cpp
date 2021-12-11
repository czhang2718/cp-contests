#include "bits/stdc++.h"
using namespace std;

int n;
const int M=1002;
int h[M][M];
int g[M][M];
vector<pair<int, int>> cows;

#define f first
#define s second

int main(){
  freopen("cowrect.in", "r", stdin);
  freopen("cowrect.out", "w", stdout);
  cin >> n;
  for(int i=0; i<n; i++){
    int x, y; char c; cin >> x >> y >> c;
    x++; y++;
    if(c=='H') h[x][y]++, cows.push_back({x, y});
    else g[x][y]++;
  }

  for(int x=1; x<=1001; x++){
    for(int y=1; y<=1001; y++){
      h[x][y]+=h[x-1][y]+h[x][y-1]-h[x-1][y-1];
      g[x][y]+=g[x-1][y]+g[x][y-1]-g[x-1][y-1];
    }
  }

  auto garea=[&](int x1, int y1, int x0, int y0){
    return g[x1][y1]-g[x1][y0-1]-g[x0-1][y1]+g[x0-1][y0-1];
  };
  auto harea=[&](int x1, int y1, int x0, int y0){
    return h[x1][y1]-h[x1][y0-1]-h[x0-1][y1]+h[x0-1][y0-1];
  };

  pair<int, int> ans={1e9, 0};
  for(int i=0; i<cows.size(); i++){
    for(int j=i+1; j<cows.size(); j++){
      pair<int, int> a=cows[i];
      pair<int, int> b=cows[j];
      // a
      // b
      if(a.f>b.f) swap(a, b);
      int l=min(a.s, b.s);
      int r=max(a.s, b.s);
      if(garea(b.f, r, a.f, l)) continue;
      int L=l, R=r;
      while(l-1>0 && !garea(b.f, l-1, a.f, l-1)){
        l--;
        if(harea(b.f, l, a.f, l)) L=l;
      }
      while(r+1<=1001 && !garea(b.f, r+1, a.f, r+1)){
        r++;
        if(harea(b.f, r, a.f, r)) R=r;
      }
      ans=min(ans, {-harea(b.f, r, a.f, l), (R-L)*(b.f-a.f)});
    }
  }
  cout << -ans.f << '\n' << ans.s;
}

// 