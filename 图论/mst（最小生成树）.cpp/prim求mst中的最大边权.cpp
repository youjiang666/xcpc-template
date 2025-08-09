//https://www.lanqiao.cn/problems/3322/learning/?page=1&first_category_id=1&name=%E6%97%85%E8%A1%8C%E9%94%80%E5%94%AE

/*
给定n个节点m条边的图，求可以遍历所有节点的最大边权的最小值
*/

/*
使用mst（最小生成树）求解，这里采用prim算法
通过维护集合外到集合内点的最小值dis实现求得最小生成树
通过堆结构实现，每次将堆中弹出的节点的权加入mst集合
再由该点出发更新临点的dis值，若dis变小了即把该dis加入堆
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

struct edge{
  int v,w;
};

vector<edge>vr[N];
priority_queue<pair<int,int>>pq;
bitset<N>vis;
int ans,dis[N];

void solve()
{
  int n,m;cin >> n >> m;
  for(int i = 1;i <= m;++ i)
  {
    int u,v,w;cin >> u >> v >> w;
    vr[u].push_back({v,w});
    vr[v].push_back({u,w});
  }

  ans = 0;
  for(int i = 2;i <= n;++ i)dis[i] = P;
  vis.reset();
  pq.push({0,1});
  while(!pq.empty())
  {
    auto _ = pq.top();
    int u = _.second,vlu = - _.first;
    pq.pop();
    if(vis[u])continue;
    vis[u] = 1;
    ans = max(ans,vlu); 

    for(auto x : vr[u])
    {
      int v = x.v,w = x.w;
      if(vis[v])continue;
      if(w < dis[v])dis[v] = w,pq.push({- w,v});
    }
  }

  cout << ans << "\n";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  cin >> _;
  while(_--)solve();
  return 0;
}