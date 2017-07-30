# include<stdio.h>
# include<string.h>
# include<math.h>
# include<math.h>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
const int maxn=1600;
const double pi=acos(-1.0);
const double eps=0.000000001;
int n;
pair<double,int> arrow[maxn<<1];
int cnt=0;

struct point{
    double x,y;
    point(double x=0,double y=0):x(x),y(y) {}
    point operator -(const point &rhs){
        return point(x-rhs.x,y-rhs.y);
    }
};
point p1[maxn],p2[maxn];
point st;

void add(double a,double b){
    a-=eps;b+=eps;
    arrow[cnt++]=mp(a,1);
    arrow[cnt++]=mp(b,-1);
}

int main(){
    double a,b;
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%lf%lf%lf%lf",&p1[i].x,&p1[i].y,&p2[i].x,&p2[i].y);
        }
        scanf("%lf%lf",&st.x,&st.y);
        cnt=0;
        for(int i=1;i<=n;i++){
            p1[i]=p1[i]-st;p2[i]=p2[i]-st;
            a=atan2(p1[i].y,p1[i].x);b=atan2(p2[i].y,p2[i].x);
            if(a>b) swap(a,b);
            if(b-a>pi){
                add(-pi,a);
                add(b,pi);
            }
            else add(a,b);
        }
        sort(arrow,arrow+cnt);
        int ans=0,now=0;
        for(int i=0;i<cnt;i++){
            now+=arrow[i].second;
            ans=max(ans,now);
        }
        printf("%d\n",ans);
    }
    return 0;
}
