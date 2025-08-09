//https://codeforces.com/contest/2128/problem/E1

/*
给定大小为n的数组，求长度至少为k的子数组的最大中位数
*/

/*
确定答案具有单调性，直接二分答案，主要在于check的设计上
当a[i] < x赋值-1，当a[i] >= x时赋值1，再做一次前缀和，问题就转变为了
判断某个长度大于k的区间的和大于等于0(显然满足这样条件的区间可以使得该区间中值至少为 x)
要使得区间和最大便等于后缀最大值减掉前缀最小值预处理后逐个更新即可
注意：
信息之间需要匹配上，例如在枚举了l时更新了l - 1的前缀mi那么r = l + k - 1，
但当枚举l时mi被l更新了，那么r = l + k
注意信息的匹配
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

int a[N],pre[N],mx[N],n,k,L,R;

bool check(int x)
{
  for(int i = 1;i <= n;++ i)pre[i] = (a[i] < x ? -1 : 1) + pre[i - 1];
  mx[n + 1] = n;
  for(int i = n;i >= k;-- i)
  {
    if(pre[i] < pre[mx[i + 1]])mx[i] = mx[i + 1];
    else mx[i] = i;
  }
  int mi = 0;
  for(int l = 0;l <= n - k;++ l)
  {
    mi = min(mi,pre[l]);
    if(pre[mx[l + k]] >= mi)
    {
      L = l,R = mx[l + k];
      return 1;
    }
  }
  return 0;
}

void solve()
{
  cin >> n >> k;
  for(int i = 1;i <= n;++ i)cin >> a[i];

  int l = 0,r = n + 1;
  while(l + 1 != r)
  {
    int mid = (l + r) >> 1;
    if(check(mid))l = mid;
    else r = mid;
  }
  cout << l << " " << L + 1 << " " << R << "\n";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  cin >> _;
  while(_--)solve();
  return 0;
}