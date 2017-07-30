# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1010;
int n;
int c[maxn];

int main(){
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++) scanf("%d",&c[i]);
        double ans=0.5*(c[1]+c[n]);
        double p=0;
        for(int i=2;i<n;i++){
            p+=i*(i-1);
        }
        p=p/(n*1.0)/((n-1)*1.0)/((n-2)*1.0);
        for(int i=2;i<n;i++) ans+=p*c[i];
        printf("%.6lf\n",ans);
    }
    return 0;
}
