//https://www.luogu.com.cn/problem/P2871

/*
n件物品，m容量，w为体积，v为价值，求最大价值
*/

/*
最优解问题考虑动态规划，分解子问题
发现就是求第 i 件物品以及容量为 j 的最大容量
dp[n][m]就是答案
观察状态发现更新状态仅依赖于左上方的旧状态滚动更新
所以由后往前更新转移方程为
dp[i] = max(dp[i],dp[i - w] + v);
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 2e4 + 10,P = 1e9 + 7;

int dp[N];

void solve()
{
  int n,m;cin >> n >> m;
  fr(i,n)
  {
    int w,v;cin >> w >> v;
    for(int j = m;j >= w;-- j)dp[j] = max(dp[j],dp[j - w] + v);
  }
  cout << dp[m];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}