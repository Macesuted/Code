#include <bits/stdc++.h>
using namespace std;

bool mem1;

int readInt(void) {
    int x = 0, f = +1;
    char c = getchar();
    while (!('0' <= c && c <= '9')) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
void write(int v) {
    if (v < 0) putchar('-'), v = -v;
    if (v > 9) write(v / 10);
    putchar((v % 10) ^ 48);
    return;
}

#define maxn 35
#define maxm 115
#define mod 998244353

long long v[maxm], binom[maxn][maxn];
long long f[maxm][maxn][maxn][maxn];

inline long long Mod(long long a) { return a >= mod ? a - mod : a; }
inline long long Add(long long &a, long long b) { return a = Mod(a + b); }
int popcount(int a) { return a == 0 ? 0 : popcount(a >> 1) + (a & 1); }

void solve(void) {
    for (int i = 0; i < maxn; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) binom[i][j] = Mod(binom[i - 1][j - 1] + binom[i - 1][j]);
    }
    int n = readInt(), m = readInt(), K = readInt();
    for (int i = 0; i <= m; i++) v[i] = readInt();
    for (int i = 0, po = 1; i <= n; i++, po = po * v[0] % mod) f[0][i][i & 1][i >> 1] = po * binom[n][i] % mod;
    for (int i = 0; i < m; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= K; k++)
                for (int l = 0; l < maxn; l++) {
                    if (!f[i][j][k][l]) continue;
                    for (int x = 0, po = 1; j + x <= n; x++, po = po * v[i + 1] % mod) {
                        long long nl = l + x;
                        if (k + (nl & 1) > K) continue;
                        Add(f[i + 1][j + x][k + (nl & 1)][nl >> 1], f[i][j][k][l] * binom[n - j][x] % mod * po % mod);
                    }
                }
    long long ans = 0;
    for (int k = 0; k <= K; k++)
        for (int l = 0; l < maxn; l++)
            if (k + popcount(l) <= K)
                Add(ans, f[m][n][k][l]);
    write(ans), putchar('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("sequence.in", "r", stdin), freopen("sequence.out", "w", stdout);
#endif
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}