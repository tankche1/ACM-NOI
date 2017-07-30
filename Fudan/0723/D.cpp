# include<stdio.h>
# include<string.h>
# include<math.h>
# include<string>
# include<map>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=200010;
struct point{
    int x,y,z;
    point(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
};
point a[maxn];
int x[maxn];
LL ans[maxn];
int n,m;
bool cmp1(point a,point b){return a.z<b.z;}
bool cmp2(point a,point b){return a.y<b.y;}
int c[maxn];

inline int lowbit(int x){return x&(-x);}
void add(int x,int v){
    while(x<=n) c[x]+=v,x+=lowbit(x);
}

int ask(int x){
    int res=0;
    while(x>0) res+=c[x],x-=lowbit(x);
    return res;
}

void cdq(int L,int R){
    if(L==R) return;
    //printf("L:%d R:%d \n",L,R);
    int M=(L+R)>>1;
    cdq(L,M);cdq(M+1,R);
    sort(a+L,a+M+1,cmp2);sort(a+M+1,a+R+1,cmp2);
    int pos1=L,pos2=M+1;
    for(int tt=1;tt<=R-L+1;tt++){
        if((pos2>R)||(pos1<=M&&a[pos1].y<a[pos2].y)){
            add(a[pos1].x,1);pos1++;
        }
        else{
            //printf("tt:%d plus:%d\n",tt,ask(n)-ask(a[pos2].x));
            ans[a[pos2].z]+=ask(n)-ask(a[pos2].x);
            pos2++;
        }
    }
    for(int tt=L;tt<=M;tt++)
        add(a[tt].x,-1);

    pos1=M,pos2=R;
    for(int tt=1;tt<=R-L+1;tt++){
        if((pos2==M)||(pos1>=L&&a[pos1].y>a[pos2].y)){
            add(a[pos1].x,1);pos1--;
        }
        else{
            ans[a[pos2].z]+=ask(a[pos2].x-1);pos2--;
        }
    }
    for(int tt=L;tt<=M;tt++)
        add(a[tt].x,-1);
    return;
}
int pos[maxn];

int main(){
    //freopen("in.txt","r",stdin);
    memset(c,0,sizeof(c));
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].x);a[i].y=i;a[i].z=-i;pos[a[i].x]=i;
        }
        for(int i=1;i<=m;i++){
            scanf("%d",&x[i]);a[pos[x[i]]].z=m-i+1;
        }
        sort(a+1,a+n+1,cmp1);
        for(int i=1;i<=n;i++) a[i].z=i;
        memset(ans,0,sizeof(ans));
        cdq(1,n);
        sort(a+1,a+n+1,cmp1);
        //for(int i=1;i<=n;i++)
        //    printf("x:%d y:%d z:%d ans:%d\n",a[i].x,a[i].y,a[i].z,ans[i]);
        for(int i=2;i<=n;i++)
            ans[i]+=ans[i-1];
        for(int i=n;i>n-m;i--){
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}
