# include<stdio.h>
# include<set>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long LL;
multiset<int> s;

int n,d,m;
int x[maxn<<1],cnt=0;

struct Gas{
    int x,p;
    Gas(){}
}gas[maxn];

bool cmp(Gas A,Gas B){
    return A.x<B.x;
}

int main(){
    scanf("%d%d%d",&d,&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&gas[i].x,&gas[i].p);
    }
    m++;gas[m].x=0;gas[m].p=0;
    sort(gas+1,gas+m+1,cmp);

    for(int i=1;i<m;i++){
        if(gas[i+1].x-gas[i].x>n) {puts("-1");return 0;}
    }
    if(d-gas[m].x>n) {puts("-1");return 0;}

    //for(int i=1;i<=m;i++) printf("x:%d price:%d\n",gas[i].x,gas[i].p);

    x[cnt++]=d;
    for(int i=1;i<=m;i++){
        x[cnt++]=gas[i].x;if(gas[i].x+n<d) x[cnt++]=gas[i].x+n;
    }
    sort(x,x+cnt);
    int nn=cnt;cnt=1;
    for(int i=1;i<nn;i++){
        if(x[i]!=x[i-1]) x[cnt++]=x[i];
    }

    int L=m+1,R=m;
    LL ans=0;
    for(int i=cnt-2;i>=0;i--){
        //printf("%d to %d\n",x[i],x[i+1]);
        while(L>1&&gas[L-1].x+n>=x[i+1]) L--,s.insert(gas[L].p);
        while(R>L&&gas[R].x>x[i]) s.erase(s.find(gas[R].p)),R--;
        //printf("L:%d R:%d\n",L,R);
        if(L>R) {puts("-1");return 0;}
        ans+=(LL)(x[i+1]-x[i])*(*s.begin());
    }

    printf("%I64d\n",ans);
    return 0;
}
