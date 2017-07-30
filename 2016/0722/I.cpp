#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1010;
const int INF=1000100;
int H,W,n;

bool vis[maxn];
int print1[maxn],print2[maxn];

struct tank{
    int L,R,bh;
    tank() {}
}T[maxn];

int xl[maxn],xr[maxn],yl[maxn],yr[maxn];

bool cmp(tank A,tank B){
    return A.L<B.L;
}
int main() {
    freopen("in.txt","r",stdin);
    scanf("%d%d",&W,&H);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&xl[i],&yl[i],&xr[i],&yr[i]);
    }

    int x;memset(vis,0,sizeof(vis));
    while(scanf("%d",&x)!=EOF) vis[x]=1;

    int ans1=0;
    for(int i=1;i<=n;i++){
        T[i].L=xl[i];T[i].R=xr[i];T[i].bh=i;
    }

    sort(T+1,T+n+1,cmp);

    int limit=0,dis=0,pos=-1;
    for(int i=1;i<=n;i++){

        if(T[i].L>limit&&pos==-1) {ans1=INF;break;}
        if(T[i].L>limit){

            limit=dis;print1[++ans1]=T[pos].bh;pos=-1;
            //printf("i:%d bh:%d ans1:%d limit:%d dis:%d pos:%d\n",i,T[i].bh,ans1,limit,dis,pos);
            i--;continue;
        }
        if(vis[T[i].bh]) print1[++ans1]=T[i].bh;
        //printf("i:%d bh:%d ans1:%d limit:%d dis:%d pos:%d\n",i,T[i].bh,ans1,limit,dis,pos);

        if(1){
            if(vis[T[i].bh]){
                if(T[i].R>limit){
                    limit=T[i].R;
                    if(T[i].R>=dis){
                        dis=T[i].R;pos=-1;
                    }
                }
            }
            else{
                if(T[i].R>dis){
                    dis=T[i].R;pos=i;
                }
            }
        }
    }

    if(ans1!=INF&&limit<W&&pos!=-1) print1[++ans1]=T[pos].bh,limit=dis;

    if(limit<W) ans1=INF;


    int ans2=0;
    for(int i=1;i<=n;i++){
        T[i].L=yl[i];T[i].R=yr[i];T[i].bh=i;
    }

    sort(T+1,T+n+1,cmp);

    limit=0,dis=0,pos=-1;
    for(int i=1;i<=n;i++){
        if(T[i].L>limit&&pos==-1) {ans2=INF;break;}
        if(T[i].L>limit){
            limit=dis;print2[++ans2]=T[pos].bh;pos=-1;
            i--;continue;
           //  printf("i:%d bh:%d ans2:%d pos:%d\n",i,T[i].bh,ans2,pos);
        }
        if(vis[T[i].bh]) print2[++ans2]=T[i].bh;
         //printf("i:%d bh:%d ans2:%d pos:%d\n",i,T[i].bh,ans2,pos);

        if(1){
            if(vis[T[i].bh]){
                if(T[i].R>limit){
                    limit=T[i].R;
                    if(T[i].R>=dis){
                        dis=T[i].R;pos=-1;
                    }
                }
            }
            else{
                if(T[i].R>dis){
                    dis=T[i].R;pos=i;
                }
            }
        }
    }

    if(ans2!=INF&&limit<H&&pos!=-1) print2[++ans2]=T[pos].bh,limit=dis;

    if(limit<H) ans2=INF;

    //printf("ans1:%d ans2:%d\n",ans1,ans2);

    if(ans1==INF&&ans2==INF){
        puts("-1");
    }
    else{
        if(ans1<=ans2){
        //puts("hei");
            printf("%d\n",ans1);
            for(int i=1;i<ans1;i++) printf("%d ",print1[i]);printf("%d\n",print1[ans1]);
        }
        else{
            printf("%d\n",ans2);
            for(int i=1;i<ans2;i++) printf("%d ",print2[i]);printf("%d\n",print2[ans2]);
        }
    }
	return 0;
}
