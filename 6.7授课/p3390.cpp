#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e2+10,P=1e9+7;

struct mtx{
  ll c[N][N] = {};
}A,res;

ll n,k;

mtx operator*(mtx & x,mtx & y)
{
  mtx t;
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= n;++ j)
      for(int k = 1;k <= n;++ k)
        t.c[i][j] = (t.c[i][j] + x.c[i][k] * y.c[k][j]) % P;
  return t;
}

void qmi(ll b)
{
  for(int i = 1;i <= n;++ i)res.c[i][i] = 1;
  while(b)
  {
    if(b & 1)res = res * A;
    A = A * A;b >>= 1;
  }
}

void solve()
{
  cin >> n >> k;
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= n;++ j)cin >> A.c[i][j];
  qmi(k);
  for(int i = 1;i <= n;++ i)
    for(int j = 1;j <= n;++ j)cout << res.c[i][j] << " \n"[j == n];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}