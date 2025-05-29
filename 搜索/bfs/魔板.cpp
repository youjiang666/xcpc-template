//P2730 [USACO3.2] 魔板 Magic Squares
/*
给定末状态，求初始状态通过a，b，c三种操作到达该状态的最小操作数
*/

/*
和八数码本质一样的最小操作数问题，通过坐标变换之间模拟三种操作进行状态转移即可
*/
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e6+10,P=1e9+7;

string st = "12345678";
map<string,string>mp;

void solve()
{
  char x;
  string en = "";
  for(int i = 0;i < 8;++ i)cin >> x,en += x;

  
  queue<string>q;
  q.push(st);
  while(!q.empty())
  {
    string t = q.front();
    q.pop();

    //A
    string y = t;
    for(int i = 0;i < 4;++ i)swap(y[i],y[8 - i - 1]);
    if(!mp.count(y))q.push(y),mp[y] = mp[t] + 'A';
    //这个位置使用了mp[st],所以自动创建了一个st的建值

    //B
    for(int i = 1;i < 4;++ i)y[i] = t[i - 1];
    for(int i = 4;i < 7;++ i)y[i] = t[i + 1];
    y[0] = t[3],y[7] = t[4];
    if(!mp.count(y))q.push(y),mp[y] = mp[t] + 'B';

    //C
    y = t;
    y[1] = t[6],y[2] = t[1],y[5] = t[2],y[6] = t[5];
    if(!mp.count(y))q.push(y),mp[y] = mp[t] + 'C';

    if(mp.count(en))
    {
      int n = mp[en].length();
      cout << n << endl;
      for(int i = 0;i < n;++ i)
      {
        if(i && i % 60 == 0)cout << endl;
        cout << mp[en][i];
      }
      return;
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