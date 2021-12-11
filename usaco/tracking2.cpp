#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

int n, K;
const int MOD=1e9+7;
const int N=100001;
ll dp[N];
ll ps[N];

ll bpow(ll a, int b){
  if(b==0) return 1;
  ll x=bpow(a, b/2);
  x=(x*x)%MOD;
  if(b&1) x=(x*a)%MOD;
  return x;
}

ll inv(int x){
  return bpow(x, MOD-2);
}

ll add(ll a, ll b){
  a+=b;
  a+=MOD;
  for(int i=0; i<2; i++) if(a>=MOD) a-=MOD;
  return a;
}

ll mult(ll a, ll b){
  return (a*b)%MOD;
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("tracking2.in", "r", stdin);
  freopen("tracking2.out", "w", stdout);

  cin >> n >> K;
  vector<pair<int, int>> seg;
  for(int i=1; i<=n-K+1; i++){
    int m; cin >> m;
    seg.push_back({m, -i});
  }
  sort(seg.begin(), seg.end(), greater<pair<int, int>>());
  for(int i=0; i<seg.size(); i++){
    seg[i].second*=-1;
  }

  ll ans=1;
  int s=0;
  set<int> avail;
  for(int i=1; i<=n; i++) avail.insert(i); //n+1 screw over stuff??

  while(s<n-K+1){
    int v=seg[s].first;
    vector<int> start={seg[s].second};

    while(s+1<n-K+1 && seg[s+1].first==seg[s].first){
      s++;
      start.push_back(seg[s].second);
    }

    vector<int> xc;
    for(int i:start){
      if(avail.lower_bound(i)==avail.end()) break;
      int j=*avail.lower_bound(i);
      while(j<i+K && *avail.lower_bound(j)==j){
        avail.erase(j);
        xc.push_back(j);
        j++;
      }
    }

    ll tot=1;
    int j=0;
    ll p=1;
    int op=1e9-v;
    pair<int, int> cur={0, 0};
    queue<pair<int, int>> q; q.push({0, 1});
    int r=start[start.size()-1];

    ll num=0;
    for(int k=0; k<xc.size(); k++){
      int i=xc[k];
      auto it=upper_bound(start.begin(), start.end(), i-K);
      if(it!=start.begin()){
        it--;
        cur={*it, *it+K-1};
      }
      while(cur.first && !q.empty() && q.front().first<cur.first){
        tot=add(tot, -q.front().second);
        q.pop();
      }
      dp[i]=mult(tot, p);
      if(i>=r) num=add(num, mult(dp[i], bpow(op, xc.size()-1-k)));
      tot=add(tot, mult(dp[i], inv(mult(p, op))));
      q.push({i, mult(dp[i], inv(mult(p, op)))});
      p=mult(p, op);
    }
    
    ans=mult(ans, num);
    s++;
  }

  cout << ans;
}
// 