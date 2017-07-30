# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxl=5010;
const int maxn=310;
const int INF=~0U>>1;
int Len,m,n;
int p[maxn],d[maxn];
int main(){
    scanf("%d%d",&Len,&m);Len=Len*2;
    for(int i=1;i<=m;i++)
        scanf("%d",&p[i]),p[i]*=2;
    scanf("%d",&n);
    d[1]=0;
    for(int i=2;i<=n;i++)
        scanf("%d",&d[i]),d[i]*=2;
    int anslen=0,ansst=0,num=0,L,R,M,tt=0;
    for(int st=0;st+d[n]<=Len;st++){
            //printf("st:%d d[n]:%d L:%d\n",st,d[n],Len);
        num=0;
        for(int i=1;i<=m;i++){
            L=1,R=n;
            while(L<=R){
                M=(L+R)>>1;
                if(d[M]+st<=p[i]) L=M+1;
                else R=M-1;
            }
            tt=INF;
            if(L-1>=1) tt=min(tt,p[i]-d[L-1]-st);
            if(L<=n) tt=min(tt,d[L]+st-p[i]);
            num+=tt;
        }
        //printf("st:%d num:%d\n",st,num);
        if(num>anslen) anslen=num,ansst=st;
    }
    if(ansst%2==0)
        printf("%d ",ansst/2);
    else printf("%d.5 ",ansst/2);
    if(anslen%2==0)
        printf("%d ",anslen/2);
    else printf("%d.5 ",anslen/2);
    return 0;
}
