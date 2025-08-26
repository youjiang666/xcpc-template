//https://www.luogu.com.cn/problem/P1880

/*
给定排成一圈的 n堆石子，质量为 w[i]，一次只能合并相邻的石堆
合并代价为两堆的和，求最小以及最大操作代价
*/

/*
之间把它拉直成 2n的一排，发现可以等价的找出所有状态
正常区间 dp转移然后找长度为 n的最大最小代价即可

可以优化
对于dpmx来说，越长的区间值越大，那么对于dpmx[i][j] = max(dpmx[i + 1][j],dpmx[i][j - 1]) + s[j] - s[i - 1]
区间 i ~ j内的最大操作在长度为 j - i区间内里产生

对于dpmi来说，最佳分割点就是在 p[i][j - 1] ~ p[i + 1][j]里（四边形不等式优化区间枚举）
所有枚举 k的时候只需要枚举这个范围即可，并且每次更新记录区间的最佳分割点
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 2e2 + 10,P = 1e9 + 7;

ll prefix[N],dpmx[N][N],dpmi[N][N],a[N],mi = inf,mx,p[N][N];

void solve()
{
  int n;cin >> n;
  fr(i,n)cin >> a[i],prefix[i] = prefix[i - 1] + a[i],p[i][i] = i,p[i + n][i + n] = i + n;
  fr(i,n)prefix[i + n] = prefix[i + n - 1] + a[i];

  for(int i = 2;i <= n;++ i)
    fr(l,(n << 1) - i + 1)
    {
      int r = l + i - 1;
      dpmi[l][r] = inf;
      /*
      for(int k = l;k < r;++ k)
      {
        dpmi[l][r] = min(dpmi[l][r],dpmi[l][k] + dpmi[k + 1][r] + prefix[r] - prefix[l - 1]);
        dpmx[l][r] = max(dpmx[l][r],dpmx[l][k] + dpmx[k + 1][r] + prefix[r] - prefix[l - 1]);
      }
      */
      for(int k = p[l][r - 1];k <= p[l + 1][r];++ k)
      {
        ll op = dpmi[l][k] + dpmi[k + 1][r] + prefix[r] - prefix[l - 1];
        if(op <= dpmi[l][r])dpmi[l][r] = op,p[l][r] = k;
      }
      dpmx[l][r] = max(dpmx[l][r - 1],dpmx[l + 1][r]) + prefix[r] - prefix[l - 1];
    }
  
  fr(i,n)
  {
    mi = min(mi,dpmi[i][i + n - 1]);
    mx = max(mx,dpmx[i][i + n - 1]);
  }
  cout << mi << "\n" << mx;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}