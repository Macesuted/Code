#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::ios;

#define CANNOT_USE_THIS_CARD true
#define CAN_USE_THIS_CARD false
#define THIS_PIG_IS_DEAD true
#define THIS_PIG_IS_NOT_DEAD false
#define THIS_PIG_IS_JUMP true
#define THIS_PIG_IS_NOT_JUMP false
#define THIS_PIG_LIKE_BAD true
#define THIS_PIG_DO_NOT_LIKE_BAD false
#define CROSSBOW_ON true
#define CROSSBOW_DOWN false
#define THIS_TURN_USED_KILL true
#define THIS_TURN_DO_NOT_USE_KILL false

struct card {
    char which;
    bool use;
};

typedef std::vector<card>::iterator myit;

class pig {
private:
    int hp;
    bool use_kill;
    bool crossbow;
    bool jumped;
    bool like_bad;
    void die(int);
    void clear(void);
    void del(myit&);
    myit find(char);
    void cut(void);
    void use(card&);
    void hurt(int);
    bool canuse(char);
    int find_K(void);
    int find_F(void);
    bool K_respond(void);
    bool N_respond(void);
    bool W_respond(void);
    bool ask_J(int);
    bool back_J(int);

public:
    pig(void);
    int num;
    bool dead;
    std::string name;
    std::vector<card> cards;
    void myturn(void);
    void jump(void);
    void K(int);
    void F(int);
    void N(void);
    void W(void);
};

void gameover(std::string);

int n, m;
int FP;
card stack[2005];
pig member[15];
int top = 1;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (register int i = 1; i <= n; i++) {
        cin >> member[i].name;
        member[i].num = i;
        if (member[i].name == "FP")
            FP++;
        for (register int j = 1; j <= 4; j++) {
            card c;
            cin >> c.which;
            c.use = CAN_USE_THIS_CARD;
            member[i].cards.push_back(c);
        }
    }
    for (top = 1; top <= m; top++) {
        card c;
        cin >> c.which;
        c.use = CAN_USE_THIS_CARD;
        stack[top] = c;
    }
    top = 1;
    int point = 0;
    member[1].jump();
    while (true) {
        point = point % n + 1;
        if (member[point].dead == THIS_PIG_IS_DEAD)
            continue;
        member[point].myturn();
    }
}

void gameover(std::string who) {
    cout << who << std::endl;
    for (register int i = 1; i <= n; i++) {
        if (member[i].dead == THIS_PIG_IS_DEAD)
            cout << "DEAD";
        else
            for (myit it = member[i].cards.begin(); it != member[i].cards.end(); it++) {
                if (it->use == CANNOT_USE_THIS_CARD)
                    continue;
                cout << it->which << ' ';
            }
        cout << std::endl;
    }
    exit(0);
}

void pig::die(int who) {
    this->dead = THIS_PIG_IS_DEAD;
    if (this->name == "MP")
        gameover("FP");
    if (this->name == "FP")
        FP--;
    if (FP == 0)
        gameover("MP");
    if (this->name == "FP") {
        member[who].cut();
        member[who].cut();
        member[who].cut();
    }
    if (this->name == "ZP" && member[who].name == "MP")
        member[who].clear();
    return;
}

void pig::clear(void) {
    this->cards.clear();
    this->crossbow = CROSSBOW_DOWN;
    return;
}

void pig::del(myit& it) {
    it->use = CANNOT_USE_THIS_CARD;
    return;
}

myit pig::find(char which) {
    for (myit it = this->cards.begin(); it != this->cards.end(); it++) {
        if (it->use == CANNOT_USE_THIS_CARD)
            continue;
        if (it->which == which)
            return it;
    }
    return this->cards.end();
}

void pig::cut(void) {
    this->cards.push_back(stack[top++]);
    if (top > m)
        top = m;
    return;
}

void pig::use(card& c) {
    if (c.which == 'K') {
        int who;
        who = this->find_K();
        if (who != 0) {
            c.use = CANNOT_USE_THIS_CARD;
            this->K(who);
        }
    } else if (c.which == 'P') {
        if (this->hp < 4) {
            c.use = CANNOT_USE_THIS_CARD;
            this->hp++;
        }
    } else if (c.which == 'F') {
        int who;
        who = this->find_F();
        if (who != 0) {
            c.use = CANNOT_USE_THIS_CARD;
            this->F(who);
        }
    } else if (c.which == 'N') {
        c.use = CANNOT_USE_THIS_CARD;
        this->N();
    } else if (c.which == 'W') {
        c.use = CANNOT_USE_THIS_CARD;
        this->W();
    } else if (c.which == 'Z') {
        c.use = CANNOT_USE_THIS_CARD;
        this->crossbow = CROSSBOW_ON;
    }
    return;
}

void pig::hurt(int who) {
    this->hp--;
    if (this->hp == 0) {
        myit t = this->find('P');
        if (t == this->cards.end())
            this->die(who);
        else {
            this->del(t);
            this->hp++;
        }
    }
    return;
}

bool pig::canuse(char c) {
    if (c == 'P' && this->hp < 4)
        return true;
    if ((c == 'K' && this->find_K() != 0) || (c == 'F' && this->find_F() != 0) || c == 'N' || c == 'W' ||
        c == 'Z')
        return true;
    return false;
}

int pig::find_K(void) {
    if (this->use_kill == THIS_TURN_USED_KILL && this->crossbow == CROSSBOW_DOWN)
        return 0;
    if (this->name == "MP")
        for (register int point = this->num % n + 1; point != this->num; point = point % n + 1) {
            if (member[point].dead == THIS_PIG_IS_DEAD)
                continue;
            if (member[point].like_bad == THIS_PIG_LIKE_BAD ||
                (member[point].name == "FP" && member[point].jumped == THIS_PIG_IS_JUMP))
                return point;
            else
                return 0;
        }
    else if (this->name == "ZP")
        for (register int point = this->num % n + 1; point != this->num; point = point % n + 1) {
            if (member[point].dead == THIS_PIG_IS_DEAD)
                continue;
            if (member[point].name == "FP" && member[point].jumped == THIS_PIG_IS_JUMP)
                return point;
            else
                return 0;
        }
    else if (this->name == "FP")
        for (register int point = this->num % n + 1; point != this->num; point = point % n + 1) {
            if (member[point].dead == THIS_PIG_IS_DEAD)
                continue;
            if (member[point].name != "FP" && member[point].jumped == THIS_PIG_IS_JUMP)
                return point;
            else
                return 0;
        }
    return 0;
}

int pig::find_F(void) {
    if (this->name == "MP")
        for (register int point = this->num % n + 1; point != this->num; point = point % n + 1) {
            if (member[point].dead == THIS_PIG_IS_DEAD)
                continue;
            if (member[point].like_bad == THIS_PIG_LIKE_BAD ||
                (member[point].name == "FP" && member[point].jumped == THIS_PIG_IS_JUMP))
                return point;
        }
    else if (this->name == "ZP")
        for (register int point = this->num % n + 1; point != this->num; point = point % n + 1) {
            if (member[point].dead == THIS_PIG_IS_DEAD)
                continue;
            if (member[point].name == "FP" && member[point].jumped == THIS_PIG_IS_JUMP)
                return point;
        }
    else if (this->name == "FP")
        return 1;
    return 0;
}

bool pig::K_respond(void) {
    myit it = this->find('D');
    if (it == this->cards.end())
        return false;
    this->del(it);
    return true;
}

bool pig::N_respond(void) {
    myit it = this->find('K');
    if (it == this->cards.end())
        return false;
    this->del(it);
    return true;
}

bool pig::W_respond(void) {
    myit it = this->find('D');
    if (it == this->cards.end())
        return false;
    this->del(it);
    return true;
}

bool pig::ask_J(int who) {
    bool check = true;
    if (this->jumped == THIS_PIG_IS_NOT_JUMP)
        return false;
    for (register int point = who; point != who || check == true; point = point % n + 1) {
        if (member[point].dead == THIS_PIG_IS_DEAD)
            continue;
        check = false;
        if (this->name != "FP" && member[point].name == "FP")
            continue;
        if (this->name == "FP" && member[point].name != "FP")
            continue;
        myit it = member[point].find('J');
        if (it != member[point].cards.end()) {
            member[point].del(it);
            member[point].jump();
            return !member[point].back_J(this->num);
        }
    }
    return false;
}

bool pig::back_J(int to) {
    for (register int point = this->num % n + 1; point != this->num; point = point % n + 1) {
        if (member[point].dead == THIS_PIG_IS_DEAD)
            continue;
        if (this->name != "FP" && member[point].name == "ZP")
            continue;
        if (this->name == "FP" && member[point].name == "FP")
            continue;
        if (this->name == "ZP" && member[point].name != "FP")
            continue;
        myit it = member[point].find('J');
        if (it != member[point].cards.end()) {
            member[point].del(it);
            member[point].jump();
            return !member[to].ask_J(point);
        }
    }
    return false;
}

pig::pig(void) {
    this->hp = 4;
    this->dead = THIS_PIG_IS_NOT_DEAD;
    this->jumped = THIS_PIG_IS_NOT_JUMP;
    this->crossbow = CROSSBOW_DOWN;
    this->like_bad = THIS_PIG_DO_NOT_LIKE_BAD;
    this->use_kill = THIS_TURN_DO_NOT_USE_KILL;
    return;
}

void pig::myturn(void) {
    this->cut();
    this->cut();
    bool check = true;
    while (check) {
        check = false;
        for (myit it = this->cards.begin(); it != this->cards.end(); it++) {
            if (it->use == CANNOT_USE_THIS_CARD)
                continue;
            if (canuse(it->which) == false)
                continue;
            use(*it);
            if (this->dead == THIS_PIG_IS_DEAD)
                return;
            it = this->cards.begin() - 1;
            check = true;
        }
    }
    member[this->num].use_kill = THIS_TURN_DO_NOT_USE_KILL;
    return;
}

void pig::jump(void) {
    this->jumped = THIS_PIG_IS_JUMP;
    return;
}

void pig::K(int to) {
    if (this->use_kill == THIS_TURN_USED_KILL && this->crossbow == false)
        return;
    this->jump();
    this->like_bad = THIS_PIG_DO_NOT_LIKE_BAD;
    this->use_kill = THIS_TURN_USED_KILL;
    if (member[to].K_respond() == false)
        member[to].hurt(this->num);
    return;
}

void pig::F(int to) {
    this->jump();
    this->like_bad = THIS_PIG_DO_NOT_LIKE_BAD;
    if (member[to].ask_J(this->num) == true)
        return;
    if (this->name == "MP" && member[to].name == "ZP") {
        member[to].hurt(this->num);
        return;
    }
    int who;
    while (true) {
        myit t;
        t = member[to].find('K');
        if (t == member[to].cards.end()) {
            who = 2;
            break;
        } else
            member[to].del(t);
        t = this->find('K');
        if (t == this->cards.end()) {
            who = 1;
            break;
        } else
            this->del(t);
    }
    if (who == 2)
        member[to].hurt(this->num);
    if (who == 1)
        this->hurt(to);
    return;
}

void pig::N(void) {
    for (register int point = this->num % n + 1; point != this->num; point = point % n + 1) {
        if (member[point].dead == THIS_PIG_IS_DEAD)
            continue;
        if (member[point].ask_J(this->num) == true)
            continue;
        if (member[point].N_respond() == false) {
            member[point].hurt(this->num);
            if (member[point].name == "MP" && this->jumped == THIS_PIG_IS_NOT_JUMP) {
                this->like_bad = THIS_PIG_LIKE_BAD;
            }
        }
    }
    return;
}

void pig::W(void) {
    for (register int point = this->num % n + 1; point != this->num; point = point % n + 1) {
        if (member[point].dead == THIS_PIG_IS_DEAD)
            continue;
        if (member[point].ask_J(this->num) == true)
            continue;
        if (member[point].W_respond() == false) {
            member[point].hurt(this->num);
            if (member[point].name == "MP" && this->jumped == THIS_PIG_IS_NOT_JUMP)
                this->like_bad = THIS_PIG_LIKE_BAD;
        }
    }
    return;
}
