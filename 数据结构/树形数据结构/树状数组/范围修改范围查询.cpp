//P3372 【模板】线段树 1
/*
操作一给x到y区间内所有数加上k，二查询区间的和
*/
//用树状数组实现范围修改范围查询
//对差分数组求和再求和便为原数组的求和可以推出sum = k * (d1 + d2 + ··· + dk) - ((1 - 1) * di + ··· + (k - 1) * dk)
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=1e6+10,P=1e9+7;

ll a[N],t1[N],t2[N],n;//t1记录差分数组，t2记录(i - 1) * di数组

ll lowbit(int x){return -x & x;}

void update(int x,ll k,ll t[])
{
  for(int i = x;i <= n;i += lowbit(i))t[i] += k;
}

ll getprefix(int x,ll t[])
{
  ll res = 0;
  for(int i = x;i >= 1;i -= lowbit(i))res += t[i];
  return res;
}

void add(int x,int y,ll k)
{
    update(x,k,t1);
    update(y + 1,-k,t1);
    update(x,(x - 1) * k,t2);
    update(y + 1,- y * k,t2);//维护两个差分数组
}

void solve()
{
  int m;cin >> n >> m;
  for(int i = 1;i <= n;++ i)
  {
    cin >> a[i];
    add(i,i,a[i]);
  }
  while(m --)
  {
    int op;cin >> op;
    if(op == 1)
    {
      ll x,y,k;cin >> x >> y >> k;
      add(x,y,k);
    }else{
      ll x,y;cin >> x >> y;
      cout << getprefix(y,t1) * y - getprefix(y,t2) - getprefix(x - 1,t1) * (x - 1) + getprefix(x - 1,t2) << endl;
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