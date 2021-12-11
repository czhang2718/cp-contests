#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i=a; i<=b; i++)
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;

ll dp[1001][1001][11];
int n, m, K;
const int MOD=1000000009;

int main(){
	cin.tie(0)->sync_with_stdio(0);
	freopen("team.in", "r", stdin);
	freopen("team.out", "w", stdout);

	cin >> n >> m >> K;
	vi a(n+1);
	vi b(m+1);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, m) cin >> b[i];
	sort(all(a)); sort(all(b));

	rep(i, 0, n){
		rep(j, 0, m){
			dp[i][j][0]=1;
		}
	}
	rep(i, 1, n){
		rep(j, 1, m){
			rep(k, 1, K){
				dp[i][j][k]=dp[i-1][j][k]+dp[i][j-1][k]-dp[i-1][j-1][k]+(ll)MOD;
				if(b[j]<a[i]) dp[i][j][k]+=dp[i-1][j-1][k-1];
				dp[i][j][k]%=MOD;
			}
		}
	}
	cout << dp[n][m][K];
}
