//蓝桥 3352 可行路径的方案数
/*
n个节点m条边求1到n的最短路径方案数
*/

/*
树上dp，松弛操作即可，当更新成功时，直接重置v的dp值
当两者相等时v的dp值加上u的即可，最后输出dp[n]即为所求
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=2e5+10,P=1e9+7;

vector<int>v[N];
ll dp[N],d[N];

void bfs()
{
  bitset<N>vis;
  queue<int>q;
  q.push(1);
  memset(d,0x3f,sizeof(d));
  d[1] = 0;
  dp[1] = 1;
  while(!q.empty())
  {
    int x = q.front();q.pop();
    if(vis[x])continue;
    vis[x] = 1;

    for(auto y : v[x])
    {
      if(vis[y])continue;
      if(d[y] < d[x] + 1)continue;
      else if(d[y] > d[x] + 1)
      {
        d[y] = d[x] + 1;
        dp[y] = dp[x];
      }else
        dp[y] = (dp[x] + dp[y]) % P;
      q.push(y);
    }
  }
}

void solve()
{
  int n,m;cin >> n >> m;
  while(m--)
  {
    int a,b;cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }
  bfs();
  //for(int i = 1;i <= n;++ i)cout << dp[i] << " ";
  cout << dp[n];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}