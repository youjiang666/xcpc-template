//https://www.luogu.com.cn/problem/P1776

/*
给定n个物品,m容量,限制物品使用量为 m[i]个，求最大价值
*/

/*
多重背包转换为01背包问题，从旧状态枚举物品数量后逐个转移取最大
但复杂度太高了，考虑优化

此处采用单调队列优化，对于单个物品，它状态的转移只能来自于旧状态里与
其差值为 w倍数且数量不超过 m的位置，找到这些值里面最大的即可
把状态分成 w个类然后使用单调队列维护大小为 m + 1的窗口的最大值
队列内部的权值为与当前位置的可加入的物品最大值
当当前位置的值比队尾加上一些物品的值还大时，更新队列
再每次取队头的权值即可

由于状态更新多次需要使用到旧状态，采用二维滚动数组优化空间
*/

#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 4e4 + 10,P = 1e9 + 7;

int fg,dp[2][N],q[N];

void solve()
{
  int n,ed;cin >> n >> ed;
  fr(i,n)
  {
    int v,w,m;cin >> v >> w >> m;
    for(int j = 0;j < w;++ j)
    {
      int h = 1,t = 0;
      for(int k = j;k <= ed;k += w)
      {
        while(h <= t && dp[fg ^ 1][q[t]] + (k - q[t]) / w * v <= dp[fg ^ 1][k])-- t;
        q[++ t] = k;
        if(q[h] < k - m * w)++ h;
        dp[fg][k] = dp[fg ^ 1][q[h]] + (k - q[h]) / w * v;
      }
    }
    fg ^= 1;
  }
  cout << dp[fg ^ 1][ed];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}