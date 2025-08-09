#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

int lo(ll x)
{
  int ans = 0;
  while(1 << ans <= x >> 1)++ ans;
  return ans;
}

void solve()
{
  int n = 2e5;

  cout << bitset<32>(n);
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}