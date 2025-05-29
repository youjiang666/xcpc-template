//P3375 【模板】KMP
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

int nx[N];//next数组也叫失配数组

void solve()
{
  string s,p;cin >> s >> p;
  s = ' ' + s;
  p = ' ' + p;
  int n = s.length() - 1,m = p.length() - 1;

  //自我匹配得到失配数组
  for(int i = 2,j = 0;i <= m;++ i)
  {
    while(j && p[i] != p[j+1])j = nx[j];
    if(p[i] == p[j+1])++ j;
    nx[i] = j;
  }

  //利用nx数组加速匹配
  for(int i = 1,j = 0;i <= n;++ i)
  {
    while(j && s[i] != p[j+1])j = nx[j];
    if(s[i] == p[j+1])++ j;
    if(j == m)cout << i - m + 1 << endl;//完全匹配
  }

  for(int i = 1;i <= m;++ i)cout << nx[i] << " ";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}