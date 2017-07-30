# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
//后缀自动机
//SAM
//Suffix Automation

struct State{
    int len,dp;
    int val,way;
    State *par,*go[26];
    State(){
    }
};
State *root,*last;
State seq[maxn*2];int seq_cnt;
State *New(int _len){
    State *o=&seq[seq_cnt++];o->dp=1;o->val=0;o->way=0;
    memset(o->go,0,sizeof(o->go));o->par=0;o->len=_len;
    return o;
}

void extend(int w){
    State *p=last;
    State *np=New(p->len+1);
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

char X;
char s[maxn];
int n;
State* que[maxn<<1];
int head,tail=-1;
State *now;
int cnt[maxn<<1];
State *b[maxn<<1];

int main(){
    int T;
    long long ans;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        ans=0;
        while((X=getchar())&&(X<'a'||X>'z'));
        scanf("%s",s);n=strlen(s);
        init();
        for(int i=0;i<n;i++){
            extend(s[i]-'a');
        }

        for(int i=0;i<=n;i++) cnt[i]=0;
        for(int i=0;i<seq_cnt;i++) cnt[seq[i].len]++;
        for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
        for(int i=0;i<seq_cnt;i++) b[--cnt[seq[i].len]]=&seq[i];
        for(int i=seq_cnt-1;i>=0;i--){
            for(int j=0;j<26;j++){
                if(b[i]->go[j]!=0) b[i]->dp+=b[i]->go[j]->dp;
            }
        }



        /*for(int i=0;i<seq_cnt;i++){
            if(b[i]->val==0){
                if(b[i]->go[X-'a']!=0) if(b[i]->go[X-'a']->val!=-1) b[i]->go[X-'a']->val=1;
            }
            else{
                if(b[i]->go[X-'a']!=0) b[i]->go[X-'a']->val=-1;
            }
        }*/

        b[0]->way=1;
        for(int i=0;i<seq_cnt;i++){
            for(int j=0;j<26;j++){
                if(j==X-'a') continue;
                if(b[i]->go[j]!=0) b[i]->go[j]->way+=b[i]->way;
            }
        }

        for(int i=0;i<seq_cnt;i++){
            if(b[i]->go[X-'a']!=0) ans+=b[i]->way*b[i]->go[X-'a']->dp;
        }

        /*for(int i=0;i<seq_cnt;i++){
            //printf("i:%d go:%d val:%d dp:%d\n",i,seq[i].go[X-'a'],seq[i].val,seq[i].dp);;
            if(seq[i].val==1) ans+=seq[i].way*seq[i].dp;
        }*/


        /*head=0;tail=-1;
        que[++tail]=root;
        while(head<=tail){
            now=que[head];head++;
            if(now->go[X-'a']!=0){
                ans+=now->go[X-'a']->dp;
                //printf("%d\n",now->go[X-'a']->dp);
            }
            for(int i=0;i<26;i++){
                if('a'+i==X) continue;
                if(now->go[i]==0) continue;
                que[++tail]=now->go[i];
            }
        }*/
        printf("Case #%d: ",Tcase);
        printf("%I64d\n",ans);
    }
    return 0;
}
