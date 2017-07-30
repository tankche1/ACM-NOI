# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n,r,w,h;

struct point{
    LL x,y,b1,b2;
}p[maxn];

bool cmp1(point A,point B){
    if(A.b1!=B.b1)
        return A.b1<B.b1;
    return A.b2<B.b2;
}

int dp[maxn];
inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int C[maxn],n;
    void init(int nn) {n=nn;for(int i=0;i<=n;i++) C[i]=0;}

    void insert(int x,int val){
        while(x<=n){
            C[x]=max(C[x],val);x+=lowbit(x);
        }
    }

    int query(int x){
        int res=0;
        while(x>0){
            res=max(res,C[x]);x-=lowbit(x);
        }
        return res;
    }

}fwt;

LL con[maxn];
int cnt=0,_cnt;

int main(){
    scanf("%d%d%d%d",&n,&r,&w,&h);

    for(int i=1;i<=n;i++){
        scanf("%I64d%I64d",&p[i].x,&p[i].y);
        p[i].b1=p[i].y-p[i].x*r;
        p[i].b2=p[i].y+p[i].x*r;
        con[++cnt]=p[i].b2;
    }

    sort(con+1,con+cnt+1);
    _cnt=0;con[++_cnt]=con[1];
    for(int i=2;i<=cnt;i++){
        if(con[i]!=con[i-1]) con[++_cnt]=con[i];
    }
    cnt=_cnt;

    for(int i=1;i<=n;i++) p[i].b2=lower_bound(con+1,con+cnt+1,p[i].b2)-con;

    int ans=0;
    sort(p+1,p+n+1,cmp1);
    fwt.init(cnt+1);
    for(int i=1;i<=n;i++){
        dp[i]=fwt.query((int)p[i].b2)+1;
        fwt.insert((int)p[i].b2,dp[i]);
        ans=max(ans,dp[i]);
    }

    printf("%d\n",ans);
    return 0;
}
