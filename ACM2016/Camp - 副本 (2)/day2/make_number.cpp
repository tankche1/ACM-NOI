# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
int n,k;
int main(){
    freopen("input.txt","w",stdout);
    srand(time(NULL));
    n=500;k=50;
    printf("%d %d\n",n,k);
    for(int i=1;i<=n;i++)
        printf("%d ",i);
    puts("");
    return 0;
}
