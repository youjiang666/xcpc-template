//https://atcoder.jp/contests/abc412/tasks/abc412_e lcm序列
/*
求区间l到r的各项的前缀lcm的数的个数
*/

/*
分析性质可知l + 1到r内的个数就是素数幂的个数 + 1
分段筛O(根号 R + (R−L+1) ⋅ log log R)
先使用欧拉筛筛出根号r内的素数（对于所有合数，在他的根号下一定存在质数使之分解）
然后再使用上面的素数来筛掉l到r内的合数（分左右边界步长为其本身）
筛的同时找质数幂（可以被自己除完）
*/

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e7+10,P=1e9+7;

bitset<N>vis,vs;
int cnt,prime[N];

void f(int ed)
{
  for(int i = 2;i <= ed;++ i)
  {
    if(!vis[i])prime[++ cnt] = i;
    for(int j = 1;j <= cnt;++ j)
    {
      if(prime[j] * i > ed)break;
      vis[prime[j] * i] = 1;
      if(!(i % prime[j]))break;
    }
  }
}

void solve()
{
  ll l,r;cin >> l >> r;
  if(l == r)
  {
    cout << 1;
    return;
  }
  int n = r - l + 1;
  f(sqrt(r));
  for(int i = 1;i <= cnt;++ i)
  {
    for(ll j = (l / prime[i] + 1) * prime[i];j <= r;j += prime[i])
    {
      if(vs[j - l])continue;
      vs[j - l] = 1;
      -- n;
      ll op = j;
      while(!(op % prime[i]))op /= prime[i];
      if(op == 1)++ n;
    }
  }
  cout << n;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}