//https://www.luogu.com.cn/problem/P1714

/*
给定长度n的数组，求长度为 m以内的非空最大子段和
*/

/*
以某个位置结尾的子段和为prefix[i] - prefix[mi]
要使得该值最大那便最下化prefix[mi],那么对于长度小于 m这个限制
我们只需要单调队列维护大小为 m的窗口最小值即可，然后取 prefix[i] - mi[i - 1]
因为是非空的所有取不含 i这个位置
*/

#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e7 + 10,P = 1e9 + 7;

ll a[N],prefix[N],mi[N],f[N],ans = -P;

void solve()
{
  int n,m;cin >> n >> m;
  fr(i,n)cin >> a[i],prefix[i] = prefix[i - 1] + a[i];
  int h = 1,t = 0;
  for(int i = 0;i <= n;++ i)
  {
    while(h <= t && prefix[f[t]] >= prefix[i])-- t;
    f[++ t] = i;
    if(f[h] <= i - m)++ h;
    mi[i] = prefix[f[h]];
  }
  fr(i,n)ans = max(ans,prefix[i] - mi[i - 1]);
  cout << ans; 
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}