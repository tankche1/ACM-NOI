#include<bits/stdc++.h>
using namespace std;
const int maxn=30011;
int n;
void init(){
    scanf("%d",&n);
}
void print(int A,int B){
    int a,b,c,d; a=b=c=d=0;
    for (int i=1;i<=8;++i) if (B>=i && ((A>>(B-i))&1)) a=a*2+1;else a*=2;
    for (int i=9;i<=16;++i) if (B>=i && ((A>>(B-i))&1)) b=b*2+1;else b*=2;
    for (int i=17;i<=24;++i) if (B>=i && ((A>>(B-i))&1)) c=c*2+1;else c*=2;
    for (int i=25;i<=32;++i) if (B>=i && ((A>>(B-i))&1)) d=d*2+1;else d*=2;
    printf("%d.%d.%d.%d/%d\n",a,b,c,d,B);
}
struct Trie{
    struct node{
        node *c[2]; bool x; int dep;
        void clear(){memset(c,0,sizeof(c)); x=0; dep=0;}
    }e[maxn],*root;
    int tot=0;
    node* newnode(int x){e[tot].clear(); e[tot].dep=x; return e+tot++;}
    void clear(){tot=0; root=newnode(0);}
    void ins(string s,int n){
//        cout<<s<<' '<<n<<endl;
        node *p=root;
        for (int i=0;i<n;++i){
            if (p->x) return;
            int x=s[i]-'0';
            if (!p->c[x]) p->c[x]=newnode(p->dep+1);
            p=p->c[x];
        }
        p->x=1;
    }
    void write(){
        static node *q[maxn]; static int X[maxn]; int w=1; q[1]=root; X[1]=0;
        static int ans1[maxn],ans2[maxn],N; N=0;
        for (int i=1;i<=w;++i){
            if (q[i]->x) continue;
            if (!q[i]->c[0]) ans1[++N]=X[i]*2,ans2[N]=q[i]->dep+1;else q[++w]=q[i]->c[0],X[w]=X[i]*2;
            if (!q[i]->c[1]) ans1[++N]=X[i]*2+1,ans2[N]=q[i]->dep+1;else q[++w]=q[i]->c[1],X[w]=X[i]*2+1;
        }
        printf("%d\n",N);
        for (int i=1;i<=N;++i) print(ans1[i],ans2[i]);
    }
}T;
void work(){
    T.clear(); int a,b,c,d,e;
    if (!n){puts("1\n0.0.0.0/0"); return;}
    while (n--){
        scanf("%d.%d.%d.%d/%d",&a,&b,&c,&d,&e);
        string s="";
        for (int i=7;i>=0;--i) if ((a>>i)&1) s+='1';else s+='0';
        for (int i=7;i>=0;--i) if ((b>>i)&1) s+='1';else s+='0';
        for (int i=7;i>=0;--i) if ((c>>i)&1) s+='1';else s+='0';
        for (int i=7;i>=0;--i) if ((d>>i)&1) s+='1';else s+='0';
        T.ins(s,e);
    }
    T.write();
}
int main(){
    int T; scanf("%d",&T);
    for (int t=1;t<=T;++t) init(),printf("Case #%d:\n",t),work();
    return 0;
}
