#include "bits/stdc++.h"
using namespace std;

int n, r;
const double PI=3.14159265358929;

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("sight.in", "r", stdin);
  freopen("sight.out", "w", stdout);

  cin >> n >> r;

  vector<pair<double, double>> a;
  priority_queue<double, vector<double>, greater<double>> pq;

  for(int i=0; i<n; i++){
    int x, y; cin >> x >> y;
    double al=acos(r/sqrt(1.0*x*x+1.0*y*y));
    double a0=atan(1.0*y/x);
    if(x<0) a0+=PI;
    a0-=al;
    if(a0<0) a0+=2*PI;
    a.push_back({a0, a0+2*al});
  }
  sort(a.begin(), a.end());

  int ans=0;
  int it=2;
  while(it--){
    for(int i=0; i<n;i++){
      while(!pq.empty() && pq.top()<a[i].first) pq.pop();
      if(!it) ans+=pq.size();
      pq.push(a[i].second);
      a[i].first+=2*PI;
      a[i].second+=2*PI;
    }
  }
  cout << ans;
}