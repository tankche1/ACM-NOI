# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int main(){
    freopen("input.txt","w",stdout);
    for(int i=1;i<=10;i++){
    int n=100000;
    printf("%d\n",n);
    for(int i=1;i<n;i++) printf("%d ",i+1);printf("1\n");
}
    return 0;
}
