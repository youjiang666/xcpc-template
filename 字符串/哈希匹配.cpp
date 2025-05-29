//2047.斤斤计较的小Z
#include<bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
const int N=1e6+10,P=1e9+7;

ull h[N],h_ans,ans,base = 7,op = 1;

void solve()
{
  string s,p;cin >> s >> p;
  s = ' ' + s;
  p = ' ' + p;
  int n = s.length() - 1,m = p.length() - 1;
  for(int i = 1;i <= n;++ i)h[i] = h[i - 1] * base + s[i];
  for(int i = 1;i <= m;++ i)h_ans = h_ans * base + p[i],op *= base;//p长度不固定的话预处理一下b[i]=b的i次方

  for(int i = m;i <= n;++ i)if(h[i] - h[i-m]*op == h_ans)++ ans;
  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}