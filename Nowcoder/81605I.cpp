/**
 * @file 81605I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

int a[maxn], b[maxn], pos[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    auto calc = [&](void) {
        int cnt = 0;
        for (int i = 1; i < n; i++) cnt += (a[i] + 1 == a[i + 1]);
        return cnt;
    };

    vector<string> ans;
    while (calc() < n - 1) {
        for (int i = 1; i <= n; i++) pos[b[i] = a[i]] = i;
        string op(n, 'A');
        int cnt = 0;
        for (int l = 1, r, t = 0; l <= n; l = r + 1, t = !t) {
            r = l;
            while (r < n && pos[r + 1] > pos[r]) r++;
            if (t)
                for (int i = l; i <= r; i++) op[pos[i] - 1] = 'B', cnt++;
        }
        ans.push_back(op);
        for (int i = n; i; i--)
            for (int j = 1; j < i; j++)
                if (op[j - 1] > op[j]) swap(a[j], a[j + 1]), swap(op[j - 1], op[j]);
    }
    reverse(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (auto i : ans) cout << i << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}