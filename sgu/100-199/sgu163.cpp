# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int n,m;
int num[20];
int main(){
    scanf("%d%d",&n,&m);
    int ans=0;
    for(int i=-3;i<=3;i++){
        num[i+3]=pow(i,m);
    }
    int x;
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
       if(num[x+3]>=0) ans+=num[x+3];
    }
    printf("%d\n",ans);

    return 0;
}
