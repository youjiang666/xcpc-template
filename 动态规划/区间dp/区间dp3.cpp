//https://www.luogu.com.cn/problem/P1063

/*
给定 n个珠子，珠子有头和尾，头的属性值为 a[i],尾的属性值为 a[i + 1]，特别的第 n颗珠子的尾为 a[1]
当两珠子的尾与相邻的珠子的头相等时可以将两个珠子合并，价值为 a[i] * a[j] * a[j + 1]，即 i的头乘上 i的尾再乘上j的尾部
求最大价值
*/

/*
涉及区间问题最优解考虑区间dp
有两种设法dp[i][j]
若dp表示将第 i到 j颗珠子合并，转移方程为
dp[l][r] = max(dp[l][r],dp[l][k] + dp[k + 1][r] + a[l] * a[k + 1] * a[r + 1]);(l <= k && k < r)
若dp表示将以 a[i]为头 a[j]为尾的珠子合并，转移方程为
dp[l][r] = max(dp[l][r],dp[l][k] + dp[k][r] + a[k] * a[r] * a[l]);(l < k && k < r)

注意以上两种的总长度是不同的细节上略有差异
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 2e2 + 10,P = 1e9 + 7;

int a[N],dp[N][N],mx;

void solve()
{
  int n;cin >> n;
  fr(i,n)cin >> a[i],a[n + i] = a[i];
  a[(n << 1) + 1] = a[1];

  for(int i = 2;i <= n;++ i)
    fr(l,(n << 1) - i + 1)
    {
      int r = l + i - 1;
      for(int k = l;k < r;++ k)
        dp[l][r] = max(dp[l][r],dp[l][k] + dp[k + 1][r] + a[k + 1] * a[r + 1] * a[l]);
    }
  fr(i,n)mx = max(mx,dp[i][i + n - 1]);
  cout << mx;

  /*
  for(int i = 2;i <= n;++ i)
    fr(l,(n << 1) - i + 2)
    {
      int r = l + i;
      for(int k = l + 1;k < r;++ k)
        dp[l][r] = max(dp[l][r],dp[l][k] + dp[k][r] + a[k] * a[r] * a[l]);
    }
  fr(i,n)mx = max(mx,dp[i][i + n]);
  cout << mx;
  */
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}