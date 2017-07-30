# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
int main(){
    srand(time(NULL));
    int a;
    freopen("input.txt","w",stdout);
    for(int i=1;i<=6666;i++){
        a=rand()%2016+1;
        printf("%d\n",a);
    }
    return 0;
}
