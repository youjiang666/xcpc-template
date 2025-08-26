//https://www.acwing.com/problem/content/description/1060/

/*
给定股票每天的价格，你可以多次交易，最多持有一股，当你抛售股票的第二天不可以购入股票，求最大收益
*/

/*
不难发现其实就三种状态
抛售了，不持有股份
未抛售，持有股份
未抛售，持有股份
转化成有向图后观察状态之间的关系即可写出转移方程
再滚动优化即可
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e6 + 10,P = 1e9 + 7;

ll dp[2][3],fg;

void solve()
{
  int n;cin >> n;
  dp[1][1] = dp[1][2] = -P;
  fr(i,n)
  {
    int x;cin >> x;
    dp[fg][0] = max(dp[fg ^ 1][0],dp[fg ^ 1][2]);
    dp[fg][1] = max(dp[fg ^ 1][0] - x,dp[fg ^ 1][1]);
    dp[fg][2] = dp[fg ^ 1][1] + x;
    fg ^= 1;
  }
  cout << max(dp[fg ^ 1][0],dp[fg ^ 1][2]);
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}