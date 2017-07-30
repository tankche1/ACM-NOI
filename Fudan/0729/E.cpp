# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=500010;
const int INF=maxn-5;
struct point{
    int x,y,z;
    point() {}
};
point p[maxn],c[maxn];
int n,m,IQ;
int val[maxn];
int ti[maxn];//i贡献的逆序队最小被去掉的时间
LL f[maxn];//i次操作被减去的逆序队数目

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree1{
    int C[maxn<<1];
    void init(){memset(C,0,sizeof(C));}

    void add(int x,int v){
        while(x<=IQ) C[x]+=v,x+=lowbit(x);
    }

    int sum(int x){
        int res=0;
        while(x>0){
            res+=C[x];x-=lowbit(x);
        }
        return res;
    }
}fwt1;
void cdq(int L,int R){
    if(L==R) return;
    int M=(L+R)>>1;
    cdq(L,M);cdq(M+1,R);
    int pos1=L,pos2=M+1,pos=L;
    int minz=INF;
    for(int tt=1;tt<=R-L+1;tt++){
        if(pos2>R||(pos1<=M&&p[pos1].x>=p[pos2].x)){
            minz=min(minz,p[pos1].z);c[pos++]=p[pos1];pos1++;
        }
        else{
                //printf("minz:%d\n",minz);
            ti[p[pos2].y]=min(ti[p[pos2].y],minz);c[pos++]=p[pos2];pos2++;
        }
    }
    for(int i=L;i<=R;i++)
        p[i]=c[i];
    return;
}
LL ans=0;
int main(){
    int x;
    scanf("%d%d",&n,&m);
    IQ=0;
    for(int i=1;i<=n;i++){
        p[i].y=i;scanf("%d",&p[i].x);p[i].z=INF;IQ=max(IQ,p[i].x);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&x);p[x].z=min(p[x].z,i);
    }
    for(int i=1;i<=n;i++) ti[i]=p[i].z;
    fwt1.init();
    for(int i=n;i>=1;i--){
        val[i]=fwt1.sum(p[i].x-1);
        fwt1.add(p[i].x,1);
        ans+=val[i];
        //printf("val[%d]:%d\n",i,val[i]);
    }

    cdq(1,n);
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)
        f[ti[i]]+=val[i];//,printf("i:%d ti:%d\n",i,ti[i]);
    printf("%I64d\n",ans);
    for(int i=1;i<=m;i++){
        ans-=f[i];
        printf("%I64d\n",ans);
    }
    return 0;
}
