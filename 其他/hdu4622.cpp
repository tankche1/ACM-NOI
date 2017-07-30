# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2010;
char s[maxn];

struct State{
    State *par,*go[26];
    int len;//right;
    State(){}
};
State *root,*last;

State seq[maxn<<1];
int seq_cnt=0;

State *New(int _len){
    State *o=&seq[seq_cnt++];
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

struct Query{
    int l,r,bh;
    Query() {}
    bool operator < (const Query &rhs)const{
        return (l==rhs.l)?(r<rhs.r):(l<rhs.l);
    }
}q[maxn*5];
int qnum;

void init(){
    seq_cnt=0;root=New(0);last=root;
}

int cal(){
    int ans=0;
    for(int i=1;i<seq_cnt;i++){
        ans+=seq[i].len-seq[i].par->len;
    }
    return ans;
}

int ans[maxn*5];

int main(){
    int tcase;
    scanf("%d",&tcase);
    int n;
    while(tcase--){
        scanf("%s",s);n=strlen(s);
        scanf("%d",&qnum);
        for(int i=1;i<=qnum;i++)
            scanf("%d%d",&q[i].l,&q[i].r),q[i].l--,q[i].r--,q[i].bh=i;
        sort(q+1,q+qnum+1);
        q[0].l=-1;
        for(int i=1;i<=qnum;i++){
            if(q[i].l!=q[i-1].l){
                init();
                for(int j=q[i].l;j<=q[i].r;j++)
                    extend(s[j]-'a');
            }
            else{
                for(int j=q[i-1].r+1;j<=q[i].r;j++)
                    extend(s[j]-'a');
            }
            ans[q[i].bh]=cal();
        }
        for(int i=1;i<=qnum;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}
