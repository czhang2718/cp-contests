/*

CHT
slide j, f_j(i) is concave (induct). cht. f(x) = arithmetic term + k*x^2.
keep track of arithmetic prog start locations, initial value, 
time of creation. vector + binary search

 */

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define int ll
typedef pair<int, int> pii;
#define f first
#define s second

const int M=200001;
const int Q=M;
int n, m, q;
vector<int> qu[M];
int c[M], xc[Q], ans[Q];

signed main(){
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> m;
  for(int i=0; i<m; i++){
    cin >> c[i];
  }

  cin >> q;
  for(int i=0; i<q; i++){
    int y; cin >> xc[i] >> y;
    qu[y-1].push_back(i);
  }

  int t=0;
  vector<pair<pii, pii>> a;
  // x t old a

  auto sq=[&](int x)->ll{
    return ll(x)*x;
  };

  auto eval=[&](int x)->ll{
    auto p=*--upper_bound(a.begin(), a.end(), make_pair(make_pair(x, ll(1e18)), make_pair(ll(1e18), ll(1e18))));
    return p.s.f+ll(t-p.f.s)*sq(x)+(x-p.f.f)*p.s.s;
  };

  auto insert=[&](int b){
    int x=n;
    for(int i=n-1; i; i/=2){
      while(x-i>=1 && eval(x-i+1)+sq(x-i+1)-(eval(x-i)+sq(x-i))>=b) x-=i;
    }
    ll old=eval(x);
    while(a.size() && a[a.size()-1].f.f>=x) a.pop_back(); 
    t++;
    a.push_back({{x, t}, {old+sq(x), b}});
  };

  a={{{1, t}, {0, c[0]}}};
  for(int j:qu[0]){
    ans[j]=eval(xc[j]);
  }

  for(int i=1; i<m; i++){
    insert(c[i]);
    for(int j:qu[i]){
      ans[j]=eval(xc[j]);
    }
  }

  for(int i=0; i<q; i++) cout << ans[i] << '\n';
}