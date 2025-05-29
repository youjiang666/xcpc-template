//蓝桥 3517 砍树
/*
给定n个节点，m条边，选择一个编号使得m条边都不连通，输出编号最大的
*/

/*
考虑树上边差分，（对于u到v以v作为该边的编号），对m条边的两端节点差分，再做前缀和得到权值，找到权值为m的再比一下编号即可
细节：对差分复原是自下而上跑，普通树上前缀和是自上而下跑
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=1e9+7;

vector<int>vec[N];
map<int,int>num[N];

int dep[N],st[N][17],diff[N],prefix[N];

void dfs(int x,int fa)
{
  prefix[x] = diff[x];
  for(auto y : vec[x])
  {
    if(y == fa)continue;
    dfs(y,x);
    prefix[x] += prefix[y];
  }
}

void init(int x,int fa)
{
  dep[x] = dep[fa] + 1;

  st[x][0] = fa;
  for(int i = 1;i <= 16;++ i)
    st[x][i] = st[st[x][i - 1]][i - 1];

  for(auto y : vec[x])
  {
    if(y == fa)continue;
    init(y,x);
  } 
}

int lca(int x,int y)
{
  if(dep[x] < dep[y])swap(x,y);

  for(int i = 16;i >= 0;-- i)if(dep[st[x][i] <= dep[y]])x = st[x][i];
  if(x == y)return x;

  for(int i = 16;i >= 0;-- i)if(st[x][i] != st[y][i])x = st[x][i],y = st[y][i];
  return st[x][0];
}

void solve()
{
  int n,m;cin >> n >> m;

  for(int i = 1;i < n;++ i)
  {
    int u,v;cin >> u >> v;
    vec[u].push_back(v);
    vec[v].push_back(u);
    num[u][v] = num[v][u] = i;
  }

  init(1,0);

  for(int i = 1;i <= m;++ i)
  {
    int u,v;cin >> u >> v;
    ++ diff[u],++ diff[v],diff[lca(u,v)] -= 2;
  }

  dfs(1,0);
  
  int ans = -1;
  for(int i = 1;i <= n;++ i)
    if(prefix[i] == m)
      ans = max(ans,num[st[i][0]][i]);
  
  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}