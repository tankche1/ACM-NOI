# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=90010;
struct State{
    State *par,*go[26];
    int len,dp;//right;
    State(){}
};
State *root,*last;

State seq[maxn<<1];
int seq_cnt=0;

State *New(int _len){
    State *o=&seq[seq_cnt++];o->dp=1;
    o->len=_len;o->par=0;memset(o->go,0,sizeof(o->go));
    return o;
}

void extend(int w){
    State *np=New(last->len+1);
    State *p=last;
    while(p&&p->go[w]==0) p->go[w]=np,p=p->par;
    if(p==0) np->par=root;
    else{
        State *q=p->go[w];
        if(q->len==p->len+1)
            np->par=q;
        else{
            State *nq=New(p->len+1);
            nq->par=q->par;q->par=nq;np->par=nq;
            memcpy(nq->go,q->go,sizeof(q->go));
            while(p&&p->go[w]==q) p->go[w]=nq,p=p->par;
        }
    }
    last=np;
}

char s[maxn],ans[maxn];
int ansl;
int n;
int tcase,k;
int cnt[maxn];
State *b[maxn<<1];
int main(){
    root=New(0);last=root;root->dp=0;
    scanf("%s",s);n=strlen(s);
    for(int i=0;i<n;i++)
        extend(s[i]-'a');
    for(int i=0;i<seq_cnt;i++) cnt[seq[i].len]++;
    for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
    for(int i=0;i<seq_cnt;i++) b[--cnt[seq[i].len]]=&seq[i];
    for(int i=seq_cnt-1;i>=0;i--){
        for(int j=0;j<26;j++){
            if(b[i]->go[j]!=0) b[i]->dp+=b[i]->go[j]->dp;
        }
    }

    scanf("%d",&tcase);
    State *p;
    while(tcase--){
        scanf("%d",&k);
        ansl=0;p=root;
        while(1){
            k-=(p!=root);
            if(k==0) break;
            for(int i=0;i<26;i++){
                if(p->go[i]==0) continue;
                if(k<=p->go[i]->dp){
                    p=p->go[i];ans[ansl++]='a'+i;break;
                }
                else{
                    k-=p->go[i]->dp;
                }
            }
        }
        ans[ansl]='\0';
        puts(ans);
    }
    return 0;
}
