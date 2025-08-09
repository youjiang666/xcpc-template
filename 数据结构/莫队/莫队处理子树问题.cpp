//https://www.lanqiao.cn/problems/3504/learning/?page=1&first_category_id=1&name=%E9%A2%9C%E8%89%B2%E5%B9%B3%E8%A1%A1%E6%A0%91

/*
给定一颗节点数为n的树，节点具有属性值c，求子树中各颜色数量相同的树的个数
*/

/*
对于一颗有向树，以每个节点做根得到n个子树，求出dfn以及sz，再枚举各点，
即可知道连续的区间为一颗子树，对区间使用莫队，排序后通过双指针小幅度摆动
求得该子树是否满足条件（即set中最小值等于最大值）
注意：
set要设为multiset
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=2e5+10,P=1e9+7,rotateDelta[4] = {3, 0, 0, 1};

struct Q{
  int l,r;
  ll ord;
}q[N];

vector<int>vr[N];
multiset<int>st;
int c[N],fa[N],dfn[N],o,sz[N],siz,ct[N];

ll hilbert(int x, int y, int pow = 18, int rotate = 0)
{
  if (pow == 0) return 0;
  int hpow = 1 << (pow - 1);
  int seg = (x < hpow)? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);

  seg = (seg + rotate) & 3;
  int nx = x & (hpow - 1);
  int ny = y & (hpow - 1);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  ll subSquareSize = 1LL << (2 * pow - 2);
  ll res = seg * subSquareSize;
  ll add = hilbert(nx, ny, pow - 1, nrot);

  if (seg == 1 || seg == 2)res += add;
  else res += (subSquareSize - add - 1);

  return res;
}

void dfs(int x)
{
  dfn[++ o] = x;
  sz[x] = 1;
  for(auto y : vr[x])
  {
    dfs(y);
    sz[x] += sz[y];
  }
}

bool operator <(Q &a,Q &b)
{
  return a.ord < b.ord;
}

void add(int x)
{
  int v = c[dfn[x]];
  if(ct[v])st.erase(st.find(ct[v]));
  ++ ct[v];
  st.insert(ct[v]);
}

void del(int x)
{
  int v = c[dfn[x]];
  st.erase(st.find(ct[v]));
  -- ct[v];
  if(ct[v])st.insert(ct[v]);
}

void solve()
{
  int n;cin >> n;
  siz = sqrt(n);
  for(int i = 1;i <= n;++ i)
    cin >> c[i] >> fa[i],vr[fa[i]].push_back(i);

  dfs(1);
  
  for(int i = 1;i <= n;++ i)
    q[i].l = i,q[i].r = i + sz[dfn[i]] - 1,q[i].ord = hilbert(q[i].l,q[i].r);

  sort(q + 1,q + n + 1);

  int l = 1,r = 0,ans = 0;
  for(int i = 1;i <= n;++ i)
  {
    int ll = q[i].l,rr = q[i].r;
    while(rr > r)add(++ r);
    while(ll < l)add(-- l);
    while(rr < r)del(r --);
    while(ll > l)del(l ++);
    ans += (*st.rbegin() == *(st.begin()));
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