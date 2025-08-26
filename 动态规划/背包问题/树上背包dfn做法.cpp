//https://www.luogu.com.cn/problem/P2014

/*
给定大小为 n门课，第 i门课依附于第 x门课，价值为 v，最多选 n门课
求最大价值
*/

/*
树上子问题就是对应的子树，可以把树扁平化，后序遍历得到 dfn
设dp[i][j] 为 dfn里从前 i个物品容量为 j的最大价值
那么当 j >= w[dfn[i]]时 dp[i][j] = max(dp[i - 1][j - w[dfn[i]]] + v[dfn[i]],dp[i - sz[dfn[i]]][j])（可选节点）
否则 dp[i][j] = dp[i - sz[dfn[i]]][j]（无法选择该节点）
状态转移依赖于旧状态
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e3 + 10,P = 1e9 + 7;

int dp[N][N],o[N][N],s[N],v[N],w[N],m,dfn[N],sz[N],op;

void dfs(int x)
{
  sz[x] = 1;
  fr(i,s[x])
  {
    int y = o[x][i];
    dfs(y);
    sz[x] += sz[y];
  }
  dfn[++ op] = x;
}

void solve()
{
  int n;cin >> n >> m;
  fr(i,n)
  {
    int x,y;cin >> x >> y;
    w[i] = 1;
    v[i] = y;
    o[x][++ s[x]] = i;
  }

  dfs(0);

  fr(i,op)
  {
    int x = dfn[i];
    for(int j = m;j >= 0;-- j)
    {
      if(j >= w[x])dp[i][j] = max(dp[i - 1][j - w[x]] + v[x],dp[i - sz[x]][j]);
      else dp[i][j] = dp[i - sz[x]][j];
    }
  }
  cout << dp[op][m];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}