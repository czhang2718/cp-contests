#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define f first
#define s second

const int N=2002;
ll mx;
int n, k;
pair<int, int> a[N];
pair<int, ll> dp[N][N];

int search(int i, int j, pair<int, ll> c, int need){
	if(i==n+1) return c<=make_pair(0, 0LL);
	if(dp[i][j]<c) return 0;
	int ans=search(i+1, j, c, need);
	if(ans>=need) return ans;
	if(a[i].f>j) ans+=search(i+1, j+1, {c.f-1, c.s+a[i].s}, need-ans);
	return ans;
}

vector<pair<int, ll>> search2(int i, int j, pair<int, ll> c){
	if(i==n+1){
		if(c<=make_pair(0, 0LL)) return {{0, 0}};
		return {};
	}
	if(dp[i][j]<c) return {};
	vector<pair<int, ll>> ans=search2(i+1, j, c);
	if(a[i].f>j){
		vector<pair<int, ll>> add=search2(i+1, j+1, {c.f-1, c.s+a[i].s});
		for(auto p:add){
			ans.push_back({p.f+1, p.s-a[i].s});
			if(ans.size()==k) break;
		}
	}
	return ans;
}

int main(){
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> k;
	ll tot=0;
	for(int i=1; i<=n; i++){
		int w, d; cin >> w >> d;
		a[i]={d, w};
		tot+=w;
	}
	sort(a+1, a+n+1);

	for(int i=n; i>=1; i--){
		for(int j=0; j<i; j++){
			dp[i][j]=dp[i+1][j];
			if(a[i].f>j) dp[i][j]=max(dp[i][j], {dp[i+1][j+1].f+1, dp[i+1][j+1].s-a[i].s});
		}
	}

	mx=tot+1;
	auto convert=[&](ll x)->pair<int, ll>{
		return {x/mx, (x%mx)-mx+1};
	};
	ll c=ll(n+1)*mx;
	for(ll add=ll(n+1)*mx; add; add/=2){
		while(c-add>=0 && search(1, 0, convert(c-add), k)<k){
			c-=add;
		}
	}
	vector<pair<int, ll>> ans=search2(1, 0, convert(c));
	int s=k-ans.size();
	sort(ans.begin(), ans.end());
	reverse(ans.begin(), ans.end());
	for(auto p:ans) cout <<p.f << " " << -p.s << '\n';
	c--;
	while(s--){
		cout << convert(c).f << " " << -convert(c).s << "\n";
	}
}
// smallest c st cnt(x>=c) <=k