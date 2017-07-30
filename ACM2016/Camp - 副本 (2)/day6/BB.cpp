# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
double pi=acos(-1.0);
double eps=1e-13;
struct point{
    int x,y;
    double val;
    int v;
    point() {}
}p[maxn];
int n;

bool cmpy(point A,point B){
    if(A.y==B.y) return A.x>B.y;
    return A.y>B.y;
}
double gy[maxn];
inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int C[maxn];
    void clear(){
        memset(C,0,sizeof(C));
    }

    void add(int x,int v){
        //printf("x:%d v:%lld\n",x,v);
        while(x<=n){
            C[x]+=v;x+=lowbit(x);
        }
    }

    int sum(int x){
        int res=0;
        while(x>0){
            res+=C[x];x-=lowbit(x);
        }
        return res;
    }

}fwt;

LL calc(double k){
    double _cos=cos(k),_sin=sin(k);
    for(int i=1;i<=n;i++){
        gy[i]=_cos*p[i].y-_sin*p[i].x;p[i].val=gy[i];
    }
    sort(gy+1,gy+n+1);
    int len=0;
    for(int i=1;i<=n;i++){
        if(i==1||fabs(gy[i]-gy[i-1])>0) gy[++len]=gy[i];
    }
    //for(int i=1;i<=len;i++) printf("gy[%d]:%.3lf ",i,gy[i]);puts("");
    for(int i=1;i<=n;i++){
        p[i].v=lower_bound(gy+1,gy+len+1,p[i].val)-gy;
    //    printf("p[%d] v:%d ",i,p[i].v);
    }//puts("");

    LL ans=0;
    fwt.clear();
    for(int i=1;i<=n;i++){
        ans+=i-1-fwt.sum(p[i].v-1);
        fwt.add(p[i].v,1);
    }
    //printf("k:%.12lf ans:%lld\n",k,ans);
    return ans;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p[i].x,&p[i].y);
    }
    sort(p+1,p+n+1,cmpy);
    LL tt=(LL)n*(n-1)/2;
    double L=0,R=pi,M,M1;
    for(int i=1;i<=80;i++){
        if(R<L) break;
        M=(L+R)/2.0;
        if(calc(M)<=tt/2) R=M;
        else L=M;
    }
    if(tt%2==0){
        M1=M;
        L=0;R=pi;
        for(int i=1;i<=80;i++){
            if(R<L) break;
            M=(L+R)/2.0;
            if(calc(M)<=tt/2+1) R=M;
            else L=M;
        }
        M=(M1+M)/2.0;
    }
    printf("%.12lf\n",M);
    return 0;
}
