# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

int main(){
    freopen("input.txt","w",stdout);
    printf("1\n1000000\n");
    for(int i=2;i<=1000000;i++) printf("%d ",i-1);puts("");
    for(int i=1;i<=1000000;i++) printf("%d ",20);puts("");
    printf("1\nQ 1\n");
    return 0;
}
