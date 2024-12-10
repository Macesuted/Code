/**
 * @file 9550.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-28
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

vector<string> ans;
int cnt = 0;

void pop(int top, int to1, int push, int to2) {
    return ans.push_back("POP " + to_string(top) + " GOTO " + to_string(to1) + "; PUSH " + to_string(push) + " GOTO " +
                         to_string(to2));
}
void halt(int push, int to) { return ans.push_back("HALT; PUSH " + to_string(push) + " GOTO " + to_string(to)); }

void solve(int x) {
    if (!x) return;
    if (x & 1)
        solve((x - 1) >> 1), cnt++, pop(cnt, cnt + 1, cnt, 1);
    else
        solve(x - 1), cnt++, pop(cnt, cnt + 1, cnt, cnt);
    return;
}

void solve(void) {
    int x;
    cin >> x, x = (x - 1) >> 1;

    solve(x);

    cnt++, halt(cnt, 1);

    cout << ans.size() << endl;
    for (auto s : ans) cout << s << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}