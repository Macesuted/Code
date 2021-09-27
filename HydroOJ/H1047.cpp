/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

vector<string> asks;

class Json {
   private:
    struct Object {
        string type;

        string value;
        vector<Object*> array;
        map<string, Object*> object;
    };
    Object* main;

    Object* analysis(const string& file, int l, int r) {
        Object* object = new Object();
        while (isspace(file[l])) l++;
        while (isspace(file[r])) r--;
        if (file[l] == '"') {
            l++, r--;
            object->type = "String";
            for (register int i = l; i <= r; i++) object->value.push_back(file[i]);
        } else if (file[l] == '{') {
            l++, r--;
            object->type = "Object";
            for (register int i = l; i <= r;) {
                while (file[i] != '"') i++;
                i++;
                string name;
                while (file[i] != '"') name.push_back(file[i++]);
                while (file[i] != ':') i++;
                i++;
                int ql = i, qr = i - 1;
                int cntM = 0, cntL = 0;
                while (qr < r && (file[qr + 1] != ',' || cntM || cntL)) {
                    qr++;
                    if (file[qr] == '[') cntM++;
                    if (file[qr] == ']') cntM--;
                    if (file[qr] == '{') cntL++;
                    if (file[qr] == '}') cntL--;
                }
                object->object[name] = analysis(file, ql, qr);
                i = qr + 2;
                while (i <= r && isspace(file[i])) i++;
            }
        } else if (file[l] == '[') {
            l++, r--;
            object->type = "Array";
            for (register int i = l; i <= r;) {
                while (isspace(file[i])) i++;
                int ql = i, qr = i - 1;
                int cntM = 0, cntL = 0;
                while (qr < r && (file[qr + 1] != ',' || cntM || cntL)) {
                    qr++;
                    if (file[qr] == '[') cntM++;
                    if (file[qr] == ']') cntM--;
                    if (file[qr] == '{') cntL++;
                    if (file[qr] == '}') cntL--;
                }
                object->array.push_back(analysis(file, ql, qr));
                i = qr + 2;
                while (i <= r && isspace(file[i])) i++;
            }
        } else {
            object->type = "Other";
            for (register int i = l; i <= r; i++) object->value.push_back(file[i]);
        }
        return object;
    }

   public:
    inline void analysis(const string& file) { return main = analysis(file, 0, file.size() - 1), void(); }
    inline string query(const string& path) {
        Object* p = main;
        auto cur = path.begin();
        while (true) {
            string name;
            while (cur != path.end() && *cur != '[' && *cur != '.') name.push_back(*(cur++));
            if (name.size()) {
                if (p->object.find(name) == p->object.end()) return "undefined";
                p = p->object[name];
            }
            if (cur == path.end()) break;
            if (*cur == '[') {
                if (p->type != "Array" && p->type != "String") return "undefined";
                int num = 0;
                cur++;
                while (*cur != ']') num = num * 10 + (*cur - '0'), cur++;
                if (p->type == "Array") {
                    if (num >= (int)p->array.size()) return "undefined";
                    p = p->array[num];
                } else {
                    if (num >= (int)p->value.size()) return "undefined";
                    string s;
                    s.push_back(p->value[num]);
                    return '"' + s + '"';
                }
            }
            cur++;
        }
        if (p->type == "Object") return "[Object]";
        if (p->type == "Array") return "[Array]";
        if (p->type == "String") return '"' + p->value + '"';
        return p->value;
    }
} json;

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        asks.push_back(str);
    }
    string file;
    cin >> file;
    json.analysis(file);
    for (auto i : asks) cout << json.query(i) << endl;
    return 0;
}
