# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;

int main(){
    int n,x,a;
    while(scanf("%d",&n)!=EOF){
        bool ok=true;
        for(int i=1;i<=n;i++){
            scanf("%d",&x);a=(int)sqrt(x);
            if(a*a!=x) ok=false;
        }
        if(ok) puts("Yes");
        else puts("No");
    }
    return 0;
}
