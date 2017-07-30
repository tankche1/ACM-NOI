# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=250010;
struct State{
    int val;
    State *go[26],*par;
    State() {}
};
State *last,*root;
State seq[maxn<<1];
int seq_cnt=0;

State *New(int _val){
    State *o=&seq[seq_cnt++];
    o->val=_val;o->par=0;memset(o->go,0,sizeof(o->go));
    return o;
}

void extend(int w){
    State *p=last;
    State *np=New(p->val+1);
    while(p&&p->go[w]==0)
        p->go[w]=np,p=p->par;
    if(p==0){
        np->par=root;
    }
    else{
        State *q=p->go[w];
        if(q->val==p->val+1)
            np->par=q;
        else{
            State *nq=New(p->val+1);
            nq->par=q->par;
            q->par=nq;
            np->par=nq;
            memcpy(nq->go,q->go,sizeof(q->go));
            while(p&&p->go[w]==q)
                p->go[w]=nq,p=p->par;
        }
    }
    last=np;
}

char s1[maxn],s2[maxn];
int n1,n2;
int main(){
    root=New(0);last=root;
    scanf("%s%s",s1,s2);
    n1=strlen(s1);n2=strlen(s2);
    for(int i=0;i<n1;i++)
        extend(s1[i]-'a');
    int ans=0,w;
    State *now=root;
    int res=0;
    for(int i=0;i<n2;i++){
        w=s2[i]-'a';
        if(now->go[w]) res++,now=now->go[w];
        else{
            while(now&&now->go[w]==0) now=now->par;
            if(now==0) res=0,now=root;
            else{
                 res=now->val+1,
                now=now->go[w];//res=now->val;
            }
        }
        ans=max(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}
