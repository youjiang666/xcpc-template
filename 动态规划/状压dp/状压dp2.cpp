//https://www.cnblogs.com/dx123/p/17301967.html

//给定m * n的地图，只有当a[i][j] 为 1时可以放置物品，求放置物品不相邻的总方案数

/*
范围较小可以考虑状压
先求出每行的合法状态，每行的初始状态得到一个值取反，然后枚举状态，当状态并并上不为零就是非法
相邻行互相转移
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 5e3 + 10,P = 1e8;

ll dp[15][N],op[15][N],s[15],w[N];//记录每行合法状态,合法数，每行初始状态取反

void solve()
{
  int m,n;cin >> m >> n;
  fr(i,m)fr(j,n)
  {
    int x;cin >> x;
    w[i] <<= 1,w[i] += !x;
  }
  
  fr(i,m)
  {
    for(int j = 0;j < (1 << n);++ j)
    {
      if(j & w[i] || j & (j << 1))continue;
      op[i][++ s[i]] = j;
    }
  }

  s[0] = 1;
  dp[0][1] = 1;
  fr(i,m)
  {
    fr(j,s[i - 1])fr(k,s[i])
    {
      int x = op[i - 1][j],y = op[i][k];
      if(!(x & y))dp[i][k] = (dp[i][k] + dp[i - 1][j]) % P;
    }
  }

  ll ans = 0;
  fr(i,s[m])ans = (ans + dp[m][i]) % P;
  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}