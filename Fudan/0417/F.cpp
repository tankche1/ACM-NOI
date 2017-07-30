# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000100;
int n,m;
int row[maxn],line[maxn];
int a[maxn];
long long ans[maxn];

inline int pos(int x,int y){
    return (x-1)*m+y;
}

int main(){
    char t;
    scanf("%d%d",&n,&m);
    ans[1]=0;
    for(int i=1;i<=n*m;i++){
        while((t=getchar())&&t!='.'&&t!='+');
        a[i]=(t=='+');
        ans[1]+=(a[i]==0);
    }

    int now=0;
    for(int i=1;i<=n;i++){
        now=0;
        for(int j=1;j<=m;j++){
            if(a[pos(i,j)]==0) now++;
            else{
                if(now) row[now]++,now=0;
            }
        }
        if(now) row[now]++;
    }

    for(int j=1;j<=m;j++){
        now=0;
        for(int i=1;i<=n;i++){
            if(a[pos(i,j)]==0) now++;
            else{
                if(now) line[now]++,now=0;
            }
        }
        if(now) line[now]++;
    }

    int k=max(n,m);
    long long tmp1=0,tmp2=0;
    for(int i=k;i>1;i--){
            //printf("tot[%d]:%d\n",i,line[i]+row[i]);
        tmp1+=(line[i]+row[i])*(i+1);
        tmp2+=(line[i]+row[i]);
        ans[i]=tmp1-tmp2*i;
    }

    for(int i=1;i<=k;i++) {printf("%d",ans[i]);if(i<k) printf(" ");}puts("");
    return 0;
}
