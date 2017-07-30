#include <bits/stdc++.h>
#define rep(i,a,b) for (int i = (a); i <= (b); i++)
using namespace std;
typedef vector<int> VI;
const int maxn = 1011;
int a[maxn], b[maxn], n, m;
int pa[maxn];//, pos[maxn];
queue<int>q[maxn];
int main()
{
    //freopen("a.txt","r",stdin);
    int T;
    cin>>T;
    rep(i,0,1000)
        while (!q[i].empty())
            q[i].pop();
    while (T--){
        scanf("%d%d", &n, &m);
        rep(i,1,n)
            scanf("%d", a+i);
        rep(i,1,n)
            scanf("%d", b+i);

        memset(pa, 0, sizeof(pa));
        rep(i,1,n)
            q[a[i]].push(i);
        bool FLAG = 0;
        rep(i,1,n){
            if (q[b[i]].empty()) FLAG = 1;
            else{
                pa[q[b[i]].front()] = i;
                q[b[i]].pop();
            }
        }
        rep(i,1,n){
            if (!q[a[i]].empty()){
                FLAG = 1;
                while (!q[a[i]].empty())
                    q[a[i]].pop();
            }
        }
        /*
        rep(i,1,n)
            printf("%d ", pa[i]);
        cout<<endl;*/

        rep(i,1,m){
            int l, r;
            scanf("%d%d",&l,&r);
            if (FLAG) continue;
            sort(pa+l, pa+r+1);
        }
        rep(i,1,n){
            if (pa[i]){
                if (pa[i] != i) FLAG = 1;
            }
        }
        if (FLAG) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}
