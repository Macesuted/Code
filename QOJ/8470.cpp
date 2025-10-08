/**
 * @file 8470.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

using Mbit = bitset<129>;
using M = array<Mbit, 128>;

unordered_map<string, M> val;
M Mzero;

M bitNot(M b) {
    for (size_t i = 0; i < 128; i++) b[i][128] = !b[i][128];
    return b;
}
M bitOr(M b, M v) {
    for (size_t i = 0; i < 128; i++) assert(v[i].count() == v[i][128]);
    for (size_t i = 0; i < 128; i++)
        if (v[i][128]) b[i] = 0, b[i][128] = true;
    return b;
}
M bitAnd(M b, M v) {
    for (size_t i = 0; i < 128; i++) assert(v[i].count() == v[i][128]);
    for (size_t i = 0; i < 128; i++)
        if (!v[i][128]) b[i] = 0;
    return b;
}
M bitXor(M b, M v) {
    for (size_t i = 0; i < 128; i++) b[i] ^= v[i];
    return b;
}

M readHex(string s) {
    M ans = Mzero;

    reverse(s.begin(), s.end());
    for (size_t i = 0; i < s.size() - 2; i++) {
        int v = ('0' <= s[i] && s[i] <= '9' ? s[i] - '0' : 10 + s[i] - 'a');
        for (size_t j = 0; j < 4; j++) ans[i << 2 | j][128] = v >> j & 1;
    }

    return ans;
}
M readVar(string s) { return val[s]; }
M readTerm(string s) {
    bool rev = false;
    if (s[0] == '~') s = s.substr(1), rev = true;
    M ans = s[0] == '0' ? readHex(s) : readVar(s);
    if (rev) ans = bitNot(ans);
    return ans;
}

void solve(void) {
    string code;

    for (int i = 0; i < 128; i++) Mzero[i] = 0;

    M& x = val["x"] = Mzero;
    for (int i = 0; i < 128; i++) x[i][i] = true;

    while (getline(cin, code)) {
        stringstream ssin(code);

        string var, eq, lef, op, rig;
        ssin >> var >> eq >> lef;

        if (!(ssin >> op)) {
            val[var] = readTerm(lef);
            continue;
        }

        ssin >> rig;

        if (op == "<<" || op == ">>") {
            M l = readTerm(lef);
            int r = stoi(rig);

            val[var] = Mzero;
            for (int i = 0; i < 128; i++) {
                int j = (op == "<<" ? i - r : i + r);
                if (0 <= j && j < 128) val[var][i] = l[j];
            }
        } else {
            if (lef[0] == '0' || (lef[0] == '~' && lef[1] == '0')) swap(lef, rig);
            M l = readTerm(lef), r = readTerm(rig);

            if (op == "&")
                val[var] = bitAnd(l, r);
            else if (op == "|")
                val[var] = bitOr(l, r);
            else
                val[var] = bitXor(l, r);
        }
    }

    M base = Mzero;
    for (int i = 0; i < 128; i++) {
        x[i][i] = !x[i][i];
        for (int j = 0; j < 128; j++)
            if (x[i][j]) {
                if (base[j].count())
                    x[i] ^= base[j];
                else {
                    base[j] = x[i], x[i] = 0;
                    for (int x = j + 1; x < 128; x++)
                        if (base[j][x]) base[j] ^= base[x];
                    for (int x = 0; x < j; x++)
                        if (base[x][j]) base[x] ^= base[j];
                    break;
                }
            }
        if (x[i].count()) return cout << ":(" << endl, void();
    }

    vector<int> ans(32);
    for (size_t i = 0; i < 128; i++) ans[i >> 2] |= base[i][128] << (i & 3);

    string os;
    for (int i = 31; ~i; i--) os.push_back(ans[i] < 10 ? '0' + ans[i] : 'a' + ans[i] - 10);
    while (os.size() > 1 && os[0] == '0') os.erase(0, 1);

    cout << "0x" << os << endl;

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