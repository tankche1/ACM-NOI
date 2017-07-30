# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=20000;
struct State{
    int val;
    State *par,*go[26];
    State(){
    }
};
State *root,*last;
State seq[maxn*2];int seq_cnt;
State *New(int _val){
    State *o=&seq[seq_cnt++];
    memset(o->go,0,sizeof(o->go));o->par=0;o->val=_val;
    return o;
}

void extend(int w){
    State *p=last;
    State *np=New(p->val+1);
    while(p&&p->go[w]==0) p->go[w]=np,p=p->par;
    if(p==0) np->par=root;
    else{
        State *q=p->go[w];
        if(q->val==p->val+1){
            np->par=q;
        }
        else{
            State *nq=New(p->val+1);
            memcpy(nq->go,q->go,sizeof(q->go));
            nq->par=q->par;
            q->par=nq;
            np->par=nq;
            while(p&&p->go[w]==q)
                p->go[w]=nq,p=p->par;
        }
    }
    last=np;
}

int n;
char s[maxn];
int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%s",s);
        n=strlen(s);seq_cnt=0;
        for(int i=n;i<n+n;i++)
            s[i]=s[i-n];
        root=New(0);last=root;
        for(int i=0;i<n+n;i++){
            extend(s[i]-'a');
        }
        State *p=root;
        int len=0;bool ok;
        while(1){
            ok=false;
            for(int j=0;j<26;j++){
                if(p->go[j]==0) continue;
                //printf("%c",'a'+j);
                ok=true;
                p=p->go[j];len++;break;
            }
            if(!ok) break;
        }
        printf("%d\n",2*n-len+1);
    }
    return 0;
}
