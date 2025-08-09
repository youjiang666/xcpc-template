#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

ll qmi(ll a,ll b,ll p)
{
  ll res = 1;
  while(b)
  {
    if(b & 1)res = res * a % p;
    a = a * a % p;b >>= 1;
  }
  return res;
}

void solve()
{
  int a,b,p;cin >> a >> b >> p;
  cout << a << "^" << b << " mod " << p << "=" << qmi(a,b,p);
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}