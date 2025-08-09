//https://www.lanqiao.cn/problems/3322/learning/?page=1&first_category_id=1&name=%E6%97%85%E8%A1%8C%E9%94%80%E5%94%AE

/*
给定n个节点m条边的图，求可以遍历所有节点的最大边权的最小值
*/

/*
使用mst（最小生成树）求解，这里采用kruskal算法
先将各边按边权大小排序，再遍历所有边，通过并查集维护点集，
若该边两点不处于一个集合将两点连接并将边加入mst
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

struct edge{
  int u,v,w;
}a[N];

bool operator <(edge & a ,edge & b)
{
  return a.w < b.w;
}

int pre[N],ans;

int root(int x)
{
  return pre[x] = (pre[x] == x ? x : root(pre[x]));
}

void solve()
{
  int n,m;cin >> n >> m;
  for(int i = 1;i <= m;++ i)
  {
    int u,v,w;cin >> u >> v >> w;
    a[i] = {u,v,w};
  }
  sort(a + 1,a + m + 1);
  ans = 0;
  for(int i = 1;i <= n;++ i)pre[i] = i;
  for(int i = 1;i <= m;++ i)
  {
    int u = a[i].u,v = a[i].v,w = a[i].w;
    int ru = root(u),rv = root(v);
    if(ru == rv)continue;
    ans = max(ans,w);
    pre[ru] = rv;
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