//蓝桥 4385 最近公共祖先LCA查询
/*
离线查询，记录要查询的组利用dfs+并查集求出lca
*/

//在数据较大时可以考虑把dfs改成非递归的形式使用栈的方法实现
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=1e9+7;

struct Q{int z,id;};

vector<int>vr[N];
vector<Q>q[N];
bitset<N>vis;

int pre[N],ans[N];

int root(int x){return pre[x] = pre[x] == x ? x : root(pre[x]);}

void dfs(int x,int fa)
{
  vis[x] = 1;//也可以放在后面再标记
  for(auto y : vr[x])
  {
    if(y == fa)continue;
    dfs(y,x);
    pre[y] = x;//搜完子树后合并子节点到父节点上
  }
  for(auto i : q[x])if(vis[i.z])ans[i.id] = root(i.z);//当z访问过直接等于其的根否则交给z来处理
}

void solve()
{
  int n;cin >> n;
  for(int i = 1;i <= n;++ i)pre[i] = i;
  for(int i = 1;i < n;++ i)
  {
    int u,v;cin >> u >> v;
    vr[u].push_back(v);
    vr[v].push_back(u);
  }
  
  int _;cin >> _;
  for(int i = 1;i <= _;++ i)
  {
    int x,y;cin >> x >> y;
    q[x].push_back({y,i});
    q[y].push_back({x,i});//记录问题离线求解
  }

  dfs(1,0);

  for(int i = 1;i <= _;++ i)cout << ans[i] <<endl;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}