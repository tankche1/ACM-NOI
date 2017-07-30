# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
struct Union_set{
    int fa[2],size,sum;
}p[maxn];
int n,m;

int find(int x){
    int root,r;
    if(p[x].fa[1]==-1){
        root=x;
        while(p[root].fa[0]!=root) root=p[root].fa[0];
        r=p[x].fa[0];
        while(x!=root){
            p[x].fa[0]=root;x=r;r=p[r].fa[0];
        }
        return root;
    }
    else{
        root=p[x].fa[1];
        while(p[root].fa[0]!=root) root=p[root].fa[0];
        p[x].fa[1]=root;
        return root;
    }
}

int main(){
    int op,x,y;
    int px,py;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++) p[i].fa[0]=i,p[i].fa[1]=-1,p[i].size=1,p[i].sum=i;
        for(int tt=1;tt<=m;tt++){
            scanf("%d",&op);
            if(op==1){
                scanf("%d%d",&x,&y);
                px=find(x);py=find(y);
                if(px==py) continue;
                p[px].fa[0]=py;p[py].size+=p[px].size;p[py].sum+=p[px].sum;
            }
            else if(op==2){
                scanf("%d%d",&x,&y);
                px=find(x);py=find(y);
                if(px==py) continue;
                p[px].size--;p[px].sum-=x;
                p[x].fa[1]=py;
                p[py].size++;p[py].sum+=x;
            }
            else{
                scanf("%d",&x);
                px=find(x);
                printf("%d %d\n",p[px].size,p[px].sum);
            }
        }
    }
	return 0;
}
