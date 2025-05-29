//P2294 [HNOI2005] 狡猾的商人
/*
对w组数据，n为节点数，m为信息条数，w为两节点之间的总和的关系，判断是否有信息是矛盾的
*/

/*
直接带权并查集，对于每条信息先看是否可以在已有的信息里找到（两者根相同）
如果可以就判断一下dis[u] - dis[v] == w，
不相等即矛盾了，无法判断的话之间加入（两根不同）

细节：
对于路径压缩时先更新根的权值再更新节点的权
合并两根的时候dis[rx] = dis[r] - dis[l] + v（通过画图向量的合成或者举例来理解）
查询就是dis[l] - dis[r]
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e5+10,P=1e9+7;

int pre[N];
ll dis[N];

int root(int x)
{
  if(pre[x] == x)return x;
  int t = pre[x];
  pre[x] = root(pre[x]);
  dis[x] += dis[t];
  return pre[x];
}

void merge(int l,int r,ll v)
{
  int lr = root(l),rr = root(r);
  pre[lr] = rr;
  dis[lr] = dis[r] + v - dis[l];
}

bool check(int l,int r,ll v)
{
  int lr = root(l),rr = root(r);
  if(lr == rr && dis[l] - dis[r] != v)return 1;
  //只有在两者位于一个集合时才可以判断是否与之前的信息矛盾否则无法判断
  return 0;
}

void solve()
{
  int n,m;cin >> n >> m;
  for(int i = 1;i <= n + 1;++ i)pre[i] = i,dis[i] = 0;

  int flag = 0;
  while(m --)
  {
    int l,r;ll v;cin >> l >> r >> v;
    flag |= check(l,r + 1,v);
    if(flag)continue;
    merge(l,r + 1,v);
  }

  if(flag)cout << "false" << endl;
  else cout << "true" << endl;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  cin >> _;
  while(_--)solve();
  return 0;
}