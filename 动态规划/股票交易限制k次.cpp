//https://www.acwing.com/problem/content/description/1059/

/*
给定股票每天的价格，你可以多次交易，最多持有一股，求最大收益，限制最多 k次交易
*/

/*
再加一维区分状态表示交易次数
优化掉第一个维度，更新只依赖于前一个状态
dp[i][j][0] = max(dp[i - 1][j][0],dp[i - 1][j][1] + x)
dp[i][f][1] = max(dp[i - 1][j][1],dp[i - 1][j - 1][0] - x)
逆序更新完全符号上式
但顺序更新时发现变成了
dp[i][j][0] = max(dp[i - 1][j][0],dp[i - 1][j][1] + x)
dp[i][f][1] = max(dp[i - 1][j][1],dp[i][j - 1][0] - x)
其实并不影响因为dp[i][j - 1][0] >= dp[i - 1][j - 1][0]
显然是没有问题的

也可以重新定义影响
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
  int n,k;cin >> n >> k;
  fr(i,k)dp[i][1] = - P;
  fr(i,n)
  {
    int x;cin >> x;
    for(int j = 1;j <= k;++ j)
    {
      dp[j][0] = max(dp[j][0],dp[j][1] + x);
      dp[j][1] = max(dp[j][1],dp[j - 1][0] - x);
      //cout << dp[j][0] << " " << dp[j][1] << "\n";
    }
  }
  cout << dp[k][0];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}
/*

*/