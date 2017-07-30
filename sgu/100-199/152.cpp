# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
bool can[10010];
int t[10010];
int n,a[10010];
int main(){
    int sum=0,now=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),sum+=a[i];
    for(int i=1;i<=n;i++){
        t[i]=(int)(a[i]*100)/sum;now+=t[i];
        can[i]=(a[i]*100%sum)>0;
    }
    for(int i=1;i<=n;i++){
        if(now<100&&can[i]){
            now++;t[i]++;
        }
    }
    printf("%d",t[1]);
    for(int i=2;i<=n;i++)
        printf(" %d",t[i]);
    puts("");
    return 0;
}
