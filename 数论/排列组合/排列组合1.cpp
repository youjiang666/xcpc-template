//https://www.lanqiao.cn/problems/20650/learning/

/*
给定n * n的网格，求(1,1) -> (n,n)经过x * y为奇数的坐标个数不少于n - 1的路径方案数
*/

/*
首先我们设x = (n + 1) / 2,y = n / 2，x 为n以内为奇数的坐标数
由题可知当坐标的横坐标以及纵坐标都为奇数时是我们需要经过的点，我们就称之为奇点
我们先分类讨论当n为奇数时，把奇点组成一张新的x * x的网格
再次分类讨论：

当到终点吃了n份荤菜时：此时方案数就可以是在x * x的网格图上从(1,1) -> (x,x)的所有路径（正好经过n个奇点）,一共2 * x - 2次决策选一半向下或向右，一共C(2 * x - 2,x - 1)种方案

当到终点吃了n - 1份荤菜时：我们这样思考，比我们吃n份时少吃一份，可以看作在网格里向右下角走了一步，这样就少经过了一个几点，这种状态可以基于n份荤菜的方案转移过来，也就是在决策（决定向右还是向下）的时候选一步决策向右下走，到达终点路径一共有2 * x - 2次决策，所有一共有(2 * x - 2) * C(2 * x - 2,x - 1)方案

最后荤菜数只有上述两种情况，总方案为(2 * x - 1) * C(2 * x - 2,x - 1)
x带入得到ans = n * C(n - 1,(n - 1) / 2)

当n为偶数时：
我们可以把原图缩小到(n - 1) * (n - 1)此时转化后的奇点图得到的合法状态只有n - 1个，而且不可以少也就是不可以进行向右下走，那么对于这个图方案个数便是其的全部路径也就是C(n - 2,(n - 2) / 2)

将图还原发现在上述情况之外还有个分叉（点(n - 1,n - 1)这里可以向右或向下），所以方案数再乘2
最后ans = 2 * C(n - 2,(n - 2) / 2)

最后得到
n 为奇数：ans = n * C(n - 1,(n - 1) / 2)
n 为偶数：ans = 2 * C(n - 2,(n - 2) / 2)

ps：在n为奇数的讨论里也可以这样思考，做向右下方移动操作一次有（n - 1）种，以及不操作也是一种，一起n种对应的就是上述两种荤菜n - 1个以及n个的情况
*/
#include<bits/stdc++.h>
using namespace std;
#define fr(i,n) for(int i = 1;i <= n;++ i)
using ll = long long;
const ll inf = 2e18;
const int N = 1e5 + 10,P = 998244353;

ll f[N],invf[N];

ll qmi(ll a,ll b)
{
  ll res = 1;
  while(b)
  {
    if(b & 1)res = res * a % P;
    a = a * a % P,b >>= 1;
  }
  return res;
}

void init()
{
  f[0] = 1;
  fr(i,N - 1)f[i] = f[i - 1] * i % P;
  invf[N - 1] = qmi(f[N - 1],P - 2);
  for(int i = N - 2;i >= 0;-- i)invf[i] = invf[i + 1] * (i + 1) % P;
}

ll C(int a,int b)
{
  return f[a] * invf[b] % P * invf[a - b] % P;
}

void solve()
{
  int n;cin >> n;
  if(n & 1)cout << n * C(n - 1,(n - 1) >> 1) % P << "\n";
  else cout << (((n - 1) * C(n - 2,(n - 2) >> 1) % P) << 1) % P << "\n";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  init();
  cin >> _;
  while(_--)solve();
  return 0;
}