//P3368 【模板】树状数组 2
/*
区间修改单点查询
*/

/*
想到可以使用树状数组维护差分数组然后还原得到原数组来实现要求
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

ll a[N],t[N],n;

ll lowbit(int x){return -x & x;}

void update(int k,int x)
{
  for(int i = k;i <= n;i += lowbit(i))t[i] += x;
}

ll getprefix(int x)
{
  ll res = 0;
  for(int i = x;i >= 1;i -= lowbit(i))res += t[i];
  return res;
}

void solve()
{
  int m;cin >> n >> m;
  for(int i = 1;i <= n;++ i)
  {
    cin >> a[i];
    update(i,a[i] - a[i - 1]);//插入差分数组到树状数组
  }
  while(m --)
  {
    int op;cin >> op;
    if(op == 1)
    {
      int x,y,k;cin >> x >> y >> k;
      update(x,k);
      update(y + 1,-k);//修改差分数组以及和该位置有关的前缀和
    }else{
      int x;cin >> x;
      cout << getprefix(x) << endl;//返回所维护的差分数组的前缀和
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