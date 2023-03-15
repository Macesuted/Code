#include <bits/stdc++.h>
using namespace std;

int System(string cmd) { return system(cmd.c_str()); }

int main(int argc, char* argv[]) {
    assert(argc == 2);
    string name = argv[1];
    System("g++ " + name + "-gen.cpp -o " + name + "-gen -Ofast");
    System("g++ " + name + ".cpp -o " + name + " -O2");
    System("g++ " + name + "-force.cpp -o " + name + "-force -Ofast");
    for (int i = 1;; i++) {
        System("./" + name + "-gen > " + name + ".in");
        cout << "#########################" << endl;
        cout << "Test #" << i << endl;
        cout << "Solution:" << endl;
        System("time -p ./" + name);
        cout << "Force:" << endl;
        System("time -p ./" + name + "-force < " + name + ".in > " + name + ".ans");
        if (System("check " + name + ".out " + name + ".ans")) {
            cout << "Wrong Answer!" << endl;
            return 0;
        }
        cout << "Accepted!" << endl;
    }
    return 0;
}