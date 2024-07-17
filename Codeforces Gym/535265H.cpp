/**
 * @file 535265H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

struct Team {
    string name;
    int solve, time;
    
    bool operator < (const Team& o) const { return this->solve == o.solve ? this->time < o.time : this->solve > o.solve; }
};


Team A[maxn], B[maxn];
unordered_map<string, int> S;


int main() {

    int n, m;

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i].name >> A[i].solve >> A[i].time, S[A[i].name]++;
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> B[i].name >> B[i].solve >> B[i].time, S[B[i].name]++;

    sort(A + 1, A + n + 1), sort(B + 1, B + m + 1);

    int ans = INT_MAX;

    {
        int p = 1, c = 1;
        while (A[p].name != "lzr010506") {
            if (S[A[p].name] == 1) c++;
            p++;
        }
        ans = min(ans, c);
    }

    {
        int p = 1, c = 1;
        while (B[p].name != "lzr010506") {
            if (S[B[p].name] == 1) c++;
            p++;
        }
        ans = min(ans, c);
    }

    cout << ans << endl;

    return 0;
}