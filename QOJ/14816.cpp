#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 5005
#define mod 998244353

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }
int64_t Add(int64_t &x, int64_t y) { return x = Mod(x + y); }

class SumStruct {
   private:
    int64_t g[maxn], h[maxn];

   public:
    void init(int64_t f[]) {
        g[0] = f[0];
        for (int i = 1; i < maxn; i++) g[i] = Mod(g[i - 1] + f[i]);

        h[0] = g[0];
        for (int i = 1; i < maxn; i++) h[i] = Mod(h[i - 1] + g[i]);

        return;
    }
    int64_t getS(int l, int r) { return l == 0 ? g[r] : Mod(g[r] + mod - g[l - 1]); }
    int64_t getL(int l, int r) { return l == 0 ? h[r] : Mod(h[r] + mod - (h[l - 1] + (r - l + 1) * g[l - 1]) % mod); }
    int64_t getR(int l, int r) { return Mod(((r - l + 2) * getS(l, r) - getL(l, r)) % mod + mod); }
};

int64_t f[maxn][maxn], g[maxn][maxn], fl[maxn], fr[maxn];
SumStruct FL, FR, G;

int a[maxn], d[maxn], e[maxn];
int64_t Ac[maxn], Bc[maxn], Cc[maxn], Dc[maxn], Ec[maxn];
int64_t b[maxn], c[maxn], Bs[maxn], Cs[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 2; i <= n + 1; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 2; i <= n + 1; i++) cin >> e[i];

    for (int i = 1; i <= n + 1; i++) {
        Ac[i] = (a[i] >= 0 ? 1 : -a[i] + 1);
        Bc[i] = (b[i] >= 0 ? 1 : -b[i] + 1);
        Cc[i] = (c[i] >= 0 ? 1 : -c[i] + 1);
        Dc[i] = (d[i] >= 0 ? 1 : -d[i] + 1);
        Ec[i] = (e[i] >= 0 ? 1 : -e[i] + 1);
    }

    for (int i = 1; i <= n + 1; i++)
        Bs[i] = (b[i] >= 0 ? b[i] : -b[i] * (-b[i] + 1) / 2) % mod, Cs[i] = (c[i] >= 0 ? c[i] : -c[i] * (-c[i] + 1) / 2) % mod;

    auto init = [&](int i) -> void { return FL.init(fl), FR.init(fr), G.init(g[i]); };

    g[0][0] = 1;
    init(0);

    for (int i = 1; i <= n + 1; i++) {
        int64_t BcxCc = Bc[i] * Cc[i] % mod, BcxCs = Bc[i] * Cs[i] % mod, BsxCc = Bs[i] * Cc[i] % mod;

        for (int v = (a[i] >= 0 ? a[i] : 0); v <= (a[i] >= 0 ? a[i] : -a[i]); v++) {
            int vl = max(0, v - abs(d[i])), vr = min(maxn - 1, v + abs(e[i]));

            if (vl < v) {
                int64_t sumF = (d[i] >= 0 ? FR.getS(vl, v - 1) : FR.getR(vl, v - 1)),
                        sumG = (d[i] >= 0 ? G.getS(vl, v - 1) : G.getR(vl, v - 1));

                if (d[i] < 0 && v + d[i] < vl) {
                    Add(sumF, FR.getS(vl, v - 1) * (vl - (v + d[i])) % mod);
                    Add(sumG, G.getS(vl, v - 1) * (vl - (v + d[i])) % mod);
                }

                Add(f[i][v], Mod((sumF + sumG * BsxCc % mod * v) % mod * Ec[i] % mod + mod));
                Add(g[i][v], sumG * Ec[i] % mod);
            }

            if (v <= vr) {
                int64_t sumF = (e[i] >= 0 ? FL.getS(v, vr) : FL.getL(v, vr)),
                        sumG = (e[i] >= 0 ? G.getS(v, vr) : G.getL(v, vr));

                if (e[i] < 0 && v - e[i] > vr) {
                    Add(sumF, FL.getS(v, vr) * ((v - e[i]) - vr) % mod);
                    Add(sumG, G.getS(v, vr) * ((v - e[i]) - vr) % mod);
                }

                Add(f[i][v], Mod((sumF - sumG * BcxCs % mod * v) % mod * Dc[i] % mod + mod));
                Add(g[i][v], sumG * Dc[i] % mod);
            }

            g[i][v] = g[i][v] * BcxCc % mod;
        }

        BcxCc = Bc[i + 1] * Cc[i + 1] % mod, BcxCs = Bc[i + 1] * Cs[i + 1] % mod, BsxCc = Bs[i + 1] * Cc[i + 1] % mod;

        for (int v = 0; v < maxn; v++)
            fr[v] = Mod((f[i][v] * BcxCc - g[i][v] * BsxCc % mod * v) % mod + mod),
            fl[v] = Mod((f[i][v] * BcxCc + g[i][v] * BcxCs % mod * v) % mod + mod);

        init(i);
    }

    int64_t tot = 1;
    for (int i = 1; i <= n + 1; i++) tot = tot * Ac[i] % mod * Bc[i] % mod * Cc[i] % mod * Dc[i] % mod * Ec[i] % mod;

    cout << f[n + 1][0] << ' ' << Mod(tot + mod - g[n + 1][0]) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
