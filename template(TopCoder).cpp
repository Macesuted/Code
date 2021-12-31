#include <bits/stdc++.h>
using namespace std;

#ifdef MACESUTED

bool mem1;

#endif

#define Class CLASS
#define Method METHOD
#define Parameters void
#define Returns int

class Class {
   private:
   public:
    Returns Method(Parameters) {
    }
};

#ifdef MACESUTED

bool mem2;

int main() {
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
    ios::sync_with_stdio(false);

    Class _;
    _.Method();

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}

#endif