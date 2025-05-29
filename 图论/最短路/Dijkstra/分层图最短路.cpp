//P4568 [JLOI2011] 飞行路线
/*
给定0 ~ n-1节点，m条边，k层，st，ed作为起点终点，u到v存在双向边边权为w
*/

/*
考虑分层图加dj解决，将图分成k + 1层，只能从小往大或者同层松弛操作，一旦弹出即为最小
细节：点是0 ~ n-1，所以初始化的时候小心
无向图记得建立双向边
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = INT_MAX;
const int N=1e4+10,P=1e9+7;

struct edge{int v,w;};

vector<edge>vr[N];

int n,m,k,st,ed,dis[N][11],vis[N][11];

int dj()
{
  for(int i = 0;i <= k;++ i)
    for(int j = 0;j <= n;++ j)dis[j][i] = inf;

  for(int i = 0;i <= k;++ i)dis[st][i] = 0;

  priority_queue<pair<ll,pair<int,int>>>pq;
  pq.push({0,{0,st}});
  while(!pq.empty())
  {
    auto _ = pq.top();pq.pop();
    int cnt = - _.second.first,u = _.second.second;
    if(vis[u][cnt])continue;
    if(u == ed)return dis[u][cnt];
    vis[u][cnt] = 1;
    for(auto ed : vr[u])
    {
      int v = ed.v,w = ed.w;
      if(cnt + 1 <= k && dis[u][cnt] < dis[v][cnt + 1])dis[v][cnt + 1] = dis[u][cnt],pq.push({- dis[v][cnt + 1],{- cnt - 1,v}});
      if(dis[u][cnt] < dis[v][cnt] - w)dis[v][cnt] = dis[u][cnt] + w,pq.push({- dis[v][cnt],{- cnt,v}});
    }
  }
  return -1;
}

void solve()
{
  cin >> n >> m >> k;
  cin >> st >> ed;
  
  while(m --)
  {
    int u,v,w;cin >> u >> v >> w;
    vr[u].push_back({v,w});
    vr[v].push_back({u,w});
  }

  cout << dj();
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}