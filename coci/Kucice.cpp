#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define f first
#define s second
// #define double long double

const int N=1001;
int n;
int x[N], y[N];
const int MOD=1e9+7;
const double PI=3.14159265358979;
int pw[N];
double alpha[N];

double angle(int i, int j){
  return atan2(x[i]-x[j], y[i]-y[j]);
}

int main(){
  cin.tie(0)->sync_with_stdio(0);

  cin >> n;
  x[n]=1e6;
  if(n==1){
    cout << 1; return 0;
  }
  pw[0]=1;
  for(int i=1; i<=n; i++){
    pw[i]=2*pw[i-1];
    if(pw[i]>=MOD) pw[i]-=MOD;
  }
  for(int i=0; i<n; i++){
    cin >> x[i] >> y[i];
  }

  ll ans=0;

  for(int i=0; i<n; i++){
    vector<double> pts;
    for(int j=0; j<n; j++){
      if(j==i) continue;
      pts.push_back(angle(i, j));
    }
    sort(pts.begin(), pts.end());

    queue<double> q;
    int it=2;
    int ad=0;
    while(it--){
      for(int j=0; j<n-1; j++) {
        while(q.size() && pts[j]-q.front()>=PI){
          q.pop();
        }
        if(!it) ad=(ad+pw[n-2-q.size()])%MOD;
        q.push(pts[j]);
        pts[j]+=2*PI;
      }
    }
    ans=(ans+pw[n]-ad-1+MOD)%MOD;
  }

  cout << ans;
}

// misread....