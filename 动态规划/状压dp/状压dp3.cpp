//https://www.luogu.com.cn/problem/P2704

/*
给定n*m 的网格，只有当格子属性为 P时才可以放置炮兵
炮兵会攻击以自己为中心向四个方向延申两个距离的方格
求最大放置炮兵数量
*/

/*
数量较少，考虑状压dp
正常处理每一行的合法状态
若我们设两维的dp[i][j]为第 i行 j状态下的最大数量，会发现
对于第 i行我们无论是从第 i - 1行转移还是i - 2行转移都
分别还要依赖到再上一行的值，那么我们再扩展一维
记录第 i行与第i - 1行之间的合法状态对，新加的一维为第 i - 1行的状态
这样就可以只枚举三行的状态找合法的然后只依赖于第i - 1行里记录的其行的合法状态加上 i行状态炮兵数

当然可以使用滚动数组优化掉第 1维
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e2 + 10,P = 1e9 + 7;

int w[N],op[N][1 << 10],s[N],ct[1 << 10],dp[N][1 << 10][1 << 10],ans;

void solve()
{
  int n,m;cin >> n >> m;
  fr(i,n)fr(j,m)
  {
    char x;cin >> x;
    w[i] = (w[i] << 1) + (x == 'H');
  }

  fr(i,n)for(int j = 0;j < (1 << m);++ j)
  {
    if(j & (j << 1) || j & (j << 2) || j & w[i])continue;
    op[i][++ s[i]] = j;
  }
    
  fr(i,(1 << m) - 1)for(int j = 0;j < m;++ j)ct[i] += (i >> j) & 1;

  s[0] = 1;
  fr(i,s[1])dp[1][i][1] = ct[op[1][i]],ans = max(ans,dp[1][i][1]);

  for(int i = 2;i <= n;++ i)
  {
    fr(j,s[i])fr(k,s[i - 1])fr(o,s[i - 2])
    {
      if(op[i][j] & op[i - 1][k] 
        || op[i - 1][k] & op[i - 2][o] 
        || op[i][j] & op[i - 2][o])continue;

      dp[i][j][k] = max(dp[i][j][k],dp[i - 1][k][o] + ct[op[i][j]]);
      ans = max(dp[i][j][k],ans);
    }
  }

  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}