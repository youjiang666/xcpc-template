/*
树的重心求法
*/

/*
树重心的一些性质
定义：去除任意节点后使得两个子树大小中的最大值的最小对应的节点为重心
1.重心的子树中的最大值小于等于n/2；
2.除重心外的节点都必然存在一颗大于n/2的子树；
3.重心个数至多为2，若为2则两重心必然相邻，将链接两重心的边删去后一定划分为两颗大小相等的树
4，树所有点到某点的距离和到重心最小，若存在两个重心则距离和相同，反之距离和最小点便为重心
5.把两颗树通过一条边相连新重心在较大树的链接点与其原重心的简单路径上，若两树大小相等则重心就是两链接点
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

vector<int>vr[N];
vector<int>v;//记录重心

int mss[N],sz[N],n;

void dfs(int x,int fa)
{
  sz[x] = 1;
  for(auto y : vr[x])
  {
    if(y == fa)continue;
    dfs(y,x);
    sz[x] += sz[y];//合并子树到根上
    mss[x] = max(mss[x],sz[y]);//更新子树中的最大值
  }
  mss[x] = max(mss[x],n - sz[x]);//继续更新
  if(mss[x] <= n / 2)v.push_back(x);
}

void solve()
{
  cin >> n;
  for(int i = 1;i < n;++ i)
  {
    int u,v;cin >> u >> v;
    vr[u].push_back(v);
    vr[v].push_back(u);
  }
  dfs(1,0);
  for(auto x : v)cout << x << " ";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}