/*
求最长公共子序列，并求出具体序列
*/

/*
s串与p串组成一个二维矩阵，二维dp记录即可
如果相等则从左上角dp转移+1，否则取上侧和左侧最大的
最后输出dp[n][m]即可
具体序列的话直接从最末尾开始倒推就行
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e3+10,P=1e9+7;

int dp[N][N],ans,n,m;
string a,b;

void solve1()//求具体序列（不唯一）
{
  int i = n,j = m,op=dp[n][m];
  string res;
  while(op && i >= 1 && j >= 1)
  {
    if(a[i] == b[j])//相当于倒推，向左上走
    {
      res = a[i] + res;
      --i,--j;
    }else //否则走大的那条边
      dp[i-1][j] >= dp[i][j-1] ? --i : --j;
  }
  cout << res;
}

void solve()//求LCS的长度
{
  cin >> n >> m;
  cin >> a >> b;
  a = ' ' + a;
  b = ' ' + b;
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= m;++ j)
      dp[i][j] = (a[i] == b[j] ? 
        dp[i - 1][j - 1] + 1 : max(dp[i - 1][j],dp[i][j - 1]));
  cout << dp[n][m] << endl;
  solve1();
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}