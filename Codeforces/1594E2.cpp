/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 2005
#define mod 1000000007

typedef pair<int, int> pii;

struct STR {
    int p[7];
};

map<string, int> MAP;
set<int> uses;

int f[maxn];
int k, n, inv6;
map<int, int> c;

int Pow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

STR dfs(int p, int dep) {
    int g[7] = {0, 0, 0, 0, 0, 0, 0};
    if (dep == k - 1 || uses.find(p) == uses.end()) {
        if (c.find(p) != c.end())
            g[c[p]] = f[dep];
        else
            g[1] = g[2] = g[3] = g[4] = g[5] = g[6] = f[dep];
        return STR({g[0], g[1], g[2], g[3], g[4], g[5], g[6]});
    }
    STR l = dfs(p << 1, dep + 1), r = dfs(p << 1 | 1, dep + 1);
    for (int cp = 1; cp <= 6; cp++)
        if (c.find(p) == c.end() || c[p] == cp)
            for (int lc = 1; lc <= 6; lc++)
                if (abs(cp - lc) % 3)
                    for (int rc = 1; rc <= 6; rc++)
                        if (abs(cp - rc) % 3) g[cp] = (g[cp] + l.p[lc] % mod * r.p[rc]) % mod;
    return STR({g[0], g[1], g[2], g[3], g[4], g[5], g[6]});
}

void work(void) {
    inv6 = Pow(6, mod - 2);
    MAP["white"] = 1;
    MAP["green"] = 2;
    MAP["red"] = 3;
    MAP["yellow"] = 4;
    MAP["blue"] = 5;
    MAP["orange"] = 6;
    cin >> k >> n;
    f[k - 1] = 1;
    for (int i = k - 2; ~i; i--) f[i] = 16 * f[i + 1] % mod * f[i + 1] % mod;
    for (int i = 1; i <= n; i++) {
        int p;
        string s;
        cin >> p >> s;
        c[p] = MAP[s];
        while (p) uses.insert(p), p >>= 1;
    }
    STR ret = dfs(1, 0);
    long long answer = 0;
    for (int i = 1; i <= 6; i++) answer = (answer + ret.p[i]) % mod;
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}