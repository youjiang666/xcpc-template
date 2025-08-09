//https://www.lanqiao.cn/courses/40610/learning/?id=2841123&compatibility=false

/*
给定大小为n的数组，操作一修改a[x] -> y，二为求l ~ r区间中a[p]为第几小
*/

/*
暴力分块，通过二分修改数组，以及求解整块中小于a[p]的个数
注意：
对于残缺的块中我们对l到r进行扫描，用于是对原数组扫描，所以无序，
所以不可以直接break，要全都扫一遍才能统计完全
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

vector<vector<int>>v;
int a[N],siz,bel[N],L[N],R[N];

void cg(int x,int y)
{
  int c = bel[x];
  v[c].erase(lower_bound(v[c].begin(),v[c].end(),a[x]));
  v[c].insert(lower_bound(v[c].begin(),v[c].end(),y),y);
  a[x] = y;
}

int query(int l,int r,int x)
{
  int ans = 0;
  if(bel[l] == bel[r])
  {
    for(int i = l;i <= r;++ i)if(a[i] < x)++ ans;
    return ans + 1;
  }
  for(int i = l;i <= R[bel[l]];++ i)if(a[i] < x)++ ans;
  for(int clo = bel[l] + 1;clo < bel[r];++ clo)ans += lower_bound(v[clo].begin(),v[clo].end(),x) - v[clo].begin();
  for(int i = L[bel[r]];i <= r;++ i)if(a[i] < x)++ ans;
  return ans + 1;
}

void solve()
{
  int n;cin >> n;
  for(int i = 1;i <= n;++ i)cin >> a[i];
  siz = sqrt(n);
  v.resize(n / siz + 1);
  for(int i = 1;i <= n;++ i)
  {
    int _ = i / siz;
    bel[i] = _;
    v[_].push_back(a[i]);
    if(i > 1 && bel[i] != bel[i - 1])R[bel[i - 1]] = i - 1,L[bel[i]] = i;
  }
  L[bel[1]] = 1,R[bel[n]] = n;
  for(int i = bel[1];i <= bel[n];++ i)sort(v[i].begin(),v[i].end());

  int m;cin >> m;
  while(m --)
  {
    int _,x,y;cin >> _ >> x >> y;
    if(_ == 1)cg(x,y);
    else{
      int p;cin >> p;
      cout << query(x,y,a[p]) << " ";
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