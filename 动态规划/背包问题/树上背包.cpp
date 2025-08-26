//https://www.luogu.com.cn/problem/P2014

/*
给定大小为 n门课，第 i门课依附于第 x门课，价值为 v，最多选 n门课
求最大价值
*/

/*
把 0视为虚拟节点，v[0] = w[0] = 0,发现依赖关系呈现为树形，递归后由叶子节点开始装入课程
设dp[i][j]为以 i为根节点的子树里容量为 j的最大价值
转移时先装入父节点进空背包再看子树，由子树已经更新的信息合并上来，dp[fa][j] = max(dp[fa][j],dp[fa][j - k] + dp[son][k]);
注意从后向前更新依赖于旧信息，不然会重复选择物品
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e3 + 10,P = 1e9 + 7;

int dp[N][N],o[N][N],s[N],v[N],w[N],m;

void dfs(int x)
{
  fr(i,m)dp[x][i] = v[x];
  fr(i,s[x])
  {
    int y = o[x][i];
    dfs(y);
    for(int j = m;j >= w[x];-- j)
      for(int k = 0;k <= j - w[x];++ k)dp[x][j] = max(dp[x][j],dp[x][j - k] + dp[y][k]);
  }
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

  cout << dp[0][m];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}