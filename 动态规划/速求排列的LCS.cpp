//https://www.cnblogs.com/dx123/p/17301417.html

/*
求解排列的lcs长度
*/

/*
根据排列的性质直接将问题转化成求b中数字在a中位置数组的lis，采用二分优化
*/

#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e6 + 10,P = 1e9 + 7;

int ans[N],op[N],o;

void solve()
{
  int n;cin >> n;
  fr(i,n)
  {
    int x;cin >> x;
    op[x] = i;
  }
  fr(i,n)
  {
    int x;cin >> x;
    if(op[x] > ans[o])ans[++ o] = op[x];
    else ans[lower_bound(ans,ans + o,op[x]) - ans] = op[x];
  }
  cout << o;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}