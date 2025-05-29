//蓝桥 19707 零食采购
/*
n个节点n-1条边，每个点有一个属性，q次查询u到v路径上有多少种不同的属性
*/

/*
注意到属性比较少，考虑对不同属性自上而下跑前缀和，再利用lca实现路径查询
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long; 
const int N=1e5+10,P=1e9+7;

vector<int>vec[N];
map<int,int>lca[N];
vector<pair<int,int>>Q;
vector<int>q[N];
bitset<N>vis;

int f[N],pre[N],a[N],prefix[N][21];

int root(int x){return pre[x] = pre[x] == x ? x : root(pre[x]);}

void Tarjan(int x,int fa)
{
  f[x] = fa;
  for(auto y : vec[x])
  {
    if(fa == y)continue;
    Tarjan(y,x);
    pre[y] = x;
  }
  
  vis[x] = 1;//放这里是为了防止方案中x == y的情况
  for(auto y : q[x])if(vis[y])lca[x][y] = lca[y][x] = root(y);
}

void dfs(int x)
{
  for(int i = 1;i <= 20;++ i)prefix[x][i] = prefix[f[x]][i];
  ++ prefix[x][a[x]];
  for(auto y : vec[x])
  {
    if(y == f[x])continue;
    dfs(y);
  }
}

void solve()
{
  int n,_;cin >> n >> _;
  for(int i = 1;i <= n;++ i)cin >> a[i],pre[i] = i;

  for(int i = 1;i < n;++ i)
  {
    int u,v;cin >> u >> v;
    vec[u].push_back(v);
    vec[v].push_back(u);
  }
  
  for(int i = 1;i <= _;++ i)
  {
    int u,v;cin >> u >> v;
    Q.push_back({u,v});
    q[u].push_back(v);
    q[v].push_back(u);
  }
  
  Tarjan(1,0);
  dfs(1);

  for(auto y : Q)
  {
    int ans = 0;
    int u = y.first,v = y.second,z = lca[u][v];
    for(int i = 1;i <= 20;++ i)
      if(prefix[u][i] + prefix[v][i] - prefix[z][i] - prefix[f[z]][i])++ ans;
    cout << ans << endl;
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}