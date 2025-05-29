//P3374 【模板】树状数组 1
/*
单点修改范围查询
*/

/*
维护前缀和即可
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

ll a[N],t[N],n;

ll lowbit(int x){return -x & x;}

void update(int k,int x)
{
  a[k] += x;//更新a数组
  for(int i = k;i <= n;i += lowbit(i))t[i] += x;//更新树状数组中与该点有关的区间和
}

ll getprefix(int x)
{
  ll res = 0;
  for(int i = x;i >= 1;i -= lowbit(i))res += t[i];//返回prefix[x]
  return res;
}

void solve()
{
  int m;cin >> n >> m;
  for(int i = 1;i <= n;++ i)
  {
    int x;cin >> x;
    update(i,x);//更新tree
  }
  while(m --)
  {
    int op,x,y;cin >> op >> x >> y;
    if(op == 1)update(x,y);
    else cout << getprefix(y) - getprefix(x - 1) << endl;
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}