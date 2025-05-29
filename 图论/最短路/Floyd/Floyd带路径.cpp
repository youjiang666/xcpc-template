//1121 蓝桥公园
//O(n的三次方)
//用邻接矩阵储存
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10,P = 1e9 + 7;

int n,pre[405][405];
ll dis[405][405],inf = 2e18;//dis[i][j]表示i到j的距离

void floyd()
{
  //枚举以k为中转点，i到j会不会变短
  for(int k = 1;k <= n;++ k)
    for(int i = 1;i <= n;++ i)
      for(int j = 1;j <= n;++ j)
        if(dis[i][k] + dis[k][j] < dis[i][j])
        {
          dis[i][j] = dis[i][k] + dis[k][j];
          pre[i][j] = k;//记录一下插点
        }
}

void path(int i,int j)
{
  if(pre[i][j] == 0)return;
  int k = pre[i][j];
  path(i,k);
  cout << k;//先输出左侧插点以保证路径由a到b
  path(k,j);
}

void out_path()
{
  int a,b;cin >> a >> b;
  cout << a;
  path(a,b);
  cout << b;
}

void solve()
{
  int m,q;cin >> n >> m >> q;
  
  //初始化一下邻接矩阵，自己到自己为0，其他为无穷
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= n;++ j)
      dis[i][j] = i == j ? 0 : inf;
  
  //可能有重边所以取min，无向图取双向
  while(m --)
  {
    ll u,v,w;cin >> u >> v >> w;
    dis[u][v] = min(w,dis[u][v]);
    dis[v][u] = min(w,dis[v][u]);
  }

  floyd();

  while(q --)
  {
    int u,v;cin >> u >> v;
    cout << (dis[u][v] == inf ? -1 : dis[u][v]) << endl;
  }
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int _ = 1;
    //cin >> _;
    while(_ --)solve();
    return 0;
}
