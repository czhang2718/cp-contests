#include "bits/stdc++.h"
using namespace std;

const int N=52;
int n;
int A[N];
int dp[N][N][N][N];

int ckmax(int &a, int b){
	a=max(a, b);
	return a;
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	freopen("subrev.in", "r", stdin);
	freopen("subrev.out", "w", stdout);

	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> A[i];
		dp[i][i][A[i]][A[i]]=1;
		for(int a=50; a>=1; a--){
			for(int b=a; b<=50; b++){
				if(a<=A[i] && b>=A[i]) dp[i][i][a][b]=1;
			}
		}
	}

	for(int l=1; l<n; l++){
		for(int i=1; i+l<=n; i++){
			int j=i+l;
			for(int a=1; a<=50; a++){
				for(int b=a; b<=50; b++){
					dp[i][j][a][b]=max(dp[i+1][j][a][b], dp[i][j-1][a][b]);
					if(A[i]>=a && A[i]<=b) ckmax(dp[i][j][a][b], 1+dp[i+1][j][A[i]][b]);
					if(A[j]>=a && A[j]<=b) ckmax(dp[i][j][a][b], 1+dp[i][j-1][a][A[j]]);

					if(A[j]>=a && A[j]<=b) ckmax(dp[i][j][a][b], 1+dp[i+1][j-1][A[j]][b]);
					if(A[i]<=b && A[i]>=a) ckmax(dp[i][j][a][b], 1+dp[i+1][j-1][a][A[i]]);
					if(A[j]>=a && A[i]<=b && A[i]>=A[j]) ckmax(dp[i][j][a][b], 2+dp[i+1][j-1][A[j]][A[i]]);
				}
			}
		}
	}
	// ohh you don't have to use everything you swap

	cout << dp[1][n][1][50];
}