//求 01背包最优解的方案数

/*
当某个状态由另一个状态转移过来时
dp[j - w] + v > dp[j],此时直接继承旧的状态的方案数
dp[j - w] + v == dp[j],此时加上旧状态的方案数
注意初始化 0 ~ m的方案数为 1
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e6 + 10,P = 1e9 + 7;

ll dp[N],c[N];

void solve()
{
  int n,m;cin >> n >> m;
  for(int i = 0;i <= m;++ i)c[i] = 1;
  fr(i,n)
  {
    int w,v;cin >> w >> v;
    for(int j = m;j >= w;-- j)
      if(dp[j - w] + v > dp[j])
      {
        dp[j] = dp[j - w] + v;
        c[j] = c[j - w];
      }else if(dp[j - w] + v == dp[j])
        c[j] = (c[j - w] + c[j]) % P;
  }
  cout << c[m];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}
/*
5 5
5 8 
2 4 
3 4
5 7
4 8

3
*/