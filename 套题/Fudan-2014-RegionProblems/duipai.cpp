#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
typedef pair<int,int> pii;

const int maxn = 2000000;
const ll x = 123;

int N, Q, mv;
char op[maxn], s[maxn];
map<ll, pii> G;

inline int idx(char ch) {
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    else if (ch >= 'A' && ch <= 'Z')
        return ch - 'A' + 10;
    else if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 36;
    else if (ch == '.')
        return 62;
    return 63;
}

void solve (ll u) {
    ll tmp = u;

    while (s[mv] != '}') {
        mv++;
        if (s[mv] == '}')
            return;
        u = tmp;

        while (s[mv] != ':')
            u = u * x + idx(s[mv++]);

        int l = ++mv;

        if (s[mv] == '{')
            solve(u * x + 62LL);
        else
            while (s[mv+1] != ',' && s[mv+1] != '}') mv++;

        G[u] = make_pair(l, mv);
        mv++;
    }
}

int main () {
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%s", s);

        mv = 0;
        G.clear();
        solve(0);

        scanf("%d", &Q);
        for (int i = 1; i <= Q; i++) {
            scanf("%s", op);

            ll ret = 0;
            int len = strlen(op);

            for (int i = 0; i < len; i++)
                ret = ret * x + idx(op[i]);

            if (G.count(ret)) {
                pii u = G[ret];
                for (int i = u.first; i <= u.second; i++)
                    printf("%c", s[i]);
                printf("\n");
            } else
                printf("Error!\n");
        }
    }
    return 0;
}
