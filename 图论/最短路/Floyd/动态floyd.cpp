//https://atcoder.jp/contests/abc416/tasks/abc416_e

/*
给定n个点m条边，k个机场，机场之间可以以t的时间来往，给定操作1：建立x到y权值为t的路，
操作2：在x点建立机场，操作3：查询当前所有路径总和
*/

/*
全源最短路考虑floyd，主要在于怎么更新，回到基础的floyd，枚举中间点获取最短路，
那么我们更新的时候也可以这样，复杂度瓶颈在于机场的建立，反复记录遍历会很慢，
先使得所有边权值乘于2然后设立虚拟源点0使得机场节点相连，边权为 t,然后跑图只需要跑半张即可得到答案
当dis缩小时之间维护答案以免反复遍历求ans

注意：floyd的k是在最外层或者最内层这样更新是信息才是正确的
     单边更新时注意不用乱剪枝，一定要有所依据
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 1e18;
const int N=5e2+10,P=1e9+7;

ll dis[N][N],t,n,ans;
bitset<N>vis;

void update(int x,int y,int w)
{
  for(int i = 0;i <= n;++ i)
    for(int j = 0;j < i;++ j)
    {
      ll op = min(dis[i][x] + dis[y][j],dis[i][y] + dis[x][j]) + w;
      if(op < dis[i][j])
      {
        if(i && j)
        {
          if(dis[i][j] != inf)ans -= (dis[i][j] - op);
          else ans += op;
        }
        dis[i][j] = dis[j][i] = op;
      }
    }
}

void solve()
{
  int m;cin >> n >> m;
  for(int i = 0;i <= n;++ i)
    for(int j = 0;j <= n;++ j)
      if(i != j)dis[i][j] = inf;

  while(m --)
  {
    ll u,v,w;cin >> u >> v >> w;
    w <<= 1;
    if(w < dis[u][v])dis[u][v] = dis[v][u] = w;
  }

  int k;cin >> k >> t;
  while(k --)
  {
    int x;cin >> x;
    if(vis[x])continue;
    vis[x] = 1;
    update(0,x,t);
  }

  for(int k = 0;k <= n;++ k)//k不可以放在i j中间
    for(int i = 0;i <= n;++ i)
      for(int j = 0;j <= n;++ j)
        dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);

  ans = 0;
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j < i;++ j)
      if(dis[i][j] != inf)ans += dis[i][j];

  int q;cin >> q;
  while(q --)
  {
    int _;cin >> _;
    if(_ == 1)
    {
      int u,v,w;cin >> u >> v >> w;
      w <<= 1;
      if(w < dis[u][v])update(u,v,w);
    }else if(_ == 2)
    {
      int x;cin >> x;
      if(vis[x])continue;
      vis[x] = 1;
      update(0,x,t);
    }else cout << ans << "\n";
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}