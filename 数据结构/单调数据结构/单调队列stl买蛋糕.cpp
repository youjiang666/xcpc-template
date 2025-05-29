//蓝桥 3707 买蛋糕
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=998244353;

int mi[N],mx[N],ans,a[N];
deque<int>dq;

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
  dq.push_back(1);
  for(int i = 2;i <= n;++ i)
  {
    if(i >= k && dq.front() < i -k + 1)dq.pop_front();
    while(dq.size() && a[i] <= a[dq.back()])dq.pop_back();
    dq.push_back(i);
    if(i >= k)mi[i - k + 1] = a[dq.front()];
  }
  dq.clear();
  dq.push_back(1);
  for(int i = 2;i <= n;++ i)
  {
    if(i >= k && dq.front() < i -k + 1)dq.pop_front();
    while(dq.size() && a[i] >= a[dq.back()])dq.pop_back();
    dq.push_back(i);
    if(i >= k)mx[i - k + 1] = a[dq.front()];
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