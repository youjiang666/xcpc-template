//https://www.luogu.com.cn/problem/P1352

/*
给定一颗树，各节点贡献为 w[i]，对于所有节点其父节点选择了便不可以
选择该节点，求最大贡献
*/

/*
线性dp的子结构是线段，树形dp的子结构是子树
分解出子问题后，把各个状态表示并转移即可求出原问题最优解

对于每个节点也就两种状态选择了或未选择，用0 和 1表示
状态转移为:
dp[x][0] += max(dp[son][1],dp[son][0])求和;
dp[x][1] = w[x] + dp[son][0]求和;
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 6e3 + 10,P = 1e9 + 7;

vector<int>vr[N];
int w[N],dp[N][2],ans;

void dfs(int x,int fa)
{
  dp[x][1] = w[x];
  for(auto y : vr[x])
  {
    if(y == fa)continue;
    dfs(y,x);
    dp[x][1] += dp[y][0];
    dp[x][0] += max(dp[y][0],dp[y][1]);
  }
}

void solve()
{
  int n;cin >> n;
  fr(i,n)cin >> w[i];
  fr(i,n - 1)
  {
    int u,v;cin >> u >> v;
    vr[v].push_back(u);
    vr[u].push_back(v);
  }

  dfs(1,0);

  cout << max(dp[1][0],dp[1][1]);
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}