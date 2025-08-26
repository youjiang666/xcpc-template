//https://www.luogu.com.cn/problem/P2516

/*
求出a和b最长公共子序列长度以及lcs的种类
*/

/*
数据量比较小直接n^2做法，也方便求解种类数，注意一个一个的状态
dp[i][j]表示 a 以 i 结尾 b 以 j 结尾
求长度
对于i行j列：
当a[i] == b[j]时可以接到dp[i - 1][j - 1]这个状态的后面长度增加 1
当a[i] != b[j]时可以接到dp[i - 1][j] 或者 dp[i][j - 1]中的较大者

求种类数：
考虑你回溯的话状态可以怎么转移
对于i行j列：
当a[i] == b[j]时
可以由dp[i - 1][j - 1]状态转移种类数，然后还有就是dp[i - 1][j] 以及 dp[i][j - 1] 中与 dp[i][j] 等值的也可以
当a[i] != b[j]时dp[i - 1][j] 以及 dp[i][j - 1] 中与 dp[i][j] 等值的可以转移
但注意此时若 dp[i - 1][j - 1] 的值也等于 dp[i][j]的话是有状态（说明dp[i][j - 1]是由dp[i - 1][j - 1]转过来的）重复了的
所以此时要减去dp[i - 1][j - 1]以保证去重（暗含了一个性质该情况下左和上的值一定相等这才导致重复可以画一个框演示理解）

空间大概在5e7，采用滚动数组优化，用2 * n的二维数组以及op作为当前状态编号来滚动状态（因为当前状态是依赖于三个方向上的）
*/

#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 5e3 + 10,P = 1e8;

int dp[2][N],ct[2][N],op,mx;

void solve()
{
  string a,b;cin >> a >> b;
  int n = a.length(),m = b.length();
  a = ' ' + a;
  b = ' ' + b;
  fr(j,m - 1)
  {
    fr(i,n - 1)
    {
      if(a[i] == b[j])
      {
        dp[op][i] = dp[op ^ 1][i - 1] + 1;
        if(dp[op][i] == 1)ct[op][i] = 1;
        else ct[op][i] = ct[op ^ 1][i - 1];
        mx = max(mx,dp[op][i]);
      }else dp[op][i] = max(dp[op][i - 1],dp[op ^ 1][i]);

      if(dp[op][i - 1] == dp[op][i])ct[op][i] = (0ll + ct[op][i] + ct[op][i - 1]) % P;
      if(dp[op][i] == dp[op ^ 1][i])ct[op][i] = (0ll + ct[op][i] + ct[op ^ 1][i]) % P;
      if(dp[op][i] == dp[op ^ 1][i - 1])ct[op][i] = ((0ll + ct[op][i] - ct[op ^ 1][i - 1]) % P + P) % P;
    }
    op ^= 1;
    fr(i,n)ct[op][i] = 0;
  }
  cout << mx << "\n" << ct[op ^ 1][n - 1];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}