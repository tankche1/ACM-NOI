# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL N;
LL x;
int main(){
    scanf("%I64d",&N);
    LL two=1;
    for(x=0;x<=N;x++){
        two=two<<1;
        if(two*(x+1)-1>=N) break;
    }
    printf("%I64d\n",x);
    return 0;
}
