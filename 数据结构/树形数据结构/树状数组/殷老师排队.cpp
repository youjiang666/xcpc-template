//蓝桥 3620 殷老师排队
/*
给定n个点，每个点有对应的权值，操作一更改某点的权值，二查询某点的一个有关区间和的式子值
*/

/*
涉及在线查询区间和，考虑使用树状数组维护，单点修改区间查询操作
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e5+10,P=1e9+7;

int a[N],t[N],n,m;

int lowbit(int x){return x & - x;}//lowbit操作

void update(int k,int x)
{
  a[k] += x;
  for(int i = k;i <= n;i += lowbit(i))t[i] += x;//更新所有和k位置有关的区间和
}

int getprefix(int x)
{
  int res = 0;
  for(int i = x;i >= 1;i -= lowbit(i))res += t[i];//由不同区间组成prefix[x]
  return res;
}

void solve()
{
  cin >> n >> m;
  for(int i = 1;i <= n;++ i)
  {
    int x;cin >> x;
    update(i,x);
  }

  while(m --)
  {
    int op;cin >> op;
    if(op == 1)
    {
      int x,y;cin >> x >> y;
      update(x,y - a[x]);
    }else {
      int x;cin >> x;
      cout << (2 * x - n) * a[x] + getprefix(n) - 2 * getprefix(x) << endl;
    }
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}