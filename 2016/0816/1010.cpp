/*#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<map>
#include<set>*/

#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define per(i,a,b) for (int i=(b);i>=(a);i--)
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)x.size())
typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> PII;
//head


struct node{
    node *par,*go[27];
    int val;
    node(int _val):
            par(0),val(_val){
        memset(go,0,sizeof(go));
    }
    node(){}
};
node *root,*last;
node SC[211111];
int tot=0;
node* New(int val){
    node *e = &SC[++tot];
    e->val=val,e->par=0;
    memset(e->go,0,sizeof(e->go));
    return e;
}

void extend(int w){
    node *p = last;
    node *np = New(p->val+1);
    while (p && p->go[w]==0)
        p->go[w] = np,p = p->par;
    if (p==0)
        np->par = root;
    else{
        node *q = p->go[w];
        if (p->val+1==q->val)
            np->par = q;
        else{
            node *nq = New(p->val+1);
            memcpy(nq->go,q->go,sizeof(q->go));
            nq->par = q->par;
            q->par = nq;
            np->par = nq;
            while (p && p->go[w]==q)
                p->go[w] = nq,p = p->par;
        }
    }
    last = np;
}

int n, m;
char S[101111];
void init(){
    tot = 0;
    root = New(0);
    last = root;
    rep(i, 1, n){
        scanf("%s", S + 1);
        int ll = strlen(S + 1);
        for (int j=1;j<=ll;j++)
            extend(S[j]-'a');
        extend(26);
    }
}


int main(){
    int T, Tcase = 0;
    cin>>T;
    while (T--){
        cin>>n>>m;
        init();
        printf("Case #%d:\n", ++Tcase);
        rep(i, 1, m){
            scanf("%s", S + 1);
            int ll = strlen(S + 1);
            node *p = root;
            rep(j, 1, ll){
                int c = S[j] - 'a';
                //while (p && p->go[c] == 0)
                  //  p = p->par;
                if(p->go[c]==0) {p=root;break;}
                if (p != 0) p = p->go[c];
                else p = root;
            }
            if (p == root) printf("0\n");
            else printf("%d\n", p->val - p->par->val);
        }
    }
    return 0;
}
