# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int a[20];
int main(){
    int x,y;
    for(int i=1;i<=16;i++){
        scanf("%d",&a[i]);
        if(a[i]==0) x=(i+3)/4,y=i-(x-1)*4;
    }
    int res=0;
    for(int i=2;i<=16;i++)
        for(int j=1;j<i;j++)
            if(a[j]>a[i]) res++;
    if(((res+15)&1)==((x+y)&1)) puts("YES");
    else puts("NO");
    return 0;
}
