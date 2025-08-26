//https://www.luogu.com.cn/problem/P1776

/*
给定n个物品,m容量,限制物品使用量为 m[i]个，求最大价值
*/

/*
多重背包转换为01背包问题，从旧状态枚举物品数量后逐个转移取最大
但复杂度太高了，考虑优化

此处采用二进制优化，分解m[i] = 2^0 + 2^1 + 2^2 + .... + other
然后枚举取最大即可，这样就可以枚举完全取0 ~ m中所有状态的最优解
不需要二维滚动数组，一维就够了
*/

#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 4e4 + 10,P = 1e9 + 7;

ll dp[N];

void solve()
{
  int n,ed;cin >> n >> ed;
  fr(i,n)
  {
    int v,w,m;cin >> v >> w >> m;
    for(int k = 0;m >= (1 << k);++ k)
    {
      ll vv = v << k,ww = w << k;
      m -= (1 << k);
      for(int j = ed;j >= ww;-- j)dp[j] = max(dp[j],dp[j - ww] + vv);
    }

    ll vv = v * m,ww = w * m;
    for(int j = ed;j >= ww;-- j)dp[j] = max(dp[j],dp[j - ww] + vv);
  }
  cout << dp[ed];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}