# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
int main(){
    srand(time(NULL));
    freopen("input.txt","w",stdout);
    int n=100000;
    printf("%d %d\n",n,1000000000000000000);
    int t;
    for(int i=1;i<=n;i++){
        printf("%d %d ",rand()%1000000-500000,rand()%1000000-500000);
        t=rand()%4+1;
        if(t==1) puts("U");
        else if(t==2) puts("D");
        else if(t==3) puts("L");
        else puts("R");
    }
    return 0;
}
