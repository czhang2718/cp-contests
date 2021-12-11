#include "bits/stdc++.h"
using namespace std;

#define rep(i, a, b) for(short i=a; i<=b; i++)
const short N=52;
short dp[N][N][N][N][2];
short a[N];
short n;

int main(){
  cin.tie(0)->sync_with_stdio(0);
  // freopen("subrev.in", "r", stdin);
  // freopen("subrev.out", "w", stdout);

  cin >> n;
  rep(i, 1, n){
    cin >> a[i];
  }

  auto ckmax=[&](short &a, short b)->short{
    a=max(a, b);
    return a;
  };

  rep(len, 0, n-1){
    rep(i, 1, n-len){
      short j=i+len;
      if(!len){
        rep(l, 1, a[i]){
          rep(r, a[i], 50){
            dp[i][i][l][r][0]=dp[i][i][l][r][1]=1;
          }
        }
      }
      else{
        rep(l, 1, 50){
          rep(r, l, 50){
            dp[i][j][l][r][0]=dp[i+1][j][l][r][0];
            if(a[i]>=l && a[i]<=r) ckmax(dp[i][j][l][r][0], 1+dp[i+1][j][a[i]][r][0]);

            dp[i][j][l][r][1]=dp[i+1][j][l][r][1];
            if(a[i]>=l && a[i]<=r) ckmax(dp[i][j][l][r][1], 1+dp[i+1][j][a[i]][r][1]);


            rep(k, i+1, j){
              if(a[k]>=a[i]) continue;
              // 1
              if(a[i]>=l && a[i]<=r){
                ckmax(dp[i][j][l][r][1], dp[i+1][k-1][l][a[i]][1] + 1 + dp[k+1][j][a[i]][r][0]);
                if(a[k]>=l) ckmax(dp[i][j][l][r][1], 1 + dp[i+1][k-1][a[k]][a[i]][1] + 1 + dp[k+1][j][a[i]][r][0]);
              }

              // 0
              if(a[k]<=r && a[k]>=l){
                rep(m, a[k], r) ckmax(dp[i][j][l][r][1], 1+dp[i+1][k-1][a[k]][m][1]+dp[k+1][j][m][r][0]);
              }
            }
          }
        }
      }
    }
  }

  cout << dp[1][n][1][50][1];
}

// is heaven all we thought it'd be?