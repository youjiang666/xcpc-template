//https://codeforces.com/gym/102875/problem/I
/*
给定n*m的矩阵，起点（sx,sy），终点（ex,ey），格子属性矩阵a，b，边权矩阵c（横着走），矩阵w（竖着走）
当t % (a + b) < a可以横着走，否则可以竖着走，可以在原地等待，求st到ed的最短时间
*/

/*
这是一个带等待时间的最短路，考虑贪心+dj，在松弛的时候，贪心的等待，判断wait + w + dis[u] < dis[v],
若满足则进行松弛
细节：在压缩二维到一维后回转的时候应该是x = (u - 1) / m + 1,y = (u - 1) % m + 1
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 1e18;
const int N=25e4 + 10,P=1e9+7;

int a[N],b[N],c[N][2],w[N][2],n,m,sx,sy,ex,ey,st,ed;//c[][0]代表左，w[][0]代表上
ll dis[N];

void dj()
{
  bitset<N>vis;
  priority_queue<pair<ll,int>>pq;

  pq.push({0,st});
  while(!pq.empty())
  {
    auto _ = pq.top();pq.pop();
    int u = _.second;
    if(vis[u])continue;
    if(u == ed)return;
    vis[u] = 1;
    int op = dis[u] % (a[u] + b[u]);
    if(op >= a[u])
    {
      int x = (u - 1) / m + 1,y = (u - 1) % m + 1;
      if(y - 1 >= 1 && dis[u] + c[u][0] < dis[u - 1])
        dis[u - 1] = dis[u] + c[u][0],pq.push({- dis[u - 1],u - 1});
      if(y + 1 <= m && dis[u] + c[u][1] < dis[u + 1])
        dis[u + 1] = dis[u] + c[u][1],pq.push({- dis[u + 1],u + 1});

      ll wait = a[u] - op + b[u];
      if(x - 1 >= 1 && dis[u] + w[u][0] + wait < dis[u - m])
        dis[u - m] = dis[u] + w[u][0] + wait,pq.push({- dis[u - m],u - m});
      if(x + 1 <= n && dis[u] + w[u][1] + wait < dis[u + m])
        dis[u + m] = dis[u] + w[u][1] + wait,pq.push({- dis[u + m],u + m});
    }else{
      int x = (u - 1) / m + 1,y = (u - 1) % m + 1;
      if(x - 1 >= 1 && dis[u] + w[u][0] < dis[u - m])
        dis[u - m] = dis[u] + w[u][0],pq.push({- dis[u - m],u - m});
      if(x + 1 <= n && dis[u] + w[u][1] < dis[u + m])
        dis[u + m] = dis[u] + w[u][1],pq.push({- dis[u + m],u + m});

      ll wait = a[u] - op;
      if(y - 1 >= 1 && dis[u] + c[u][0] + wait < dis[u - 1])
        dis[u - 1] = dis[u] + c[u][0] + wait,pq.push({- dis[u - 1],u - 1});
      if(y + 1 <= m && dis[u] + c[u][1] + wait < dis[u + 1])
        dis[u + 1] = dis[u] + c[u][1] + wait,pq.push({- dis[u + 1],u + 1});
    }
  }
}

void solve()
{
  cin >> n >> m >> sx >> sy >> ex >> ey;

  st = (sx - 1) * m + sy;
  ed = (ex - 1) * m + ey;

  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= m;++ j)cin >> a[(i - 1) * m + j];

  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= m;++ j)cin >> b[(i - 1) * m + j];

  for(int i = 1;i <= n;++ i)
    for(int j = 1;j < m;++ j)
    {
      int u = (i - 1) * m + j,v = u + 1;
      int x;cin >> x;
      c[u][1] = c[v][0] = x; 
    }

  for(int i = 1;i < n;++ i)
    for(int j = 1;j <= m;++ j)
    {
      int u = (i - 1) * m + j,v = u + m;
      int x;cin >> x;
      w[u][1] = w[v][0] = x; 
    }

  for(int i = 1;i <= n * m;++ i)dis[i] = inf;
  dis[st] = 0;
  dj();
  
  /*
  for(int i = 1;i <= n;++ i)
  {
    for(int j = 1;j <= m;++ j)
    {
      if(dis[(i - 1) * m + j] == inf)cout << "no "; 
      else cout << dis[(i - 1) * m + j] << " ";
    }
    cout << endl;
  }
  */
  cout << dis[ed];
} 

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}