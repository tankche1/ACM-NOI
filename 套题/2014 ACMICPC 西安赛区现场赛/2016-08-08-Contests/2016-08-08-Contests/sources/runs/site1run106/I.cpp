#include<bits/stdc++.h>
#define rep(i,a,b) for (int i = (a); i <= (b); i++)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll, int> PLI;
const int maxn = 30033, maxt = maxn * 32;

ll A, B;
int trans[maxt][2], tot, n;
bool End[maxt];
vector<PLI> ans;
void read(int &x){
    int ch;
    while (!isdigit(ch = getchar()));
    x = ch - '0';
    while (isdigit(ch = getchar()))
        x = x*10 + ch -'0';
}
int cc[32];
void Buildtrie(){
    memset(End, 0, sizeof(End));
    memset(trans, 0, sizeof(trans));
    tot = 0;
    rep(i, 1, n){
        int p = 0, l;
        rep(j,0,3){
            int tmp;
            read(tmp);
            rep(k, 0, 7){
                if ((1<<(7-k)) & tmp)
                    cc[j * 8 + k] = 1;
                else
                    cc[j * 8 + k] = 0;
            }
        }
        read(l);
        rep(j,0,l-1){
            int k = cc[j];
            if (!trans[p][k]) trans[p][k] = ++tot;
            p = trans[p][k];
        }
        End[p] = 1;
    }
}
void dfs(int u, int l){
    if (End[u]) return;
    if (!u){
        ll now = 0;
        rep(i, 0, 31){
            if (cc[i]){
                now ^= (1ll<<(31-i));
            }
        }
        ans.push_back(PLI(now, l));
        return;
    }
    cc[l] = 1;
    dfs(trans[u][1], l+1);
    cc[l] = 0;
    dfs(trans[u][0], l+1);
}
void Getans(){
    memset(cc, 0, sizeof(cc));
    if (End[0]) return;
    if (trans[0][1] == 0 && trans[0][0] == 0){
        ans.push_back(PLI(0,0));
        return;
    }
    cc[0] = 1;
    dfs(trans[0][1], 1);
    cc[0] = 0;
    dfs(trans[0][0], 1);
}
int main(){
    int T;
    cin>>T;
    rep(TT, 1, T){
        scanf("%d", &n);
        Buildtrie();
        ans.clear();
        Getans();
        printf("Case #%d:\n", TT);
        printf("%d\n", ans.size());
        for (int ss = 0; ss < (int)ans.size(); ss++){
            PLI Ans = ans[ss];
            int tmp[4];
            ll Tmp = Ans.fi;
            rep(i,0,3){
                tmp[i] = Tmp % (1 << 8);
                Tmp >>= 8;
            }
            for (int i = 3; i>=0;i--){
                printf("%d",tmp[i]);
                if (i != 0) printf(".");
                else printf("/%d\n", Ans.se);
            }
        }
    }
    return 0;
}
