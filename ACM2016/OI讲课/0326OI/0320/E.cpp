# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int a[maxn];
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int ans=10000000;
    for(int i=1;i<n+1-i;i++){
        if(a[i]+a[n+1-i]<ans) ans=a[i]+a[n+1-i];
    }
    printf("%d\n",ans);
    return 0;
}
