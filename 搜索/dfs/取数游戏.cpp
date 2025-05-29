//P1123 取数游戏
/*
给定n*m矩阵取出一些两两不相邻的数求最大总和
*/

/*
同理标记回溯，更新出最大总和即可
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;
int n,m,a[10][10],vis[10][10],ans;
int xx[9] = {-1,-1,-1,0,0,0,1,1,1},yy[9] = {-1,0,1,-1,0,1,-1,0,1};

int judge(int x,int y)
{
  for(int o = 0;o <= 8;++ o)if(vis[x + xx[o]][y + yy[o]])return 0;
  return 1;
}

void dfs(int x,int y,int sum)
{
  for(int i = x;i <= n;++ i)
    for(int j = (i == x ? y : 1);j <= m;++ j)
    {
      if(!judge(i,j))continue;
        vis[i][j] = 1;
        dfs(i,j,sum + a[i][j]);
        vis[i][j] = 0;
    }
    ans = max(ans , sum);
    return;
} 

void solve()
{
  cin >> n >> m;
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= m;++ j)cin >> a[i][j];
  dfs(1,1,0);
  memset(vis,0,sizeof(vis));
  cout << ans <<endl;
  ans = 0;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  cin >> _;
  while(_--)solve();
  return 0;
}