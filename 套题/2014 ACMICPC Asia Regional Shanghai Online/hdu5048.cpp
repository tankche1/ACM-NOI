# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int n,m;
const int maxn=110;
const double eps=1e-12;
double x1[maxn],x2[maxn],yy1[maxn],y2[maxn],z1[maxn],z2[maxn];
double lx[maxn],ly[maxn],lz[maxn],a[maxn],b[maxn],c[maxn];
char type[maxn];
double ans[10];

struct Segment{
    double l,r;
    char col;
    Segment() {}
}seg[maxn];
int cnt;
double p[maxn<<1],px[maxn<<1];
bool cover[maxn<<1][4];

inline int code(char c){
    if(c=='R') return 1;
    else if(c=='G') return 2;
    return 3;
}

int id(bool Red,bool Green,bool Blue){
    if(Red==0&&Green==0&&Blue==0) return 1;
    if(Red==1&&Green==0&&Blue==0) return 2;
    if(Red==0&&Green==1&&Blue==0) return 3;
    if(Red==0&&Green==0&&Blue==1) return 4;
    if(Red==1&&Green==1&&Blue==0) return 5;
    if(Red==1&&Green==0&&Blue==1) return 6;
    if(Red==0&&Green==1&&Blue==1) return 7;
    if(Red==1&&Green==1&&Blue==1) return 8;
}

int main(){
    double two,one,zero;
    double delt;
    double t,t1,t2;
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        for(int i=1;i<=8;i++) ans[i]=0.0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%lf%lf%lf%lf%lf%lf",&x1[i],&yy1[i],&z1[i],&x2[i],&y2[i],&z2[i]);
        }
        for(int i=1;i<=m;i++){
            scanf("%lf%lf%lf%lf%lf%lf",&lx[i],&ly[i],&lz[i],&a[i],&b[i],&c[i]);
            while((type[i]=getchar())&&type[i]!='R'&&type[i]!='G'&&type[i]!='B');
        }

        for(int i=1;i<=n;i++){
            cnt=0;
            for(int j=1;j<=m;j++){
                two=one=zero=0.0;
                two=two+(x1[i]-x2[i])*(x1[i]-x2[i])/(a[j]*a[j]);
                two=two+(yy1[i]-y2[i])*(yy1[i]-y2[i])/(b[j]*b[j]);
                two=two+(z1[i]-z2[i])*(z1[i]-z2[i])/(c[j]*c[j]);

                one=one+2.0*(x1[i]-x2[i])*(x2[i]-lx[j])/(a[j]*a[j]);
                one=one+2.0*(yy1[i]-y2[i])*(y2[i]-ly[j])/(b[j]*b[j]);
                one=one+2.0*(z1[i]-z2[i])*(z2[i]-lz[j])/(c[j]*c[j]);

                zero=zero+(x2[i]-lx[j])*(x2[i]-lx[j])/(a[j]*a[j]);
                zero=zero+(y2[i]-ly[j])*(y2[i]-ly[j])/(b[j]*b[j]);
                zero=zero+(z2[i]-lz[j])*(z2[i]-lz[j])/(c[j]*c[j]);
                zero-=1;

                if(two>0){
                    if(one*one-4*two*zero<=0) continue;
                    delt=sqrt(one*one-4*two*zero);
                    t1=(-one-delt)/(2.0*two);
                    t2=(-one+delt)/(2.0*two);
                    t1=max(t1,0.0);t2=min(t2,1.0);
                    //printf("i:%d j:%d t1:%.3lf t2:%.3lf\n",i,j,t1,t2);

                    if(t1<=t2){
                        cnt++;seg[cnt].l=t1;seg[cnt].r=t2;seg[cnt].col=type[j];
                    }
                    continue;
                }
            }

            t=sqrt((x2[i]-x1[i])*(x2[i]-x1[i])+(y2[i]-yy1[i])*(y2[i]-yy1[i])+(z2[i]-z1[i])*(z2[i]-z1[i]));
            if(cnt==0) {ans[1]+=t;continue;}

            int len=0,ll=0,L,R;
            for(int i=1;i<=cnt;i++){
                p[++len]=seg[i].l;p[++len]=seg[i].r;
            }p[++len]=0.0;p[++len]=1.0;
            sort(p+1,p+len+1);
            px[++ll]=p[1];
            for(int i=2;i<=len;i++){
                if(p[i]-p[i-1]>eps) px[++ll]=p[i];
            }len=ll;
            //for(int i=1;i<=len;i++) printf("px[%d]:%.3lf\n",i,px[i]);
            for(int i=1;i<len;i++) cover[i][3]=cover[i][1]=cover[i][2]=0;
            for(int i=1;i<=cnt;i++){
                L=lower_bound(px+1,px+len+1,seg[i].l-eps)-px;
                R=lower_bound(px+1,px+len+1,seg[i].r-eps)-px;
                for(int k=L;k<R;k++) cover[k][code(seg[i].col)]=1;
            }

            for(int i=1;i<len;i++){
                ans[id(cover[i][1],cover[i][2],cover[i][3])]+=t*(px[i+1]-px[i]);
            }
        }
        for(int i=1;i<=8;i++){
            if(fabs(ans[i])<eps) ans[i]=0;
            printf("%.10lf\n",ans[i]);
        }
    }
    return 0;
}
