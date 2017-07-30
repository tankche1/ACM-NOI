# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;

int main(){
    srand(time(NULL));
    int n=10;
    for(int i=1;i<=n;i++){
        int m=rand()%10000+10;
        for(int j=1;j<=m;j++) printf("%c",'a'+rand()%5);puts("");
    }
    printf("#\n");
    return 0;
}
