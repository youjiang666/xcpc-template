//蓝桥 1142 百亿富翁
/*
给定n个数，求每个数的左侧第一个比它大的，右侧第一个比它大的编号，不存在则为-1
*/

/*
分从两侧跑两次单调栈，每次记录要压栈的左侧的编号，栈底放-1
*/
#include<bits/stdc++.h>
using namespace std;
using ll =long long;
const int N=7e5+10,P=1e9+7;

int a[N],l[N],R[N],stk[N] = {-1},top;//栈底存入-1

void solve()
{
  int n;cin >> n;
  for(int i = 1;i <= n;++ i)cin >> a[i];
  for(int i = 1;i <= n;++ i)
  {
    while(a[stk[top]] <= a[i] && top)-- top;//寻找更优直到栈底
    l[i] = stk[top];//记录最优
    stk[++ top] = i;//压栈
  }
  for(int j = 1;j <= n;++ j)cout << l[j] << " ";
  cout << endl;
  top = 0;//清空栈
  for(int i = n;i >= 1;-- i)
  {
    while(a[stk[top]] <= a[i] && top)-- top;
    R[i] = stk[top];
    stk[++ top] = i;
  }
  for(int j = 1;j <= n;++ j)cout << R[j] << " ";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}