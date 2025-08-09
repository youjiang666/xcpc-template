//https://www.lanqiao.cn/problems/19776/learning/?page=1&first_category_id=1&name=%E5%88%86%E5%9D%97
/*
给定n大小的数组以及q次操作，操作1为修改l到r的数加上x，2为查询l到r中小于x的数的个数
*/

/*
暴力分块，注意各个数组含义，sz设为根号n最快，令第i个元素属于 i / sz这个块
再做操作即可，分成三个部分更新以及查询
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e5+10,P=1e9+7;

ll a[N],add[N];
int bel[N],L[N],R[N];
vector<ll>v[N];

void resort(int x)
{
  v[x].clear();
  for(int i = L[x];i <= R[x];++ i)v[x].push_back(a[i]);
  stable_sort(v[x].begin(),v[x].end());
}

void Add(int l,int r,int x)
{
  if(bel[l] == bel[r])
  {
    for(int i = l;i <= r;++ i)a[i] += x;
    resort(bel[l]);
    return;
  }
  for(int i = l;i <= R[bel[l]];++ i)a[i] += x;
  resort(bel[l]);
  for(int blo = bel[l] + 1;blo < bel[r];++ blo)add[blo] += x;//这里枚举的中间的完整的块
  for(int i = L[bel[r]];i <= r;++ i)a[i] += x;
  resort(bel[r]);
}

ll query(int l,int r,int x)
{
  ll res = 0;
  if(bel[l] == bel[r])
  {
    for(int i = l;i <= r;++ i)
      if(a[i] < x - add[bel[i]])++ res;
    return res;
  }
  for(int i = l;i <= R[bel[l]];++ i)if(a[i] < x - add[bel[i]])++ res;
  for(int blo = bel[l] + 1;blo < bel[r];++ blo)res += lower_bound(v[blo].begin(),v[blo].end(),x - add[blo]) - v[blo].begin();
  for(int i = L[bel[r]];i <= r;++ i)if(a[i] < x - add[bel[i]])++ res;
  return res;
}

void solve()
{
  int n,q;cin >> n;
  int sz = sqrt(n);
  for(int i = 1;i <= n;++ i)
  {
    cin >> a[i];
    bel[i] = i / sz;
    if(i > 1 && bel[i] != bel[i - 1])L[bel[i]] = i,R[bel[i - 1]] = i - 1; 
  }

  L[bel[1]] = 1,R[bel[n]] = n;
  for(int blo = bel[1];blo <= bel[n];++ blo)resort(blo);

  cin >> q;
  while(q --)
  {
    int _,l,r,x;cin >> _ >> l >> r >> x;
    if(_ == 1)
      Add(l,r,x);
    else
      cout << query(l,r,x) << "\n";
  }
}

int main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
int _ = 1;
//cin >> _;
while(_--)solve();
return 0;
}