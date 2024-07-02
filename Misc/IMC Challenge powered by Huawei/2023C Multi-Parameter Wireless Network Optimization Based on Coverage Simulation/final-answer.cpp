/**
 * @file final-answer.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

const int only = -1;
const int seed[7] = {0, 634278, 563829, 534624, 118562, 339567, 156283};
const double coef[7][4] = {
    {}, {}, {4, 6, 2.25, 1.45}, {4, 6.75, 1.55, 1.45}, {5, 6.75, 1.55, 1.45}, {4, 6.75, 3, 1.45}, {5, 6.75, 1.55, 1.45}};
int nT = 50;

//-------------------------------------------------------------------------------------------------

typedef pair<int, int> pii;

const int nBS = 21;
const int ptnAngle[17][2] = {{105, 6}, {110, 6}, {90, 6},  {65, 6},   {45, 6},  {25, 6},  {110, 12}, {90, 12}, {65, 12},
                             {45, 12}, {25, 12}, {15, 12}, {110, 25}, {65, 25}, {45, 25}, {25, 25},  {15, 25}};

struct Ant {
    int azm, tlt, ptn;
    Ant(void) = default;
    Ant(int _azm, int _tlt, int _ptn) : azm(_azm), tlt(_tlt), ptn(_ptn) { return; }
};

int caseNumber = 0;

double diff(Ant a, Ant b) {
    return fabs(a.azm - b.azm) / 60 * coef[caseNumber][0] + fabs(a.tlt - b.tlt) / 20 * coef[caseNumber][1] +
           fabs(ptnAngle[a.ptn][0] - ptnAngle[b.ptn][0]) / 95 * coef[caseNumber][2] +
           fabs(ptnAngle[a.ptn][1] - ptnAngle[b.ptn][1]) / 19 * coef[caseNumber][3];
}
double submit(map<pii, Ant> answer) {
    cerr << '?' << endl;
    nT--;
    cout << answer.size() << endl;
    for (auto [id, ant] : answer)
        cout << "site" << id.first << ' ' << id.second << ' ' << ant.azm << ' ' << ant.tlt << ' ' << ant.ptn << endl;

    string emp;
    double R1, R2, R3, u1, u2, score;
    cin >> emp >> R1 >> emp;
    cin >> emp >> R2 >> emp;
    cin >> emp >> R3 >> emp;
    cin >> emp >> u1 >> emp;
    cin >> emp >> u2 >> emp;
    cin >> emp >> score;
    return score;
}

map<int, vector<Ant>> mods[nBS + 1];

int main() {
    cin >> caseNumber;

    cout << "start" << endl;

    {
        string s;
        getline(cin, s), getline(cin, s);
        stringstream ssin(s);
        ssin.get();
        while (true) {
            while (!ssin.eof() && ssin.get() != '[');
            if (ssin.eof()) break;
            ssin.get(), ssin.get(), ssin.get(), ssin.get(), ssin.get();
            int BSid = 0, ant, azm, tlt, ptn;
            ssin >> BSid, ssin.get(), ssin.get();
            ssin >> ant, ssin.get();
            ssin >> azm, ssin.get();
            ssin >> tlt, ssin.get();
            ssin >> ptn, ssin.get();
            ssin.get();
            mods[BSid][ant].emplace_back(azm, tlt, ptn);
        }
    }

    map<pii, Ant> answer, base;
    double score = 0;

    {
        base[{1, 1}] = {130, 11, 0};
        base[{1, 2}] = {260, 7, 2};
        base[{1, 3}] = {0, 3, 10};
        base[{2, 4}] = {315, 1, 6};
        base[{2, 5}] = {95, 18, 13};
        base[{2, 6}] = {175, 13, 10};
        base[{3, 7}] = {170, -7, 7};
        base[{3, 8}] = {10, 5, 15};
        base[{3, 9}] = {240, 13, 15};
        base[{4, 10}] = {30, 11, 13};
        base[{4, 11}] = {330, 9, 9};
        base[{5, 12}] = {355, 14, 5};
        base[{5, 13}] = {160, 11, 14};
        base[{5, 14}] = {105, 14, 15};
        base[{6, 15}] = {270, -7, 5};
        base[{6, 16}] = {180, 13, 10};
        base[{6, 17}] = {350, 3, 0};
        base[{7, 18}] = {170, -5, 10};
        base[{7, 19}] = {330, 13, 10};
        base[{8, 20}] = {205, 22, 8};
        base[{8, 21}] = {40, 16, 11};
        base[{8, 22}] = {280, 10, 0};
        base[{9, 23}] = {160, 14, 5};
        base[{9, 24}] = {40, 26, 5};
        base[{9, 25}] = {80, 20, 11};
        base[{10, 26}] = {210, 11, 3};
        base[{10, 27}] = {40, 5, 3};
        base[{10, 28}] = {330, -5, 9};
        base[{11, 29}] = {280, -8, 13};
        base[{11, 30}] = {110, -8, 0};
        base[{12, 31}] = {265, 30, 5};
        base[{12, 32}] = {30, 14, 16};
        base[{12, 33}] = {185, 11, 15};
        base[{13, 34}] = {100, -8, 0};
        base[{13, 35}] = {240, 2, 0};
        base[{13, 36}] = {350, -8, 13};
        base[{14, 37}] = {120, 18, 11};
        base[{14, 38}] = {220, 8, 3};
        base[{14, 39}] = {350, 18, 10};
        base[{15, 40}] = {280, -5, 14};
        base[{15, 41}] = {170, -7, 8};
        base[{15, 42}] = {350, 5, 3};
        base[{16, 43}] = {200, -5, 15};
        base[{16, 44}] = {350, 7, 4};
        base[{17, 45}] = {160, 7, 0};
        base[{17, 46}] = {25, 13, 5};
        base[{17, 47}] = {235, 3, 5};
        base[{18, 48}] = {350, 7, 16};
        base[{18, 49}] = {220, 1, 12};
        base[{18, 50}] = {60, 1, 5};
        base[{20, 54}] = {240, 17, 5};
        base[{20, 55}] = {170, 12, 5};
        base[{20, 56}] = {30, -3, 7};
        base[{21, 57}] = {270, 9, 14};
        base[{21, 58}] = {160, 20, 0};
        base[{21, 59}] = {90, 13, 10};
    }

    if (caseNumber == 1)
        answer = base, score = 85.45;
    else {
        for (int i = 1; i <= nBS; i++)
            for (auto [j, ops] : mods[i]) {
                answer[{i, j}] = *ops.begin();
                for (const auto &ant : ops)
                    if (diff(ant, base[{i, j}]) < diff(answer[{i, j}], base[{i, j}])) answer[{i, j}] = ant;
            }
        score = submit(answer);
    }

    if (only != -1 && caseNumber != only) {
        if (caseNumber == 1) submit(answer);
        cout << "end" << endl;
        return 0;
    }

    mt19937_64 rnd(seed[caseNumber]);

    while (nT) {
        int i = rnd() % nBS + 1;
        while (mods[i].empty()) i = rnd() % nBS + 1;
        int jCnt = rnd() % mods[i].size();
        auto jp = mods[i].begin();
        while (jCnt--) jp++;
        int j = jp->first;
        if (mods[i][j].size() == 1) continue;

        vector<int> ids;
        for (int k = 0; k < (int)mods[i][j].size(); k++) ids.push_back(k);
        sort(ids.begin(), ids.end(),
             [&](int x, int y) { return diff(mods[i][j][x], answer[{i, j}]) < diff(mods[i][j][y], answer[{i, j}]); });

        auto ans = answer;
        ans[{i, j}] = mods[i][j][ids[rnd() % min(3, (int)mods[i][j].size() - 1) + 1]];

        double sc = submit(ans);
        if (sc >= score) answer = ans, score = sc;
    }

    cout << "end" << endl;

    return 0;
}
