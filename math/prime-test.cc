#include <iostream>
#include <cstdlib>
using namespace std;
typedef long long LL;
LL minfactor, p[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}
LL qmult(LL a, LL b, LL mod) {  // 快速乘模
    LL sum = 0;
    while (b) {
        if (b & 1) {
            sum += a;
            if (sum >= mod) sum -= mod;  // 此处无需用%，%运算比减法慢很多
        }
        b >>= 1, a <<= 1;
        if (a >= mod) a -= mod;
    }
    return sum;
}
LL qpow(LL a, LL b, LL mod) {  // 快速幂模
    LL res = 1;
    while (b) {
        if (b & 1) res = qmult(res, a, mod);
        b >>= 1;
        a = qmult(a, a, mod);
    }
    return res;
}
bool prime_test(LL n, LL a) {  // 对整数n，底数a进行测试，返回true表示通过测试
    LL p = qpow(a, n - 1, n);
    if (p != 1) return false;
    else {  // 二次探测
        LL s = n - 1;
        while (!(s & 1) && p == 1) {
            s >>= 1;
            p = qpow(a, s, n);
        }
        if (p == 1 || p == n - 1) return true;
        else return false;
    }
}
bool Miller_Rabin(LL n) {  // 对整数n进行Miller_Rabin素数测试，返回true表示通过测试
    if (n <= 29) {    // if这一块其实可以不用
        for (int i = 0; i < 10; i++) {
            if (n == p[i]) return true;
        }
        return false;
    }
    for (int i = 0; i < 10; i++) {  // 利用前10个素数作为底数测试的正确率已经非常高
        if (gcd(n, p[i]) == 1 && !prime_test(n, p[i])) return false;
    }
    return true;
}
LL randf(LL x, LL n, LL c) {  // 满足要求的产生伪随机数函数
    return (qmult(x, x, n) + c) % n;
}
LL pollard_rho(LL n, LL c) {  // 查找n的因数，c为上面函数要用的随机数，c也可自己指定（但要有变化）
    LL x = rand() % n, y = x, i = 1, k = 2, p;  // 随机生成随机数的初始值，也可自己指定
    while (true) {
        i++;
        x = randf(x, n, c);
        p = gcd(y - x + n, n);
        if (p > 1 && p < n) return p;
        if (y == x) return n;   // 判圈，返回n表示查找失败，要更新随机种子重新查找
        if (i == k) { y = x; k <<= 1; }  // 更新范围和记录的数
    }
}
void find_factor(LL n) {  // 查找所有因数
    if (Miller_Rabin(n)) {
        minfactor = min(minfactor, n);
        return ;
    }
    LL p = n;
    while (p == n) p = pollard_rho(n, rand() % (n - 1) + 1);  // 查找失败则更新随机种子重新查找，直到找到因子
    find_factor(p);     // 递归查找更小因子
    find_factor(n / p);
}

int main() {
    int t; cin >> t;
    while (t--) {
        LL N; cin >> N;
        if (Miller_Rabin(N)) cout << "Prime" << endl;
        else {
            minfactor = N;
            find_factor(N);
            cout << minfactor << endl;
        }
    }
    return 0;
}