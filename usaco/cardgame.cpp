#include "bits/stdc++.h"
using namespace std;

const int N=100001;
int n;
bool have[N];
int ans[N];
int pairs[4*N], red[4*N], blue[4*N];

void comb(int x){
	int g=min(red[2*x+1], blue[2*x+2]);
	red[x]=red[2*x+1]+red[2*x+2]-g;
	blue[x]=blue[2*x+1]+blue[2*x+2]-g;
	pairs[x]=pairs[2*x+1]+pairs[2*x+2]+g;
}

void upd(int i, int b, int r, int x, int lx, int rx){
	if(rx-lx==1){
		red[x]+=r;
		blue[x]+=b;
		return;
	}
	int m=(lx+rx)/2;
	if(i<m) upd(i, b, r, 2*x+1, lx, m);
	else upd(i, b, r, 2*x+2, m, rx);
	comb(x);
}

void upd(int i, int b, int r){
	upd(i, b, r, 0, 0, 2*n+1);
}

void reset(){
	for(int i=0; i<4*2*n; i++){
		red[i]=blue[i]=pairs[i]=0;
	}
}

int main(){
  cin.tie(0)->sync_with_stdio(0);
  freopen("cardgame.in", "r", stdin);
  freopen("cardgame.out", "w", stdout);

  cin >> n;
  vector<int> e, b;
  for(int i=0; i<n ;i++){
  	int x; cin >> x;
  	have[x]=1;
  	e.push_back(x);
  }
  for(int i=2*n; i>=1; i--){
  	if(have[i]) continue;
  	b.push_back(i);
  }

  for(int i=0; i<n; i++){
  	upd(b[i], 1, 0);
  	upd(e[i], 0, 1);
  	ans[i+1]=pairs[0];
  	// cout << pairs[0] << "\n";
  }
  reset();
  for(int i=n-1; i>=0; i--){
  	upd(2*n+1-b[i], 1, 0);
  	upd(2*n+1-e[i], 0, 1);
  	ans[i]+=pairs[0];
  }
  int mx=0;
  for(int i=0; i<=n; i++){
  	mx=max(mx, ans[i]);
  }
  cout << mx;
}