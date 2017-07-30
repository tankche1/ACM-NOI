# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
char id[3]={'R','G','B'};
int main(){
    srand(time(NULL));
    printf("1\n");
    int n=rand()%100+1;
    int m=rand()%100+1;
    printf("%d %d\n",n,m);
    int a,b,c,d,e,f,t;
    for(int i=1;i<=n;i++){
        a=rand()%100+1,b=rand()%100+1;c=rand()%100+1;d=rand()%100+1;e=rand()%100+1;f=rand()%100+1;
        printf("%d %d %d %d %d %d\n",a,b,c,d,e,f);
    }
    for(int i=1;i<=m;i++){
        a=rand()%100+1,b=rand()%100+1;c=rand()%100+1;d=rand()%100+1;e=rand()%100+1;f=rand()%100+1;t=rand()%3;
        printf("%d %d %d %d %d %d %c\n",a,b,c,d,e,f,id[t]);
    }
    return 0;
}
