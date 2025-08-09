//https://codeforces.com/contest/2113/problem/C
/*
给定n*m的地图，爆炸半径为k格，'g'：金子，'.'：空地，'#'：石头
只有空地可以放炸弹，炸完可以清空半径为k的所有格子，并且收集到k + 1位置的金子，求最多可收集的金子数
*/

/*
通过模拟可知第一次爆炸之后还存在的金子都可以收集到，所以我们只需要关注第一次即可，
为了使得收集的最多，我们只要找到半径为k的一个空地使得损失的金子最少即可
考虑使用二维前缀和，注意更新的细节
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e3+10,P=1e9+7;

char ma[N][N];
int pf[N][N],op[4];

void solve()
{
  int n,m,k;cin >> n >> m >> k;
  int ans = 0;
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= m;++ j)
    {
      cin >> ma[i][j];
      if(ma[i][j] == 'g')pf[i][j] = 1,++ ans;
      else pf[i][j] = 0;
      pf[i][j] += pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1];
    }
  -- k;
  int mi = ans;
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= m;++ j)
      if(ma[i][j] == '.')
      {
        op[0] = min(n,i + k);
        op[1] = max(0,i - k - 1);
        op[2] = min(m,j + k);
        op[3] = max(0,j - k - 1);
        mi = min(mi,pf[op[0]][op[2]] + pf[op[1]][op[3]] - pf[op[1]][op[2]] - pf[op[0]][op[3]]);
        //防止越界
      }
        
  cout << ans - mi << "\n";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  cin >> _;
  while(_--)solve();
  return 0;
}