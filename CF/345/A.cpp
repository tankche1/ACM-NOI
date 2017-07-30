# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long LL;

int n;

struct point{
    int x,y;
    point() {}
}p[maxn];

bool cmpx(point a,point b) {
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}

bool cmpy(point a,point b) {
    if(a.y!=b.y) return a.y<b.y;
    return a.x<b.x;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&p[i].x,&p[i].y);
    sort(p+1,p+n+1,cmpx);
    LL ans=0;
    int j;
    for(int i=1;i<=n;i++){
        j=i;
        while(j<n&&p[j+1].x==p[j].x) j++;
        ans+=(LL)(j-i+1)*(j-i)/2;
        i=j;
    }

    for(int i=1;i<=n;i++){
        j=i;
        while(j<n&&p[j+1].x==p[j].x&&p[j+1].y==p[j].y) j++;
        ans-=(LL)(j-i+1)*(j-i)/2;
        i=j;
    }

    sort(p+1,p+n+1,cmpy);
    for(int i=1;i<=n;i++){
        j=i;
        while(j<n&&p[j+1].y==p[j].y) j++;
        ans+=(LL)(j-i+1)*(j-i)/2;
        i=j;
    }
    printf("%I64d\n",ans);
    return 0;
}
