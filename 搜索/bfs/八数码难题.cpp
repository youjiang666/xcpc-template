//P1379 八数码难题
/*
3 * 3的棋盘给定初始状态0可以和任意相邻位置交换，求到目标状态的最小操作次数
*/

/*
遇到最小操作数问题可以考虑一下bfs，使用map将string映射一下记录vis，bfs里之间模拟移动的过程即可
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

struct op_0{string s;int o;}op;//记录0的位置以免反复遍历找0

int dx[4] = {-3,1,3,-1};
string goal = "123804765";
map<string,int>vis;

void solve()
{
  string s;cin >> s;
  if(s == goal)
  {
    cout << 0;
    return;
  }
  queue<op_0>q;
  int o = 0;
  while(s[o] != '0')++ o;

  int ans = 0;
  q.push({s,o});
  while(!q.empty())
  {
    ++ ans;
    int en = q.size();
    while(en --)
    {
      string t = q.front().s;
      int x = q.front().o;
      q.pop();
      if(vis[t])continue;
      vis[t] = 1;
      for(int i = 0;i < 4;++ i)
      {
        if(i == 3 && (x == 3 || x == 6) || i == 1 && (x == 2 || x == 5))continue;
        //左边界不能向左走，右边界不能向右走
        //这里可以将x映射到x = (x - 1) / 3 + 1，y = (x - 1) % 3 + 1,然后判边界
        int xx = x + dx[i];
        if(xx < 0 || xx > 8)continue;//越界
        
        swap(t[x],t[xx]);//交换0和dx位置
        q.push({t,xx});
        if(t == goal)//到达目标序列
        {
          cout << ans;
          return;
        }
        swap(t[x],t[xx]);//复原现场
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}