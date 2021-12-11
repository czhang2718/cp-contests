#include "bits/stdc++.h"
using namespace std;

#define rep(i, a, b) for(int i=a; i<=b; i++)
#define trav(x, a) for(auto &x:a)
#define sz(x) (int) x.size()
#define nl '\n'
#define pb push_back
#define f first
#define s second
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N=200000;
int rnk[N];
int n;
string s;
string str[N];
int id[N];
int ix[N];
vector<pii> bucket[N];
int ind[N];
int lcp[N];
long long ans[N];
int mn[N];
int mn2[N];
int cut[N];

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("standingout.in", "r", stdin);
  freopen("standingout.out", "w", stdout);

  cin >> n;
  string t;
  for(int i=0; i<n; i++){
    cin >> t;
    for(int j=sz(s); j<sz(s)+sz(t); j++) id[j]=i, ix[j]=sz(t)-(j-sz(s));
    s+=t+"`";
  }

  // suffix array
  int pt=1;
  while(pt<sz(s)) pt*=2;
  while(sz(s)<pt) s+='`';

  vi sa;
  rep(i, 0, pt-1) rnk[i]=(s[i]-'`'), sa.pb(i);

  for(int k=0; (1<<k)<=pt; k++){
    rep(i, 0, max(26, pt-1)) bucket[i].clear();
    trav(i, sa){
      int lst=(k?(pt+i-(1<<(k-1)))%pt:i);
      bucket[rnk[lst]].pb({lst, rnk[i]});
    }
    pii p={-1, -1};
    int cur=-1;
    sa.clear();
    rep(i, 0, max(26, pt-1)){
      trav(j, bucket[i]){
        sa.pb(j.f);
        if(p.f==-1){
          rnk[j.f]=++cur;
          p={i, j.s}; continue;
        }

        if(make_pair(i, j.s)>p) rnk[j.f]=++cur;
        else rnk[j.f]=cur;
        p={i, j.s};
      }
    }
  }

  // //lcp
  rep(i, 0, pt-1) ind[sa[i]]=i;

  int k=-1;
  rep(i, 0, pt-1) {
    int j=ind[i];
    if(j==0) continue;
    while(k+1+sa[j-1]<pt && s[sa[j-1]+k+1]==s[i+k+1] && s[i+k+1]!='`') k++;
    lcp[j-1]=k+1;
    if(k!=-1) k--;
  }

  for(int i=pt-2; i>=0; i--){
    if(s[sa[i]]=='`') continue;
    mn[i]=lcp[i];
    if(sa[i]!=pt-1 && id[sa[i]]==id[sa[i+1]]) mn[i]=min(mn[i+1], lcp[i]);
  }
  rep(i, 1, pt-1){
    if(s[sa[i]]=='`') continue;
    mn2[i]=lcp[i-1];
    if(sa[i] && id[sa[i]]==id[sa[i-1]]) mn2[i]=min(mn2[i], mn2[i-1]);
    cut[i]=max(mn[i], mn2[i]);
    ans[id[sa[i]]]+=ix[sa[i]]-max(cut[i], (sa[i] && id[sa[i]]==id[sa[i-1]]?lcp[i-1]:0));
  }

  rep(i, 0, n-1) cout << ans[i] << nl;
}