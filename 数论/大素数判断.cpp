//P4718 【模板】Pollard-Rho
/*
判断一个大数是否是素数，不是则输入最大的质因子
*/

/*
通过Miller-Rabin测试是否为素数，不是则通过Pollard-Rho去找质因子
记录后找到最大的输出即可
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;

// 读取一个 64 位整数，支持负数
ll read_ll() {
    ll x = 0;
    int f = 1;
    char c = getchar();
    // 跳过非数字字符，处理负号
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    // 解析数字字符
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x * f;
}

// 快速幂取模：计算 a^b % mod，时间 O(log b)
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b) {
        if (b & 1)
            res = (i128)res * a % mod;
        a = (i128)a * a % mod;
        b >>= 1;
    }
    return res;
}

// Miller-Rabin 素性测试：判断 n 是否为素数
bool isPrime(ll n) {
    // 小于 2 或偶数直接判断
    if (n < 2) return false;
    for (ll p : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n % p == 0)
            return n == p;
    }
    // 写 n-1 = d * 2^s
    ll d = n - 1, s = 0;
    while (!(d & 1)) {
        d >>= 1;
        ++s;
    }
    // 选定一组确定性底数，提高测试可靠性
    for (ll a : {2,325,9375,28178,450775,9780504,1795265022}) {
        if (a % n == 0) continue;
        ll x = qpow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        // 检查 x^(2^r) 是否能变为 n-1
        for (int r = 1; r < s; ++r) {
            x = (i128)x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        // 若所有循环都没触达 n-1，则为合数
        if (composite) return false;
    }
    return true;
}

// 全局随机数引擎，用于 Pollard Rho 随机化
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Pollard Rho 算法：找到 n 的一个非平凡因子
ll pollard(ll n) {
    if (n % 2 == 0) return 2;
    // 随机常数 c
    ll c = uniform_int_distribution<ll>(1, n - 1)(rng);
    // 初始值 x, y
    ll x = uniform_int_distribution<ll>(0, n - 1)(rng);
    ll y = x;
    ll d = 1;
    // f(v) = v^2 + c mod n
    auto f = [&](ll v) { return ((i128)v * v + c) % n; };
    // 循环直到找到非平凡因子
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = __gcd(llabs(x - y), n);
    }
    // 若失败（d == n），重试
    return d == n ? pollard(n) : d;
}

// 分解 n 得到所有素因子，存入 res 向量
void factor(ll n, vector<ll>& res) {
    if (n == 1) return;
    // 若 n 是素数，直接加入
    if (isPrime(n)) {
        res.push_back(n);
    } else {
        // 否则用 Pollard Rho 找到因子 d
        ll d = pollard(n);
        factor(d, res);
        factor(n / d, res);
    }
}

// 主求解函数，处理多组测试
void solve() {
    int T = (int)read_ll();  // 读入测试组数
    while (T--) {
        ll n = read_ll();      // 读入待测数
        if (isPrime(n)) {
            puts("Prime");   // 若是素数则输出 Prime
        } else {
            vector<ll> fac;
            factor(n, fac);    // 分解质因子
            ll mx = 0;
            // 找到最大的质因子
            for (ll v : fac)
                mx = max(mx, v);
            printf("%lld\n", mx);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();  // 调用主函数
    return 0;
}
