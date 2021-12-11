#include "bits/stdc++.h"
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

int i2=500000004;
int i6=166666668;
const int mod=1e9+7;
int n, k, P, ans, all;

int add(int a, int b){
	return (ll(a)+b)%mod;
}

int mult(int a, int b){
	return (ll(a)*b)%mod;
}

int c2(int x){
	return mult(mult(x, x-1), i2);
}

int c3(int x){
	return mult(x, mult(mult(x-1, x-2), i6));
}

int len(vector<pii> v){
	int ret=0;
	for(auto p:v) ret+=p.second-p.first+1;
	return ret;
}

void f(vector<pii> a, vector<pii> b, int cur, int p){
	if(a.size()==0) return;
	if(b.size()==0){
		ans=add(ans, mult(len(a), c2(cur)));
		return;
	}

	vector<pii> done={{0, p-1}};
	if(b==done){
		cur=add(cur, k&(p-1));
		ans=add(ans, mult(len(a), c2(cur)));
		return;
	}

	int p2=p/2;

	auto pb=[&](int l, int r, vector<pii>& v){
		l=max(l, 0); r=min(r, p2-1);
		if(r<l) return;
		v.push_back({l, r});
	};
	
	vector<pii> A[2], B[2];
	for(auto x:a) pb(x.first, x.second, A[0]), pb(x.first-p2, x.second-p2, A[1]);
	for(auto x:b) pb(x.first, x.second, B[0]), pb(x.first-p2, x.second-p2, B[1]);

	if((k/p2)&1){
		for(int i=0; i<=1; i++) f(A[i], B[i^1], cur+len(B[i]), p2);
	}
	else{
		for(int i=0; i<=1; i++) f(A[i], B[i], cur, p2);
	}
}

void go(vector<pair<int, int>> vec){
	vector<vector<pair<int, int>>> todo(2);
	int P2=P/2;
	for(auto p:vec){
		int l=p.first, r=p.second;
		// cout << l << " " << r << "\n";
		int L=p.first/P2, R=p.second/P2;
		if(L==R) todo[L].push_back({l%P2, r%P2});
		else todo[0].push_back({l, P2-1}), todo[1].push_back({0, r%P2});
	}
	for(int i=0; i<2; i++){
		ans=add(ans, c3(len(todo[i])));
		f(todo[i], todo[i^1], 0, P2);
	}
}

int main(){
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> k;
	k++;
	P=2;
	while(P<=k) P*=2;
	all=add(mult(2, c3(P/2)), mult(P, c2(k-P/2))); 
	ans=0;

	map<int, vector<pair<int, int>>> mp;
	for(int i=0; i<n ;i++){
		int l, r; cin >> l >> r;
		int L=l/P; int R=r/P;
		ans=add(ans, mult(all, max(0, R-1-L)));
		if(L==R){
			if(l%P==0 && r%P==P-1) ans=add(ans, all);
			else mp[L].push_back({l%P, r%P});
		}
		else{
			if(r%P!=P-1) mp[R].push_back({0, r%P});
			else ans=add(ans, all);
			if(l%P) mp[L].push_back({l%P, P-1});
			else ans=add(ans, all);
		}
	}

	for(auto p:mp){
		go(p.second);
	}

	cout << ans;
}

// is this a fairytale?