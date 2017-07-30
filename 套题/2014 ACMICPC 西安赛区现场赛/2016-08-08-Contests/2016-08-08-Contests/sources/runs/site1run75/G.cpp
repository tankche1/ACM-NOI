#include<bits/stdc++.h>
using namespace std;
const int maxn=200011;
char s1[maxn],s2[maxn];
void init(){
    scanf("%s%s",s1,s2);
}
struct Pam{
    struct node{
        node *c[26],*f; int t,len;
        void clear(){memset(c,0,sizeof(c)); f=0; t=0;}
    }e[maxn],*root,*last;
    int tot;
    node* newnode(int x){e[tot].clear(); e[tot].len=x; return e+tot++;}
    void clear(){tot=0; root=newnode(0); root->f=newnode(-1); last=root;}
    void ins(char *s,int i){
        int x=s[i]-'a'; node *p=last;
        while (s[i]!=s[i-p->len-1]) p=p->f;
        if (!p->c[x]){
            last=p->c[x]=newnode(p->len+2); node *q=p->f;
            if (q) while (s[i]!=s[i-q->len-1]) q=q->f;
            if (q) last->f=q->c[x];else last->f=e;
        }
        last=p->c[x]; ++last->t;
    }
    void gao(){
        for (int i=tot-1;i>=0;--i) if (e[i].f) e[i].f->t+=e[i].t;
    }
    /*void watch(node *x){
        printf("Id=%d f=%d len=%d t=%d \n",x-e,x->f?x->f-e:-1,x->len,x->t);
        for (int i=0;i<26;++i) if (x->c[i]) printf("c[%c]=%d ",'a'+i,x->c[i]-e);
        putchar('\n');
        for (int i=0;i<26;++i) if (x->c[i]) watch(x->c[i]);
    }
    void watch(){
        watch(root); watch(root->f);
    }*/
}t1,t2;
int gao(){
    static Pam::node *q1[maxn],*q2[maxn]; int w=2; long long ans=0;
    q1[1]=t1.e; q1[2]=t1.e->f; q2[1]=t2.e; q2[2]=t2.e->f;
    for (int i=1;i<=w;++i){
//        if (i>2) cout<<q1[i]->t<<' '<<q2[i]->t<<endl;
        if (i>2) ans+=1LL*q1[i]->t*q2[i]->t;
        for (int x=0;x<26;++x) if (q1[i]->c[x] && q2[i]->c[x]) q1[++w]=q1[i]->c[x],q2[w]=q2[i]->c[x];
    }
    return ans;
}
void work(){
    t1.clear(); t2.clear();
    for (int i=0;s1[i];++i) t1.ins(s1,i); t1.gao(); //t1.watch(); puts("-------------------------");
    for (int i=0;s2[i];++i) t2.ins(s2,i); t2.gao(); //t2.watch(); puts("");
    cout<<gao()<<endl;
}
int main(){
    int T; scanf("%d",&T);
    for (int t=1;t<=T;++t) init(),printf("Case #%d: ",t),work();
    return 0;
}
