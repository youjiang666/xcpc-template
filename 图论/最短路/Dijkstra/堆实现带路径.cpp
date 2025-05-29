//路径输出
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = INT_MAX;
const int N=1e6+10,P=1e9+7;

struct edge{int v,w;};
int n,dis[N],pre[N];//使用pre前驱数组记录
bitset<N>vis;
vector<edge>vr[N];

void dj(int st)
{
	priority_queue<pair<int,int>>pq;
  for(int i = 1;i <= n;++ i)dis[i] = inf;
  dis[st] = 0;
  pq.push({0,st});
  while(!pq.empty())
  {
    auto t = pq.top();pq.pop();
		
    int x = t.second;
    if(vis[x])continue;
    vis[x] = 1;
    
    //松弛操作
    for(auto ed : vr[x])
    {
      ll y = ed.v,w = ed.w;

      if(dis[x] + w < dis[y])
      {
        dis[y] = dis[x] + w;
        pre[y] = x;//记录前驱点
        pq.push({- dis[y],y});
      }
    }
  }
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
  int m,s;cin >> n >> m >> s;

  while(m --)
  {
    int u,v,w;cin >> u >> v >> w;
    vr[u].push_back({v,w});
  }
	
	dj(s);
	
  for(int i = 1;i <= n;++ i)cout << dis[i] << " ";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}