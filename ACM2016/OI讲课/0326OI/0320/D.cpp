# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int a[5],b[5];
int main(){
    scanf("%d%d%d",&a[0],&a[1],&a[2]);
    scanf("%d%d%d",&b[0],&b[1],&b[2]);;
    sort(a,a+3);
    sort(b,b+3);
    if(a[0]*a[0]+a[1]*a[1]!=a[2]*a[2]) {puts("NO");return 0;}
    if(b[0]*b[0]+b[1]*b[1]!=b[2]*b[2]) {puts("NO");return 0;}
    if(a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]) puts("YES");
    else puts("NO");
    return 0;
}
