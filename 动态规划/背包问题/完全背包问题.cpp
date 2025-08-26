//https://www.luogu.com.cn/problem/P1616

/*
给定n物品m容量，物品数量是无限的，求最大价值
*/

/*
完全背包，状态更新依赖于新的状态，直接从左向右更新即可
dp[i] = max(dp[i],dp[j - w] + v);
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e7 + 10,M = 1e4 + 10,P = 1e9 + 7;

ll dp[N];

void solve()
{
  int n,m;cin >> m >> n;
  fr(i,n)
  {
    int w,v;cin >> w >> v;
    for(int j = w;j <= m;++ j)dp[j] = max(dp[j],dp[j - w] + v);
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