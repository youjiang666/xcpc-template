//P1219 [USACO1.5] 八皇后 Checker Challenge
/*
填下一个格子，标记行，列，斜线后dfs回溯取消标记找下一种可能
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;
int ans,n,b1[20],b2[30],b3[30],a[20];

void dfs(int x)
{
  if(x > n)
  {
    ++ ans;
    if(ans <= 3)
    {
      for(int i = 1;i <= n;++ i)cout << a[i] << " ";
      cout << endl;
    }
    return;
  }
  for(int y = 1;y <= n;++ y)
  {
    if(!b1[y] && !b2[n - x + y] && !b3[x + y - 1])
    {
      b1[y] = b2[n - x + y] = b3[x + y - 1] = 1;
      a[x] = y;
      dfs(x + 1);
      b1[y] = b2[n - x + y] = b3[x + y - 1] = 0;
    }
  }
}

void solve()
{
  cin >> n;
  dfs(1);
  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}