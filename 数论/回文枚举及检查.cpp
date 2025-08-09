//https://atcoder.jp/contests/abc414/tasks/abc414_c
/*
给定a和n，求1到n中10进制与a进制都是回文的数的和
*/

/*
直接枚举1到n内所有回文数，判断a进制下是否是回文即可，注意枚举以及检查时的写法
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

ll a,n,ans;

bool f(ll x)
{
  ll y = 0,t = x;
  while(t)y = y * a + t % a,t /= a;
  return x == y;
}

void solve()
{
  cin >> a >> n;
  for(int i = 1;;++ i)
  {
    ll t = i / 10,x = i,y = i;
    while(t)x = x * 10 + t % 10,t /= 10;
    if(x > n)
    {
      cout << ans;
      return;
    }
    if(f(x))ans += x;
    t = i;
    while(t)y = y * 10 + t % 10,t /= 10;
    if(y <= n && f(y))ans += y;
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}