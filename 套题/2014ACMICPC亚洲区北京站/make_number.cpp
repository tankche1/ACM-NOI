# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
char id[3]={'R','G','B'};
int main(){
    srand(time(NULL));
    puts("1");
    int n=rand()%1000+1,m=rand()%1000+1;
    n=6;
    printf("%d\n",n*n);
    for(int x1=1;x1<=n;x1++)
        for(int y1=1;y1<=n;y1++)
    printf("%d %d\n",x1,y1);
    return 0;
}
