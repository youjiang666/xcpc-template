//NC288979	智乃的“凑数”题
/*
对n个数进行操作，进行m次查询输出行和和列和相乘为x的方案
*/

/*
dfs先把该数加入找下一层，再弹出向下转移，用元组记录标记当前同一状态防止反复转移
*/
//有时候可以把表打出来来找寻合法的剪枝方法
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

struct {int o,p,q;}back;

map<tuple<int,int,int>,bool>vin;
vector<int>v1,v2;
int a[N],flag = 0,n,x;
bitset<N>vis;

void dfs(int u,int v,int op)
{
  if(vin[make_tuple(u,v,op)])return;//记录重复状态
  vin[make_tuple(u,v,op)] = 1;
  if(u * v > x || flag || u > x || v > x)return;//去除不合法状态
  if(u * v == x)
  {
    flag = 1;//标记找到了，方便其他函数退出
    cout << "Yes" << endl;
    cout << v1.size() << " " << v2.size() << endl;
    for(auto i : v1)cout << i << " ";
    cout << endl;
    for(auto i : v2)cout << i << " ";
    cout << endl;
    return;
  }
  if(op == n + 1)return;//越界
  //三种操作
  if((u + a[op]) * v <= x)
  {
    v1.push_back(a[op]);
    dfs(u + a[op],v,op + 1);//回溯
    v1.pop_back();
  }
  
  if((v + a[op]) * u <= x)
  {
    v2.push_back(a[op]);
    dfs(u,v + a[op],op + 1);
    v2.pop_back();
  }
  
  dfs(u,v,op + 1);
  return;
}

void solve()
{
  int m;cin >> n >> m;
  for(int i = 1;i <= n;++ i)cin >> a[i];
  while(m --)
  {
    cin >> x;
    if(vis[x])
    {
      cout << "No" << endl;
      continue;
    }
    vin.clear();
    v1.clear();
    v2.clear();
    flag = 0;
    dfs(0,0,1);//行和，列和，步数坐标
    if(!flag)cout << "No" << endl,vis[x] = 1;
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}