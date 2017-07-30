# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=400010;
const int maxm=20*maxn;
const int INF=~0U>>1;
typedef long long LL;

struct Node{
    Node *ch[2];
    int val;
};
Node *null,seq[maxm*2];
Node *_min[maxn],*_max[maxn];
int dped[maxn],dpst[maxn];
int que[maxn];
int seq_cnt=0;

Node *New(int v){
    Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;o->val=v;
}

void Insert1(Node *x,Node *y,int L,int R,int pos,int val){
    int M=(L+R)>>1;
    if(y!=null) x->val=min(y->val,val);
    else x->val=val;
    if(L==R) return;
    if(pos<=M){
        x->ch[1]=y->ch[1];
        if(y->ch[0]==null) x->ch[0]=New(val);
        else x->ch[0]=New(min(val,y->ch[0]->val));
        Insert1(x->ch[0],y->ch[0],L,M,pos,val);
    }
    else{
        x->ch[0]=y->ch[0];
        if(y->ch[1]==null) x->ch[1]=New(val);
        else x->ch[1]=New(min(val,y->ch[1]->val));
        Insert1(x->ch[1],y->ch[1],M+1,R,pos,val);
    }
}

void Insert2(Node *x,Node *y,int L,int R,int pos,int val){
    int M=(L+R)>>1;
    if(y!=null) x->val=max(y->val,val);
    else x->val=val;
    if(L==R) return;
    if(pos<=M){
        x->ch[1]=y->ch[1];
        if(y->ch[0]==null) x->ch[0]=New(val);
        else x->ch[0]=New(max(val,y->ch[0]->val));
        Insert2(x->ch[0],y->ch[0],L,M,pos,val);
    }
    else{
        x->ch[0]=y->ch[0];
        if(y->ch[1]==null) x->ch[1]=New(val);
        else x->ch[1]=New(max(val,y->ch[1]->val));
        Insert2(x->ch[1],y->ch[1],M+1,R,pos,val);
    }
}
int find1,find2;
int ans=0;

void Query1(Node *x,int L,int R,int val){
    int M=(L+R)>>1;
    if(L==R) {find1=L;return;}
    if((x->ch[1]!=null)&&x->ch[1]->val<val) Query1(x->ch[1],M+1,R,val);
    else Query1(x->ch[0],L,M,val);
    return;
}

void Query2(Node *x,int L,int R,int val){
    int M=(L+R)>>1;
    if(L==R) {find2=L;return;}
    if((x->ch[1]!=null)&&x->ch[1]->val>val) Query2(x->ch[1],M+1,R,val);
    else Query2(x->ch[0],L,M,val);
    return;
}

int A[maxn];
int n,m;

int _size[maxn],need[maxn];

void read(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&A[i]),que[i]=INF;//,A[i]++;
    A[0]=0;dped[0]=0;que[0]=0;

    int L,R,M;
    for(int i=1;i<=n;i++){
        L=0,R=i-1,M;
        while(L<=R){
            M=(L+R)>>1;
            if(que[M]<A[i]) L=M+1;
            else R=M-1;
        }
        dped[i]=L-1+1;
        ans=max(ans,dped[i]);
        que[L]=min(que[L],A[i]);
    }

    A[n+1]=0;dpst[n+1]=0;que[0]=maxn;
    for(int i=1;i<=n;i++) que[i]=0;
    for(int i=n;i>=1;i--){
        L=0;R=n-i+1;M;
        while(L<+R){
            M=(L+R)>>1;
            if(que[M]>A[i]) L=M+1;
            else R=M-1;
        }
        dpst[i]=L-1+1;
        que[L]=max(A[i],que[L]);
        //printf("dpst[%d]:%d\n",i,dpst[i]);
    }

    memset(_size,0,sizeof(_size));memset(need,0,sizeof(need));
    for(int i=1;i<=n;i++){
        if(dped[i]+dpst[i]-1==ans) _size[dped[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(dped[i]+dpst[i]-1==ans&&_size[dped[i]]==1) need[i]=1;
    }
}

int main(){
    null=new Node();null->ch[0]=null->ch[1]=null;null->val=0;
    read();

    for(int i=0;i<=n+1;i++) _min[i]=null,_max[i]=null;

    Node *u=New(400010);
    Insert1(u,_min[0],0,n,0,0);
    _min[0]=u;
    for(int i=1;i<=n;i++){
        _min[i]=New(0);
        Insert1(_min[i],_min[i-1],0,n,dped[i],A[i]);
    }

    u=New(0);
    Insert2(u,_max[n+1],0,n,0,n+1);
    _max[n+1]=u;
    for(int i=n;i>=1;i--){
        _max[i]=New(0);
        Insert2(_max[i],_max[i+1],0,n,dpst[i],A[i]);
    }

    int a,b;
    //LL tot=0;

    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        //if(numed[a]+numst[a]-1!=ans) {printf("%d\n",ans);continue;}
        find1=0;Query1(_min[a-1],0,n,b);
        find2=0;Query2(_max[a+1],0,n,b);
        //printf("find1:%d find2:%d\n",find1,find2);
        if(find1+1+find2>=ans) printf("%d\n",find1+1+find2);
        else{
            if(!need[a]) printf("%d\n",ans);
            else printf("%d\n",ans-1);
        }

    }
    return 0;
}
