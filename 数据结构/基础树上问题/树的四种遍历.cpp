//其实只有dfs以及bfs，在二叉树中dfs又分为前中后序遍历，bfs也叫层序遍历
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

int ls[N],rs[N];
//前序遍历，根->左儿子->右儿子
void dfs1(int x)
{
  cout << x << " ";
  if(ls[x])dfs1(ls[x]);
  if(rs[x])dfs1(rs[x]);
}
//中序遍历，左儿子->根->右儿子(相当于画条竖线从左到右扫描)
void dfs2(int x)
{
  if(ls[x])dfs2(ls[x]);
  cout << x << " ";
  if(rs[x])dfs2(rs[x]);
}
//后序遍历，左儿子->右儿子->根
void dfs3(int x)
{
  if(ls[x])dfs3(ls[x]);
  if(rs[x])dfs3(rs[x]);
  cout << x << " ";
}
//层序遍历，根开始从左到右遍历
void bfs()
{
  queue<int>q;
  q.push(1);
  while(!q.empty())
  {
    int x = q.front();q.pop();
    cout << x << " ";
    if(ls[x])q.push(ls[x]);
    if(rs[x])q.push(rs[x]);
  }
}
void solve()
{
  int n;cin >> n;
  for(int i = 1;i <= n;++ i)cin >> ls[i] >> rs[i];
  dfs1(1);
  cout << endl;
  dfs2(1);
  cout << endl;
  dfs3(1);
  cout << endl;
  bfs();
  cout << endl;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}
/*
//test
10
2 3
4 5
6 7
8 0
0 9
0 0
10 0
0 0
0 0
0 0
*/