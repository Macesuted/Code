#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

#ifdef MACESUTED

bool mem1;

#endif

class Class {
   private:
   public:
    void Method(void) {}
};

#ifdef MACESUTED

Class _;

bool mem2;

int main() {
    ios::sync_with_stdio(false);
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    _.Method();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}

#endif