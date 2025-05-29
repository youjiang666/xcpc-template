//
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e9;
const int N=3e3+10,P=1e9+7;

struct edge{int v,w;};

vector<edge>vr[N];

int cnt[N],h[N],n,dis[N];

bool spfa(int x)
{
  bitset<N>vis;
  for(int i = 1;i <= n;++ i)h[i] = inf;

  queue<int>q;
  q.push(x),vis[0] = 1,h[0] = 0;
  while(!q.empty())
  {
    int u = q.front();q.pop();
    vis[u] = 0;
    for(auto ed : vr[u])
    {
      int v = ed.v,w = ed.w;
      if(h[u] + w < h[v])
      {
        h[v] = h[u] + w;
        ++ cnt[v];
        if(cnt[v] >= n)return 0;
        if(!vis[v])q.push(v),vis[v] = 1;
      }
    }
  }
  return 1;
}

void dj(int x)
{
  for(int i = 1;i <= n;++ i)dis[i] = inf;
  bitset<N>vis;
  dis[x] = 0;

  priority_queue<pair<int,int>>pq;
  pq.push({0,x});
  while(!pq.empty())
  {
    int u = pq.top().second;pq.pop();
    if(vis[u])continue;
    vis[u] = 1;
    for(auto ed : vr[u])
    {
      int v = ed.v,w = ed.w;
      if((ll)dis[u] + w < dis[v])
      {
        dis[v] = dis[u] + w;
        pq.push({- dis[v],v});
      }
    }
  }
}

void solve()
{
  int m;cin >> n >> m;
  while(m --)
  {
    int u,v,w;cin >> u >> v >> w;
    vr[u].push_back({v,w});
  }

  for(int i = 1;i <= n;++ i)vr[0].push_back({i,0});

  if(!spfa(0))
  {
    cout << -1 << "\n";
    return;
  }

  //for(int i = 1;i <= n;++ i)cout << h[i] << " ";

  for(int i = 1;i <= n;++ i)
    for(auto &ed : vr[i])
      ed.w += h[i] - h[ed.v];

  for(int i = 1;i <= n;++ i)
  {
    ll ans = 0;
    dj(i);
    for(int j = 1;j <= n;++ j)
    {
      if(dis[j] == inf)ans += (ll)j * inf;
      else ans += (ll)j * (dis[j] + h[j] - h[i]);
    }
    cout << ans << "\n";
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}