# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int n,p,k,d,one;
int main(){
    freopen("final.in","r",stdin);
    freopen("final.out","w",stdout);
    scanf("%d%d%d%d",&n,&p,&k,&d);
    if(d==1){
        if(k<n){
            one=p/k;
            for(int i=1;i<=k;i++) printf("%d\n",one);
            printf("%d\n",p-one*k);
            for(int i=1;i<=n-k-1;i++) printf("%d\n",0);
        }
        else{
            if(p%n) printf("Wrong information");
            else{
                one=p/n;
                for(int i=1;i<=n;i++) printf("%d\n",one);
            }
        }
    }
    else{
        if(d==2) one=p;
        else if(d>=3) one=p-(1+d-2)*(d-2)/2;
        if(one<=d-2) printf("Wrong information");
        else{
            printf("%d\n",one);
            for(int i=d-2;i>=1;i--) printf("%d\n",i);
            for(int i=1;i<=n-1-(d-2);i++) printf("%d\n",0);
        }
    }
    return 0;
}
