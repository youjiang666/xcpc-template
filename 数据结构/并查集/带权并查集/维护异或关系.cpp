//UVA12232 Exclusive-OR
/*
每组给定0 ~ n-1节点，告知q条信息
对于 I p v 指 p节点值为 v
对于 I p q v 指 p节点与 q节点异或为 v
对于 Q k p1 ~ pk 指查询这 k个节点异或和  
*/

/*
对于多个节点的关系维护想到带权并查集，由于当知道一个集合里任意一个值可以推出根的值从而退出该集合所有的值
为了记录这些已知的节点，我们设置一个虚拟源点该点可设置为 n他的值设置成 0这样就可以判断一个值是否已知
细节：对于输入可以使用 getline得到信息字符串再使用 s.c_str()转成 c风格字符串用于sscanf读取得到返回值用于判断I操作的种类
合并的时候要把一直把源点作为根
查询的时候若除去已知的点之外存在有同一个根上的数量为奇数则该查询不可知
输出记得对上题目要求
*/

//血的教训：t 和 root 里一开始的 t 重复了，调了一个小时才发现，改 temp 后就过了。
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=2e4+10,P=1e9+7;

int pre[N],t,dis[N],out;//pre 记录父亲，dis 记录点与根节点值的异或值。
//out是当发现冲突时用于跳出除读入外操作的标记。

int root(int x)
{
  if(pre[x] == x)return x;
  int temp = pre[x];
  pre[x] = root(temp);//先递归更新父亲的 dis 的值。
  dis[x] ^= dis[temp];//再回溯更新 x 的 dis 值可以通过画图得出这个规律。
  return pre[x];
}

int read(string &s,int &a,int &b,int &c)
{
  getline(cin,s);
  return sscanf(s.c_str(),"%d %d %d",&a,&b,&c);//通过 sscanf 的返回值来处理题目的输入
}

void init(int n)
{
  out = 0;
  cout << "Case " << ++ t << ":\n";
  for(int i = 0;i <= n;++ i)pre[i] = i,dis[i] = 0;
}

int merge(int x,int y,int v,int n)
{
  int xr = root(x),yr = root(y);
  if(xr == yr)return (v == (dis[x] ^ dis[y]));
  
  if(xr == n)swap(xr,yr);//设n号节点为虚拟源点，意指已经推断出值的点的集合
  pre[xr] = yr;
  dis[xr] = dis[x] ^ dis[y] ^ v;
  return 1;
}

void query(int k,int n)
{
  int res = 0;
  map<int,int>mp;
  //使用map记录各个非n的根节点的数量当某个根的数为偶数时计算的时候就会被约去，此时这个根的值不会影响结果
  mp.clear();
  for(int i = 1;i <= k;++ i)
  {
    int x;cin >> x;
    if(out)continue;
    int xr = root(x);
    if(xr != n)++ mp[xr];
    res ^= dis[x];
  }

  if(out)return;

  for(auto x : mp)
  {
    if(x.second & 1)//当某个根的数为奇数时那么它的值会影响结果且该根不在n节点上所以我们无从知晓res。
    {
      cout << "I don't know.\n";
      return;
    }
  }
  cout << res << "\n";
}

void solve()
{
  int n,q;cin >> n >> q;
  if(n == 0 && q == 0)return;
  init(n);
  int cnt = 0;//记录有几条声明。
  while(q --)
  {
    char op;cin >> op;
    if(op == 'I')
    {
      ++ cnt;
      string s;
      int a,b,c;
      int _ = read(s,a,b,c);//通过read的返回值确定I的操作类型。
      if(out)continue;
      int fg;

      if(_ == 2) fg = merge(a,n,b,n);
        //因为当一个集合里任意知道一个元素的值可以通过dis推断出根节点的值再由根节点推断出集合内所有元素的值，
        //所以应该将该点集合内所有元素全部合到 n 节点上。
      else fg = merge(a,b,c,n);

      if(!fg)out = cnt;
    }else {
      int k;cin >> k;
      query(k,n);
    }
  }
  
  if(out)cout << "The first " << out << " facts are conflicting.\n";
  cout << "\n";

  solve();
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}
