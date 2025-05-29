//蓝桥 3029 卖树
/*
给定n个节点的树，一号节点为初始根，边权为k，根可以花费c代价移动到相邻位，
求由根出发的最长的路径权值之和减掉花费的最大值
*/

/*
由初始根更新各点到初始根的距离，找到最深的点，再由该点出发再找到离该点最远的点，
方法同上，再更新各点到该点的距离，则 ans = (depv,depu) * k - c * dep1的最大值
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=1e9+7;

vector<int>vr[N];

int depU[N],depV[N],dep1[N];//记录各点到U，V，1的距离

void dfs(int x,int fa,int dep[])
{
  dep[x] = dep[fa] + 1;//子树长等于父节点长加1
  for(auto y : vr[x])//遍历子树
  {
    if(y == fa)continue;//当子节点等于父节点时跳过防止重复跑也就是沿根一直向下跑
    dfs(y,x,dep);
  }
}

void solve()
{
  ll n,k,c;cin >> n >> k >> c;
  for(int i = 1;i < n;++ i)
  {
    int u,v;cin >> u >> v;
    vr[u].push_back(v);
    vr[v].push_back(u);
  }
  dep1[0] = depU[0] = depV[0] = -1;//这样的话这三个点到自己的距离会被更新成0
  dfs(1,0,dep1);
  int U = 1;
  for(int i = 1;i <= n;++ i)if(dep1[i] > dep1[U])U = i;
  //找到最深的节点作为U到V的直径的一个端点
  dfs(U,0,depU);//从U去找到最长的作为直径
  int V = 1;
  for(int i = 1;i <= n;++ i)if(depU[i] > depU[V])V = i;
  dfs(V,0,depV);
  ll ans = 0;
  for(int i = 1;i <= n;++ i)
  {
    ans = max(ans,max(depV[i],depU[i]) * k - c * dep1[i]);//从i出发最长的路径为i到U或者到V可证明到其它点一定没这长
    vr[i].clear();//多组测试需重构图
  }
  cout << ans << endl;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  cin >> _;
  while(_--)solve();
  return 0;
}