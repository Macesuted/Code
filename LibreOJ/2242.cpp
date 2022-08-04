/**
 * @file 2242.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define mod 19260817
#define base 31

typedef pair<int64_t, int> pli;

int64_t powb[maxn], hsh[maxn];
deque<vector<pli>> hashS;
vector<pli> cache, head, tail;
int lenHead, lenTail;
deque<int> lenHashS;

int64_t getHash(int l, int r) { return (hsh[r] + mod - hsh[l - 1] * powb[r - l + 1] % mod) % mod; }

void solve(void) {
    string s, t;
    cin >> s;
    int n = s.size();
    s = " " + s + "*";
    int64_t val = 0;
    for (int i = 1, len = 0, tot = 0; i <= n + 1; i++) {
        if (s[i] == '*') {
            if (len) cache.emplace_back(val, len), val = len = 0;
            if (cache.empty()) continue;
            hashS.push_back(cache), lenHashS.push_back(tot), cache.clear(), tot = 0;
            continue;
        }
        tot++;
        if (s[i] == '?') {
            if (len) cache.emplace_back(val, len), val = len = 0;
            cache.emplace_back(-1, 1);
            continue;
        }
        val = (val * base + s[i] - 'a') % mod, len++;
    }
    if (s[1] != '*') head = hashS.front(), lenHead = lenHashS.front(), hashS.pop_front(), lenHashS.pop_front();
    if (s[n] != '*' && !hashS.empty())
        tail = hashS.back(), lenTail = lenHashS.back(), hashS.pop_back(), lenHashS.pop_back();
    int tn = hashS.size(), q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        int m = t.size();
        t = " " + t;
        for (int i = 1; i <= m; i++) hsh[i] = (hsh[i - 1] * base + t[i] - 'a') % mod;
        auto check = [&](int l, const vector<pli>& vec) {
            int p = l;
            for (auto i : vec)
                if (i.first == -1 || getHash(p, p + i.second - 1) == i.first)
                    p += i.second;
                else
                    return false;
            return true;
        };
        if (!check(1, head) || !check(m - lenTail + 1, tail)) {
            cout << "NO" << '\n';
            continue;
        }
        int p = 0;
        for (int l = 1 + lenHead, r = m - lenTail, i = l; i <= r && p < tn && i + lenHashS[p] - 1 <= m; i++)
            if (check(i, hashS[p])) i += lenHashS[p++] - 1;
        cout << (p == tn ? "YES" : "NO") << '\n';
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    powb[0] = 1;
    for (int i = 1; i < maxn; i++) powb[i] = powb[i - 1] * base % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}