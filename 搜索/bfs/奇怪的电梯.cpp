//P1135 奇怪的电梯
/*
每个点一个权值电梯在一条直线上移动，在某点可以向左移动w步或者向右移动w步，求最小操作次数
*/

/*
直接按题意扩展状态即可
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

int a[210],vis[210],n,sx,ex;
queue<int>q;

void bfs()
{
  q.push(sx);
  while(!q.empty())
  {
    int x = q.front();
    q.pop();
    int xx = x + a[x];
    if(xx <= n && vis[xx] == -1)
    {
      q.push(xx);
      vis[xx] = vis[x] + 1;
    }
    xx = x - a[x];
    if(xx > 0 && vis[xx] == -1)
    {
      q.push(xx);
      vis[xx] = vis[x] + 1;
    }
  }
}

void solve()
{
  cin >> n >> sx >> ex;
  for(int i = 1;i <= n;++ i)cin >> a[i];
  memset(vis,-1,sizeof(vis));
  vis[sx] = 0;
  bfs();
  //for(int i = 1;i <= n;++ i)cout << vis[i] << " "; 
  cout << vis[ex];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}