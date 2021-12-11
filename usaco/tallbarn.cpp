#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;

const ld eps=.000000000;
ll n, k;
ll a[100001];
ld ans;
ll taken; //???FSD>FSDKL

bool check(ld m){
  taken=0;
  ans=0;
  for(int i=1; i<=n; i++){
    // a[i]/(c*(c+1))>=m
    // ax=c^2+c
    // c^2+c-a/x=0
    // c=(-1+/sqrt(1+4a/x))/2
    ll x=ll(-1+sqrt(1+(ld)4*a[i]/m))/2;
    // for(ll d=a[i]-1; d; d/=2){
    //   auto check2=[&](ll c)->bool{
    //     assert(c>0);
    //     return ld(a[i])/c/(c+1)>=m-eps;
    //   };
    //   while(x+d<a[i] && check2(x+d)) x+=d;
    // }
    taken+=x;
    ans+=ld(a[i])/(1+x);
  }
  return taken>=k;
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("tallbarn.in", "r", stdin);
  freopen("tallbarn.out", "w", stdout);

  // cout << fixed << setprecision(10);
  cin >> n >> k;
  k-=n;
  for(int i=1; i<=n; i++) cin >> a[i];

  ld l=0, r=1e12;
  for(int it=0; it<100; it++){
    ld m=(l+r)/2;
    if(check(m)) l=m;
    else r=m;
  }
  check(l);
  cout << (ll)roundl(ans-ld(k-taken)*l);
  // cout << ans << '\n';
  // cout << round(ans);
}

// strategy: place 1 in each, then greedily take from story which decreases the most
// simulate this by binary searching on the last decrease amt
// >= >= ... < 
// i get undertones of sadness