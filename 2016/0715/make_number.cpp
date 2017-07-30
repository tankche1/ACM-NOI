# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;

int main(){
    srand(time(NULL));
    for(int k=1;k<=10;k++){
    int n=30,m1=10,m2=rand()%10+1;
    printf("%d %d %d\n",n,m1,m2);
    for(int i=1;i<=m1;i++){
        int a=rand()%n+1,b=rand()%n+1;
        if(a>b) swap(a,b);
        printf("%d %d %d\n",a,b,rand()%5+1);
    }
    for(int i=1;i<=m1;i++){
        int a=rand()%n+1,b=rand()%n+1;
        if(a>b) swap(a,b);
        printf("%d %d %d\n",a,b,n-(rand()%5+1)+1);
    }
    }
    return 0;
}
