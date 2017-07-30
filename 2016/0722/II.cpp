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
    //freopen("in.txt","r",stdin);
    scanf("%d%d",&W,&H);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&xl[i],&yl[i],&xr[i],&yr[i]);
    }

    int x1,x2;memset(vis,0,sizeof(vis));
    scanf("%d%d",&x1,&x2);vis[x1]=vis[x2]=1;

    int ans1=0;
    for(int i=1;i<=n;i++){
        T[i].L=xl[i];T[i].R=xr[i];T[i].bh=i;
    }

    sort(T+1,T+n+1,cmp);

    int limit=0;

    for(int i=1;i<=n;i++){
        Loop:
        if(T[i].L>limit) {ans1=INF;break;}

        int j=i;
        while(j<n&&T[j+1].L<=limit) j++;
        for(int k=i;k<=j;k++){
            if(vis[T[k].bh]&&T[k].R>limit){
                limit=T[k].R;print1[++ans1]=T[k].bh;vis[T[k].bh]=0;goto Loop;
            }
            else if(vis[T[k].bh]) vis[T[k].bh]=0,print1[++ans1]=T[k].bh;
        }

        int dis=0,pos=-1;

        for(int k=i;k<=j;k++){
            if(T[k].R>dis){
                dis=T[k].R;pos=k;
            }
        }

        limit=dis;print1[++ans1]=T[pos].bh;
        i=j;
    }
    if(limit<W){
        ans1=INF;
    }

    vis[x1]=vis[x2]=1;

    int ans2=0;
    for(int i=1;i<=n;i++){
        T[i].L=yl[i];T[i].R=yr[i];T[i].bh=i;
    }

    sort(T+1,T+n+1,cmp);

    limit=0;

    for(int i=1;i<=n;i++){
        Loop2:
        if(T[i].L>limit) {ans2=INF;break;}

        int j=i;
        while(j<n&&T[j+1].L<=limit) j++;
        for(int k=i;k<=j;k++){
            if(vis[T[k].bh]&&T[k].R>limit){
                limit=T[k].R;print2[++ans2]=T[k].bh;vis[T[k].bh]=0;goto Loop2;
            }
            else if(vis[T[k].bh]) vis[T[k].bh]=0,print2[++ans2]=T[k].bh;
        }

        int dis=0,pos=-1;

        for(int k=i;k<=j;k++){
            if(T[k].R>dis){
                dis=T[k].R;pos=k;
            }
        }

        limit=dis;print2[++ans2]=T[pos].bh;
        i=j;
    }
    if(limit<H){
        ans2=INF;
    }

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
