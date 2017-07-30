# include<stdio.h>
# include<string.h>
# include<math.h>
# include<string>
# include<map>
# include<algorithm>
using namespace std;
int n,m,len;
char s[12][110];
int a[11];
int bh[11];
int nouse=0;

bool cmp(int c,int d){
    if(a[c]==a[d]) return c<d;
    return a[c]>a[d];
}

int main(){
    freopen("bad.in","r",stdin);
    freopen("bad.out","w",stdout);
    char tt;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]);
    }
    int num,pos;memset(a,0,sizeof(a));
    for(int i=1;i<=m;i++){
            num=0;
        for(int j=1;j<=n;j++){
            while((tt=getchar())&&tt!='.'&&tt!='X');
            num+=tt=='X';if(tt=='X') pos=j;
        }
        if(num==0||num>1) nouse++;
        else a[pos]++;
    }
    for(int i=1;i<=n;i++) bh[i]=i;
    sort(bh+1,bh+n+1,cmp);
    double ans;
    for(int i=1;i<=n;i++){
        printf("%s ",s[bh[i]]);ans=(double)a[bh[i]]*100/m;
        printf("%.2lf%%\n",ans);
    }
    ans=(double)nouse*100/m;
    printf("Invalid %.2lf%%",ans);
    return 0;
}
