# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
char id[3]={'R','G','B'};
int main(){
    srand(time(NULL));
    puts("1");
    int n=rand()%10+1,m=rand()%10+1,ang=rand()%179+1,R=rand()%10+1;
    printf("%d %d %d %d\n",n,m,ang,R);
    printf("%d %d %d %d %d %d\n",rand()%10+1,rand()%10+1,rand()%10+1,rand()%10+1,rand()%10+1,rand()%10+1);
    for(int i=1;i<=n;i++){
        printf("%d %d\n",rand()%10+1,rand()%10+1);
    }
    int t=0;
    for(int i=1;i<=m;i++){
        t=t+rand()%10+1;
        int op=rand()%2+1;
        int ang=rand()%179+1;
        printf("%d %d %d\n",op,t,ang);
    }
    return 0;
}
