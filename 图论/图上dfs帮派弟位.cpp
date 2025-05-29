//蓝桥 3891 帮派弟位
/*
按子树大小为第一关键词序号为第二关键词输出序号m的排名
*/

/*
先dfs到底，初始siz为1，然后自下而上合并子树大小，再排个序即可
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=1e9+7;

int siz[N];
vector<int>v[N];
pair<int,int>v1[N];

void dfs(int x)
{
  for(auto y : v[x])
  {
    dfs(y);//先找子树的大小
    siz[x] += siz[y];//合并到父亲上
  }
}

void solve()
{
  int n,m;cin >> n >> m;
  for(int i = 1;i < n;++ i)
  {
    int a,b;cin >> a >> b;
    v[b].push_back(a);//将b的儿子压入，v用来记录儿子
  }
  for(int i = 1;i <= n;++ i)siz[i] = 1;
  dfs(1);
  for(int i = 1;i <= n;++ i)v1[i] = {- siz[i] + 1,i};
  sort(v1 + 1,v1 + n + 1);
  for(int i = 1;i <= n;++ i)
    if(v1[i].second == m)
    {
      cout << i;
      return;
    }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}