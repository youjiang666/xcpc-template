//P8306	【模板】字典树
/*
查询有多少以s为前缀
*/

/*
建树然后记录pass，查询的时候让s走到底再返回pass即可
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=3e6+10,P=1e9+7;

int son[N][63],tot = 1,pass[N];//动态开点，还可以加上一个en数字记录结尾个数

//映射一下字母到数字尽量减少空间的浪费
int f(char x)
{
  if('A' <= x && x <= 'Z')return (x - 'A' + 26);
  if('a' <= x && x <= 'z')return (x - 'a');
  return (x - '0' + 52);
}

void insert(string s)
{
  int o = 1;
  for(int i = 0;s[i];++ i)
  {
    int x = f(s[i]);
    if(!son[o][x])son[o][x] = ++ tot;
    o = son[o][x];
    ++ pass[o];
  }
  //++en[o];en数组加在这里记录结尾
}

int query(string s)
{
  int o = 1;
  for(int i = 0;s[i];++ i)
  {
    int x = f(s[i]);
    if(!son[o][x])return 0;
    o = son[o][x];
  }
  return pass[o];
}

//清空树
void clear()
{
  for(int i = 1;i <= tot;++ i)
  {
    pass[i] = 0;
    for(int j = 0;j <= 61;++ j)son[i][j] = 0;
  }
  tot = 1;
  return;
}

void solve()
{
  int n,q;cin >> n >> q;
  while(n --)
  {
    string s;cin >> s;
    insert(s);
  }
  while(q --)
  {
    string s;cin >> s;
    cout << query(s) << endl;
  }
  clear();
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  cin >> _;
  while(_--)solve();
  return 0;
}