# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=250010;
typedef long long LL;
int n,m,K;

struct State{
    State *par,*go[26],*pa;
    int len,right,sub;//right;
    State(){}
};
State *root,*last;
State *pos[maxn];

State seq[maxn<<1];
int seq_cnt=0;

State *New(int _len){
    State *o=&seq[seq_cnt++];o->right=0;o->sub=0;
    o->len=_len;o->par=0;memset(o->go,0,sizeof(o->go));
    return o;
}

void extend(int w,int pp){
    State *np=New(last->len+1);pos[pp]=np;np->right=1;
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

void init(){
    seq_cnt=0;root=New(0);last=root;
}
char s[50010];
int op[maxn];char c[maxn];
State *b[maxn<<1];
int cnt[maxn];
LL print[maxn];

State *find(State *x){
    if(x==x->pa) return x;
    else return x->pa=find(x->pa);
}

int main(){
    while(scanf("%d%d%d",&n,&m,&K)!=EOF){
    init();
    scanf("%s",s);
    for(int i=0;i<n;i++)
        extend(s[i]-'a',0);
    for(int i=1;i<=m;i++){
        scanf("%d",&op[i]);
        if(op[i]==1) {
            while(scanf("%c",&c[i])&&(c[i]<'a'||c[i]>'z'));
            extend(c[i]-'a',i);n++;
            print[i]=-1;
        }
    }
    LL ans=0;
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<seq_cnt;i++) cnt[seq[i].len]++;
    for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
    for(int i=0;i<seq_cnt;i++) b[--cnt[seq[i].len]]=&seq[i];
    for(int i=seq_cnt-1;i>=0;i--){
        if(b[i]->par!=0) b[i]->par->right+=b[i]->right;
        if(b[i]->right>=K){
            if(b[i]->par!=0) ans+=b[i]->len-b[i]->par->len;
        }
    }
    for(int i=0;i<seq_cnt;i++){
        if(b[i]->right>=K) b[i]->pa=b[i];
        else if(b[i]->par!=0) b[i]->pa=b[i]->par->pa;
        else b[i]->pa=0;
    }

    State *px;
    for(int i=m;i>=1;i--){
        if(op[i]==1){
            px=find(pos[i]);px->sub++;
            while(px&&px->right-px->sub<K){
                if(px->par!=0)
                    ans-=px->len-px->par->len,
                    px->par->pa->sub+=px->sub,
                    px->sub=0,px->pa=px->par->pa,
                    px=px->pa;
                else px=px->par;
            }
        }
        else print[i]=ans;
    }
    for(int i=1;i<=m;i++)
        if(print[i]!=-1) printf("%I64d\n",print[i]);
    }
    return 0;
}
