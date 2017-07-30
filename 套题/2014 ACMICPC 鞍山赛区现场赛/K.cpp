# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=60;
const int mod=(1e+9)+7;
const double eps=1e-9;
double pi=acos(-1.0);
typedef long long LL;

LL fast_pow(int a,int b){
    if(!b) return 1;
    LL half=fast_pow(a,b>>1);
    half=half*half%mod;
    if(b&1) half=half*a%mod;
    return half;
}

LL inv(int x){
    return fast_pow(x,mod-2);
}

struct Point{
    double x,y,ang;
    Point(double x=0,double y=0):x(x),y(y) {}
}p[maxn];

int sgn(double a){
    if(fabs(a)<eps) return 0;
    if(a<0) return -1;
    return 1;
}

double Length(Point A){
    return sqrt(A.x*A.x+A.y*A.y);
}

Point Rotate(Point A,double angle){
    return Point(A.x*cos(angle)-A.y*sin(angle),A.x*sin(angle)+A.y*cos(angle));
}

int n,m,C;
int g[maxn][maxn],link[maxn];
double midx,midy;

int bh[maxn],cnt;

bool cmp(int a,int b){
    if(sgn(p[a].ang-p[b].ang)==0)
        return Length(Point(p[a].x-midx,p[a].y-midy))<Length(Point(p[b].x-midx,p[b].y-midy));
    return p[a].ang<p[b].ang;
}
Point tt;
bool check1(){
    double angle=p[link[bh[0]]].ang-p[bh[0]].ang;
    for(int i=1;i<cnt;i++){
        tt=Rotate(Point(p[bh[i]].x-midx,p[bh[i]].y-midy),angle);tt.x+=midx;tt.y+=midy;
        if(sgn(tt.x-p[link[bh[i]]].x)!=0||sgn(tt.y-p[link[bh[i]]].y)!=0) return false;
    }
    return true;
}

bool check2(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(g[i][j]!=g[link[i]][link[j]]) {
                   // printf("i:%d link[i]:%d j:%d link[j]:%d\n",i,link[i],j,link[j]);
                    return false;
            }
        }
    }
    return true;
}

bool used[maxn];

int calc(){
    memset(used,false,sizeof(used));
    int res=0;
    for(int i=1;i<=n;i++){
        if(used[i]) continue;
        if(!used[i]){
            res++;
            int x=i;used[i]=1;
            while(!used[link[x]]){
                used[link[x]]=1;
                x=link[x];
            }
        }
    }
    return res;
}

int main(){
    int T,a,b;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d%d",&n,&m,&C);
        for(int i=1;i<=n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        memset(g,0,sizeof(g));
        for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);
            g[a][b]=g[b][a]=1;
        }

        midx=0;midy=0;
        for(int i=1;i<=n;i++){
            midx+=p[i].x,midy+=p[i].y;
        }midx=midx/(n*1.0);midy=midy/(n*1.0);

        cnt=0;
        for(int i=1;i<=n;i++){
            if(p[i].x==midx&&p[i].y==midy) {link[i]=i;continue;}
            bh[cnt++]=i;
            p[i].ang=atan2(p[i].y-midy,p[i].x-midx);
        }

        int zhihuan=0;
        LL ans=0;
        sort(bh,bh+cnt,cmp);
        /*for(int i=0;i<cnt;i++){
            printf("x:%.2lf y:%.2lf ang:%.2lf\n",p[bh[i]].x,p[bh[i]].y,p[bh[i]].ang);
        }*/
        for(int i=0;i<cnt;i++){
            for(int j=0;j<cnt;j++){
                link[bh[j]]=bh[(i+j)%cnt];
                //printf("bh[j]:%d - bh:%d\n",bh[j],bh[(i+j)%cnt]);
            }
            /*for(int j=1;j<=n;j++) printf("link[%d]:%d\n",j,link[j]);
            for(int j=1;j<=n;j++){
                printf("x:%.2lf y:%.2lf - xx:%.2lf yy:%.2lf\n",p[j].x,p[j].y,p[link[j]].x,p[link[j]].y);
            }
            puts("");*/
            if(!check1()) continue;
            //puts("hei");
            if(!check2()) continue;
            //puts("fuck");
            zhihuan++;
            ans+=fast_pow(C,calc());
        }
        ans=ans*inv(zhihuan)%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
