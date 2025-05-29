//P4779 【模板】单源最短路径（标准版）
//不能正确处理负边权
//O(mlogm)
/*
也可以通过重载结构体内运算符来排
本代码使用的是pair大根堆（加入堆是dis加个负号就可以是距离小的点在上面）
bool operator < (const load &other)const
  {
    return w > other.w;
  }
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = INT_MAX;
const int N=1e6+10,P=1e9+7;

struct edge{int v,w;};
int n,dis[N];
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

      //通过x到y更近就更新并加入堆中
      if(dis[x] + w < dis[y])
      {
        dis[y] = dis[x] + w;
        pq.push({- dis[y],y});
      }
    }
  }
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