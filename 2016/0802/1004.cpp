# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=4010;
typedef long long LL;

struct point{
    LL x,y;
    double ang;
    point() {}
    point(LL _x,LL _y):x(_x),y(_y) {}

}pp[maxn],p[maxn];

point operator - (point A,point B){
    return point(A.x-B.x,A.y-B.y);
}

LL Cross(point A,point B){
    return A.x*B.y-A.y*B.x;
}

LL Dot(point A,point B){
    return A.x*B.x+A.y*B.y;
}

bool cmp(point A,point B){
    return A.ang<B.ang;
}

int n;

int main(){
    int cnt;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%I64d%I64d",&pp[i].x,&pp[i].y);
        }

        LL ans=(LL)n*(n-1)*(n-2)/6,online=0;
        int res;

        for(int t=1;t<=n;t++){
            cnt=0;
            for(int i=1;i<=n;i++){
                if(i==t) continue;
                p[cnt++]=pp[i]-pp[t];
            }

            for(int i=0;i<cnt;i++) p[i].ang=atan2(p[i].y,p[i].x);
            sort(p,p+cnt,cmp);

            for(int i=0;i<cnt;i++) p[i+cnt]=p[i];

            res=0;
            for(int i=1;i<cnt;i++){
                if(Cross(p[i],p[i-1])==0&&Dot(p[i],p[i-1])>0) {
                    res++;
                }
                else res=0;
                online+=res;
            }

            for(int p1=0,p2=0,i=0;i<cnt;i++){
                while(p1<=i||(p1<i+cnt&&Cross(p[i],p[p1])>0&&Dot(p[i],p[p1])>0)) p1++;
                while(p2<=i||(p2<i+cnt&&Cross(p[i],p[p2])>0)) p2++;
                ans-=(p2-p1);
            }
        }
        ans-=online/2;

        printf("%I64d\n",ans);
    }
    return 0;
}
