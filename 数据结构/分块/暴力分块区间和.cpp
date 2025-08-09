//https://www.lanqiao.cn/problems/1133/learning/?page=1&first_category_id=1&name=%E5%8C%BA%E9%97%B4%E4%BF%AE%E6%94%B9
/*
给定n大小的数组以及q次操作，操作1为修改l到r的数加上x，2为查询l到r的和,区间修改区间查询
*/

/*
暴力分块，注意各个数组含义，sz设为根号n最快，令第i个元素属于 i / sz这个块
再做操作即可,分成三个部分更新以及查询
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

ll a[N],sum[N],add[N];//sum和add记录每个块的和以及每个元素一起的增量
int bel[N],L[N],R[N];//bel记录每个元素属于的块，l和r记录每个块的左右端点

void Add(int l,int r,ll x)
{
  if(bel[l] == bel[r])
  {
    for(int i = l;i <= r;++ i)a[i] += x,sum[bel[l]] += x;
    return;
  }
  for(int i = l;i <= R[bel[l]];++ i)a[i] += x,sum[bel[l]] += x;
  for(int blo = bel[l] + 1;blo < bel[r];++ blo)add[blo] += x;//这里枚举的中间的完整的块
  for(int i = L[bel[r]];i <= r;++ i)a[i] += x,sum[bel[r]] += x;
}

ll query(int l,int r)
{
  ll res = 0;
  if(bel[l] == bel[r])
  {
    for(int i = l;i <= r;++ i)res += a[i] + add[bel[i]];
    return res;
  }
  for(int i = l;i <= R[bel[l]];++ i)res += a[i] + add[bel[i]];
  for(int blo = bel[l] + 1;blo < bel[r];++ blo)res += sum[blo] + add[blo] * (R[blo] - L[blo] + 1);
  for(int i = L[bel[r]];i <= r;++ i)res += a[i] + add[bel[i]];
  return res;
}

void solve()
{
  int n,q;cin >> n >> q;
  int sz = sqrt(n);
  for(int i = 1;i <= n;++ i)
  {
    cin >> a[i];
    bel[i] = i / sz;
    sum[bel[i]] += a[i];
    if(i > 1 && bel[i] != bel[i - 1])L[bel[i]] = i,R[bel[i - 1]] = i - 1; 
  }

  L[bel[1]] = 1,R[bel[n]] = n;

  while(q --)
  {
    int _,l,r;cin >> _ >> l >> r;
    if(_ == 1)
    {
      ll x;cin >> x;
      Add(l,r,x); 
    }else
      cout << query(l,r) << "\n";
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}