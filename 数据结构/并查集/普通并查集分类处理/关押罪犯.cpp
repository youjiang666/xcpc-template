//P1525 [NOIP 2010 提高组] 关押罪犯
/*
给定1 ~ n节点，不同节点之间有个边权 c，求解分成两个集合使得两图中最大的边权值最小的值
*/

/*
类似于二分图，这里采用贪心+并查集解决，使用 enemy记录每个人的一个代表性敌人
将l连到r的代表性敌人上，r连到l的代表性敌人上，最后只要不存在l和r在同一个集合里的信息
则可以不发生任何冲突，不然在第一条冲突的信息即为最小的最大边权
*/
//普通并查集做分类处理
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e5+10,P=1e9+7;

int pre[N],enemy[N];

struct people{
  int a,b,c;

  bool operator < (const people & u)const
  {
    return c < u.c;
  }
}p[N];//按罪犯之间的仇恨值排序

int root(int x)
{
  return pre[x] = pre[x] == x ? x : root(pre[x]);
}

void solve()
{
  int n,m;cin >> n >> m;

  for(int i = 1;i <= n;++ i)pre[i] = i;

  for(int i = 0;i < m;++ i)
  {
    int l,r,v;cin >> l >> r >> v;
    p[i] = {l,r,v};
  }

  sort(p,p + m);

  for(int i = m - 1;i >= 0;-- i)//贪心的先选仇恨大的
  {
    int l = p[i].a,r = p[i].b;
    int lr = root(l),rr = root(r);

    if(lr == rr)//当l,r不可避免的在一个集合中该值为答案
    {
      cout << p[i].c;
      return;
    }

    //记录l,r的敌人，将各组l,r的敌人合并到一个区间
    if(enemy[l])
    {
      int t = enemy[l];
      pre[rr] = root(t);
    }else enemy[l] = r;
    
    if(enemy[r])
    {
      int t = enemy[r];
      pre[lr] = root(t);
    }else enemy[r] = l;
  }
  cout << 0;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}