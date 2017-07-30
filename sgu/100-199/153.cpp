# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int m;
int tcase,n;
int p[20];
int d[20];
int to[600];
int S[1000],top;
int loop[1010],len=0;
bool vis[1010];

void print(bool win){
    if(win) puts("FIRST PLAYER MUST WIN");
    else puts("SECOND PLAYER MUST WIN");
}

void aprint(int x,int cur){
    if(cur==10) return;
    aprint(x>>1,cur+1);printf("%d",x&1);
    if(cur==1) puts("");
}
int main(){
    //freopen("input.txt","r",stdin);
    int st,j;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&m);//n++;
        for(int i=1;i<=m;i++)
            scanf("%d",&p[i]);
        p[++m]=1;
        d[0]=1;
        for(int i=1;i<=8;i++){
            d[i]=0;
            for(int j=1;j<=m;j++)
                if(i-p[j]>=0&&d[i-p[j]]==0) d[i]=1;
        }
        if(n<=8) {print(d[n]);continue;}
        else n-=8;
        st=0;
        for(int i=0;i<=8;i++)
            st=(st<<1)+d[i];
        for(int i=0;i<512;i++){
            j=i;j=i&(255);j<<=1;
            for(int k=1;k<=m;k++)
                if(!((i>>(p[k]-1))&1)) j|=1;
            to[i]=j;
        }
        int now=0;
        memset(vis,false,sizeof(vis));
        int x=st;
        S[top=0]=st;vis[x]=1;//aprint(x,1);
        while(now<n){
            x=to[x];now++;//aprint(x,1);
            if(vis[x]){
                len=0;
                while(S[top]!=x){
                    len++;top--;
                }
                len++;
               // printf("now:%d len:%d\n",now,len);
                break;
            }
            vis[x]=1;
            S[++top]=x;
        }
        if(now==n) print(x&1);
        else{
            now=now+(n-now)/len*len;
            while(now<n)
                x=to[x],now++;
            print(x&1);
        }
    }
    return 0;
}
