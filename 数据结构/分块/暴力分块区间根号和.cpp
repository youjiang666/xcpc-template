//https://www.lanqiao.cn/problems/4549/learning/?page=1&first_category_id=1&name=%E5%8C%BA%E9%97%B4%E5%BC%80
/*
给定n大小的数组以及q次操作，操作1为修改l到r的数开根号，2为查询l到r的和,区间修改区间查询
*/

/*
暴力分块，注意各个数组含义，sz设为根号n最快，令第i个元素属于 i / sz这个块
再做操作即可,分成三个部分更新以及查询，注意当fg大于7时元素都为1后续不会再改变（剪枝）
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

ll a[N],sum[N];//sum和fg记录每个块的和以及每个元素开根的次数
int bel[N],L[N],R[N],fg[N];//bel记录每个元素属于的块，l和r记录每个块的左右端点

void sq(int l,int r)
{
  for(int i = l;i <= r;++ i)sum[bel[i]] -= a[i],a[i] = ll(sqrt(a[i])),sum[bel[i]] += a[i];
}

void cg(int l,int r)
{
  if(bel[l] == bel[r])
  {
    sq(l,r);
    return;
  }
  sq(l,R[bel[l]]);
  for(int blo = bel[l] + 1;blo < bel[r];++ blo)
  {
    if(fg[blo] >= 7)continue;//fg大于7就不需要改了，该块所有元素为 1
    ++ fg[blo];
    sq(L[blo],R[blo]);
  }
  sq(L[bel[r]],r);
}

ll query(int l,int r)
{
  ll res = 0;
  if(bel[l] == bel[r])
  {
    for(int i = l;i <= r;++ i)res += a[i];
    return res;
  }
  for(int i = l;i <= R[bel[l]];++ i)res += a[i];
  for(int blo = bel[l] + 1;blo < bel[r];++ blo)res += sum[blo];
  for(int i = L[bel[r]];i <= r;++ i)res += a[i];
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
    if(_ == 1)cg(l,r);
    else cout << query(l,r) << "\n";
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}