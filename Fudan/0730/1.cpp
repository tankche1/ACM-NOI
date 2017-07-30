# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int MaxN=100007;

int l,s[MaxN];

int Check(int x)
{
    int i; bool u[10];
    memset(u,false,sizeof(u));
    while(x)
    {
        if(u[x%10]) return 0;
        u[x%10]=true; x/=10;
    }
    return 1;
}

void Init()
{
    int i;
    for(i=1;i<=100000;i++)
        s[i]=s[i-1]+Check(i);
    return;
}

int main(){
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    Init();
    int T,a,b;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&a,&b);
        printf("%d\n",s[b]-s[a-1]);
    }
    return 0;
}
