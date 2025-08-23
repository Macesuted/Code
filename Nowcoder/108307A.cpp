/**
 * @file 108307A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-14
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

bool isvar(char c) { return isdigit(c) || isalpha(c) || c == '_'; }

void solve(void) {
    int TAB;
    scanf("%d", &TAB);

    string s;
    char c = getchar();
    while (c != EOF) s.push_back(c), c = getchar();

    {
        size_t l = 0, r = s.size() - 1;
        while (isspace(s[l])) l++;
        while (isspace(s[r])) r--;
        s = s.substr(l, r - l + 1);
    }

    {
        size_t l = 1;
        while (!(s[l - 1] == '*' && s[l] == '/')) l++;

        for (size_t i = 0; i <= l; i++) putchar(s[i]);
        putchar('\n');

        s = s.substr(l + 1);
    }

    {
        size_t l = 0;
        while (isspace(s[l])) l++;
        s = s.substr(l);
    }

    for (size_t i = 0; i < s.size(); i++)
        if (isspace(s[i])) s[i] = ' ';

    {
        string t;
        t.push_back(s[0]);
        for (size_t i = 1; i + 1 < s.size(); i++) {
            t.push_back(s[i]);
            if (s[i] != ' ') continue;
            if (isvar(t[t.size() - 2]) && isvar(s[i + 1])) continue;
            t.pop_back();
        }
        t.push_back(s.back());
        s = t;
    }

    {
        s = '$' + s + '$';

        vector<size_t> pre(s.size());
        stack<size_t> S;
        for (size_t i = 1; i + 1 < s.size(); i++) {
            if (s[i] == '{') S.push(i);
            if (s[i] == '}') pre[i] = S.top(), S.pop();
        }

        string t;
        for (size_t i = 1; i + 1 < s.size(); i++) {
            if (s[i] == '+' && s[i + 1] == '+') {
                s[i] = s[i + 1] = 'a';
                t.push_back('+'), t.push_back('+');
                i = i + 1;
                continue;
            }

            if (s[i] == '+' || s[i] == '&' || s[i] == '/') t.push_back(' ');
            if (s[i] == '=' && s[i - 1] != '=') t.push_back(' ');

            if (s[i] == '{') t.push_back(' ');

            if (s[i] == '(') {
                if (i >= 2 && s.substr(i - 2, 2) == "if") t.push_back(' ');
                if (i >= 5 && s.substr(i - 5, 5) == "while") t.push_back(' ');
                if (i >= 6 && s.substr(i - 6, 6) == "return") t.push_back(' ');
            }

            t.push_back(s[i]);

            if (s[i] == '+' || s[i] == '&' || s[i] == '/') t.push_back(' ');
            if (s[i] == '=' && s[i + 1] != '=') t.push_back(' ');

            if (s[i] == ',') t.push_back(' ');

            if (s[i] == '!' && t[t.size() - 2] == '\n') t.push_back('\n');
            if (s[i] == '{') t.push_back('\n');
            if (s[i] == '}') {
                if (i + 9 < s.size() && s.substr(i + 1, 9) == "otherwise")
                    t.push_back(' ');
                else if (pre[i] >= 6 && s.substr(pre[i] - 6, 6) == "repeat")
                    t.push_back(' ');
                else
                    t.push_back('\n');
            }
            if (s[i] == '?') t.push_back('\n');
        }
        s = t;
    }

    while (s.back() == '\n') s.pop_back();

    {
        size_t pre = 0;
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == '{') pre += TAB;

            putchar(s[i]);

            if (i + 1 < s.size() && s[i + 1] == '}') pre -= TAB;

            if (s[i] == '\n')
                for (size_t t = 0; t < pre; t++) putchar(' ');
        }
    }

    return;
}

int main() {
    int _ = 1;
    while (_--) solve();

    return 0;
}