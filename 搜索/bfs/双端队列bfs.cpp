//P4667 [BalticOI 2011] Switch the Lamp On 电路维修 (Day1)
/*
方格的对角线含电线有两个方向，转动电线使得线路由左上连至右下，求最小代价
*/

/*
最小操作代价考虑bfs，又由于每个格子里电线只有两种状态，设0为联通1为不连通，
把格点看作点，优先扩展连通的边，这样可以更快逼近答案，类似dj算法，A*思想
*/
//类似于dj算法，将可能更优的路径先拓展，且弹出复杂度O(1)，也可以叫01bfs（边权为0或1），大大减少了的要扩展的点
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=3e5,P=1e9+7;

int vr[N][4],n,m,dx[4],dis[N];
bitset<N>vis;

void solve()
{
  cin >> n >> m;
  int en = ++ n * ++ m;
  int dx[4] = {- m - 1,- m + 1,m + 1,m - 1};//向四个角走的坐标变换（0代表左上角，1代表右上）
  for(int i = 1;i < n;++ i)
    for(int j = 1;j < m;++ j)
    {
      char op;cin >> op;
      int x = (i - 1) * m + j;
      if(op == '/')vr[x][2] = vr[x + m + 1][0] = 1;//1代表不连通操作代价为1
      else vr[x + 1][3] = vr[x + m][1] = 1;
      //该边影响的四条边权
    }
  
  deque<int>q;
  q.push_back(1);
  vis[1] = 1;
  while(!q.empty())
  {
    int t = q.front();
    q.pop_front();
    for(int i = 0;i < 4;++ i)//向四个对角扩展
    {
      int xx = t + dx[i];//也可以映射到x，y后再判不合法
      if(!(1 <= xx && xx <= en) || t % m == 0 && (i == 1 || i == 2) || t % m == 1 && (i == 0 || i == 3))continue;//不越界且移动合法
      if(!vis[xx] || dis[t] + vr[t][i] < dis[xx])
      {
        if(vr[t][i])q.push_back(xx);
        else q.push_front(xx);//将与t连通的放在队列前面优先拓展
        dis[xx] = dis[t] + vr[t][i],vis[xx] = 1;
      }
    }
  }

  if(vis[en])cout << dis[en];
  else cout << "NO SOLUTION";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}