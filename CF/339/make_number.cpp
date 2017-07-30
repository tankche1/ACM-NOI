# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
int main(){
    srand(time(NULL));
    int n=rand()%10000+1;
    int A=rand()%1000000;
    int cf=rand()%100+1;
    int cm=rand()%100+1;
    int m=(rand()%10)*A+rand()%1000000;
    printf("%d %d %d %d %d\n",n,A,cf,cm,m);
    for(int i=1;i<=n;i++){
        printf("%d ",rand()%A+1);
    }puts("");
    return 0;
}
