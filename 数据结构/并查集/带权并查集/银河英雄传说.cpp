//P1196 [NOI2002] 银河英雄传说、
/*
t条信息，M i j 是指将 i接到 j的队尾，C i j 指查询 i到 j之间有多少战舰
*/

/*
带权并查集维护节点之间关系
细节：合并两个集合的时候要记录 sz，因为是把一方放在另一方队尾，所以 dis[lr] = sz[rr]
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e5+10,P=1e9+7;

int pre[N],dis[N],sz[N];

int root(int x)
{
  if(pre[x] == x)return x;
  else {
    int t = pre[x];
    pre[x] = root(pre[x]);//先更新父亲
    dis[x] += dis[t];//常规更新
    return pre[x];
  }
}

void merge(int l,int r)
{
  int lr = root(l),rr = root(r);
  if(lr == rr)return;
  pre[lr] = rr;
  dis[lr] = sz[rr];//根作为队头 dis[rr] = 0,所已合并完之后 dis[lr] = sz[rr]
  sz[rr] += sz[lr];//合并sz
}

void query(int l,int r)
{
  int lr = root(l),rr = root(r);
  if(lr != rr)cout << -1 << endl;
  else cout << max(0,abs(dis[r] - dis[l]) - 1) << endl;
}

void solve()
{
  for(int i = 1;i <= N;++ i)pre[i] = i,sz[i] = 1;
  int t;cin >> t;
  while(t --)
  {
    char op;int l,r;cin >> op >> l >> r;
    if(op == 'M')merge(l,r);
    else query(l,r);
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}