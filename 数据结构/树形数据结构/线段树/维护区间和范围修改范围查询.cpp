//P3372 【模板】线段树 1
//经典模型：范围修改，单点修改，范围重置（修改和重置可以放在一起，关键在于重置优先级高于修改） + 维护区间和，区间最值
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=1e9+7;

ll a[N],t[N << 2],lz[N << 2];//t树维护区间和，lz记录懒标记，最多扩展节点为总n的4倍

void up(int o){t[o] = t[o << 1] + t[o << 1 | 1];}//合并子节点信息

void lazy(int o,ll v,int n)//懒标记并更新该节点值
{
  t[o] += v * n;
  lz[o] += v;
}

void down(int o,int ln,int rn)//下放懒标记
{
  if(lz[o])
  {
    lazy(o << 1,lz[o],ln);
    lazy(o << 1 | 1,lz[o],rn);//更新左右儿子
    lz[o] = 0;//懒标记下放完毕，清除懒标记
  }
}

void bulid(int l,int r,int o)//建树
{
  if(l == r)//basecase，递归出口，然后会自下向上合并信息
  {
    t[o] = a[l];
    return;
  }

  int mid = (l + r) >> 1;
  bulid(l,mid,o << 1);
  bulid(mid + 1,r,o << 1 | 1);
  up(o);
}

void add(int jobl,int jobr,ll v,int l,int r,int o)
{
  if(jobl <= l && r <= jobr)
  {
    lazy(o,v,r - l + 1);
    return;
  }

  int mid = (l + r) >> 1;
  down(o,mid - l + 1,r - mid);
  if(jobl <= mid)add(jobl,jobr,v,l,mid,o << 1);
  if(jobr > mid)add(jobl,jobr,v,mid + 1,r,o << 1 | 1);
  up(o);
}

ll query(int jobl,int jobr,int l,int r,int o)
{
  if(jobl <= l && r <= jobr)return t[o];//该节点管辖区间被目标区间完全包含直接返回，该值一定是正确的

  int mid = (l + r) >> 1;
  down(o,mid - l + 1,r - mid);//必定会向下走所有下放懒标记并更新子节点，以确保所返回的值都为正确的值
  ll ans = 0;
  if(jobl <= mid)ans += query(jobl,jobr,l,mid,o << 1);
  if(jobr > mid)ans += query(jobl,jobr,mid + 1,r,o << 1 | 1);
  return ans;
}

void solve()
{
  int n,m;cin >> n >> m;
  for(int i = 1;i <= n;++ i)cin >> a[i];

  bulid(1,n,1);

  while(m --)
  {
    int op;cin >> op;
    if(op == 1)
    {
      int l,r;ll v;cin >> l >> r >> v;
      add(l,r,v,1,n,1);
    }else {
      int l,r;cin >> l >> r;
      cout << query(l,r,1,n,1) << endl;
    }
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}