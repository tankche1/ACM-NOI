# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int a[maxn];
LL sum=0;
int n,k;

int main(){
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
            printf("Case #%d: ",Tcase);
        scanf("%d%d",&n,&k);
        sum=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];
        if(sum%k!=0) {puts("-1");continue;}
        int want=sum/k;
        int ans=0;

        for(int i=1;i<=n;i++){
            if(a[i]==want) continue;
            if(a[i]<want) ans++,a[i+1]+=a[i];
            else if(a[i]>want) ans++,a[i]-=want,i--;
            //printf("i:%d ans:%d want:%d\n",i,ans,want);
        }
        //printf("Case #%d: ",Tcase);
        printf("%d\n",ans);
    }
    return 0;
}
