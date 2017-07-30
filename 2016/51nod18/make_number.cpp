# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<time.h>
# include<algorithm>
using namespace std;

int main(){
    srand(time(NULL));
    int n=10000+1;
    int a,b;
    printf("%d\n",n);
    for(int i=1;i<=n;i++){
        a=rand()%10000+1;b=rand()%10000+1;if(a>b) swap(a,b);
        printf("%d %d\n",a,b);
    }
    return 0;
}
