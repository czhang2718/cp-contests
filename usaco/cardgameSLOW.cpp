#include "bits/stdc++.h"
using namespace std;

const int N=100001;
int ans[N];
int n;
bool use[N];
vector<int> elsie, bessie;
int lg[N];

struct segtree{
  int n;
  vector<int> mn, lazy;

  segtree(int n){
    this->n=n;
    mn.resize(4*n, 1e9);
    lazy.resize(4*n, 0);
  }

  void reset(){
    mn.clear(); lazy.clear();
    mn.resize(4*n, 1e9);
    lazy.resize(4*n, 0);
  }

  void push(int x, int lx, int rx){
    if(rx-lx==1){
      lazy[x]=0;
      return;
    }
    mn[2*x+1]+=lazy[x];
    lazy[2*x+1]+=lazy[x];
    mn[2*x+2]+=lazy[x];
    lazy[2*x+2]+=lazy[x];
    lazy[x]=0;
  }

  void add(int l, int r, int v, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r){
      lazy[x]=v;
      // cout << "mn " << lx << " " << rx << " += " << v << '\n';
      mn[x]+=v;
      // cout << "mn " << lx << " " << rx << " = " << mn[x] << '\n';
      return;
    }
    if(lx>=r || rx<=l) return;
    int m=(lx+rx)/2;
    add(l, r, v, 2*x+1, lx, m);
    add(l, r, v, 2*x+2, m, rx);
    mn[x]=min(mn[2*x+1], mn[2*x+2]);
  }

  void add(int l, int r, int v){
    if(r<=l) return;
    add(l, r, v, 0, 0, n+1);
  }


  int get_min(int l, int r, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r) return mn[x];
    if(lx>=r || rx<=l) return 2e9;
    int m=(lx+rx)/2;
    return min(get_min(l, r, 2*x+1, lx, m), get_min(l, r, 2*x+2, m, rx));
  }

  int get_min(int l, int r){
    return get_min(l, r, 0, 0, n+1);
  }

  void set(int i, int v){
    // cout << "set " << i << " " << v << ' ';
    int old=get_min(i, i+1);
    // cout << old << " ";
    add(i, i+1, -old+v);
    // cout << get_min(i, i+1) << '\n';
  }
};

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("cardgame.in", "r", stdin);
  freopen("cardgame.out", "w", stdout);

  cin >> n;
  for(int i=2; i<=2*n; i++) lg[i]=lg[i/2]+1;
  for(int i=0; i<n; i++){
    int x; cin >> x;
    elsie.push_back(x);
    use[x]=1;
  }
  for(int i=2*n; i>=1; i--){
    if(!use[i]) bessie.push_back(i);
  }

  set<pair<int, bool>> ind;
  int cur=0;
  segtree st(2*n), st2(2*n);

  auto badd=[&](int i){
    // cout << "bessie insert " << i << "\n";
    int prv;
    if(ind.size()==0 || (*ind.begin()).first>i) prv=0;
    else{
      auto p=*--ind.lower_bound({i, 0});
      prv=st.get_min(p.first, p.first+1);
      if(p.second && prv) prv--;
      if(!p.second) prv++;
    }
    ind.insert({i, 1});
    st.set(i, prv);
    st2.set(i, prv);
    // cout << "set " << i << " " << prv << "\n";
    // cout << "set "
    if(!prv) return;
    if(st.get_min(i+1, 2*n+1)>1e8){
      cur++; return;
    }
    
    if(i==2*n) return;
    int j=i+1;
    
    for(int k=lg[2*n-j]; k>=0; k--){
      if(j+(1<<k)<=2*n && st2.get_min(i+1, j+(1<<k)+1)>1) j+=(1<<k);
    }
    if(j==2*n){
      st.add(i+1, j+1, -1);
      st2.add(i+1, j+1, -1);
      // for(int i=1; i<=2*n; i++){
      //   int x=st.get_min(i, i+1);
      //   cout << (x==1e9?-1:x) << " ";
      // }
      // cout << '\n';
      cur++;
      return;
    }
    if(st2.get_min(j, j+1)>1) j++;
    // cout << "bessie insert " << i << "  " << j << " " << st2.get_min(j+1, j+2) << "\n";
    // assert(st2.get_min(j+1, j+2)==1);
    st.add(i+1, j+1, -1);
    st2.add(i+1, j+1, -1);
    // for(int i=1; i<=2*n; i++){
    //   int x=st.get_min(i, i+1);
    //   cout << (x==1e9?-1:x) << " ";
    // }
    // cout << '\n';


    // cout << "st2\n";
    // for(int i=1; i<=2*n; i++){
    //   int x=st2.get_min(i, i+1);
    //   cout << (x==1e9?-1:x) << " ";
    // }
    // cout << '\n';
  };

  auto eadd=[&](int i){
    // cout << "elsie insert " << i << "\n";
    int prv;
    if(ind.size()==0 || (*ind.begin()).first>i) prv=0;
    else{
      auto p=*--ind.lower_bound({i, 0});
      prv=st.get_min(p.first, p.first+1);
      if(p.second && prv) prv--;
      if(!p.second) prv++;
    }
    // cout << "prv " << prv << "\n";
    ind.insert({i, 0});
    st.set(i, prv);
    if(i==2*n) return;
    int j=i+1;
    for(int k=lg[2*n-j]; k>=0; k--){
      if(j+(1<<k)<=2*n && st2.get_min(i+1, j+(1<<k)+1)>0) j+=(1<<k);
    }
    if(j==2*n){
      st.add(i+1, 2*n+1, 1), st2.add(i+1, 2*n+1, 1);
      // for(int i=1; i<=2*n; i++){
      //   int x=st.get_min(i, i+1);
      //   cout << (x==1e9?-1:x) << " ";
      // }
      // cout << '\n';
      return;
    }
    
    if(st2.get_min(j, j+1)>0) j++;
    cur++, st.add(i+1, j+1, 1), st2.add(i+1, j+1, 1);
    // cout << "e j " << j << "\n";

    // for(int i=1; i<=2*n; i++){
    //   int x=st.get_min(i, i+1);
    //   cout << (x==1e9?-1:x) << " ";
    // }
    // cout << '\n';
  };

  
  for(int i=0; i<n; i++){
    eadd(elsie[i]); badd(bessie[i]);
    ans[i+1]+=cur;
  }

  st.reset(); st2.reset();
  ind.clear();
  cur=0;
  for(int i=n-1; i>=0; i--){
    int b=2*n+1-bessie[i];
    int e=2*n+1-elsie[i];
    eadd(e); badd(b); 
    ans[i]+=cur;
  }

  int mx=0;
  for(int i=0; i<=n; i++){
    mx=max(mx, ans[i]);
  }
  cout << mx;
}