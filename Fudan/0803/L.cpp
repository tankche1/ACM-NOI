# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int n;
long long a;
int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d",&n);
        a=0;
        for(int i=1;i<=n;i++)
            a=a*2+1;
        printf("%I64d\n",a);
    }
    return 0;
}
