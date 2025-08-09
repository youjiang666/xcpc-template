//https://atcoder.jp/contests/abc408/tasks/abc408_e 最小或路径
/*
给定无向图，求1到n路径中或运算值最小路径
*/

/*
从高位到低位贪心的走，每一层只走对答案贡献为零的边权（也就是（ans | w） - ans）为零，
可以到达n节点便使得ans该位为零，否则该位为1，逐渐缩小可拓展的边
也可以使用二分答案来做，利用若其为答案那么便存在路径路径上所有权值和其或运算后值不变
*/
//https://atcoder.jp/contests/abc408/tasks/abc408_e 最小或路径
/*
给定无向图，求1到n路径中或运算值最小路径
*/

/*
从高位到低位贪心的走，每一层只走对答案贡献为零的边权（也就是（ans | w） - ans）为零，
可以到达n节点便使得ans该位为零，否则该位为1，逐渐缩小可拓展的边
也可以使用二分答案来做，利用若其为答案那么便存在路径路径上所有权值和其或运算后值不变
还可以使用双向bfs加速并且每次拓展节点数小一点的那边极致优化
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = INT_MAX;
const int N=2e5+10,P=1e9+7;

struct edge{int v,w;};
vector<edge>vr[N];
int n,ans;
bitset<N>vis;

void dj(int op)
{
  vis.reset();
  vis[1] = 1;
  queue<int>q;
  q.push(1);
  while(!q.empty())
  {
    int u = q.front();q.pop();
    if(u == n)return;
    for(auto y : vr[u])
    {
      int v = y.v,w = y.w;
      if(((ans | w) - ans) < (1 << (op + 1)) 
         && ((w >> op) & 1) == 0
         && !vis[v])
      {
        vis[v] = 1;
        q.push(v);
      }
    }
  }
}

void solve()
{
  int m;cin >> n >> m;
  for(int i = 1;i <= m;++ i)
  {
    int u,v,w;cin >> u >> v >> w;
    vr[u].push_back({v,w});
    vr[v].push_back({u,w});
  }

  for(int i = 29;i >= 0;-- i)
  {
    dj(i);
    if(!vis[n])ans |= (1 << i);
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