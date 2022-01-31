/**
 * @file 1167.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

string a[4], b[4];
int cnt[26];

void solve(void) {
    for (int i = 1; i <= 3; i++) cin >> a[i];
    for (int i = 1; i <= 3; i++) cin >> b[i];
    memset(cnt, 0, sizeof(cnt));
    int g = 0, y = 0;
    for (int i = 1; i <= 3; i++)
        for (int j = 0; j < 3; j++)
            if (a[i][j] == b[i][j])
                g++;
            else
                cnt[a[i][j] - 'A']++;
    for (int i = 1; i <= 3; i++)
        for (int j = 0; j < 3; j++)
            if (a[i][j] != b[i][j] && cnt[b[i][j] - 'A'])
                y++, cnt[b[i][j] - 'A']--;
    cout << g << endl
         << y << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
