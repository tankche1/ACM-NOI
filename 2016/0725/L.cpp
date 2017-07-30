# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int w;
LL n;
int h[maxn];
LL x[maxn<<1],y[maxn<<1];

int l[maxn],r[maxn];

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int n,C[maxn<<1];
    void init(int nn,int val){
        n=nn;for(int i=1;i<=n;i++) C[i]=val;
    }

    void insert1(int x,int val){
        while(x<=n){
            C[x]=max(C[x],val);
            x+=lowbit(x);
        }
    }

    void insert2(int x,int val){
        while(x<=n){
            C[x]=min(C[x],val);
            x+=lowbit(x);
        }
    }

    int query1(int x){
        int res=0;
        while(x>0){
            res=max(res,C[x]);x-=lowbit(x);
        }
        return res;
    }

    int query2(int x){
        int res=w+1;
        while(x>0){
            res=min(res,C[x]);x-=lowbit(x);
        }
        return res;
    }
}fwt1,fwt2;

LL sum1[maxn],sum2[maxn];

bool check(LL height){
    int cnt1=0,cnt2=0;

   // printf("height:%I64d\n",height);
    for(int i=1;i<=w;i++){
        x[cnt1++]=height-i;
        x[cnt1++]=h[i]-i;
    }

    for(int i=1;i<=w;i++){
        y[cnt2++]=height+i;
        y[cnt2++]=h[i]+i;
    }

    sort(x,x+cnt1);sort(y,y+cnt2);
    cnt1=unique(x,x+cnt1)-x;
    cnt2=unique(y,y+cnt2)-y;

    fwt1.init(cnt1+1,0);
    fwt1.insert1(cnt1-(lower_bound(x,x+cnt1,h[1]-1)-x+1)+1,1);

    for(int i=2;i<=w;i++){
        l[i]=fwt1.query1(cnt1-(lower_bound(x,x+cnt1,height-i)-x+1)+1);
        fwt1.insert1(cnt1-(lower_bound(x,x+cnt1,h[i]-i)-x+1)+1,i);
    }

    fwt2.init(cnt2+1,w+1);
    fwt2.insert2(cnt2-(lower_bound(y,y+cnt2,h[w]+w)-y+1)+1,w);

    for(int i=w-1;i>=1;i--){
        r[i]=fwt2.query2(cnt2-(lower_bound(y,y+cnt2,height+i)-y+1)+1);
        fwt2.insert2(cnt2-(lower_bound(y,y+cnt2,h[i]+i)-y+1)+1,i);
    }

    LL res;

    for(int i=2;i<w;i++){
        if(l[i]==0||r[i]==w+1) continue;
        l[i]++;r[i]--;

        res=(height-h[i]);
        res+=(LL)(height+i)*(r[i]-i)-(sum2[r[i]]-sum2[i]);
        res+=(LL)(height-i)*(i-l[i])-(sum1[i-1]-sum1[l[i]-1]);
        //printf("i:%d l:%d r:%d res:%I64d\n",i,l[i],r[i],res);
        if(res<=n) return true;
    }

    return false;
}

int main(){
    freopen("landscape.in","r",stdin);
    freopen("landscape.out","w",stdout);
    LL ans=0;
    scanf("%d%I64d",&w,&n);
    for(int i=1;i<=w;i++){
        scanf("%d",&h[i]);ans=max(ans,(LL)h[i]);
    }

    sum1[0]=sum2[0]=0;
    for(int i=1;i<=w;i++) sum1[i]=sum1[i-1]+h[i]-i,sum2[i]=sum2[i-1]+h[i]+i;

    LL L=ans,R=n+ans,M;
    while(L<=R){
        M=(L+R)>>1;
        if(check(M)) L=M+1;
        else R=M-1;
    }

    ans=max(ans,L-1);
    printf("%I64d\n",ans);
    return 0;
}
