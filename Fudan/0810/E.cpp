# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n,m;
int a[maxn];
int b[maxn];

/*bool cmp(int a,int b)
{
    return a>b;
}*/

int main(){
    freopen("electricity.in","r",stdin);
    freopen("electricity.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    sort(a+1,a+m+1);
    sort(b+1,b+n+1);
    int as=1,bs=0;
    while((n>0)||(m>0)){
       // printf("as:%d bs:%d n:%d m:%d\n",as,bs,n,m);
        if(m==0) break;
        if(bs>0&&m>0) {as+=a[m],m--,bs--;continue;}
        else if(bs==0&&n>0&&as>0) {as--;bs+=b[n];n--;continue;}
        else break;
    }
    printf("%d\n",as);
    return 0;
}
