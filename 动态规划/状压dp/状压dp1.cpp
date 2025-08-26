//https://www.luogu.com.cn/problem/P1896

/*
给定n * n的网格，放置物品使得他们不会相互攻击，攻击范围为周围一圈，求放置数为 k个的总方案数
*/

/*
先考虑dfs搜索，将格子扁平化然后枚举每个格局看放或不放，求方案数，复杂度O(2 ^ (n ^ 2))
考虑记忆化发现不好记忆因为包含了前面所有格子的状态，值的话会很大

数据小，正常方法做不了，考虑状压 dp，发现每行只与相邻行有关系，先找到每行的合法状态（二进制表示）
然后向分组背包那样先枚举每行容量，再枚举物品（在这里是枚举两行的状态看是否合法，价值为该状态的物品数）
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e6 + 10,P = 1e9 + 7;

ll dp[10][100][1 << 10],s[1 << 10],ct[1 << 10],o,ans;

void solve()
{
  int n,k;cin >> n >> k;
  for(int i = 0;i < (1 << n);++ i)
  {
    if(!(i & (i << 1)))
    {
      s[++ o] = i;
      for(int j = 0;j < n;++ j)if((i >> j) & 1)++ ct[o];
    }
  }

  dp[0][0][1] = 1;
  for(int i = 1;i <= n;++ i)
    for(int j = 0;j <= k;++ j)
      for(int k = 1;k <= o;++ k)
        for(int l = 1;l <= o;++ l)
        {
          int x = s[k],y = s[l];
          if(ct[l] <= j
            && !(x & (y << 1))
            && !(x & y)
            && !(x & (y >> 1))
          )dp[i][j][l] += dp[i - 1][j - ct[l]][k];
        }
  fr(i,o)ans += dp[n][k][i];
  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}