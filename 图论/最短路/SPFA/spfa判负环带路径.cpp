//P3385 【模板】负环
//可以处理负环
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = INT_MAX;
const int N=2e3+10,P=1e9+7;

struct edge{int v,w;};

vector<edge>vr[N];
int dis[N],cnt[N],n,pre[N];
queue<int>q;
bitset<N>vis;

void clear_()
{
  for(int i = 1;i <= n;++ i)
    vr[i].clear(),vis[i] = 0,cnt[i] = 0;
  while(!q.empty())q.pop();
}

int spfa(int st)
{
  for(int i = 1;i <= n;++ i)dis[i] = inf;
  q.push(st);vis[st] = 1;dis[st] = 0;
  while(!q.empty())
  {
    int u = q.front();q.pop();vis[u] = 0;
    for(auto ed : vr[u])
    {
      int v = ed.v,w = ed.w;
      if(dis[u] + w < dis[v])
      {
        dis[v] = dis[u] + w;
        pre[v] = u;//同理记录前驱点
        cnt[v] = cnt[u] + 1;
        if(cnt[v] >= n)return 1;//当源点到该点的步数超过n了那便是有负环了
        if(!vis[v])q.push(v),vis[v] = 1;
      }
    }
  }
  return 0;
}

void dfs_path(int x,int st)
{
  if(x == st)//一直通过dfs找到起点后递归输出
  {
    cout << x;
    return;
  }
  dfs_path(pre[x],st);//递归到结束后再往下执行输出路径
  cout << x;
}

void solve()
{
  int m;cin >> n >> m;
  
  while(m --)
  {
    int u,v,w;cin >> u >> v >> w;
    vr[u].push_back({v,w});
    if(w >= 0)vr[v].push_back({u,w});
  }

  if(spfa(1))cout << "YES\n";
  else cout << "NO\n";
  clear_();
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  cin >> _;
  while(_--)solve();
  return 0;
}