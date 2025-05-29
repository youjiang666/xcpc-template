//P1892 [BalticOI 2003] 团伙
/*
n个节点，m条关系，E 表示 u和 v是敌对关系，F 则是朋友关系
具有如下传递关系：朋友的朋友是朋友，敌人的敌人也是朋友，求有几个不交集合
*/

/*
enemy记录代表性敌人，对于操作 E，将 l和 enemy[r]连接，r和 enemy[l]连接就行
细节：注意若 lr == rr时上面的操作把 rr合并到 enemy[l]上 root(lr)被改变，所以要更新一下 lr
*/

//普通并查集分类处理
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 2e18;
const int N=1e3+10,P=1e9+7;

int pre[N],enemy[N];

int root(int x)
{
  return pre[x] = pre[x] == x ? x : root(pre[x]);
}

void solve()
{
  int n;cin >> n;
  for(int i = 1;i <= n;++ i)pre[i] = i;

  int _;cin >> _;
  while(_ --)
  {
    char op;int p,q;cin >> op >> p >> q;
    int lr = root(p),rr = root(q);
    if(op == 'F')pre[lr] = rr;
    else {
      //分别将p,q与对方的敌人合并
      if(enemy[p])pre[root(rr)] = root(enemy[p]);
      else enemy[p] = q;
      //注意这里如果lr=rr的话lr就被更新了，不等于root(lr)了，所以下面不能直接使用pre[lr] = root(enemy[q])

      if(enemy[q])pre[root(lr)] = root(enemy[q]);
      else enemy[q] = p;
    }
  }

  int ans = 0;
  for(int i = 1;i <= n;++ i)if(pre[i] == i)++ ans;//当节点指向自己那他便是根可以省一个vis
  cout << ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int _ = 1;
  //cin >> _;
  while(_--)solve();
  return 0;
}