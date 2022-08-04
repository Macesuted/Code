/**
 * @file D2T3.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxc 35

int S[maxc], T[maxc], f[15][5][5];

int& Min(int& a, int b) { return a = min(a, b); }

int dp(void) {
    int ans = 0;
    for (int mode = 0; mode <= 20; mode += 10) {
        memset(f, 0x3f, sizeof(f)), f[0][0][0] = 0;
        for (int i = 0; i < 9; i++)
            for (int t1 = 0; t1 <= 4; t1++)
                for (int t2 = 0; t2 <= 4; t2++)
                    if (f[i][t1][t2] != 0x3f3f3f3f) {
                        int u = max(0, t1 - T[mode + i + 1]), rest = 4 - S[mode + i + 1] - u,
                            p = max(0, T[mode + i + 1] - t1);
                        for (int x = p; x <= p + rest; x++, u++)
                            if (x == 4) {
                                if (i < 8 && t2 <= 3) Min(f[i + 1][t2 + 1][1], f[i][t1][t2] + u);
                                if (i < 8 && t2 == 0) Min(f[i + 1][4][4], f[i][t1][t2] + u);
                            } else if (x == 3) {
                                Min(f[i + 1][t2][0], f[i][t1][t2] + u);
                                if (i < 8 && t2 <= 1) Min(f[i + 1][t2 + 3][3], f[i][t1][t2] + u);
                            } else if (x == 2) {
                                if (i < 8 && t2 <= 2) Min(f[i + 1][t2 + 2][2], f[i][t1][t2] + u);
                            } else if (x == 1) {
                                if (i < 8 && t2 <= 3) Min(f[i + 1][t2 + 1][1], f[i][t1][t2] + u);
                            } else
                                Min(f[i + 1][t2][0], f[i][t1][t2] + u);
                    }
        ans += f[9][0][0];
    }
    return ans;
}
bool check(void) {
    int rest = 14;
    for (int i = 1; i <= 29; i++) rest -= T[i];
    bool chk7 = true;
    for (int i = 1; i <= 29; i++) chk7 &= ((T[i] == 2) || (T[i] == 1 && S[i] <= 3) || (T[i] == 0));
    if (chk7) {
        int cnt = 0;
        for (int i = 1; i <= 29; i++) cnt += (T[i] == 1);
        if (cnt <= rest) return true;
    }
    for (int ban = 1; ban <= 29; ban += 1 + (ban % 10 == 9)) {
        int t_ = T[ban], s_ = S[ban];
        S[ban] += max(0, 2 - T[ban]), T[ban] = max(0, T[ban] - 2);
        int ret = INT_MAX;
        if (S[ban] <= 4) ret = dp() + S[ban] - s_;
        T[ban] = t_, S[ban] = s_;
        if (ret <= rest) return true;
    }
    return false;
}
bool check(int t, int p = 1) {
    if (p == 30) return !t && check();
    T[p] = S[p];
    for (; ~t && ~T[p]; t--, T[p]--)
        if (check(t, p + 1)) return true;
    return false;
}

void solve(void) {
    string s;
    cin >> s;
    int mode = 0;
    for (auto i : s) {
        if (i == 'm') mode = 10;
        if (i == 'p') mode = 20;
        if ('1' <= i && i <= '9') S[mode + i - '0']++;
    }
    for (int i = 0; i <= 5; i++)
        if (check(i)) return cout << i << endl, void();
    cout << "Answer > 5" << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}