//P3128 [USACO15DEC] Max Flow P
/*
n个节点n-1条边，表示u到v路径上都加一，求节点最大权值
*/

/*
树上点差分，思路同上
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N=1e5+10,P=1e9+7;

vector<int>tree[N];

int diff[N],st[N][16],dep[N],prefix[N];

void dfs(int x,int fa)
{
  prefix[x] = diff[x];
  for(auto y : tree[x])
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
  for(int i = 1;i <= 15;++ i)
    st[x][i] = st[st[x][i - 1]][i - 1];

  for(auto y : tree[x])
  {
    if(y == fa)continue;
    init(y,x);
  }
}

int lca(int x,int y)
{
  if(dep[x] < dep[y])swap(x,y);

  for(int i = 15;i >= 0;-- i)if(dep[st[x][i]] >= dep[y])x = st[x][i];
  if(x == y)return x;

  for(int i = 15;i >= 0;-- i)if(st[x][i] != st[y][i])x = st[x][i],y = st[y][i];
  return st[x][0];
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
  init(1,0);
  for(int i = 1;i <= k;++ i)
  {
    int u,v;cin >> u >> v;
    //cout << lca(u,v) <<endl;
    int c = lca(u,v);
    ++ diff[u],++ diff[v],-- diff[c],-- diff[st[c][0]];
    //cout << c << " " << st[c][0] << endl;
  }
  dfs(1,0);
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