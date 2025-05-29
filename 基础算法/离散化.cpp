/*
将无序数据映射到可以快速通过下标访问
*/

/*
先将数据加入容器，排序去重后，
利用getidx里在容器中二分可以访问到对应数据的下标
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>v;
int getidx(int x)
{
  return lower_bound(v.begin(),v.end(),x)-v.begin();
}
int main(){
  int n;cin >> n;
  int a[n + 1];
  for(int i = 1;i <= n;++ i)cin >> a[i],v.push_back(a[i]);
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  for(auto i : v)cout << i << " ";
  cout << endl;
  int x;cin >> x;
  cout << getidx(x);
}