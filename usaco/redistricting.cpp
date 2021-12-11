#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i=a; i<=b; i++)
#define f first
#define s second
#define nl '\n'
typedef vector<int> vi;
typedef pair<int, int> pii;

struct segtree{
	vi mn;
	int n;

	void init(int N){
		n=N;
		mn.resize(4*n, 1e9);
	}

	void upd(int i, int v, int x, int lx, int rx){
		if(rx-lx==1){
			mn[x]=v;
			return;
		}
		mn[x]=min(mn[x], v);
		int m=(lx+rx)/2;
		if(i<m) upd(i, v, 2*x+1, lx, m);
		else upd(i, v, 2*x+2, m, rx);
		mn[x]=min(mn[2*x+1], mn[2*x+2]);
	}

	void upd(int i, int v){
		upd(i, v, 0, 0, n+1);
	}

	int get_min(int l, int r, int x, int lx, int rx){
		if(lx>=l && rx<=r) return mn[x];
		if(lx>=r || rx<=l) return 1e9;
		int m=(lx+rx)/2;
		return min(get_min(l, r, 2*x+1, lx, m), get_min(l, r, 2*x+2, m, rx));
	}

	int get_min(int l, int r){
		if(r<=l) return 1e9;
		return get_min(l, r, 0, 0, n+1);
	}
};

int n, k;
string s;
multiset<int> pmin[600001];
int dp[300001];
int hg[300001];
multiset<int> m;

int main(){
	cin.tie(0)->sync_with_stdio(0);
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);

	cin >> n >> k >> s;

	segtree st; st.init(2*n);
	dp[0]=0;
	hg[0]=n;
	pmin[n].insert(0);
	m.insert(0);
	st.upd(n, 0);
	int h=0;
	int g=0;
	rep(i, 1, n){
		if(i-k-1>=0){
			m.erase(m.find(dp[i-k-1]));
			pmin[hg[i-k-1]].erase(pmin[hg[i-k-1]].find(dp[i-k-1]));
			if(!pmin[hg[i-k-1]].empty()) st.upd(hg[i-k-1], *pmin[hg[i-k-1]].begin());
			else st.upd(hg[i-k-1], 1e9);
		}
		h+=s[i-1]=='H';
		g+=s[i-1]=='G';
		hg[i]=h-g+n;
		dp[i]=st.get_min(0, h-g+n);
		dp[i]=min(dp[i], 1+*m.begin());

		pmin[h-g+n].insert(dp[i]);
		st.upd(h-g+n, *pmin[h-g+n].begin());
		m.insert(dp[i]);
		// cout << dp[i] << nl;
	}

	cout << dp[n];
}
