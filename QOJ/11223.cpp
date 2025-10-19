/**
 * @file 11223.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using tiii = tuple<int, int, int>;

void solve(void) {
    int n;
    cin >> n;

    string code;
    for (int i = 1; i <= n; i++) {
        string line;
        if (i == 1) getline(cin, line);
        getline(cin, line);
        code.append(line), code.push_back(' ');
    }

    unordered_map<string, int> dict;
    dict["double"] = 1;
    dict["string"] = 2;

    stringstream ssin(code);
    string s;
    while (ssin >> s)
        if (s == "message") ssin >> s, dict[s] = dict.size() + 1;

    int m = dict.size();

    vector<vector<tiii>> message(m + 1);

    ssin = stringstream(code);
    while (ssin >> s) {
        assert(s == "message");
        ssin >> s;
        int mid = dict[s];
        assert(mid);

        ssin >> s;
        assert(s == "{");

        while (ssin >> s && s != "}") {
            int label = (s == "required" ? 1 : s == "optional" ? 2 : 3);

            ssin >> s;
            int type = dict[s];
            assert(type);

            ssin >> s;
            ssin >> s;
            assert(s == "=");

            int fieldNumber;
            ssin >> fieldNumber;

            ssin >> s;
            assert(s == ";");

            message[mid].emplace_back(label, type, fieldNumber);
        }
    }

    for (int i = 1; i <= m; i++)
        sort(message[i].begin(), message[i].end(), [](const tiii& a, const tiii& b) -> bool { return get<2>(a) < get<2>(b); });

    auto _ = [&](int x, int y) -> int { return (x - 1) * m + y; };

    vector<bool> invalid(m * m + 1);
    vector<vector<int>> graph(m * m + 1);

    for (int i = 2; i <= m; i++) invalid[_(1, i)] = invalid[_(i, 1)] = true;
    for (int i = 3; i <= m; i++) invalid[_(2, i)] = true;

    for (int i = 3; i <= m; i++)
        for (int j = 3; j <= m; j++) {
            if (i == j) continue;

            for (size_t ki = 0, kj = 0; ki < message[i].size(); ki++) {
                while (kj < message[j].size() && get<2>(message[i][ki]) != get<2>(message[j][kj])) {
                    if (get<0>(message[j][kj]) == 1) invalid[_(i, j)] = true;
                    kj++;
                }
                if (kj == message[j].size()) {
                    invalid[_(i, j)] = true;
                    break;
                }

                graph[_(get<1>(message[i][ki]), get<1>(message[j][kj]))].push_back(_(i, j));

                int mi = get<0>(message[i][ki]), mj = get<0>(message[j][kj]);
                if (mi > mj) invalid[_(i, j)] = true;

                kj++;
            }
        }

    queue<int> que;
    for (int i = 1; i <= m * m; i++)
        if (invalid[i]) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        for (auto q : graph[p])
            if (!invalid[q]) invalid[q] = true, que.push(q);
    }

    int q;
    cin >> q;
    while (q--) {
        string A, B;
        cin >> A >> B;
        cout << "Wire-format ";
        if (invalid[_(dict[A], dict[B])] || invalid[_(dict[B], dict[A])]) cout << "in";
        cout << "compatible." << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    solve();

    return 0;
}
