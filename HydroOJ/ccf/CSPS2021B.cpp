#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 505
#define mod 1000000007

long long f[maxn][maxn], g[maxn][maxn];
int cnt[maxn];
string s;
int n, k;

inline long long Mod(long long x) { return x >= mod ? x - mod : x; }
inline bool check(int l, int r) { return l <= r && r - l + 1 <= k && cnt[r] - cnt[l - 1] == r - l + 1; }

void solve(void) {
    cin >> n >> k >> s;
    s = ' ' + s;
    for (int i = 1; i <= n; i++) cnt[i] = cnt[i - 1] + (s[i] == '?' || s[i] == '*');
    for (int len = 2; len <= n; len++)
        for (int l = 1, r = len; r <= n; l++, r++) {
            f[l][r] = 0;
            if ((s[l] == '(' || s[l] == '?') && (s[r] == ')' || s[r] == '?')) {
                if (l + 1 == r) f[l][r] = Mod(f[l][r] + 1);
                if (check(l + 1, r - 1)) f[l][r] = Mod(f[l][r] + 1);
                if (l + 1 < r) f[l][r] = Mod(f[l][r] + g[l + 1][r - 1]);
                for (int i = l + 1; check(l + 1, i) && i + 1 < r; i++) f[l][r] = Mod(f[l][r] + g[i + 1][r - 1]);
                for (int i = r - 1; check(i, r - 1) && i - 1 > l; i--) f[l][r] = Mod(f[l][r] + g[l + 1][i - 1]);
            }
            g[l][r] = f[l][r];
            static queue<int> que;
            while (!que.empty()) que.pop();
            long long sum = 0;
            for (int i = l, p = l + 1; i < r; i++) {
                while (!que.empty() && que.front() <= i) sum = Mod(sum + mod - g[que.front()][r]), que.pop();
                while (p <= r && (i + 1 == p || check(i + 1, p - 1))) sum = Mod(sum + g[p][r]), que.push(p++);
                g[l][r] = Mod(g[l][r] + f[l][i] * sum % mod);
            }
        }
    cout << g[1][n] << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("bracket.in", "r", stdin), freopen("bracket.out", "w", stdout);
#endif
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    clock_t tim1 = clock();
    ios::sync_with_stdio(false);

    solve();

    clock_t tim2 = clock();
    cerr << "Time: " << (tim2 - tim1) * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}

/*
ASBSCSD
*/