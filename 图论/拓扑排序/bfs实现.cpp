//B3644 【模板】拓扑排序 / 家谱树
//bfs实现也叫卡恩算法
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

vector<int>vr[110],tp;//tp内便是拓扑序列
int din[110],n;

void topo()
{
  queue<int>q;
  for(int i = 1;i <= n;++ i)
    if(!din[i])q.push(i);//从入度为零的点开始扩展
  
  while(!q.empty())
  {
    int x = q.front();q.pop();
    tp.push_back(x);
    for(auto y : vr[x])
      if(-- din[y] == 0)q.push(y);
  }
}

void solve()
{
  cin >> n;
  for(int i = 1;i <= n;++ i)
  {
    int x;
    while(cin >> x,x)vr[i].push_back(x),++ din[x];
  }

  topo();

  for(auto x : tp)cout << x << " ";
  //当tp.size() != n时说明该有向图中有环
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}