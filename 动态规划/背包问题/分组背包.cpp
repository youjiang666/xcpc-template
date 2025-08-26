//https://www.luogu.com.cn/problem/P1757

/*
给定 m容量以及 n个物品,给物品分组，每组物品只能选其中一个
求最大价值
*/

/*
分组背包，其实就是由旧状态然后枚举每组里的物品去更新出新状态
对所有枚举出来的新状态取最大值就可以了，这样就可以保证组内不冲突

具体实现直接先分组，组内先枚举容量的每个状态，再枚举物品去由旧状态更新
新状态取所有新状态的最大值，注意由后往前枚举容量，不然状态会混导致重复
*/

#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e3 + 10,P = 1e9 + 7;

int dp[N],s[N],a[N][N],w[N],v[N];

void solve()
{
  int m,n;cin >> m >> n;
  fr(i,n)
  {
    int op;cin >> w[i] >> v[i] >> op;
    a[op][++ s[op]] = i;
  }

  fr(i,N - 1)
    for(int j = m;j > 0;-- j)
      fr(k,s[i])
        if(j >= w[a[i][k]])dp[j] = max(dp[j],dp[j - w[a[i][k]]] + v[a[i][k]]);
  
  cout << dp[m];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}