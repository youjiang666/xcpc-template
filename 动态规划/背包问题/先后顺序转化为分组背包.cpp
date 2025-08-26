//https://www.luogu.com.cn/problem/P1064

/*
给定 n容量，m件物品，物品体积为 w[i]，贡献为 v[i] = w[i] * x，
限制当 y为 0时为主件，否则为 y的附件，只有选择的主件才可以拿取附件
求最大价值
*/

/*
直接枚举每个位置，再枚举可能的物品组合，由旧状态转移后取最大值
分组背包

注意：
1.不要使用vis取标记用过的状态来判断是否使用了主件，因为可能会出现我使用主件转移不了但加上附件后可以转移，
标记的话状态是会不全的
2.一定要先枚举位置再枚举可能的物值，不然有会导致状态混淆重复选择物品
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 32e3 + 10,P = 1e9 + 7;

int w[N],v[N],s[N],a[N][70],dp[N];

void solve()
{
  int n,m;cin >> n >> m;
  fr(i,m)
  {
    int x,y;cin >> w[i] >> x >> y;
    v[i] = w[i] * x;
    a[y][++ s[y]] = i;
  }

  fr(i,s[0])
  {
    int x = a[0][i];
    for(int j = n;j >= w[x];-- j)
    {
      int ww = w[x],vv = v[x];
      dp[j] = max(dp[j],dp[j - ww] + vv);

      if(s[x])
      {
        ww += w[a[x][1]],vv += v[a[x][1]];
        if(j >= ww)dp[j] = max(dp[j],dp[j - ww] + vv);
      }

      if(s[x] == 2)
      {
        ww += w[a[x][2]],vv += v[a[x][2]];
        if(j >= ww)dp[j] = max(dp[j],dp[j - ww] + vv);
        ww -= w[a[x][1]],vv -= v[a[x][1]];
        if(j >= ww)dp[j] = max(dp[j],dp[j - ww] + vv);
      }
    }
  }
  cout << dp[n];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}