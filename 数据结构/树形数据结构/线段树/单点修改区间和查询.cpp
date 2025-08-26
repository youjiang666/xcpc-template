//https://www.luogu.com.cn/problem/P3374

/*
给定大小为n的数组，m次操作，操作1：给第x个数加上k
操作2：查询[x,y]的和
*/

/*
线段树单点修改区间查询模板
*/

#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
#define lc p << 1
#define rc p << 1 | 1
using ll = long long;
const ll inf = 2e18;
const int N = 1e6 + 10,P = 1e9 + 7;

struct node{
  ll l,r,sum;
}tr[N << 2];//最坏为 4 * n

ll a[N];

void pushup(int p)
{
  tr[p].sum = tr[lc].sum + tr[rc].sum;
}

void build(int p,int l,int r)
{
  tr[p] = {l,r,a[l]};
  if(l == r)return;
  int mid = l + r >> 1;
  build(lc,l,mid);
  build(rc,mid + 1,r);
  pushup(p);
}

void update(int p,int x,ll k)
{
  if(tr[p].l == tr[p].r)
  {
    tr[p].sum += k;
    return;
  }

  int mid = tr[p].l + tr[p].r >> 1;
  if(x <= mid)update(lc,x,k);
  else update(rc,x,k);
  pushup(p);
}

ll query(int p,int l,int r){
  if(l <= tr[p].l && tr[p].r <= r)
    return tr[p].sum; 
  int mid = tr[p].l + tr[p].r >> 1;
  ll sum = 0;
  if(l <= mid)sum += query(lc,l,r);
  if(r > mid)sum += query(rc,l,r);
  return sum;
}

void solve()
{
  int n,m;cin >> n >> m;
  fr(i,n)cin >> a[i];
  build(1,1,n);
  while(m --)
  {
    int _;cin >> _;
    if(_ == 1)
    {
      int x;ll k;cin >> x >> k;
      update(1,x,k);
    }else {
      int x,y;cin >> x >> y;
      cout << query(1,x,y) << "\n";
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