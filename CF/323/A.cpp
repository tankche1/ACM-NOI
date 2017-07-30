# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=505;
int a[maxn*maxn];
int n;
int ans[maxn],now=0;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n*n;i++)
        scanf("%d",&a[i]);
    int len=n*n;
    sort(a+1,a+n*n+1);
    int tmp,res;
    a[0]=-1;
    for(int i=len;i>=1;i--){
        if(a[i]==a[i-1]) continue;
        tmp=0;res=0;
        for(int j=len;j>=i;j--) if(a[j]%a[i]==0) tmp++;
        for(int j=1;j<=now;j++) if(ans[j]%a[i]==0) res++;
        for(int j=1;(j+res)*(j+res)<=tmp;j++){
            ans[++now]=a[i];
        }
    }
    for(int i=1;i<n;i++)
        printf("%d ",ans[i]);
    printf("%d\n",ans[n]);
    return 0;
}
