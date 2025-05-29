//1225.最长回文子串
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

int p[N];//p数组里记录的以i为中心的最长回文串的长度
char s[N];

void solve()
{
  cin >> s + 1;
  int n = strlen(s + 1);
  for(int i = ((n << 1) | 1);i >= 1;-- i)s[i] = (i & 1) ? '#' : s[i >> 1];//预处理s应对偶数字符串
  int C = 0,R = 0;
  for(int i = 1;i <= ((n << 1) | 1);++ i)
  {
    p[i] = i < R ? min(R-i,p[2*C-i]) : 1;
    while(s[i+p[i]] == s[i-p[i]])++p[i];
    if(i + p[i] > R)C = i,R = i + p[i];
  }
  cout << *max_element(p+1,p+2*n+1)-1;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}