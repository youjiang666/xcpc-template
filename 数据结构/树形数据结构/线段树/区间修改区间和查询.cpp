//https://www.luogu.com.cn/problem/P3372

/*
给定大小为n的数组，m次操作，操作1：给[x,y]所有数加上k
操作2：查询[x,y]的和
*/

/*
线段树区间修改区间查询模板
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
  ll l,r,sum,add;
}tr[N << 2];//最坏为4 * n

ll a[N];

void pushup(int p){
  tr[p].sum = tr[lc].sum + tr[rc].sum;
}

void pushdown(int p){
  if(tr[p].add){
    tr[lc].sum += (tr[lc].r - tr[lc].l + 1) * tr[p].add;
    tr[rc].sum += (tr[rc].r - tr[rc].l + 1) * tr[p].add;
    tr[lc].add += tr[p].add;//注意这里是将子节点的懒标记加上父亲的而不是直接赋值
    tr[rc].add += tr[p].add;
    tr[p].add = 0;
  }
}

void build(int p,int l,int r){
  tr[p] = {l,r,a[l],0};
  if(l == r)return;
  int mid = l + r >> 1;
  build(lc,l,mid);
  build(rc,mid + 1,r);
  pushup(p);
}

void update(int p,int l,int r,ll k){
  if(l <= tr[p].l && tr[p].r <= r){
    tr[p].sum += (tr[p].r - tr[p].l + 1) * k;
    tr[p].add += k;
    return;
  }
  pushdown(p);
  int mid = tr[p].l + tr[p].r >> 1;
  if(l <= mid)update(lc,l,r,k);
  if(r > mid)update(rc,l,r,k);
  pushup(p);
}

ll query(int p,int l,int r){
  if(l <= tr[p].l && tr[p].r <= r)
    return tr[p].sum; 
  pushdown(p);
  int mid = tr[p].l + tr[p].r >> 1;
  ll sum = 0;
  if(l <= mid)sum += query(lc,l,r);
  if(r > mid)sum += query(rc,l,r);
  return sum;
}

void solve(){
  int n,m;cin >> n >> m;
  fr(i,n)cin >> a[i];
  build(1,1,n);
  while(m --){
    int _,x,y;cin >> _ >> x >> y;
    if(_ == 1){
      ll k;cin >> k;
      update(1,x,y,k);
    }else cout << query(1,x,y) << "\n";
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}