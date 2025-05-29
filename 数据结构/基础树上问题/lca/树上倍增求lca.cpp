//蓝桥 4385 最近公共祖先LCA查询
/*
n个节点n-1条边，q次查询，a和b的lca
*/

/*
使用dfs求出dep深度以及st表（某点向上走多少步是谁），再利用st表找到lca
*/
//在数据较大时可以考虑把dfs改成非递归的形式使用栈的方法实现
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=1e9+7;

vector<int>vr[N];
int st[N][21],dep[N];//记录st表以及各个点的深度

void dfs(int x,int fa)
{
  dep[x] = dep[fa] + 1;

  st[x][0] = fa;//自己向上走一步到自己的父节点
  for(int i = 1;i <= 20;++ i)
    st[x][i] = st[st[x][i - 1]][i - 1];//内层是刚更新出的信息外层是自上而下的已经更新出了的信息（树形dp）
  
  for(auto y : vr[x])
  {
    if(y == fa)continue;
    dfs(y,x);
  }
}

int lca(int x,int y)
{
  if(dep[x] < dep[y])swap(x,y);//使x为较深的节点方便使两者到达较高者的同一线

  for(int i = 20;i >= 0;-- i)if(dep[st[x][i]] >= dep[y])x = st[x][i];//跳至同一高度
  if(x == y)return x;//对应x在y的子树上的情况

  for(int i = 20;i >= 0;-- i)if(st[x][i] != st[y][i])x = st[x][i],y = st[y][i];
  //当st相等时说明该位置在lca之上，不相等则在lca之下，因为st表对应二进制的组合则跳跃总步数可以为任意步，最后到达lca的子节点上
  return st[x][0];//x为lca的子节点，返回此时的父节点即可
}

void solve()
{
  int n;cin >> n;
  for(int i = 1;i < n;++ i)
  {
    int u,v;cin >> u >> v;
    vr[u].push_back(v);
    vr[v].push_back(u);
  }
  dfs(1,0);
  int q;cin >> q;
  while(q--)
  {
    int a,b;cin >> a >> b;
    cout << lca(a,b) << endl;
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}