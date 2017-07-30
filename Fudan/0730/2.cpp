# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;

const int maxn=1000007;
int a[maxn],ch[maxn];
int n;

inline int gcd(int a,int b){
    if(a==0) return b;return gcd(b%a,a);
}

pair<int,int> sh[maxn];

int main()
{
    //freopen("2.in","r",stdin);
    //freopen("2.out","")
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        int ans=0,now=1,t;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=2;i<=n;i++)
            ch[i]=a[i]-a[i-1];
        for(int i=2;i<=n;i++){
            ans=max(ans,now);
            if(i==2||ch[i]==ch[i-1]) now++;
            else now=2;
        }ans=max(ans,now);
        for(int i=2;i<=n;i++){
            t=gcd(a[i],a[i-1]);
            sh[i].first=a[i]/t;
            sh[i].second=a[i-1]/t;
        }
        now=1;
        for(int i=2;i<=n;i++){
            ans=max(ans,now);
            if(i==2||sh[i]==sh[i-1]) now++;
            else now=2;
        }ans=max(ans,now);
        printf("%d\n",ans);
    }
}
