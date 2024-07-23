/**
 * @file 102465G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 2505
#define mod 1000000007

typedef pair<int64_t, int64_t> pll;

vector<pll> a[maxn];
vector<int64_t> ops[maxn];
int64_t len[maxn], pre[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s, len[0] = s.size();
    for (int i = 1; i < n; i++) {
        string op;
        cin >> op;
        if (op == "SUB")
            ops[i].resize(3), cin >> ops[i][0] >> ops[i][1] >> ops[i][2], len[i] = ops[i][2] - ops[i][1];
        else
            ops[i].resize(2), cin >> ops[i][0] >> ops[i][1], len[i] = len[ops[i][0]] + len[ops[i][1]];
    }

    a[n - 1].emplace_back(len[n - 1] - 1, +1);
    for (int i = n - 1; i; i--)
        if (ops[i].size() == 3) {
            int64_t fa = ops[i][0], l = ops[i][1], sum = 0;
            for (auto [x, t] : a[i]) a[fa].emplace_back(l + x, t), sum = (sum + t) % mod;
            if (l) a[fa].emplace_back(l - 1, mod - sum);
        } else {
            int64_t f1 = ops[i][0], f2 = ops[i][1], sum = 0;
            for (auto [x, t] : a[i]) {
                if (x < len[f1])
                    a[f1].emplace_back(x, t);
                else
                    sum = (sum + t) % mod, a[f2].emplace_back(x - len[f1], t);
            }
            if (sum) a[f1].emplace_back(len[f1] - 1, sum);
        }

    int64_t ans = 0;
    pre[0] = s[0];
    for (int i = 1; i < len[0]; i++) pre[i] = pre[i - 1] + s[i];
    for (auto [x, t] : a[0]) ans = (ans + t * pre[x]) % mod;
    cout << ans << endl;

    return 0;
}