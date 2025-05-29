////P3128 [USACO15DEC] Max Flow P
/*
离线求法
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N=1e5+10,P=1e9+7;

map<int,int>lca[N];
vector<pair<int,int>>ques;
vector<int>vec[N];
vector<int>tree[N];
bitset<N>vis;

int diff[N],pre[N],prefix[N],f[N];

int root(int x){return pre[x] = pre[x] == x ? x : root(pre[x]);}

void dfs(int x,int fa)
{
  prefix[x] = diff[x];
  for(auto y : tree[x])
  {
    if(y == fa)continue;
    dfs(y,x);
    prefix[x] += prefix[y];//自下向上dp
  }
}

void Tarjan(int x,int fa)
{
  f[x] = fa;
  vis[x] = 1;
  for(auto y : tree[x])
  {
    if(y == fa)continue;
    Tarjan(y,x);
    pre[y] = x;
  }
  for(auto y : vec[x])if(vis[y])lca[x][y] = lca[y][x] = root(y);//注意这里是当y已经走过时取y的根为lca
}

void solve()
{
  int n,k;cin >> n >> k;

  for(int i = 1;i < n;++ i)
  {
    int x,y;cin >> x >> y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  
  for(int i = 1;i <= k;++ i)
  {
    int u,v;cin >> u >> v;
    vec[u].push_back(v);
    vec[v].push_back(u);//存入问题
    ques.push_back({u,v});//存入需处理的边点
  }

  for(int i = 1;i <= n;++ i)pre[i] = i;
  Tarjan(1,0);

  for(auto x : ques)
  {
    int u = x.first,v = x.second;
    int z = lca[u][v];
    ++ diff[u],++ diff[v],-- diff[z],-- diff[f[z]];
    //这里处理的是点权，处理边权的话：++ diff[u],++ diff[v],diff[z] -= 2，画个图便很好理解
  }

  dfs(1,0);//前缀和复原

  int ans = 0;
  for(int i = 1;i <= n;++ i)ans = max(ans,prefix[i]);
  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}