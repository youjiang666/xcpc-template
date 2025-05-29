//B3644 【模板】拓扑排序 / 家谱树
//dfs实现拓扑排序，为匈牙利算法垫基
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

vector<int>vr[110],tp;
int c[110],n;

bool dfs(int x)
{
  c[x] = -1;
  for(auto y : vr[x])
    if(x == -1 || !c[y] && !dfs(y))return 0;
  c[x] = 1;
  tp.push_back(x);
  return 1;
}

bool topo()
{
  for(int i = 1;i <= n;++ i)
  if(!c[i] && !dfs(i))return 0;
  reverse(tp.begin(),tp.end());
}

void solve()
{
  cin >> n;
  for(int i = 1;i <= n;++ i)
  {
    int x;
    while(cin >> x,x)vr[i].push_back(x);
  }

  topo();

  for(auto x : tp)cout << x << " ";
  //当tp.size() != n或者topo返回0时说明该有向图中有环
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}