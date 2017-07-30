# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=110;
const int INF=1010;
int n;
int x[maxn*3],cnt=0;
int left[maxn][maxn][maxn*3];
int f[maxn][maxn*3];

struct Light{
    int pos,l,r;
    Light() {}
}a[maxn];
bool cmp(Light A,Light B){return A.pos<B.pos;}

void get_left(){
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=n+1;j++)
            for(int k=0;k<=cnt+1;k++)
                left[i][j][k]=INF;
    for(int i=1;i<=n;i++){
            left[i][i][a[i].r]=a[i].pos;
            left[i][i][a[i].pos]=a[i].l;
           /* for(int k=a[i].pos;k<=a[i].r;k++)
        left[i][i][k]=a[i].pos;
        for(int k=a[i].l;k<=a[i].pos;k++)
            left[i][i][k]=a[i].l;*/
	}
	for(int l=2;l<=n;l++){
        for(int i=n-l+1;i>=1;i--){
            for(int k=cnt;k>=1;k--){
                //left[i][l][k]=left[i][l][k+1];
                left[i][i+l-1][k]=min(left[i][i+l-1][k],left[i+1][i+l-1][k]);
                if(a[i].pos>=left[i+1][i+l-1][k]) left[i][i+l-1][max(a[i].pos,k)]=min(left[i][i+l-1][max(a[i].pos,k)],min(a[i].l,left[i+1][i+l-1][k]));
                if(a[i].r>=left[i+1][i+l-1][k]) left[i][i+l-1][max(a[i].r,k)]=min(left[i][i+l-1][max(a[i].r,k)],min(a[i].pos,left[i+1][i+l-1][k]));
                //if(left[i][i+l-1][k]!=INF) printf("left[%d][%d][%d]:%d\n",i,i+l-1,k,left[i][i+l-1][k]);
            }
        }
	}
	/*for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
    for(int k=1;k<=cnt;k++){
        if(left[i][j][k]!=INF) printf("left[%d][%d][%d]:%d\n",i,j,k,left[i][j][k]);
    }*/
}

int main(){
	scanf("%d",&n);
	cnt=1;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].pos,&a[i].l),x[cnt++]=a[i].pos-a[i].l,x[cnt++]=a[i].pos+a[i].l,x[cnt++]=a[i].pos;
	sort(x+1,x+cnt);
	cnt=unique(x+1,x+cnt)-x-1;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
        a[i].r=lower_bound(x+1,x+cnt+1,a[i].pos+a[i].l)-x;
        a[i].l=lower_bound(x+1,x+cnt+1,a[i].pos-a[i].l)-x;
        a[i].pos=lower_bound(x+1,x+cnt+1,a[i].pos)-x;
       // printf("i:%d l:%d r:%d pos:%d\n",i,a[i].l,a[i].r,a[i].pos);
	}
    get_left();

    memset(f,0,sizeof(f));
    //f[1][a[1].pos]=x[a[1].pos]-x[a[1].l];
    //f[1][a[1].r]=x[a[1].r]-x[a[1].pos];
    int ans=max(x[a[1].pos]-x[a[1].l],x[a[1].r]-x[a[1].pos]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=cnt;j++){
                f[i][j]=f[i][j-1];
            for(int k=0;k<i;k++)
                for(int t=1;t<=j;t++){
                    if(left[k+1][i][j]<=t){
                        f[i][j]=max(f[i][j],f[k][t]+x[j]-x[t]);
                    }
                }
                //if(f[i][j]>0) printf("f[%d][%d]:%d\n",i,j,f[i][j]);
                ans=max(ans,f[i][j]);
        }
    }
    printf("%d\n",ans);
	return 0;
}
