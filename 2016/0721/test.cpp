# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

int main(){
    freopen("1013.out","r",stdin);
    freopen("output.a","w",stdout);
    int T=0,x;
    while(scanf("%d",&x)!=EOF){
        printf("%d:%d\n",++T,x);
    }
    return 0;
}
