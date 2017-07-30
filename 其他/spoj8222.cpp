# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=250010;

struct State{
    int val,right;
    State *par,*go[26];
    State(){
    }
};
State *root,*last;
State seq[maxn*2];int seq_cnt=0;
State *New(int _val){
    State *o=&seq[seq_cnt++];o->right=0;
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
char s[maxn];
int n;
State *b[maxn<<1];
int cnt[maxn];
int dp[maxn];

int main(){
    root=New(0);last=root;
    scanf("%s",s);n=strlen(s);
    for(int i=0;i<n;i++)
        extend(s[i]-'a');

    for(int i=0;i<seq_cnt;i++)
        cnt[seq[i].val]++;
    for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
    State *now=root;
    for(int i=0;i<n;i++){
        now=now->go[s[i]-'a'];now->right++;
    }
    for(int i=0;i<seq_cnt;i++){
        b[--cnt[seq[i].val]]=&seq[i];
    }
    //puts("fuck");

    memset(dp,0,sizeof(dp));
    for(int i=seq_cnt-1;i>=0;i--){
            //printf("i:%d val:%d right:%d\n",i,b[i]->val,b[i]->right);
        dp[b[i]->val]=max(dp[b[i]->val],b[i]->right);
        if(b[i]->par!=0) b[i]->par->right+=b[i]->right;
    }
    //puts("fuck");
    for(int i=n-1;i>=1;i--) dp[i]=max(dp[i],dp[i+1]);
    for(int i=1;i<=n;i++)
        printf("%d\n",dp[i]);
    return 0;
}
