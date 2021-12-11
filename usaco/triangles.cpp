#include "bits/stdc++.h"
using namespace std;

typedef pair<int, int> pii;
#define f first
#define s second
#define PI 3.141592653589
typedef pair<long long, long long> pll;

const int N=300;
int n;
int x[N], y[N];
int ans[N][N][N];
int cnt[2];
bool sign[N];
int c[N];
pair<double, int> pts[N];

int cross(int a, int b, int c){
  pll u={x[a]-x[b], y[a]-y[b]};
  pll v={x[c]-x[b], y[c]-y[b]};
  return (u.f*v.s-u.s*v.f>0);
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("triangles.in", "r", stdin);
  freopen("triangles.out", "w", stdout);

  cin >> n;
  for(int i=0; i<n; i++){
    cin >> x[i] >> y[i];
  }

  auto add=[&](int i, int j, int k, int v){
    int a=min(i, min(j, k));
    int c=max(i, max(j, k));
    int b;
    if(a!=i && c!=i) b=i;
    else if(a!=j && c!=j) b=j;
    else b=k;
    ans[a][b][c]+=v;
  };

  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      cnt[0]=cnt[1]=0;
      for(int k=0; k<n; k++){
        if(k==i || k==j) continue;
        sign[k]=(cross(i, j, k)>0);
        cnt[sign[k]]++;
      }
      for(int k=0; k<n; k++){
        if(k==i || k==j) continue;
        add(i, j, k, -(sign[k]?cnt[0]:cnt[1]));
        // cout << i << j  << k << " " << -(sign[k]?cnt[0]:cnt[1]) << "\n";
      }
    }
  }

  auto atann=[&](int a, int b)->double{
    if(!a && !b) return 0;
    if(a==0) return (b>0?PI/2:3*PI/2);
    return atan((double)b/a);
  };

  auto angle=[&](int k, int i, int j)->double{
    pii u={x[k]-x[i], y[k]-y[i]};
    pii v={x[j]-x[i], y[j]-y[i]};
    double a=atann(u.f, u.s)-atann(v.f, v.s);
    if(u.f<0) a+=PI;
    if(v.f<0) a-=PI;
    if(a<0) a+=2*PI;
    if(a<0) a+=2*PI;
    return a;
  };


  for(int i=0; i<n; i++){
    vector<pair<double, int>> pts;
    for(int k=0; k<n; k++){
      if(k==i) continue;
      double a=angle(k, i, i);
      pts.push_back({a, k});
    }
    sort(pts.begin(), pts.end());
    for(int j=0; j<n; j++){
      if(i==j) continue;
      int ind=-1;
      for(int k=0; k<n-1; k++){
        if(pts[k].s==j){
          ind=k; break;
        }
      }

      auto rot=[&](double a, double b)->double{
        double d=a-b;
        if(d<0) d+=2*PI;
        return d;
      }; 
      int cnt=0, k=(ind+1)%(n-1);
      while(k-ind-1<n-2 && rot(pts[k%(n-1)].f, pts[ind].f)<PI) k++;

      for(int p=0; p<n-2; p++){
        int j2=pts[(ind+p+1)%(n-1)].s;
        if(rot(pts[(ind+p+1)%(n-1)].f, pts[ind].f)>PI) break;
        while(k-ind-1<n-2 && (cross(j2, i, pts[k%(n-1)].s)>0)!=(cross(j2, i, j)>0)){
          cnt++; k++;
        }
        add(i, j, j2, cnt); 
      }
    }
  }

  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      for(int k=j+1; k<n; k++){
        c[ans[i][j][k]+n-3]++;
      }
    }
  }
  for(int i=0; i<n-2; i++) cout << c[i] << '\n';
}