#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i=a; i<=b; i++)
#define trav(x, a) for(auto &x:a)
#define f first
#define s second
#define nl '\n'
#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

int n;
int f[100002];

bool comp(int a, int b){
	// tan(a)>tan(b)
	return (ll)f[a]*b>(ll)f[b]*a;
}

bool left_turn(int a, int b, int c){
	pii u={b-a, f[b]-f[a]};
	pii v={c-b, f[c]-f[b]};
	return (ll)u.f*v.s-(ll)u.s*v.f>=0;
}

// convex hull :oOoOD
int main(){
	cin.tie(0)->sync_with_stdio(0);
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);

	cin >> n;
	rep(i, 1, n) cin >> f[i];
	set<int> s;
	vi pnts;
	rep(i, 1, n+1) if(f[i] || i==n+1) pnts.pb(i);
	sort(all(pnts), comp);
	
 	stack<int> st;
 	st.push(0); st.push(pnts[0]);
 	rep(k, 1, sz(pnts)-1){
 		int i=pnts[k];
 		while(sz(st)>1){
 			int cur=st.top(); st.pop();
 			int last=st.top();
 			if(!left_turn(last, cur, i)){
 				st.push(cur); break;
 			}
 		}
 		st.push(i);
 	}
 
 	while(!st.empty()){
 		// cout << st.top() << nl;
 		s.insert(st.top()); st.pop();
 	}
 	cout << fixed;
 	rep(i, 1, n){
 		int l=*prev(s.lower_bound(i));
 		int r=*s.lower_bound(i);
 		if(r==i) cout << (ll)100000*f[i] << nl;
 		else{
 			cout << (ll)100000*(ll(i-l)*f[r]+ll(r-i)*f[l])/(r-l) << nl;
 		}
 	}
}
