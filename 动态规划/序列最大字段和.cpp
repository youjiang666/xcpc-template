//https://www.luogu.com.cn/problem/B4133

/*
求最大非空连续和
*/

/*
当前状态要么来自前一个状态加上 x，要么来自以 x 开头
dp[i] = max(dp[i - 1] + x,x)
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e7 + 10,P = 1e9 + 7;

ll dp[N],ans = - P;

void solve()
{
  int n;cin >> n;
  fr(i,n)
  {
    ll x;cin >> x;
    dp[i] = max(dp[i - 1] + x,x);
    ans = max(ans,dp[i]);
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