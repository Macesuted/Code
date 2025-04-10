/**
 * @file 9922.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

int a[maxn];
array<int, 8> pre[maxn];
int pow7[9], cnt[8], sum[6000005];
vector<array<int, 8>> valid;

int getS(const array<int, 8>& rec) {
    int S = 0;
    for (int i = 0; i < 8; i++) {
        int v = rec[i] % 3;
        S = S * 3 + v;
    }
    return S;
}
array<int, 8> minu(const array<int, 8>& a, const array<int, 8>& b) {
    array<int, 8> ans;
    for (int i = 0; i < 8; i++) ans[i] = a[i] - b[i];
    return ans;
}

void solve(void) {
    int n;
    cin >> n;

    int64_t ans = 0;
    for (int i = 0; i < 8; i++) pre[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], a[i]--;
        pre[i] = pre[i - 1], pre[i][a[i]]++;
    }

    for (const auto& delt : valid) {
        auto chk = [&](int l, int r) -> bool {
            auto res = minu(pre[r], pre[l - 1]);
            for (int i = 0; i < 8; i++)
                if (res[i] < delt[i]) return false;
            return true;
        };

        int p = 0;
        for (int i = 1; i <= n; i++) {
            while (p + 1 < i && chk(p + 1, i)) sum[getS(pre[p++])]++;
            if (chk(1, i)) ans += sum[getS(minu(pre[i], delt))];
        }
        while (p) sum[getS(pre[--p])]--;
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    pow7[0] = 1;
    for (int i = 1; i < 9; i++) pow7[i] = pow7[i - 1] * 7;

    for (int S = 0; S < pow7[8]; S++) {
        for (int i = 0; i < 8; i++) cnt[i] = S / pow7[i] % 7;
        bool chk = true;
        for (int i = 0; i < 6 && chk; i++) {
            if (cnt[i] > 2) chk = false;
            cnt[i + 1] -= cnt[i], cnt[i + 2] -= cnt[i];
            if (cnt[i + 1] < 0 || cnt[i + 2] < 0) chk = false;
        }
        if (cnt[6] > 0 || cnt[7] > 0) chk = false;
        if (!chk) continue;
        array<int, 8> rec;
        for (int i = 0; i < 8; i++) rec[i] = S / pow7[i] % 7;
        valid.push_back(rec);
    }

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
