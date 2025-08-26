//求 01背包最优解的物体编号字典序最小的具体方案

/*
正常求方案都是通过末状态回溯得到，若这里我们还是按普通方法得到 dp矩阵
我们只能得到一个倒的选择方案，又由于字典序需要从前往后贪心选择，所以我们选择倒序
更新 dp矩阵，再由dp[1][m]来贪心的回溯得到最小字典序方案
易得当dp[i + 1][j - w[i]] + v[i] == dp[i][j]时必须选此时该位置是最小的序，初始容量设为 m即可
回溯时选择了某条路就要减去 w[i]

也可以通过记录路径的列来求解，当该路径的列不等于上一个路径的列时便选上

对于完全背包的话要把因为它依赖于新状态把 i + 1改成 i即可，顺序同上

对于多重背包的话要控制跳转次数
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e3 + 10,P = 1e9 + 7;

ll dp[N][N],w[N],v[N];

void solve()
{
  int n,m;cin >> n >> m;
  fr(i,n)cin >> w[i] >> v[i];
  for(int i = n;i >= 1;-- i)
    for(int j = 0;j <= m;++ j)
    {
      dp[i][j] = dp[i + 1][j];
      if(j >= w[i])dp[i][j] = max(dp[i + 1][j - w[i]] + v[i],dp[i][j]);
    }

  int op = m;
  fr(i,n)
    if(op >= w[i] && dp[i + 1][op - w[i]] + v[i] == dp[i][op])
    {
      cout << i << " ";
      op -= w[i];//注意这里 op代表的是剩余容量所以是减去 w[i]
    }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}
/*
4 7
1 1
2 3
3 4 
4 5

1 2 4
*/