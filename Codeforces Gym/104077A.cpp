/**
 * @file 104077A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 300005

typedef tuple<int, int, int> tiii;

int lef[maxn], rig[maxn], jmp[maxn], S[maxn], T[maxn];
map<int, int> fnd;
tiii ques[maxn];
vector<int> pos[maxn];
int len;

int jump(int p) {
    while (jmp[p] != p) p = jmp[p];
    return p;
}
void rebuild(int p) {
    int q = p;
    for (int i = 1; i <= len; i++) q = lef[q];
    jmp[q] = q;
    for (int i = 1; i <= len; i++) jmp[q] = rig[jmp[q]];
    while (p != q) jmp[rig[q]] = rig[jmp[q]], q = rig[q];
    return;
}

void solve(void) {
    int n, m, q;
    cin >> n >> m >> q, len = sqrt(m);

    for (int i = 1; i <= n; i++) pos[i].push_back(m + 1);
    for (int i = 1; i <= q; i++) {
        int op, a, b = 0;
        cin >> op >> a;
        if (op == 1) cin >> b;
        ques[i] = {op, a, b};
        if (op == 1) pos[a].push_back(b), pos[a + 1].push_back(b);
    }
    for (int i = 1; i <= n; i++) {
        S[i] = T[i - 1] + 1, T[i] = T[i - 1] + pos[i].size(), fnd[T[i]] = i;
        sort(pos[i].begin(), pos[i].end());
        for (int j = S[i]; j <= T[i]; j++) lef[j] = max(j - 1, S[i]), rig[j] = min(j + 1, T[i]), jmp[j] = min(j + len, T[i]);
    }
    for (int i = 1; i <= q; i++) {
        auto [op, a, b] = ques[i];
        if (op == 2) {
            cout << fnd[jump(S[a])] << endl;
            continue;
        }
        int p = lower_bound(pos[a].begin(), pos[a].end(), b) - pos[a].begin() + S[a],
            q = lower_bound(pos[a + 1].begin(), pos[a + 1].end(), b) - pos[a + 1].begin() + S[a + 1];
        swap(lef[rig[p]], lef[rig[q]]), swap(rig[p], rig[q]);
        rebuild(p), rebuild(q);
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}