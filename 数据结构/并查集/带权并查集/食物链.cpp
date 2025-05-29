//P2024 [NOI2001] 食物链
/*
n个动物，k个信息，1代表l和r是同类，2代表l吃r，求假话总数
假话：1.与前面冲突 2.l，r不在n以内 3.当op == 2时 l和r相等
*/

/*
dis含义：0表示同类，1表示吃根节点的动物，2表示被根节点吃
合并两根的时候dis[rx] = (dis[r] - dis[l] + v + 3) % 3（通过画图向量的合成或者举例来理解）
查询就是(dis[l] - dis[r] + 3) % 3
mod3是为了使权值落在0到2之间
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e5+10,P=1e9+7;

int ans,pre[N],dis[N];

int root(int x)
{
  if(pre[x] == x)return x;
  else {
    int t = pre[x];
    pre[x] = root(pre[x]);//写并查集注意这里是pre[x]
    dis[x] = (dis[x] + dis[t]) % 3;
    return pre[x];
  }
}

bool check(int op,int l,int r)
{
  int lr = root(l),rr = root(r);
  if(lr != rr || op == (dis[l] - dis[r] + 3) % 3)return 1;
  //不在一个集合或者关系与信息符合时可以合并否则信息为假
  return 0;
}

void merge(int l,int r,int v)
{
  int lr = root(l),rr = root(r);
  pre[lr] = rr;
  dis[lr] = (dis[r] + v - dis[l] + 3) % 3;//画图
}

void solve()
{
  int n,k;cin >> n >> k;
  for(int i = 1;i <= n;++ i)pre[i] = i;

  while(k --)
  {
    int op,l,r;cin >> op >> l >> r;
    
    //非法状态处理
    if(op == 2 && l == r || l > n || r > n || !check(op - 1,l,r))
    {
      ++ ans;
      continue;
    }

    merge(l,r,op - 1);
  }

  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}