#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e2+10,P=1e9+7;

struct mtx{
  ll c[N][N] = {};
}A,res;

mtx operator*(mtx & x,mtx & y)
{
  mtx t;
  for(int i = 1;i <= 2;++ i)
    for(int j = 1;j <= 2;++ j)
      for(int k = 1;k <= 2;++ k)
        t.c[i][j] = (t.c[i][j] + x.c[i][k] * y.c[k][j] % P) % P;
  return t;
}

void qmi(ll b)
{
  res.c[1][1] = res.c[1][2] = 1;
  A.c[1][1] = A.c[1][2] = A.c[2][1] = 1;
  while(b)
  {
    if(b & 1)res = res * A;
    A = A * A;b >>= 1;
  }
}

void solve()
{
  ll n;cin >> n;
  if(n <= 2)
  {
    cout << 1;
    return;
  }
  qmi(n - 2);
  cout << res.c[1][1];
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}