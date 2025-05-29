//P8779 [蓝桥杯 2022 省 A] 推导部分和
/*
给出区间和查找区间和，找不到输出未知
*/

/*
经典带权并查集，维护一下关系即可
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
  pre[x] = root(pre[x]);//先找根再回退更新dis
  dis[x] += dis[t];//加上更新后的父亲到根节点的距离
  return pre[x];
}

void merge(int l,int r,ll v)
{
  int lr = root(l),rr = root(r);
  pre[lr] = rr;
  dis[lr] = dis[r] + v - dis[l];//更新lr到rr的距离画个图就很任意理解
}

void query(int l,int r)
{
  int lr = root(l),rr = root(r);
  if(lr != rr)
    cout << "UNKNOWN" << endl;
  else cout << dis[l] - dis[r] << endl;//只有当端点在一个集合时才可以得出距离关系
}

void solve()
{
  int n,m,q;cin >> n >> m >> q;
  for(int i = 1;i <= n + 1;++ i)pre[i] = i;

  while(m --)
  {
    int l,r;ll v;cin >> l >> r >> v;
    merge(l,r + 1,v);
  }

  while(q --)
  {
    int l,r;cin >> l >> r;
    query(l,r + 1);
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}