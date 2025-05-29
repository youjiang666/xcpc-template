//19721 最大异或结点
/*
n个点找到两个不直接相连的节点异或的最大值
*/

/*
在对某个点找最大时先移除与他相连的点，查询完再把这些点加入进行下一步查询
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int M=30e5+10,N=1e5+10;

int son[M][2],tot=1,ans,e[M],a[N];
vector<int>g[N];

//删去树中x节点的影响
void move(int x){
  int o = 1;
  e[o]--;
  for(int i = 30;i >= 0;-- i)
  {
    int y = x >> i & 1;
    o=son[o][y];
    e[o]--;
  } 
}

void insert(int x){
  int o = 1;
  e[o]++;
  for(int i = 30;i >= 0;-- i)
  {
    int y = x >> i & 1;
    if(!son[o][y])son[o][y] = ++ tot;//动态开点
    o = son[o][y];
    e[o] ++;
  }
  //++ en[o];有需要可以加上这个记录结尾
}

int query(int x){
  int res = 0,o = 1;
  for(int i = 30;i >= 0;-- i)
  {
    int y = x >> i & 1;
    if(son[o][!y] && e[o])o=son[o][!y],res |= (1 << i);//从高位往低位贪心的走相反值
    else o = son[o][y];
  }
  return res;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int n;cin >> n;
  for(int i = 1;i <= n;++ i)
  {
    cin >> a[i];
    insert(a[i]);
  }

  //记录相连的点方便从树中剔除
  for(int i = 1;i <= n;++ i)
  {
    int x;cin >> x;
    if(x==-1)continue;
    g[i].push_back(a[x]);
    g[x].push_back(a[i]);
  }

  //剔除查询最大值后再插入进行下一次查询
  for(int i = 1;i <= n;++ i)
  {
    for(auto j : g[i])move(j);
    ans=max(ans,query(a[i]));
    for(auto j : g[i])insert(j);
  }
  cout << ans;
  return 0;
}