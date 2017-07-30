# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef unsigned long long LL;
const int maxb=64;
LL two[maxb+5];
LL A,B,len;
LL a[maxb+5];
LL ans1,ans2;

int main(){
    two[0]=1;
    for(int i=1;i<=maxb;i++) two[i]=two[i-1]<<1;
    int tcase,tnum=0;
    scanf("%d",&tcase);
    while(tcase--){
        tnum++;
        scanf("%llu%llu",&A,&B);len=B-A;
        LL now=0;ans1=ans2=0;
        for(int i=1;i<maxb;i++) a[i]=(A>>(i-1))&1;
        for(int i=1;i<maxb;i++){
            //printf("a[%d]:%I64d  ans1:%I64d\n",i,a[i],ans1);
            if(a[i]==1) ans1+=two[i-1];
            else{
                if(now+len>=two[i-1]) ans1+=two[i-1];
            }
            if(a[i])
                now=now+two[i-1];
            //printf("a[%d]:%I64d  ans1:%I64d\n",i,a[i],ans1);
        }
        //printf("ans1:%I64d\n",ans1);
        now=0;
        for(int i=1;i<maxb;i++){
            if(a[i])
                now=now+two[i-1];
            if(a[i]==0){}
            else{
                if(now+len<two[i]) ans2+=two[i-1];
            }

        }
        printf("Case %d: %llu %llu\n",tnum,ans1,ans2);
    }
    return 0;
}
