/**
 * @file 7483.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-03
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

typedef tuple<uint32_t, int, int> tuii;

class Cube {
   private:
    uint16_t link[6][3][3];

    void lin(int x, int y, int z, bool w, int val) {
        int ty = y + (w == 1), tz = z + (w == 0);
        link[x][y][z] = link[x][ty][tz] = val;
        return;
    }

   public:
    uint16_t face[6][3][3];

    Cube() {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++) face[i][j][k] = i, link[i][j][k] = 0;

        lin(0, 0, 0, 0, 1);
        lin(0, 1, 0, 1, 2);
        lin(0, 1, 1, 1, 3);
        lin(0, 1, 2, 1, 4);

        lin(1, 0, 1, 0, 5);
        lin(1, 1, 0, 1, 6);
        lin(1, 1, 1, 0, 7);
        lin(1, 2, 1, 0, 8);

        lin(2, 0, 1, 0, 9);
        lin(2, 1, 1, 0, 10);
        lin(2, 2, 1, 0, 11);

        lin(3, 1, 1, 1, 12);
        lin(3, 1, 2, 1, 13);

        lin(4, 1, 0, 0, 14);
        lin(4, 1, 2, 1, 15);
        lin(4, 2, 0, 0, 16);

        lin(5, 0, 0, 0, 17);
        lin(5, 0, 2, 1, 18);
        lin(5, 1, 0, 0, 19);
        lin(5, 2, 0, 0, 20);
    }

    bool rotate(int f) {
        uint32_t vis = 0;

#define add(x, y, z) (vis ^= (uint32_t)1 << link[x][y][z])
#define addR(x, y) add(x, y, 0), add(x, y, 1), add(x, y, 2)
#define addC(x, z) add(x, 0, z), add(x, 1, z), add(x, 2, z)
#define swap(a, b, c, d) (tie(a, b, c, d) = make_tuple(b, c, d, a))
#define rotateFace(x)                                                     \
    swap(face[x][0][0], face[x][0][2], face[x][2][2], face[x][2][0]),     \
        swap(face[x][0][1], face[x][1][2], face[x][2][1], face[x][1][0]), \
        swap(link[x][0][0], link[x][0][2], link[x][2][2], link[x][2][0]), \
        swap(link[x][0][1], link[x][1][2], link[x][2][1], link[x][1][0]);

        if (f == 0) {
            addR(5, 2), addC(1, 0), addR(4, 0), addC(3, 2);
            if (vis) return false;
            rotateFace(f);
            swap(face[5][2][0], face[1][0][0], face[4][0][2], face[3][2][2]);
            swap(face[5][2][1], face[1][1][0], face[4][0][1], face[3][1][2]);
            swap(face[5][2][2], face[1][2][0], face[4][0][0], face[3][0][2]);
            swap(link[5][2][0], link[1][0][0], link[4][0][2], link[3][2][2]);
            swap(link[5][2][1], link[1][1][0], link[4][0][1], link[3][1][2]);
            swap(link[5][2][2], link[1][2][0], link[4][0][0], link[3][0][2]);
            return true;
        }
        if (f == 1) {
            addC(5, 2), addC(2, 0), addC(4, 2), addC(0, 2);
            if (vis) return false;
            rotateFace(f);
            swap(face[5][2][2], face[2][0][0], face[4][2][2], face[0][2][2]);
            swap(face[5][1][2], face[2][1][0], face[4][1][2], face[0][1][2]);
            swap(face[5][0][2], face[2][2][0], face[4][0][2], face[0][0][2]);
            swap(link[5][2][2], link[2][0][0], link[4][2][2], link[0][2][2]);
            swap(link[5][1][2], link[2][1][0], link[4][1][2], link[0][1][2]);
            swap(link[5][0][2], link[2][2][0], link[4][0][2], link[0][0][2]);
            return true;
        }
        if (f == 2) {
            addR(5, 0), addC(3, 0), addR(4, 2), addC(1, 2);
            if (vis) return false;
            rotateFace(f);
            swap(face[5][0][2], face[3][0][0], face[4][2][0], face[1][2][2]);
            swap(face[5][0][1], face[3][1][0], face[4][2][1], face[1][1][2]);
            swap(face[5][0][0], face[3][2][0], face[4][2][2], face[1][0][2]);
            swap(link[5][0][2], link[3][0][0], link[4][2][0], link[1][2][2]);
            swap(link[5][0][1], link[3][1][0], link[4][2][1], link[1][1][2]);
            swap(link[5][0][0], link[3][2][0], link[4][2][2], link[1][0][2]);
            return true;
        }
        if (f == 3) {
            addC(5, 0), addC(0, 0), addC(4, 0), addC(2, 2);
            if (vis) return false;
            rotateFace(f);
            swap(face[5][0][0], face[0][0][0], face[4][0][0], face[2][2][2]);
            swap(face[5][1][0], face[0][1][0], face[4][1][0], face[2][1][2]);
            swap(face[5][2][0], face[0][2][0], face[4][2][0], face[2][0][2]);
            swap(link[5][0][0], link[0][0][0], link[4][0][0], link[2][2][2]);
            swap(link[5][1][0], link[0][1][0], link[4][1][0], link[2][1][2]);
            swap(link[5][2][0], link[0][2][0], link[4][2][0], link[2][0][2]);
            return true;
        }
        if (f == 4) {
            addR(0, 2), addR(1, 2), addR(2, 2), addR(3, 2);
            if (vis) return false;
            rotateFace(f);
            swap(face[0][2][0], face[1][2][0], face[2][2][0], face[3][2][0]);
            swap(face[0][2][1], face[1][2][1], face[2][2][1], face[3][2][1]);
            swap(face[0][2][2], face[1][2][2], face[2][2][2], face[3][2][2]);
            swap(link[0][2][0], link[1][2][0], link[2][2][0], link[3][2][0]);
            swap(link[0][2][1], link[1][2][1], link[2][2][1], link[3][2][1]);
            swap(link[0][2][2], link[1][2][2], link[2][2][2], link[3][2][2]);
            return true;
        }
        if (f == 5) {
            addR(2, 0), addR(1, 0), addR(0, 0), addR(3, 0);
            if (vis) return false;
            rotateFace(f);
            swap(face[2][0][2], face[1][0][2], face[0][0][2], face[3][0][2]);
            swap(face[2][0][1], face[1][0][1], face[0][0][1], face[3][0][1]);
            swap(face[2][0][0], face[1][0][0], face[0][0][0], face[3][0][0]);
            swap(link[2][0][2], link[1][0][2], link[0][0][2], link[3][0][2]);
            swap(link[2][0][1], link[1][0][1], link[0][0][1], link[3][0][1]);
            swap(link[2][0][0], link[1][0][0], link[0][0][0], link[3][0][0]);
            return true;
        }
        return false;
    }

    uint32_t code(void) {
        uint32_t val = 0;
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++) val = (val << 3) - val + (uint32_t)face[i][j][k];
        return val;
    }
};

unordered_map<uint32_t, tuii> rec;
queue<tuple<Cube, uint32_t, int>> que;

void solve(void) {
    Cube init;
    uint32_t initv = init.code();
    rec[initv] = {initv, 0, 0};
    que.emplace(init, initv, 0);

    while (!que.empty()) {
        auto [p, pv, dist] = que.front();
        que.pop();

        for (int i = 0; i < 6; i++) {
            Cube q = p;
            if (!q.rotate(i)) continue;
            uint32_t qv = q.code();
            auto it = rec.find(qv);
            if (it == rec.end())
                rec[qv] = {pv, i, dist + 1}, que.emplace(q, qv, dist + 1);
            else if (get<2>(it->second) == dist + 1 && get<1>(it->second) > i)
                it->second = {pv, i, dist + 1};
        }
    }

    int q;
    cin >> q;
    while (q--) {
        Cube x;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) cin >> x.face[5][i][j];
        for (int i = 0; i < 3; i++)
            for (int f = 0; f < 4; f++)
                for (int j = 0; j < 3; j++) cin >> x.face[(f + 3) % 4][i][j];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) cin >> x.face[4][i][j];

        vector<int> ans;
        uint32_t p = x.code();
        while (p != initv) {
            auto it = rec.find(p);
            ans.push_back(get<1>(it->second)), p = get<0>(it->second);
        }
        cout << ans.size() << endl;
        for (auto i : ans) cout << i << ' ';
        cout << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
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