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

int add(int a, int b){
  a+=b;
  if(a<0) a+=MOD;
  if(a>=MOD) a-=MOD;
  return a;
}

int mult(int a, int b){
  return (ll(a)*b)%MOD;
}

double aacos(double d){
  d=max(-1.0, d);
  d=min(1.0, d);
  return acos(d);
}

double angle(int i, int j, int k){
  pii u={x[i]-x[j], y[i]-y[j]};
  pii v={x[k]-x[j], y[k]-y[j]};
  double a=aacos((u.f*v.f+u.s*v.s) / sqrt(u.f*u.f+u.s*u.s) / sqrt(v.f*v.f+v.s*v.s));

  if(a<0) a+=2*PI;
  if(u.f*v.s-u.s*v.f>0) a=2*PI-a;
  return a;
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

  int ans=0;

  for(int i=0; i<n; i++){
    vector<double> pts;
    int in=n;
    for(int j=0; j<n; j++){
      if(j==i) continue;
      pts.push_back(angle(in, i, j));
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
        if(!it) ad+=pw[n-2-q.size()];
        q.push(pts[j]);
        pts[j]+=2*PI;
      }
    }
    ans=add(ans, pw[n]-ad-1);
  }

  cout << ans;
}

// misread....