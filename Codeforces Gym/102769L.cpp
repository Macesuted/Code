/**
 * @file 102769L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 5000005
#define mod 998244353

int l[maxn], r[maxn];
vector<int> cacl[maxn], cacr[maxn];

void gen(int n, int L, int X, int Y, uint64_t A, uint64_t B) {
    auto xorshift128p = [](uint64_t& A, uint64_t& B) {
        uint64_t T = A, S = B;
        A = S;
        T ^= T << 23;
        T ^= T >> 17;
        T ^= S ^ (S >> 26);
        B = T;
        return T + S;
    };
    for (int i = 1; i <= n; i++) {
        l[i] = xorshift128p(A, B) % L + X;
        r[i] = xorshift128p(A, B) % L + Y;
        if (l[i] > r[i]) swap(l[i], r[i]);
    }
    return;
}

int64_t solve(void) {
    int n, L, X, Y;
    uint64_t A, B;
    cin >> n >> L >> X >> Y >> A >> B;
    gen(n, L, X, Y, A, B);
    vector<int> qll, qlr, qrl, qrr;
    for (int i = n; i; i--) {
        cacl[i].clear(), cacr[i].clear();
        while (!qrl.empty() && l[qrl.back()] - qrl.back() <= l[i] - i) cacl[i].push_back(qrl.back()), qrl.pop_back();
        while (!qrr.empty() && r[qrr.back()] + qrr.back() >= r[i] + i) cacr[i].push_back(qrr.back()), qrr.pop_back();
        qrl.push_back(i), qrr.push_back(i);
    }
    int64_t ret = 0, x = 1;
    for (int i = 1, ans = 0, pll = 0, plr = 0, prl = (int)qrl.size() - 1, prr = (int)qrr.size() - 1; i <= n;
         i++, x = x * 3 % mod) {
        auto updPt = [&](void) {
            pll = min(pll, (int)qll.size()), plr = min(plr, (int)qlr.size());
            prl = min(prl, (int)qrl.size()), prr = min(prr, (int)qrr.size());
            while (pll > 0 && i - qll[pll - 1] + 1 <= ans) pll--;
            while (pll < (int)qll.size() && i - qll[pll] + 1 > ans) pll++;
            while (plr > 0 && i - qlr[plr - 1] + 1 <= ans) plr--;
            while (plr < (int)qlr.size() && i - qlr[plr] + 1 > ans) plr++;
            while (prl > 0 && qrl[prl - 1] - i + 1 <= ans) prl--;
            while (prl < (int)qrl.size() && qrl[prl] - i + 1 > ans) prl++;
            while (prr > 0 && qrr[prr - 1] - i + 1 <= ans) prr--;
            while (prr < (int)qrr.size() && qrr[prr] - i + 1 > ans) prr++;
            return;
        };
        auto chkLR = [&](void) {
            int pl = INT_MIN, pr = INT_MAX;
            if (pll < (int)qll.size()) pl = max(pl, l[qll[pll]] + qll[pll] + ans - i - 1);
            if (plr < (int)qlr.size()) pr = min(pr, r[qlr[plr]] - qlr[plr] - ans + i + 1);
            if (prl < (int)qrl.size()) pl = max(pl, l[qrl[prl]] - qrl[prl] + ans + i - 1);
            if (prr < (int)qrr.size()) pr = min(pr, r[qrr[prr]] + qrr[prr] - ans - i + 1);
            return pl <= pr;
        };
        ans = min(ans + 1, n - i + 1);
        while (!qll.empty() && l[qll.back()] + qll.back() <= l[i] + i) qll.pop_back();
        while (!qlr.empty() && r[qlr.back()] - qlr.back() >= r[i] - i) qlr.pop_back();
        qll.push_back(i), qlr.push_back(i), updPt();
        while (!chkLR()) ans--, updPt();
        qrl.pop_back(), qrr.pop_back();
        for (auto j = cacl[i].rbegin(); j != cacl[i].rend(); j++) qrl.push_back(*j);
        for (auto j = cacr[i].rbegin(); j != cacr[i].rend(); j++) qrr.push_back(*j);
        updPt();
        ret = (ret + ans * x) % mod;
    }
    return ret;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    for (int i = 1; i <= _; i++) cout << "Case #" << i << ": " << solve() << endl;

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}