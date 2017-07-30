# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=300010;
const int step=18;
typedef long long LL;

struct State{
    int len,right;
    State *par,*go[26];
    State *fa[19];
    State(){
    }
};
State *root,*last;
State seq[maxn*2];int seq_cnt;
State *New(int _len){
    State *o=&seq[seq_cnt++];
    memset(o->go,0,sizeof(o->go));o->par=0;o->len=_len;o->right=0;
    return o;
}

State *pos[maxn];
void extend(int w,int tt){
    State *p=last;
    State *np=New(p->len+1);np->right=1;pos[tt]=np;
    while(p&&p->go[w]==0) p->go[w]=np,p=p->par;
    if(p==0) np->par=root;
    else{
        State *q=p->go[w];
        if(q->len==p->len+1){
            np->par=q;
        }
        else{
            State *nq=New(p->len+1);
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


void init(){
    seq_cnt=0;root=New(0);last=root;
}

int cnt[maxn];
State *b[maxn<<1];
LL ans=0;
int n,nn;
char s[maxn];
char ss[maxn<<1];
int p[maxn<<1];

void prepare(){
    for(int i=0;i<seq_cnt;i++) ++cnt[seq[i].len];
    for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
    for(int i=0;i<seq_cnt;i++) b[--cnt[seq[i].len]]=&seq[i];
    for(int i=seq_cnt-1;i>=0;i--) if(b[i]->par!=0) b[i]->par->right+=b[i]->right;

    for(int i=0;i<seq_cnt;i++) seq[i].fa[0]=seq[i].par;
    for(int j=1;j<=step;j++){
        for(int i=0;i<seq_cnt;i++){
            seq[i].fa[j]=(seq[i].fa[j-1]==0)?0:seq[i].fa[j-1]->fa[j-1];
        }
    }
}


char query[maxn];
void calc(int l,int r){
    if(!(l&1)) l++;
    if(!(r&1)) r--;
    if(l>r) return;
    l=l/2;r=r/2;
    State *p=pos[r];
    for(int i=step;i>=0;i--){
        if(p->fa[i]!=0){
            if(p->fa[i]->len>=(r-l+1)) p=p->fa[i];
        }
    }
    ans=max(ans,(LL)p->right*(r-l+1));
}

void manacher(){
    int mx=0,id=0;
    p[0]=1;
    ss[nn]='\0';//puts(ss);
    for(int i=1;i<nn;i++){
          //  printf("i:%d\n",i);
        if(mx>i) p[i]=min(mx-i,p[id*2-i]);
        else p[i]=0;
        while(i>=p[i]&&i+p[i]<nn&&ss[i+p[i]]==ss[i-p[i]]) {p[i]++;calc(i-p[i]+1,i+p[i]-1);}
        if(i+p[i]>mx) mx=i+p[i]-1,id=i;
        //printf("p[%d]:%d\n",i,p[i]);
    }
}

int main(){
    freopen("in.txt","r",stdin);
    init();
    scanf("%s",s);n=strlen(s);
    for(int i=0;i<n;i++)
        extend(s[i]-'a',i);
    prepare();
    for(int i=0;i<n*2;i++){
        if((i&1)) ss[i]=s[i/2];
        else ss[i]='#';
    }
    ss[n*2]='#';
    nn=n*2+1;
    manacher();
    printf("%I64d\n",ans);
    return 0;
}
