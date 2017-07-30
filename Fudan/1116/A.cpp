# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
const int INF=~0U>>1;
int x[maxn];
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    sort(x+1,x+n+1);
    int l=1,r=n;
    int ans=INF;
    for(int i=1;i+(n-2)/2+1<=n;i++){
        if(x[i+(n-2)/2+1]-x[i]<ans) ans=x[i+(n-2)/2+1]-x[i];
    }
    printf("%d\n",ans);
    return 0;
}
