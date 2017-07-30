# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL num[100010];
int cnt,n;
int main(){
    freopen("aztec.in","r",stdin);
    freopen("aztec.out","w",stdout);
    num[0]=0;
    for(int i=1;i<=100000;i++){
        num[i]=num[i-1]+i*(2*i-1+1)-(2*i-1);
        if(num[i]>1000000000) {cnt=i;break;}
    }
    scanf("%d",&n);
    for(int i=1;i<=cnt;i++){
        if(num[i]>n){
            printf("%d\n",i-1);break;
        }
    }
    return 0;
}
