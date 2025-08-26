//https://www.luogu.com.cn/problem/P1775

/*
给定排成一行的 n堆石子，质量为 w[i]，一次只能合并相邻的石堆
合并代价为两堆的和，求最小操作代价
*/

/*
考虑dp,数据较小区间dp
设置 dp[i][j]表示第 i到 j该区间的最小操作代价
发现可以由较短长度区间向长的区间转移
所以先枚举长度再枚举左端点转移即可
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 3e2+ 10,P = 1e9 + 7;

ll dp[N][N],prefix[N];

void solve()
{
  int n;cin >> n;
  fr(i,n)
  {
    int x;cin >> x;
    prefix[i] = prefix[i - 1] + x;
  }

  for(int i = 2;i <= n;++ i)
    fr(l,n - i + 1)
    {
      int r = l + i - 1;
      dp[l][r] = inf;
      for(int k = l;k < r;++ k)
        dp[l][r] = min(dp[l][r],dp[l][k] + dp[k + 1][r] + prefix[r] - prefix[l - 1]);
    }
  cout << dp[1][n];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}