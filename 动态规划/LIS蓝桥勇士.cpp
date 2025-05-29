//2049 蓝桥勇士
/*
找到最长上升子序列的长度
*/

/*
使用en数组记录当前最小的序列结尾
在en上二分找到第一个>=a[i]的位置x，当x在len以内就用a[i]替换掉该位置，否则加长en的长度
最后len就是en数组的长也是最后的答案
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

int a[N],en[N],len;

void solve()
{
  int n;cin >> n;
  for(int i = 1;i <= n;++ i)
  {
    cin >> a[i];
    int x = lower_bound(en,en + len + 1,a[i]) - en;
    if(x > len)en[++ len] = a[i];
    else en[x] = a[i];
  }
  cout << len;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}