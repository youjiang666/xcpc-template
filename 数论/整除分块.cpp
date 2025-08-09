//https://www.luogu.com.cn/problem/P2261
/*
给定n和k，求解k mod i的和
*/

/*
O（根号n）
公式变形后整除分块
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

void solve()
{
  ll n,k;cin >> n >> k;
  ll ans = n * k;
  for(ll l = 1,r;l <= n;l = r + 1)
  {
    if(l > k)break;
    r = min(n,k / (k / l));
    ans -= (k / l) * ((l + r) * (r - l + 1) >> 1);
  }
  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}