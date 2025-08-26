//给定股票每天的价格，你可以多次交易，最多持有一股，求最大收益

/*
设dp[i][1]表示持有股票
dp[i][0]表示不持有
转移方程便是
dp[i][0] = max(dp[i][0],dp[i - 1][1] + x);
dp[i][1] = max(dp[i][1],dp[i - 1][0] - x);
可以滚动优化，去掉第一维

如果含交易费的话直接在抛售股票时的 x减掉交易费即可
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e6 + 10,P = 1e9 + 7;

int dp[N][2];

void solve()
{
  int n;cin >> n;
  fr(i,n)
  {
    int x;cin >> x;
    dp[i][0] = max(dp[i][0],dp[i - 1][1] + x);
    dp[i][1] = max(dp[i][1],dp[i - 1][0] - x);
  }
  cout << dp[n][0];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}