/**
 * @file 12961.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 5000005
#define mod 998244353

uint64_t xorshift128p(uint64_t &A, uint64_t &B) {
    uint64_t T = A, S = B;
    A = S, T ^= T << 23, T ^= T >> 17, T ^= S ^ (S >> 26), B = T;
    return T + S;
}

int l[maxn], r[maxn];
deque<int> ld, rd, lu, ru;

void gen(int n, int L, int X, int Y, uint64_t A, uint64_t B) {
    for (int i = 1; i <= n; i++) {
        l[i] = xorshift128p(A, B) % L + X;
        r[i] = xorshift128p(A, B) % L + Y;
        if (l[i] > r[i]) swap(l[i], r[i]);
    }
    return;
}

int solve(void) {
    int n, L, X, Y;
    uint64_t A, B;
    cin >> n >> L >> X >> Y >> A >> B;
    gen(n, L, X, Y, A, B);
    auto pushMax = [](deque<int> &que, int v) {
        while (!que.empty() && que.back() < v) que.pop_back();
        return que.push_back(v);
    };
    auto pushMin = [](deque<int> &que, int v) {
        while (!que.empty() && que.back() > v) que.pop_back();
        return que.push_back(v);
    };
    auto pop = [](deque<int> &que, int v) { return !que.empty() && que.front() == v && (que.pop_front(), 1), void(); };
    int64_t ans = 1, pow3 = 3;
    int V = 1;
    ld.clear(), rd.clear(), lu.clear(), ru.clear();
    ld.push_back(l[1] + 1), rd.push_back(l[1] - 1), lu.push_back(r[1] - 1), ru.push_back(r[1] + 1);
    for (int i = 2; i <= n; ans = (ans + pow3 * V) % mod, pow3 = pow3 * 3 % mod, i++) {
        pushMax(ld, l[i] + i), pop(rd, l[i - 1] - (i - 1)), pushMin(lu, r[i] - i), pop(ru, r[i - 1] + (i - 1)), V++;
        if (i + V - 1 <= n &&
            max({ld.front() + V - i - 1, rd.empty() ? 0 : rd.front() + V + i - 1, l[i + V - 2] + 1, l[i + V - 1]}) <=
                min({lu.front() - V + i + 1, ru.empty() ? INT_MAX : ru.front() - V - i + 1, r[i + V - 2] - 1,
                     r[i + V - 1]})) {
            pushMax(rd, l[i + V - 2] - (i + V - 2)), pushMax(rd, l[i + V - 1] - (i + V - 1));
            pushMin(ru, r[i + V - 2] + (i + V - 2)), pushMin(ru, r[i + V - 1] + (i + V - 1));
            continue;
        }
        pop(ld, l[i - V + 1] + (i - V + 1)), pop(lu, r[i - V + 1] - (i - V + 1)), V--;
        if (i + V - 1 <= n &&
            max({ld.front() + V - i - 1, rd.empty() ? 0 : rd.front() + V + i - 1, l[i + V - 1]}) <=
                min({lu.front() - V + i + 1, ru.empty() ? INT_MAX : ru.front() - V - i + 1, r[i + V - 1]})) {
            pushMax(rd, l[i + V - 1] - (i + V - 1)), pushMin(ru, r[i + V - 1] + (i + V - 1));
            continue;
        }
        pop(ld, l[i - V + 1] + (i - V + 1)), pop(lu, r[i - V + 1] - (i - V + 1)), V--;
    }
    return ans;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("lost.in", "r", stdin), freopen("lost.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
