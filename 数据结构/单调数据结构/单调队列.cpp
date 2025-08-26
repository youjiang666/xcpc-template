#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e6 + 10,P = 1e9 + 7;

int a[N],q[N];

void solve()
{
  int n,k;cin >> n >> k;
  int h = 1,t = 0;
  fr(i,n)cin >> a[i];
  fr(i,n)
  {
    while(h <= t && a[i] <= a[q[t]])-- t;
    q[++ t] = i;
    if(q[h] <= i - k)++ h;
    if(i >= k)cout << a[q[h]] << " \n"[i == n];
  }

  h = 1,t = 0;
  fr(i,n)
  {
    while(h <= t && a[i] >= a[q[t]])-- t;
    q[++ t] = i;
    if(q[h] <= i - k)++ h;
    if(i >= k)cout << a[q[h]] << " \n"[i == n];
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}