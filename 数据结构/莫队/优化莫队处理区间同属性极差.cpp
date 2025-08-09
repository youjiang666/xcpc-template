//https://www.lanqiao.cn/problems/4325/learning/

/*
给定n个水晶，具有属性c，若两水晶属性相同可以获得两水晶距离差的积分，
查询m次，查询l到r区间内其可以获得的最大积分
*/

/*
可以离线查询，考虑莫队，先存下问题，处理问题的顺序，再按双指针移动对值增加删除逐个得到问题的答案
可以以块为第一关键字，然后按块的奇偶性将r作为第二关键字升降序切换（奇偶块优化）
或者预处理ord（l,r）后,对应的希尔伯特曲线的秩排序
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=5e4+10,P=1e9+7,rotateDelta[4] = {3, 0, 0, 1};// 用于计算下一层的旋转增量

struct qs{
  int l,r,id;
  ll ord;
}Q[N];

int c[N],sz,ct,ans[N];

set<int>st[N];

ll hilbert(int x, int y, int pow = 16, int rotate = 0) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow)
                ? ((y < hpow) ? 0 : 3)
                : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    int nx = x & (hpow - 1);
    int ny = y & (hpow - 1);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    ll subSquareSize = 1LL << (2 * pow - 2);
    ll res = seg * subSquareSize;
    ll add = hilbert(nx, ny, pow - 1, nrot);

    if (seg == 1 || seg == 2)
        res += add;
    else
        res += (subSquareSize - add - 1);

    return res;
}

void add(int x)
{
  int v = c[x];
  if(st[v].size() >= 2)ct -= *st[v].rbegin() - *st[v].begin();
  st[v].insert(x);
  if(st[v].size() >= 2)ct += *st[v].rbegin() - *st[v].begin();
}

void del(int x)
{
  int v = c[x];
  if(st[v].size() >= 2)ct -= *st[v].rbegin() - *st[v].begin();
  st[v].erase(x);
  if(st[v].size() >= 2)ct += *st[v].rbegin() - *st[v].begin();
}

bool operator < (qs & a,qs & b)
{
  return a.ord < b.ord;
}

void solve()
{
  int n,m;cin >> n;
  sz = sqrt(n);
  for(int i = 1;i <= n;++ i)cin >> c[i];
  cin >> m;
  for(int i = 1;i <= m;++ i)
  {
    Q[i].id = i;
    cin >> Q[i].l >> Q[i].r;
  }
  for (int i = 1; i <= m; i++) {
  Q[i].ord = hilbert(Q[i].l, Q[i].r);
}
  sort(Q + 1,Q + m + 1);
  int l = 1,r = 0;
  for(int i = 1;i <= m;++ i)
  {
    int l1 = Q[i].l,r1 = Q[i].r;
    while(r < r1)add(++ r);
    while(l > l1)add(-- l);
    while(l < l1)del(l ++);
    while(r > r1)del(r --);
    ans[Q[i].id] = ct;
  }
  for(int i = 1;i <= m;++ i)cout << ans[i] << "\n";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}