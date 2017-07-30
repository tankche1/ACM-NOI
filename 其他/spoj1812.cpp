# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=~0U>>1;

struct State{
    State *par,*go[26];
    int len;//right;
    int minl,maxl;
    State(){}
};
State *root,*last;

State seq[maxn<<1];
int seq_cnt=0;

State *New(int _len){
    State *o=&seq[seq_cnt++];
    o->len=_len;o->par=0;memset(o->go,0,sizeof(o->go));o->minl=INF;
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

int str_num,n,m;
char s[maxn];
State *b[maxn<<1];
int cnt[maxn];
int main(){
    //freopen("in.txt","r",stdin);
    root=New(0);last=root;
    //scanf("%d",&str_num);
    scanf("%s",s);n=strlen(s);
    for(int i=0;i<n;i++){
        extend(s[i]-'a');
    }

    for(int i=0;i<seq_cnt;i++) ++cnt[seq[i].len];
    for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
    for(int i=0;i<seq_cnt;i++) b[--cnt[seq[i].len]]=&seq[i];

    State *p;int w,res;
    while(scanf("%s",s)!=EOF){
        m=strlen(s);p=root;res=0;
        for(int i=0;i<seq_cnt;i++) seq[i].maxl=0;
        for(int i=0;i<m;i++){
            w=s[i]-'a';
            if(p->go[w]) p=p->go[w],res++;
            else{
                while(p&&p->go[w]==0) p=p->par;
                if(p==0) p=root,res=0;
                else{
                    res=p->len+1;p=p->go[w];
                }
            }
            p->maxl=max(p->maxl,res);
        }
        for(int i=seq_cnt-1;i>=0;i--){
            if(b[i]->par!=0){
                b[i]->par->maxl=max(b[i]->par->maxl,b[i]->maxl);
            }
            b[i]->maxl=min(b[i]->maxl,b[i]->len);
        }
        for(int i=0;i<seq_cnt;i++){
            b[i]->minl=min(b[i]->minl,b[i]->maxl);
        }
    }
    int ans=0;
    for(int i=0;i<seq_cnt;i++)
        ans=max(ans,b[i]->minl);
    printf("%d\n",ans);
    return 0;
}
