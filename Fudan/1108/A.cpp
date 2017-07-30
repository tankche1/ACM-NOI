# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
double ans;
int h,w;
int main(){
    freopen("alex.in","r",stdin);
    freopen("alex.out","w",stdout);
    scanf("%d%d",&h,&w);
    if(h<w) swap(h,w);
    if(h>=3*w) ans=w;
    else ans=max(h/3.0,w/2.0);
    printf("%.6lf\n",ans);
    return 0;
}
