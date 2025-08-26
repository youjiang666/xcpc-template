//https://www.luogu.com.cn/problem/P1833

/*
给定时间，n个物品,当 m为0时物品不限量，求最大价值
*/

/*
ed为上限,混合背包直接分类成多重背包以及完全背包即可
采用二进制枚举优化一下多重背包部分，只需一层滚动数组
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e6 + 10,P = 1e9 + 7;

int dp[N];

void solve()
{
  int a,b,c,d;scanf("%d:%d %d:%d",&a,&b,&c,&d);
  int ed = (c - a) * 60 + d - b;
  int n;cin >> n;
  while(n --)
  {
    int w,v,m;cin >> w >> v >> m;
    if(m)
    {
      for(int i = 0;m >= (1 << i);++ i)
      {
        int ww = w << i,vv = v << i;
        m -= (1 << i);
        for(int j = ed;j >= ww;-- j)dp[j] = max(dp[j],dp[j - ww] + vv);
      }

      int ww = w * m,vv = v * m;
      for(int j = ed;j >= ww;-- j)dp[j] = max(dp[j],dp[j - ww] + vv);
    }else
      for(int i = 0;i <= ed - w;++ i)dp[i + w] = max(dp[i + w],dp[i] + v);
      //注意完全背包由前向后依赖于新状态更新
  }
  cout << dp[ed];
}

int main(){
  //ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}