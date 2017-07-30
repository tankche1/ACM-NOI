# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=~0U>>1;
int n;
struct point{
    int x,z;
    point(int x=0,int z=0):x(x),z(z) {}
}p[maxn],pa,pb;
struct Segment{//a*z+b
    double a,b;int z;
    Segment(double a=0,double b=0,int z=0):a(a),b(b),z(z) {}
    bool operator < (const Segment &rhs)const{
        return z<rhs.z;
    }
}sx[maxn<<1],sy[maxn<<1];
int xcnt,ycnt;

void get(Segment *s,int &cnt){
    point a,b;
    cnt=0;
    for(int i=1;i<n;i++){
        a=p[i];b=p[i+1];
        if(p[i].z>p[i+1].z) swap(a,b);
        if(a.z==b.z)
            s[++cnt]=Segment(0,-abs(b.x-a.x),a.z);//s[++cnt]=Segment(0,-abs(b.x-a.x),a.z+1);
        else
            s[++cnt]=Segment(-fabs((double)(b.x-a.x)/(b.z-a.z)),0,a.z),
            s[++cnt]=Segment(fabs((double)(b.x-a.x)/(b.z-a.z)),0,b.z);
    }
    sort(s+1,s+cnt+1);
    //for(int i=1;i<=cnt;i++)
    //    printf("a:%.2lf b:%.2lf z:%d\n",s[i].a,s[i].b,s[i].z);
    //puts("");
}

int xx,yy;
double ans=0;
void solve(){
    int posx=1,posy=1,rx,ry;
    sx[xcnt+1].z=INF;sy[ycnt+1].z=INF;
   double xa=0,xb=xx,ya=0,yb=yy;int lastz=0,nowz;
    while((posx<=xcnt)||(posy<=ycnt)){
        nowz=min(sx[posx].z,sy[posy].z);
        ans+=xa*ya/3.0*((nowz-lastz)*(nowz-lastz)*(nowz-lastz));//printf("ans:%.2lf\n",ans);
        ans+=(ya*xb+xa*yb)/2.0*((nowz-lastz)*(nowz-lastz));//printf("ans:%.2lf\n",ans);
        ans+=xb*yb*(nowz-lastz);
        //printf("z:%d lastz:%d xa:%.2lf xb:%.2lf ya:%.2lf yb:%.2lf ans:%.2lf\n",nowz,lastz,xa,xb,ya,yb,ans);
        xb+=xa*(nowz-lastz);yb+=ya*(nowz-lastz);
        lastz=nowz;
        rx=posx-1;ry=posy-1;
        while(rx<xcnt&&sx[rx+1].z==nowz) rx++;
        while(ry<ycnt&&sy[ry+1].z==nowz) ry++;
        for(int i=posx;i<=rx;i++)
            xa+=sx[i].a,xb+=sx[i].b;
        for(int i=posy;i<=ry;i++)
            ya+=sy[i].a,yb+=sy[i].b;
        posx=rx+1;posy=ry+1;
    }
    printf("%.10f\n",ans);
}


int main(){
    freopen("lonely.in","r",stdin);
    freopen("lonely.out","w",stdout);
    int xz=-INF,yz=-INF;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&p[i].x,&p[i].z),xz=max(xz,p[i].z);
    xx=p[n].x-p[1].x;
    get(sx,xcnt);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&p[i].x,&p[i].z),yz=max(yz,p[i].z);
    yy=p[n].x-p[1].x;
    if(xz!=yz){
        puts("Invalid plan");return 0;
    }
    get(sy,ycnt);
    solve();
    return 0;
}
