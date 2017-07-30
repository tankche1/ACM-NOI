# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
int main(){
    srand(time(NULL));
    int n=rand()%2000+1;
    int k=rand()%500+10;
    printf("%d %d\n",n,k);
    for(int i=1;i<=n;i++){
        printf("%d ",rand()%300+1);
    }puts("");
    return 0;
}
