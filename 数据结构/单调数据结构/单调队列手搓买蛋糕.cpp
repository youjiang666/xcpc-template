////蓝桥 3707 买蛋糕
/*
给定n个数，求连续的区间最大值最小值差值小于等于x的概率
*/

/*
给大小为k的区间按顺序标号，跑两遍单调队列得到各区间的最大最小值再统计符合要求的区间然后除以总区间个数即可
*/
//复杂度很优秀
//这类问题也可以使用multiset(多重集合搞定)
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=998244353;

int mi[N],mx[N],a[N],dq[N],ans,hh,tt;

ll qmi(ll a,ll b)
{
  ll res = 1;
  while(b)
  {
    if(b & 1)res = res * a % P;
    a = a * a % P;b >>= 1;
  }
  return res;
}

ll inv(ll x){return qmi(x,P - 2);}

void solve()
{
  int n,k,x;cin >> n >> k >> x;
  for(int i = 1;i <= n;++ i)cin >> a[i];
  //单增
  dq[tt] = 1;
  for(int i = 2;i <= n;++ i)
  {
    if(i >= k && dq[hh] < i - k + 1)++ hh;
    while(hh <= tt && a[i] <= a[dq[tt]])-- tt;
    dq[++ tt] = i;
    if(i >= k)mi[i - k + 1] = a[dq[hh]];
  }
  //单减
  hh = tt = 0;
  dq[tt] = 1;
  for(int i = 2;i <= n;++ i)
  {
    if(i >= k && dq[hh] < i - k + 1)++ hh;
    while(hh <= tt && a[i] >= a[dq[tt]])-- tt;
    dq[++ tt] = i;
    if(i >= k)mx[i - k + 1] = a[dq[hh]];
  }
  int en = n - k + 1;
  for(int i = 1;i <= en;++ i)if(mx[i] - mi[i] <= x)++ ans;
  cout << ans * inv(en) % P;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}