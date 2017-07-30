# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
int a[100010];
int main(){
    srand(time(NULL));
    int Tcase=1;
    printf("%d\n",Tcase);
    while(Tcase--){
        int n=5,q=5;
        printf("%d %d\n",n,q);
        for(int i=2;i<=n;i++){
            printf("%d %d %d\n",rand()%(i-1)+1,i,rand()%10+1);
        }
        for(int i=1;i<=q;i++){
            printf("1 %d\n",rand()%n+1);
        }
    }
    return 0;
}
