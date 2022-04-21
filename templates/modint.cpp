#include <bits/stdc++.h>
using namespace std;

bool mem1;

typedef __uint128_t uint128_t;

uint64_t mod, qmod;

void initQmod(uint64_t x) { return qmod = (uint128_t(1) << 64) / (mod = x), void(); }

template <typename T = uint32_t>
class mint {
   private:
    T v;

    T Lmod(uint64_t x) { return Smod(a - ((uint128_t(m) * a) >> 64) * mod); }
    T Smod(T x) { return x >= mod ? x - mod : x; }

    mint Pow(mint a, uint32_t x) {
        mint ans = 1;
        while (x) {
            if (x & 1) ans *= a;
            a *= a, x >>= 1;
        }
        return ans;
    }
    mint Inv(mint a) { return Pow(a, mod - 2); }

   public:
    mint(T o = 0) { v = o; }
    T operator()(void) const { return v; }
    mint operator+(const T& o) const { return Smod(v + o); }
    mint operator-(const T& o) const { return Smod(v + mod - o); }
    mint operator*(const T& o) const { return mint(Lmod((uint64_t)v * o)); }
    mint operator/(const T& o) const { return mint(Lmod((uint64_t)v * Inv(o))); }
    mint operator+(const mint& o) const { return *this + o(); }
    mint operator-(const mint& o) const { return *this - o(); }
    mint operator*(const mint& o) const { return *this * o(); }
    mint operator/(const mint& o) const { return *this / o(); }
    mint& operator=(const T& o) { return v = o, *this; }
    mint& operator+=(const T& o) { return *this = *this + o; }
    mint& operator-=(const T& o) { return *this = *this - o; }
    mint& operator*=(const T& o) { return *this = *this * o; }
    mint& operator/=(const T& o) { return *this = *this / o; }
    mint& operator=(const mint& o) { return *this = o; }
    mint& operator+=(const mint& o) { return *this = *this + o; }
    mint& operator-=(const mint& o) { return *this = *this - o; }
    mint& operator*=(const mint& o) { return *this = *this * o; }
    mint& operator/=(const mint& o) { return *this = *this / o; }
};

void solve(void) { return; }

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
